
#include <ti/sysbios/BIOS.h>
#include <stdio.h>
#include <netmain.h>
#include <_stack.h>
#include <scom.h>
#include <gooao_c6748.h>
#include <xdc/runtime/System.h>
#include <algorithm.h>

typedef enum{
	SENDING,
	STOP_SENDING,
	SEND_ID,
	ERROR
}Tcp_runtime_status;

uint8_t MainConfig[512];
int   MainConfigSize   = 0;
int   MainConfigValid  = 0;
char *LocalIPAddr = 	"192.168.1.100"; 	//"192.168.1.2";	//
char *LocalIPMask = 	"255.255.255.0";
char *GatewayIP = 		"192.168.1.1"; 	//"192.168.1.1";	//
char *ServerIPAddr = 	"192.168.1.10";	//"192.168.1.10";	//
char *HostName = 		"testndk";
char *DomainName = 		"fr.net";

intmax_t tcpsend_count = 0, tcpsend_loop = 0, tcpsend_remainder = 0;
int32_t write_frame = 0;

extern uint8_t frame_avaliable[20];
static HANDLE 	hEchoServer=0;
//=====================================
static void		NetBoot();
// NC Callback Functions
static void		NetworkOpen();
static void		NetworkClose();
static void		NetworkIPAddr( IPN IPAddr, uint IfIdx, uint fAdd );

void tskTcpServer();

int NetworkMain()
{
    HANDLE   hCfg;
    int      rc;
    uint     tmp;

    CI_IPNET NA;
    CI_ROUTE RT;

    //它初始化协议栈及其所需内存环境。它的两个参数Priority和OpMode分别决定调度任务的优先级和调度器何时开始执行，以下采用中断模式。
    rc = NC_SystemOpen( NC_PRIORITY_HIGH, NC_OPMODE_INTERRUPT );
    if( rc )
    {
        printf("NC_SystemOpen Failed (%d)\n",rc);
        for(;;);
    }

    // Create a new configuration
    //创建配置句柄
    hCfg = CfgNew();
    if( !hCfg )
    {
        printf("Unable to open configuration\n");
        goto main_exit;
    }

    // Manually configure our local IP address
    bzero( &NA, sizeof(NA) );
    NA.IPAddr = inet_addr(LocalIPAddr);
    NA.IPMask = inet_addr(LocalIPMask);
    strcpy( NA.Domain, DomainName );
    NA.NetType = 0;
    // Add the address to interface 1
    CfgAddEntry( hCfg, CFGTAG_IPNET, 1, 0, sizeof(CI_IPNET), (UINT8 *)&NA, 0 );

    // Add our hostname
    CfgAddEntry( hCfg, CFGTAG_SYSINFO, CFGITEM_DHCP_HOSTNAME, 0, strlen(HostName), (UINT8 *)HostName, 0 );
    // Add the default gateway. Since it is the default, the
    // destination address and mask are both zero (we go ahead
    // and show the assignment for clarity).
    bzero( &RT, sizeof(RT) );
    RT.IPDestAddr = 0;
    RT.IPDestMask = 0;
    RT.IPGateAddr = inet_addr(GatewayIP);
    // Add the route
    CfgAddEntry( hCfg, CFGTAG_ROUTE, 0, 0, sizeof(CI_ROUTE), (UINT8 *)&RT, 0 );

    // We don't want to see debug messages less than WARNINGS
    tmp = DBG_WARN;
    CfgAddEntry( hCfg, CFGTAG_OS, CFGITEM_OS_DBGPRINTLEVEL,
                 CFG_ADDMODE_UNIQUE, sizeof(uint), (UINT8 *)&tmp, 0 );

    // Save the configuration to a linear buffer
    MainConfigSize = 0;
    CfgSave( hCfg, &MainConfigSize, 0 );
    printf("%d bytes required for save\n",MainConfigSize);
    if( MainConfigSize > sizeof( MainConfig ) )
        printf("FATAL: Config buffer too small\n");
    else
    {
        CfgSave( hCfg, &MainConfigSize, MainConfig );
        CfgFree( hCfg );

        // Now call what would really be the "boot" function
        NetBoot();
    }

    // Close the OS
main_exit:
    NC_SystemClose();
    return(0);
}

//---------------------------------------------------------------------
// Simulated Boot Entry Point
//---------------------------------------------------------------------
static void NetBoot()
{
    HANDLE   hCfg;
    int      rc;

    do
    {
        // Create a new configuration
        hCfg = CfgNew();
        if( !hCfg )
        {
            printf("Unable to open configuration\n");
            break;
        }

        // Load the configuration
        CfgLoad( hCfg, MainConfigSize, MainConfig );

        // Start the stack
        rc = NC_NetStart( hCfg, NetworkOpen, NetworkClose, NetworkIPAddr );

        // Delete Configuration
        CfgFree( hCfg );
    } while( rc > 0 );

}

//
// System Task Code
// NetworkOpen
//
// This function is called after the configuration has booted
//
static void NetworkOpen()
{
    hEchoServer = TaskCreate( tskTcpServer, "tskTcpServer", OS_TASKPRINORM, 0x2000, 0, 0, 0 );
}
//
// NetworkClose
//
// This function is called when the network is shutting down,
// or when it no longer has any IP addresses assigned to it.
//
static void NetworkClose()
{
	fdCloseSession( hEchoServer );
    TaskSetPri( TaskSelf(), NC_PRIORITY_LOW );
    TaskDestroy( hEchoServer );
}

//
// NetworkIPAddr
//
// This function is called whenever an IP address binding is
// added or removed from the system.
//
static void NetworkIPAddr( IPN IPAddr, uint IfIdx, uint fAdd )
{
    IPN IPTmp;

    if( fAdd )
        printf("Network Added: ");
    else
        printf("Network Removed: ");

    // Print a message
    IPTmp = ntohl( IPAddr );
    printf("If-%d:%d.%d.%d.%d\n", IfIdx,
            (UINT8)(IPTmp>>24)&0xFF, (UINT8)(IPTmp>>16)&0xFF,
            (UINT8)(IPTmp>>8)&0xFF, (UINT8)IPTmp&0xFF );
}

void tskTcpServer()
{
	ScomMessage *tcpMsg;
	SCOM_Handle hs_N2Proc, hs_Proc2N;
	SOCKET   stcp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    SOCKET   stcpbusy;
    struct   sockaddr_in sin1;
    struct   timeval timeout;           //	Timeout struct for select
    int32_t      size,tmp,i,cnt;
    HANDLE   hBuffer;
    uint8_t  (*tcprecv_Buf)[10];
    uint8_t testSend[4] = {0xaa, 0xbb, 0xcc, 0xdd};
    Tcp_runtime_status runtime_status = STOP_SENDING;

    uint8_t *ID_Buf = 0;

    hs_N2Proc = SCOM_open("NET2P");
    hs_Proc2N = SCOM_open("P2NET");

    if(!hs_N2Proc || !hs_Proc2N)
    {
        for(;;);
    }
    // Allocate the file environment for this task
    fdOpenSession( TaskSelf() );

    // Create the main TCP listen socket
    stcp = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( stcp == INVALID_SOCKET )
        goto leave;

    // Set Port = 2000, leaving IP address = Any
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family = AF_INET;
    sin1.sin_len    = sizeof( sin1 );
    sin1.sin_port   = htons(2000);

    // Bind socket
    if ( bind( stcp, (PSA) &sin1, sizeof(sin1) ) < 0 )
        goto leave;

    // Start listening
    if ( listen( stcp, 1) < 0 )
        goto leave;

    if( !(ID_Buf = mmAlloc( 10 )) )
        {
        	printf("failed temp buffer allocation\n");
            goto leave;
        }
    *ID_Buf = (uint8_t)1;

    // Configure our timeout to be 300 seconds
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;

    printf("EchoSrv Initialized\n");

    // Run until task is destroyed by the system
    while(1)
    {
        fd_set ibits, obits, xbits;
        int32_t  tmp_sendi;
        // Clear the select flags
        FD_ZERO(&ibits);
        FD_ZERO(&obits);
        FD_ZERO(&xbits);

        // We examine the main TCP, UDP, and active TCP (if any)
        FD_SET(stcp, &ibits);

        // Wait for socket activity
        if( stcpactive == INVALID_SOCKET )
        {
            // Wait without timeout
            tmp = fdSelect( 4, &ibits, &obits, &xbits, NULL);
        }
        else
        {
            // Wait for set timeout - abort active connection on no activity
            FD_SET(stcpactive, &ibits);
            tmp = fdSelect( 4, &ibits, &obits, &xbits, &timeout);
        }
        if( tmp < 0 )
        	goto leave;

        // Check for a new TCP connection
        if( FD_ISSET(stcp, &ibits) )
        {
            // We have a new connection. Assign it so sbusy at
            // first...
            size = sizeof( sin1 );
            stcpbusy = accept( stcp, (PSA)&sin1, &size );

            // If the active socket is free use it, else print out
            // a busy message
            if( stcpactive == INVALID_SOCKET )
                stcpactive = stcpbusy;
            else
                fdClose( stcpbusy );
        }

        tcpMsg = SCOM_getMsg(hs_Proc2N, BIOS_WAIT_FOREVER);
        // Check for new data on active TCP connection
        if( stcpactive != INVALID_SOCKET && FD_ISSET(stcpactive, &ibits) )
        {
        	   cnt = (int32_t)recvnc( stcpactive, (void **)(&tcprecv_Buf), 0, &hBuffer );

        	   switch((*tcprecv_Buf)[0])
				{
					case 0x00:
						runtime_status = SENDING;
						break;
					case 0x01:
						runtime_status = STOP_SENDING;
						break;
					case 0x02:
						runtime_status = SEND_ID;
						break;
					default:
						runtime_status = ERROR;
						break;
				}
        }
        if (runtime_status == SENDING)
        {
        	if(frame_avaliable[write_frame] == 1)
        	{
        		tcpsend_count = 0;
        		tcpsend_count = temple_frame[write_frame][32] + temple_frame[write_frame][33]*256
        				+ temple_frame[write_frame][34]*65536 + 36;
        		if(tcpsend_count > 350000)
        			tcpsend_count = 350000;
        		tcpsend_loop = tcpsend_count / 4096;
        		if(tcpsend_loop > 0)
        		{
        			tcpsend_remainder = tcpsend_count % 4096;
        		    for(i = 0; i < tcpsend_loop; i++)
        		    {
        		    	if (send(stcpactive, (void*)(temple_frame[write_frame]+i*4096), 4096, 0) < 0)
        		    	{
        		    		runtime_status = ERROR;
        		        	fdClose( stcpactive );
        		        	stcpactive = INVALID_SOCKET;
        		        }
        		      }
        		      if(tcpsend_remainder > 0)
        		      {
        		    	  if (send(stcpactive, (void*)(temple_frame[write_frame]+i*4096),tcpsend_remainder, 0) < 0)
        		    	  {
        		    		  runtime_status = ERROR;
        		    		  fdClose( stcpactive );
        		    		  stcpactive = INVALID_SOCKET;
        		    	  }
        		       }
        		   }
        		   if(tcpsend_loop <= 0)
        		   {
        		        	if (send(stcpactive, (void*)temple_frame[write_frame], tcpsend_count, 0) < 0)
        		        	{
        		        		runtime_status = ERROR;
        		        		fdClose( stcpactive );
        		        		stcpactive = INVALID_SOCKET;
        		        	}
        		    }
        		frame_avaliable[write_frame] = 0;
        		write_frame++;
        		if(write_frame >= 20)
        		{
        			write_frame = 0;
        		}
        	    SCOM_putMsg(hs_N2Proc, tcpMsg);
        		continue;
        	}
        	else
        	{
        		SCOM_putMsg(hs_N2Proc, tcpMsg);
        		continue;
        	}
        }
        if(runtime_status == SEND_ID)
        {
        	 if( send( stcpactive, (void*)ID_Buf, 1, 0 ) < 0 )
        	 {
        		 runtime_status = ERROR;
        		 fdClose( stcpactive );
        		 stcpactive = INVALID_SOCKET;
        		 SCOM_putMsg(hs_N2Proc, tcpMsg);
        		 continue;
        	 }
        	 runtime_status = STOP_SENDING;
        	 SCOM_putMsg(hs_N2Proc, tcpMsg);
        	 continue;
        }
        if(runtime_status == STOP_SENDING || runtime_status == ERROR)
        {
        	 if( send( stcpactive, (void*)testSend, 4, 0 ) < 0 )
        	 {
        		 runtime_status = ERROR;
        	     fdClose( stcpactive );
        	     stcpactive = INVALID_SOCKET;
        	     SCOM_putMsg(hs_N2Proc, tcpMsg);
        	     continue;
        	 }
        	SCOM_putMsg(hs_N2Proc, tcpMsg);
        	continue;
        }
    }

leave:
    // We only get here on an error - close the sockets
    if( ID_Buf )
        mmFree( ID_Buf );

    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    printf("EchoSrv Fatal Error\n");

    // This task is killed by the system - here, we block
    TaskBlock( TaskSelf() );
}


