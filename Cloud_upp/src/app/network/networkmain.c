
#include <ti/sysbios/BIOS.h>
#include <stdio.h>
#include <netmain.h>
#include <_stack.h>
#include <scom.h>
#include <gooao_c6748.h>
#include <xdc/runtime/System.h>

uint8_t MainConfig[512];
int64_t   MainConfigSize   = 0;
int64_t   MainConfigValid  = 0;
int8_t *LocalIPAddr = 	"192.168.1.100"; 	//"192.168.1.2";	//
int8_t *LocalIPMask = 	"255.255.255.0";
int8_t *GatewayIP = 		"192.168.1.1"; 	//"192.168.1.1";	//
int8_t *ServerIPAddr = 	"192.168.1.10";	//"192.168.1.10";	//
int8_t *HostName = 		"testndk";
int8_t *DomainName = 		"fr.net";

int32_t tcpsend_count;

Uint8 integration_value[2] ={0x00, 0x10};
uint8_t check[32] = {0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB,
								0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB,
								0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB,
								0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB, 0xAB};
extern uint8_t uart1_recvBuffer[6];

static HANDLE 	hEchoServer=0;
//=====================================
static void		NetBoot();
// NC Callback Functions
static void		NetworkOpen();
static void		NetworkClose();
static void		NetworkIPAddr( IPN IPAddr, uint IfIdx, uint fAdd );

extern unsigned char Value_imageBufferCmos[720*480*2];
extern unsigned char Quarter_Value_imageBufferCmos[720*480*2];

void tskTcpServer();
void tskTcpClient();

int NetworkMain()
{
    HANDLE   hCfg;
    int      rc;
    uint     tmp;

    CI_IPNET NA;
    CI_ROUTE RT;

    rc = NC_SystemOpen( NC_PRIORITY_HIGH, NC_OPMODE_INTERRUPT );
    if( rc )
    {
        printf("NC_SystemOpen Failed (%d)\n",rc);
        for(;;);
    }

    // Create a new configuration
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


//server task for echo
void tskTcpServer()
{
    SOCKET   stcp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    SOCKET   stcpbusy;
    struct   sockaddr_in sin1;
    struct   timeval timeout;           //	Timeout struct for select
    int32_t      size,tmp,i;
    HANDLE   hBuffer;
    unsigned char  (*tcprecv_Buf)[10];
    unsigned char  integration_cam_select;
    unsigned char head[4] = {0};
    int32_t Msgcount = 0;

    unsigned char *pic_sendBuf;
    ScomMessage *tcpMsg;
    SCOM_Handle hs_Proc2Net,hs_Net2Proc,hs_Net2UM, hs_UM2Net;

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

    // Configure our timeout to be 300 seconds
    timeout.tv_sec  = 300;
    timeout.tv_usec = 0;

    printf("EchoSrv Initialized\n");

    hs_Proc2Net = SCOM_open("P2NET");
    hs_Net2Proc = SCOM_open("NET2P");
    hs_Net2UM = SCOM_open("NET2UM");
    hs_UM2Net = SCOM_open("UM2NET");

    if(!hs_Proc2Net || !hs_Net2Proc ||!hs_Net2UM ||!hs_UM2Net)
    {
    	for(;;);
    }

    // Run until task is destroyed by the system
    for(;;)
    {
        fd_set ibits, obits, xbits;
        int32_t    cnt, cur_imageSize, tmp_sendi;
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
            tmp = fdSelect( 4, &ibits, &obits, &xbits, 0 );
        }
        else
        {
            // Wait for set timeout - abort active connection on no activity
            FD_SET(stcpactive, &ibits);
            tmp = fdSelect( 4, &ibits, &obits, &xbits, &timeout );
            if( tmp <= 0 )
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
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

        tcpMsg = SCOM_getMsg(hs_Proc2Net, BIOS_WAIT_FOREVER);
        cur_imageSize = tcpMsg->sizeLinear;
        pic_sendBuf = (unsigned char*)tcpMsg->bufLinear;
        integration_cam_select = tcpMsg->camCelect;
        // Check for new data on active TCP connection
        if( stcpactive != INVALID_SOCKET && FD_ISSET(stcpactive, &ibits) )
        {
            // There is data available on the active connection
            cnt = (int32_t)recvnc( stcpactive, (void **)(&tcprecv_Buf), 0, &hBuffer );

            if( (cnt > 4) && ((*tcprecv_Buf)[3] == 0x08) )
            {
            	tcpsend_count = 0;
            	tmp_sendi = cur_imageSize/4096;

            	if(tcpMsg->camCelect == 1)
            	{
            		Msgcount = 720*480*4;
            		memcpy(head, &Msgcount, 4);

            		if (send(stcpactive, head, 4, 0) < 0)
            		{
            			fdClose(stcpactive);
            	        stcpactive = INVALID_SOCKET;
            		}
            		for(i = 0; i < tmp_sendi ; i++)
            		{
            			if(send(stcpactive, (Value_imageBufferCmos+i*4096), 4096, 0 ) < 0)
            			{
            				fdClose( stcpactive );
            				stcpactive = INVALID_SOCKET;
            			}
            		}
            		send( stcpactive, (Value_imageBufferCmos+i*4096) , 3072, 0);
            		for(i = 0; i < tmp_sendi ; i++)
            		{
            			if(send(stcpactive, (Quarter_Value_imageBufferCmos+i*4096), 4096, 0 ) < 0)
            			{
            				fdClose( stcpactive );
            		        stcpactive = INVALID_SOCKET;
            			}
            		}
            		send( stcpactive, (Quarter_Value_imageBufferCmos+i*4096) , 3072, 0);
            		recvncfree( hBuffer );
            	}
            	if(tcpMsg->camCelect == 0)
            	{
            		Msgcount = 640*512*2;
            		memcpy(head, &Msgcount, 4);
            		if (send(stcpactive, head, 4, 0) < 0)
            		{
            			fdClose(stcpactive);
            			stcpactive = INVALID_SOCKET;
            		}
            		for(i = 0; i < tmp_sendi ; i++)
            		{
            			if(send(stcpactive, (pic_sendBuf+i*4096), 4096, 0 ) < 0)
            		    {
            				fdClose( stcpactive );
            		        stcpactive = INVALID_SOCKET;
            		    }
            		}
            		recvncfree( hBuffer );
            	}
            }
            else if((cnt > 4) && ((*tcprecv_Buf)[3] == 0x09))
            {
            	tcpMsg->camCelect = 1 - tcpMsg->camCelect;
            }
            else if((cnt > 4) && ((*tcprecv_Buf)[3] == 0x10))
            {
            	integration_value[0] = (*tcprecv_Buf)[1];
            	integration_value[1] = (*tcprecv_Buf)[2];
            	tcpMsg->integration_time_status = NEED_TO_OPERATE;
            }
            else if((cnt > 4) && ((*tcprecv_Buf)[3] == 0x0a))
            {
            	Msgcount = 1;
            	memcpy(head, &Msgcount, 4);
            	if (send(stcpactive, head, 4, 0) < 0)
            	{
            		fdClose(stcpactive);
            	    stcpactive = INVALID_SOCKET;
            	}
            	if (send(stcpactive, &integration_cam_select, 1, 0) < 0)
            	{
            		fdClose(stcpactive);
            		stcpactive = INVALID_SOCKET;
            	}
            	recvncfree( hBuffer );
            }
            else if((cnt > 4) && ((*tcprecv_Buf)[3] < 0x08))
            {
                tcpMsg->command = (*tcprecv_Buf)[3];
                SCOM_putMsg(hs_Net2UM, tcpMsg);
                tcpMsg = SCOM_getMsg(hs_UM2Net, BIOS_WAIT_FOREVER);
            }
            // If the connection got an error or disconnect, close
            else
            {
            	fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }

        if(tcpMsg->extra_flag == 1)
        {
        	Msgcount = 5;
        	memcpy(head, &Msgcount, 4);
        	if (send(stcpactive, head, 4, 0) < 0)
        	{
        		fdClose(stcpactive);
        		stcpactive = INVALID_SOCKET;
        	}
        	if(send(stcpactive, (void*)uart1_recvBuffer, 5, 0) < 0)
        	{
        		fdClose( stcpactive );
        		stcpactive = INVALID_SOCKET;
        	}
        	recvncfree( hBuffer );
        }

        SCOM_putMsg(hs_Net2Proc, tcpMsg);
    }

leave:
    // We only get here on an error - close the sockets
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    printf("EchoSrv Fatal Error\n");

    // This task is killed by the system - here, we block
    TaskBlock( TaskSelf() );
}


