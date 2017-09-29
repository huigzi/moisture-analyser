#include <stdio.h>
#include <netmain.h>

extern char *ServerIPAddr;

//server task for echo
void tskTcpServer()
{
    SOCKET   stcp = INVALID_SOCKET;
    SOCKET   stcpactive = INVALID_SOCKET;
    SOCKET   stcpbusy;
    struct   sockaddr_in sin1;
    struct   timeval timeout;           //	Timeout struct for select
    int      size,tmp;
    HANDLE   hBuffer;
    char     *pBuf;

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

    // Configure our timeout to be 15 seconds
    timeout.tv_sec  = 15;
    timeout.tv_usec = 0;

    printf("EchoSrv Initialized\n");

    // Run until task is destroyed by the system
    for(;;)
    {
        fd_set ibits, obits, xbits;
        int    cnt;

        // Clear the select flags
        FD_ZERO(&ibits);
        FD_ZERO(&obits);
        FD_ZERO(&xbits);

        // We examine the main TCP, UDP, and active TCP (if any)
        FD_SET(stcp, &ibits);
        //FD_SET(sudp, &ibits);

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

        // Check for new data on active TCP connection
        if( stcpactive != INVALID_SOCKET && FD_ISSET(stcpactive, &ibits) )
        {
            // There is data available on the active connection
            cnt = (int)recvnc( stcpactive, (void **)&pBuf, 0, &hBuffer );

            if( cnt > 0 )
            {
                if( send( stcpactive, pBuf, cnt, 0 ) < 0 )
                {
                    fdClose( stcpactive );
                    stcpactive = INVALID_SOCKET;
                }
                recvncfree( hBuffer );
            }
            // If the connection got an error or disconnect, close
            else
            {
                fdClose( stcpactive );
                stcpactive = INVALID_SOCKET;
            }
        }
    }

leave:
    // We only get here on an error - close the sockets
    if( stcp != INVALID_SOCKET )
        fdClose( stcp );

    printf("EchoSrv Fatal Error\n");

    // This task is killed by the system - here, we block
    TaskBlock( TaskSelf() );
}


//task for client echo
void tskTcpClient()
{
    SOCKET  s = INVALID_SOCKET;
    struct  sockaddr_in sin1;
    //int     test
    int		i;
    char    *pBuf = 0;
    struct  timeval timeout;

    printf("\n== Start TCP Echo Client Test ==\n");

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Create test socket */
    s = socket(AF_INET, SOCK_STREAMNC, IPPROTO_TCP);
    if( s == INVALID_SOCKET )
    {
    	printf("failed socket create (%d)\n",fdError());
        goto leave;
    }

    /* Prepare address for connect */
    bzero( &sin1, sizeof(struct sockaddr_in) );
    sin1.sin_family      = AF_INET;
    sin1.sin_len         = sizeof( sin1 );
    sin1.sin_addr.s_addr = inet_addr(ServerIPAddr);//IPAddr;
    sin1.sin_port        = htons(5000);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 5;
    timeout.tv_usec = 0;
    setsockopt( s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    /* Connect socket */
    if ( connect( s, (PSA) &sin1, sizeof(sin1) ) < 0 )
    {
    	printf("failed connect (%d)\n",fdError());
        goto leave;
    }

    /* Allocate a working buffer */
    if( !(pBuf = mmBulkAlloc( 2048 )) )
    {
    	printf("failed temp buffer allocation\n");
        goto leave;
    }

    /* Fill buffer with a test pattern */
    for(i=0; i<2048; i++)
        *(pBuf+i) = (char)i;

    /* Start Test */
    for(;;)// test=48; test<=12288; test*=2 )
    {
        /* Send the buffer */
        //printf("Sending %d bytes ... ",2048);
        if( send( s, pBuf, 2048, 0 ) < 0 )
        {
        	printf("send failed (%d)\n\n",fdError());
            break;
        }
        TaskSleep(100);
     }
leave:
    if( pBuf )
        mmBulkFree( pBuf );
    if( s != INVALID_SOCKET )
        fdClose( s );

    printf("== End TCP Echo Client Test ==\n\n");

    /* This task is killed by the system - here, we block */
    TaskBlock( TaskSelf() );
}
