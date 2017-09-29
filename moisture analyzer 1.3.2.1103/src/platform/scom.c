/*
 *  ======== scom.c ========
 *
 *  Synchronized COMmunication modulem for sys/bios
 *
 *  Refer to the header file for general information about the module.
 *  changed by zzw,2013-8-13
 */

#include <xdc/std.h>
#include <xdc/runtime/Memory.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <string.h>
#include "scom.h"

/* default SCOM creation attributes */
SCOM_Attrs SCOM_ATTRS = { 
    0                      /* dummy */
};

/* definition of an SCOM queue */
struct SCOM_Obj {
	Queue_Elem   elem;         /* mandatory first element */
    String     name;         /* name of the queue */
    Queue_Handle que;		//Queue_Object    que;          /* queue on which messages are placed */
    Semaphore_Handle sem;	//Semaphore_Object    sem;          /* semaphore for the queue */
};

/* internal list of SCOM queues */
//static Queue_Object queScomQueues;
static Queue_Handle queScomQueues;

/*
 *  ======== SCOM_init ========
 *  
 *  Initializes the master queue.
 */
Void SCOM_init( Void )
{
    //QUE_new( &queScomQueues );
	queScomQueues = Queue_create( NULL,NULL );
}

/*
 *  ======== SCOM_exit ========
 */
Void SCOM_exit( Void )
{
	Queue_delete(&queScomQueues);
}

/*
 *  ======== SCOM_create ========
 *  
 *  Create a new SCOM queue under given name 
 */
SCOM_Handle SCOM_create( 
    String       queueName,  /* ID (name) of the SCOM queue to be created */
    SCOM_Attrs * attrs       /* SCOM object attributes */
    )
{
    SCOM_Handle  scomQueue;

    
    /* allocate the SCOM queue object */
    scomQueue = (SCOM_Handle)Memory_alloc( NULL, sizeof( SCOM_Obj ), 0 ,NULL);
    if (scomQueue == NULL) {
        return NULL;
    }
    
    /* initialize the object */
    //QUE_new( &scomQueue->que );
    scomQueue->que = Queue_create( NULL,NULL );
    //SEM_new( &scomQueue->sem, 0 );
    scomQueue->sem = Semaphore_create(0, NULL,NULL);

    scomQueue->name = queueName;

    /* and place it on the master list of SCOM queues */
    //QUE_put( &queScomQueues, scomQueue );
    Queue_put(queScomQueues, scomQueue);
    
    return scomQueue;
}

/*
 *  ======== SCOM_open ========
 *  
 *  Get a reference to an existing SCOM queue by its name
 */
SCOM_Handle SCOM_open(
    String       queueName    /* ID (name) of the SCOM queue to be found */
    )
{
    SCOM_Handle  scomQueue;
    
    /* search the master list for a queue whose name is == queueName */
    scomQueue = Queue_head(queScomQueues);	//QUE_head( &queScomQueues );
    while ((Queue_Handle)scomQueue != queScomQueues) {
        if (!strcmp( scomQueue->name, queueName )) {
            return scomQueue;    
        }
        scomQueue = Queue_next( scomQueue );//QUE_next( scomQueue );
    }
    
    /* not found */
    return NULL;
}

/*
 *  ======== SCOM_delete ========
 *  
 *  Delete the SCOM queue
 */
Bool SCOM_delete( 
    SCOM_Handle  scomQueue     /* handle of the SCOM queue to be deleted */
    )
{
    
	Queue_remove( scomQueue );	//QUE_remove( scomQueue );
	Memory_free(NULL, scomQueue, sizeof( SCOM_Obj ));	//MEM_free( 0, scomQueue, sizeof( SCOM_Obj ) );

	 return NULL;
}


/*
 *  ======== SCOM_putMsg ========
 *  
 *  Place the message on a synchronized queue
 */
Void SCOM_putMsg(
    SCOM_Handle  scomQueue,   /* SCOM queue to which message should be put */
    Ptr          msg          /* message to be sent */
    )
{
    //QUE_put ( scomQueue->que, (QUE_Elem *)msg);
    Queue_put ( scomQueue->que, (Queue_Elem *)msg);
    //SEM_post( &scomQueue->sem );
    Semaphore_post( scomQueue->sem );
}

/*
 *  ======== SCOM_getMsg ========
 *  
 *  Receive a message from a synchronized queue
 */
Ptr SCOM_getMsg(
    SCOM_Handle  scomQueue,   /* SCOM queue from which to take a message */
    Uns          timeout      /* blocking timeout */
    )
{

//    if (SEM_pend( &scomQueue->sem, timeout ) == FALSE) {
      if (Semaphore_pend( scomQueue->sem, timeout ) == FALSE) {
        return NULL;          // semaphore timed out
    }

    return ( Queue_get( scomQueue->que ) );	//QUE_get( &scomQueue->que )
}

