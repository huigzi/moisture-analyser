/*
 *  Copyright 2003 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *  
 */
/* "@(#) ReferenceFrameworks 2.10.00.11 04-30-03 (swat-d15)" */

/*
 *  ======== scom.h ========
 *
 *  Synchronized COMmunication module
 *  
 *  This module implements message passing between tasks. It lets the user
 *  create any number of named, synchronized queues, and put messages
 *  to such queues and receive messages from them. Messages are buffers
 *  of arbitrary sizes.  The message structure's first field must be 
 *  QUE_Elem.  For example:
 *  struct MyMsg {
 *      QUE_Elem  elem;
 *      Ptr       buffer;
 *  }
 *  
 *  Usage example:
 *  
 *  0. Tasks A and B agree that A sends messages of some type MyMsg to B,
 *     via an SCOM queue named "queueForB".
 *  
 *  1. Some code (typically B's initialization part) creates the SCOM queue
 *     with a unique name:
 *     SCOM_Handle queueB = SCOM_create( "queueForB" );
 *     
 *     .---.                  .---.
 *     | A |        ========> | B |       
 *     `---'                  `---'
 *     
 *   
 *  2. A gets the reference to the SCOM queue by supplying its name:
 *     SCOM_Handle queueB = SCOM_open( "queueForB" );
 *     B can do the same if it didn't remember it from the call to 
 *     SCOM_create()
 *  
 *     .---.                  .---.
 *     | A |        ========> | B |       
 *     `---'         :   :    `---'
 *       :...........:   :......:
 *   
 *  3. Someone, typically sender task A, allocates a buffer of type MyMsg:
 *     MyMsg * msg = MEM_alloc(someMemSegId, sizeof( MyMsg ), 0 );
 *     The msg could also be static.
 *     
 *        .---->[  ]
 *        |
 *     .--+.                 .---.
 *     |A *|       ========> | B |       
 *     `---'         :   :   `---'
 *       :...........:   :......:
 *   
 *  4. A writes some information, p, into the message buffer:
 *  
 *        .---->[p ]
 *        |
 *     .--+.                 .---.
 *     |A *|       ========> | B |       
 *     `---'         :   :   `---'
 *       :...........:   :......:
 *   
 *  5. A sends the message to B by doing SCOM_putMsg( queueB, msg );
 *     There can be an unlimited number of messages waiting on an SCOM queue.
 *  
 *              [p ]<--.
 *                     |
 *     .---.           |     .---.
 *     | A |       ===(*)==> | B |       
 *     `---'         :   :   `---'
 *       :...........:   :......:
 *  
 *  
 *  6. B receives the message by saying, 
 *     MyMsg * msg = SCOM_getMsg( queueB, SYS_FOREVER ); SYS_FOREVER
 *     is a timeout value, indicating how long to wait until there's a message
 *     available on the SCOM queue. 0 as a timeout means "don't wait."
 *  
 *              [p ]<---------.
 *                            |
 *     .---.                 .+--.
 *     | A |       ========> |* B|       
 *     `---'         :   :   `---'
 *       :...........:   :......:
 *   
 *  7. If B wants to write something into the message buffer and send it back
 *     to A (i.e. if they want a two-way communication), we need an additional 
 *     queue for A, symetrical to the one for B. 
 */

#ifndef SCOM_
#define SCOM_

#ifdef __cplusplus
extern "C" {
#endif

/* SCOM object handle */
typedef struct SCOM_Obj SCOM_Obj, *SCOM_Handle;

/* SCOM object creation attributes */
typedef struct SCOM_Attrs {    
    Char    dummy;      /* no attributes at present */
} SCOM_Attrs;

/* default SCOM creation attributes */
extern SCOM_Attrs SCOM_ATTRS;   

/*
 *  ======== SCOM_init ========
 *  
 *  Initialize the module.
 */
Void SCOM_init( Void );

/*
 *  ======== SCOM_exit ========
 *
 *  Finalize the module.
 */
Void SCOM_exit( Void );

/*
 *  ======== SCOM_create ========
 *  
 *  Create a new SCOM queue under given name 
 */
SCOM_Handle SCOM_create(
    String       queueName,  /* ID (name) of the SCOM queue to be created */
    SCOM_Attrs * attrs       /* SCOM object attributes; only NULL supported */
    );

/*
 *  ======== SCOM_open ========
 *  
 *  Get a reference to an existing SCOM queue by its name
 */
SCOM_Handle SCOM_open(
      String       queueName );   /* ID (name) of the SCOM queue to be found */

/*
 *  ======== SCOM_delete ========
 *  
 *  Delete the SCOM queue
 */
Bool SCOM_delete( 
    SCOM_Handle  scomQueue   /* handle of the SCOM queue to be deleted */
    );

/*
 *  ======== SCOM_putMsg ========
 *  
 *  Place the message on a synchronized queue
 */
Void SCOM_putMsg(
    SCOM_Handle  scomQueue,   /* SCOM queue to which message should be put */
    Ptr          msg          /* message to be sent */
    );

/*
 *  ======== SCOM_getMsg ========
 *  
 *  Receive a message from a synchronized queue
 */
Ptr SCOM_getMsg(
    SCOM_Handle  scomQueue,   /* SCOM queue from which to take a message */
    Uns          timeout      /* semaphore timeout */
    );

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SCOM_ */

