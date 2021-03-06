/*
 * CodecInterface.c
 *
 * This file contains Codec driver implementation for interfacing the encoders
 * and decoders with the evm. Codec Interface Driver provides init, deinit,
 * read and write Interface to do operations on encoders and decoders connected
 * to the EVM
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file   CodecInterface.c
 *
 *  \brief  This file contains the interface function for the various
 *          hardware devices which will be communicating through the
 *          I2C bus. This file performs a read/write for External Video codecs.
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */
#include <xdc/std.h>
#include <string.h>
#include <assert.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <ti/sdo/utils/List.h>
#include <ti/sysbios/io/DEV.h>

#include <I2c.h>
#include <VpifDebug.h>

#include <Edc.h>
#include <CodecInterfaceLocal.h>

/* ========================================================================== */
/*                          MACRO DEFINITIONS                                 */
/* ========================================================================== */
/** \brief Buffer size for the write buffer */
#define BUFFER_SIZE                     (260)

/** \brief Timeout for I2C */
#define CODEC_I2C_TIMEOUT                (0xFFFFFFFF)

/** \brief Maximum IOs submitted for Async write calls. This is specially for
 handling VBI writes */
#define CODEC_IO_DEPTH                  2

/** \brief Maximum regs to be written to the async write in one call. */
#define CODEC_BUFFER_SIZE               20
/* ========================================================================== */
/*                          STATIC VARIABLES                                  */
/* ========================================================================== */
static Int32                   initCount = 0;
/**< Make record of init */

static DEV_Handle              ctrlBusHandle;

/**< pointer to the driver object of the control bus */

static Ptr                     inCtrlBus;
/**< Handle of the control bus instance created and opened */

static Ptr                     outCtrlBus;
/**< Handle of the control bus instance created and opened */

static Ptr                     outAsyncCtrlBus;
/**< Handle of the control bus instance created and opened */

static Semaphore_Handle        semObj;

/**< Semaphore Handle used while doing I2C transfer */

static Semaphore_Handle		   syncSemObj;

/**< Semaphore Handle used while syncing I2C transfer */

static Uint32 xferActual = 0; /**< Since the actual xfer size can only be known
                                   in the callback context, its required to have
                                   a global variable to check this in the caller
                                   context */

/* NOTE: Following parameters are required for handling the async write to the
 codec*/
I2c_DataParam writeBuf[CODEC_IO_DEPTH];
/**< I2C data params to be submitted */

Uint8 writeBuffer[CODEC_IO_DEPTH * (CODEC_BUFFER_SIZE + 1)];
/**< Buffer storing the write data */

IOM_Packet writeIoPacket[CODEC_IO_DEPTH];
/**< IO Packets to be submitted for asynce write */

List_Handle                      txFreeQ;
/**< Pointer to list of free packets                                      */

List_Handle                      txPendingQ;
/**< Pointer to list of submitted packets                                 */

static Edc_Data *codecAsyncCbData;

/* ========================================================================== */
/*                          LOCAL FUNCTION PROTOTYPE                          */
/* ========================================================================== */
static Void codecSyncCb(Ptr semHandle, IOM_Packet *ioPacket);

static Void codecAsyncCb(Ptr semHandle, IOM_Packet *ioPacket);

/* ========================================================================== */
/*                          FUNCTION DEFINITIONS                              */
/* ========================================================================== */
Int32 initCodecInterface(String devName)
{
    I2c_ChanParams 		i2cChanPrms = {0};
    Int32 				retVal = IOM_COMPLETED, i;
    Semaphore_Params 	semParams    = {0};
    Error_Block      	eb;
    UInt             	taskKey;
    List_Params      	listParams   = {0};    
    String 				remName = NULL;
    IOM_Fxns            *iomFxns;
    Ptr                 devPtr;


    assert(NULL != devName);
    
    if (0 == strcmp(devName, "/i2c0"))
    {
        taskKey = Task_disable();
        if (0 == initCount)
        {
            Semaphore_Params_init(&semParams);
            semParams.mode = Semaphore_Mode_BINARY;
            semObj         = Semaphore_create(0, &semParams , &eb);
            
            if(NULL == semObj)
            {
                DBG_PRINT_ERR("CODEC I/F : Semaphore Handle" 
                                                        "Create Failed!\n");
                retVal = IOM_EBADARGS;                           
            }

            Semaphore_Params_init(&semParams);
            semParams.mode = Semaphore_Mode_BINARY;
            syncSemObj     = Semaphore_create(0, &semParams , &eb); 
            
            if(NULL == syncSemObj)
            {
                DBG_PRINT_ERR("CODEC I/F : Semaphore Handle "
                                                        "Create Failed!\n");                 
                retVal = IOM_EBADARGS;                           
            }
            
            Semaphore_post(syncSemObj);
            
            /* open the control bus to the codec, so that using the codec handle
            it can be configured                                              */
            remName = DEV_match(devName, &ctrlBusHandle);
            if ((NULL == ctrlBusHandle) || (NULL == remName))
            {
                retVal = IOM_EBADARGS;
            }
            else
            {
                /* Initialize the error block                                 */
                Error_init(&eb);
#ifdef DEBUG_PRINTS                	            
                VPIF_DEBUG("CODEC I/F : Start of I2C creation\n");
#endif                
                i2cChanPrms.hEdma = NULL;
                i2cChanPrms.masterOrSlave = I2c_CommMode_MASTER;

				iomFxns = DEV_getFxns(ctrlBusHandle);
				devPtr  = DEV_getDevp(ctrlBusHandle);
				
                /* Create the I2C Channels for the TX and RX communication    */
                /* driver handle obtained from the name of the device         */
                retVal = ((IOM_Fxns *)iomFxns)->mdCreateChan(
                            &inCtrlBus,
                            devPtr,
                            remName,
                            IOM_INPUT,
                            &i2cChanPrms,
                            &codecSyncCb,
                            (Ptr)(semObj));

                if ((NULL != inCtrlBus) && (IOM_COMPLETED == retVal))
                {

                    /* driver handle obtained from the name of the device     */
                    retVal = ((IOM_Fxns *)iomFxns)->mdCreateChan(
                                &outCtrlBus,
                                devPtr,
                                remName,
                                IOM_OUTPUT,
                                &i2cChanPrms,
                                &codecSyncCb,
                                (Ptr)(semObj));

                    if ((NULL != outCtrlBus) && (IOM_COMPLETED == retVal))
                    {
                        /* create a list of packets to be used henceforth     */
                         List_Params_init(&listParams);
                         txFreeQ = List_create(&listParams, &eb);

                        /* no reclaimable packets right now!                  */
                         List_Params_init(&listParams);
                         txPendingQ = List_create(&listParams, &eb);
                         
                        if ((NULL == txPendingQ) || (NULL == txFreeQ))
                        {
                            DBG_PRINT_ERR("CODEC I/F : Queue create failed!\n");                           	                        
                            retVal = IOM_EALLOC;
                        }
						else
						{
		                    for (i = 0; i < CODEC_IO_DEPTH; i++)
		                    {
		                        memset(&writeIoPacket[i], 0x00, 
		                        							sizeof(IOM_Packet));
		                        writeBuf[i].buffer    = &writeBuffer[i];
		                        writeIoPacket[i].addr = &writeBuf[i];
                                List_put(txFreeQ,
                                            (List_Elem *)(&(writeIoPacket[i])));
		                    }
		
		                    /* driver handle obtained from the name of the device */
		                    retVal = ((IOM_Fxns *)iomFxns)->mdCreateChan(
		                                &outAsyncCtrlBus,
		                                devPtr,
		                                remName,
		                                IOM_OUTPUT,
		                                &i2cChanPrms,
		                                &codecAsyncCb,
		                                &codecAsyncCbData);
						}
                    }
                }
            }
        }

        if (((NULL == outCtrlBus) || (NULL == inCtrlBus)) ||
            ((IOM_COMPLETED != retVal) || (NULL == outAsyncCtrlBus)))
        {
            DBG_PRINT_ERR("CODEC I/F : I2C Handle Create Failed!\n");
            DBG_PRINT_ERR1("CODEC I/F : mdCreateChan status = %d\n", retVal);
        }
        else
        {
            initCount++;
        }
        Task_restore(taskKey);
    }
    else
    {
        retVal = IOM_ENOTIMPL;
    }

    return retVal;
}



Bool codecWriteReg(Edc_ControlBusType edcControlBusType,
                   Uint8 slaveAddr,
                   Uint8 subAddr,
                   const Uint8 *buffer,
                   Uint32 length)
{
    Uint8 			writeBuffer[BUFFER_SIZE + 1];
    Int32 			writeStatus	= 340;
    I2c_DataParam	writeBuf;
    Int32 			writeCount 	= 0;
    IOM_Packet 		writeIoPacket;
    Bool 			writeRegFlag = TRUE;
    IOM_Fxns        *iomFxns;


    /* Validate the input parameters                                      */
    assert(NULL != buffer);
    if (Edc_ControlBusType_I2C == edcControlBusType)
    {
        /* Write to Slave Device */
        if (length <= BUFFER_SIZE)
        {
            for (writeCount = 0; writeCount < length; writeCount++)
            {
#ifdef DEBUG_PRINTS                	            
                VPIF_DEBUG1("CODEC I/F : I2C Write: SlaveAddr = 0x%0.2X, ",
                    slaveAddr);
                VPIF_DEBUG2("SubAddr = 0x%x, Value = 0x%x\n",
                           subAddr + writeCount,
                           buffer[writeCount]);
#endif                           
            }
            /* Prepare the data to be written to the codec */
            writeBuffer[0] = subAddr;
            memcpy(&writeBuffer[1], buffer, length);

            writeBuf.buffer    = &writeBuffer[0];
            writeBuf.bufLen    = length + 1u;
            writeBuf.flags     = I2c_DEFAULT_WRITE;
            writeBuf.param     = NULL;
            writeBuf.slaveAddr = slaveAddr;

            memset(&writeIoPacket, 0x00, sizeof(IOM_Packet));

            /* Update dataparams */
            writeIoPacket.addr   = &writeBuf;
            writeIoPacket.size   = length + 1u;
            writeIoPacket.cmd    = (Uns)IOM_WRITE;
            writeIoPacket.status = IOM_COMPLETED;

            iomFxns = DEV_getFxns(ctrlBusHandle);
            
            /* Write the data to register */
            writeStatus = ((IOM_Fxns *)iomFxns)->mdSubmitChan(
                            outCtrlBus,
                            &writeIoPacket);
                            
            /* Wait for 5 milliSeconds so that bus is free                    */
            Task_sleep(3u);
                            
            if (IOM_PENDING == writeStatus)
            {
                if (Semaphore_pend(semObj, CODEC_I2C_TIMEOUT) != TRUE)
                {
                    writeRegFlag = TRUE;
                }
                else
                {
                    writeRegFlag = FALSE;
                }
            }

            /* Validate the number of words written to codec.                 */
            if ((IOM_COMPLETED == writeIoPacket.status) ||
                (IOM_PENDING == writeIoPacket.status))
            {
                if (xferActual != (length + 1))
                {
                    writeRegFlag = TRUE;
                }
                else
                {
                    writeRegFlag = FALSE;
                }
            }
            else
            {
                writeRegFlag = TRUE;
            }
        }
    }
    else
    {
        writeRegFlag = TRUE;
    }
    
    /* Return the result of writing to registers                              */
    if(writeRegFlag == TRUE)
    {
        VPIF_DEBUG("ICodec_codecWriteReg: failed\r\n"); 
    }
    else
    {
#ifdef DEBUG_PRINTS                	            	    
        VPIF_DEBUG("ICodec_codecWriteReg: passed\r\n"); 
#endif        
    }

    /* Return the result of writing to registers */
    return writeRegFlag;
}



Bool codecReadReg(Edc_ControlBusType edcControlBusType,
                  Uint8 slaveAddr,
                  Uint8 subAddr,
                  Uint8 *buffer,
                  Uint32 length)
{
    Int32 			readStatus = 340;
    I2c_DataParam 	readBuf;
    Int32 			readCount = 0;
    IOM_Packet 		ioPacket;
    Bool 			readRegFlag = TRUE;
    Uint8 			cmd[2];
    IOM_Fxns 		*iomFxns;

    /* Validate the input parameters                                          */
    assert(NULL != buffer);

    if (Edc_ControlBusType_I2C == edcControlBusType)
    {
        for (readCount = 0; readCount < length; readCount++)
        {
            /* The following the procedure to read data from encoder / decoder

               Step A: Write the address of the register to be read.
                       Note: The I2C stop should not be issued.
               Step B: Issue I2C restart.
               Step C: Read the value of the register.                        */

            /* Write Subaddress of Slave Device */
            cmd[0] = subAddr;

            /* Prepare the data to be written to the codec                  */
            readBuf.buffer    = &cmd[0];
            readBuf.bufLen    = 1u;
            readBuf.flags     = I2c_WRITE | I2c_MASTER | I2c_START;
            readBuf.param     = NULL;
            readBuf.slaveAddr = slaveAddr;

            memset(&ioPacket, 0x00, sizeof(IOM_Packet));

            ioPacket.addr   = &readBuf;
            ioPacket.size   = 1u;
            ioPacket.cmd    = (Uns)IOM_WRITE;
            ioPacket.status = IOM_COMPLETED;
            
            Semaphore_pend(syncSemObj, CODEC_I2C_TIMEOUT);
            
            iomFxns = DEV_getFxns(ctrlBusHandle);
            
            readStatus = ((IOM_Fxns *)iomFxns)->mdSubmitChan(
                            outCtrlBus,
                            &ioPacket);
            if (IOM_PENDING == readStatus)
            {
                if (Semaphore_pend(semObj, CODEC_I2C_TIMEOUT) != TRUE)
                {
                    readRegFlag = TRUE;
                }
                else
                {
                    readRegFlag = FALSE;
                }
            }

            /* If the write command is complete, read the registers of codec  */
            if ((IOM_COMPLETED == ioPacket.status) ||
                (IOM_PENDING == ioPacket.status))
            {
                ioPacket.cmd = IOM_READ;
                readBuf.flags = I2c_READ | I2c_MASTER | I2c_STOP | I2c_RESTART;
                
                readStatus = ((IOM_Fxns *)iomFxns)->mdSubmitChan(
                    									  inCtrlBus, &ioPacket);
                if (IOM_PENDING == readStatus)
                {
                    if (Semaphore_pend(semObj, CODEC_I2C_TIMEOUT) != TRUE)
                    {
                        readRegFlag = TRUE;
                    }
                    else
                    {
                        readRegFlag = FALSE;
                    }
                }
            }
            
            Semaphore_post((Semaphore_Handle)syncSemObj);
            
            /* If read is complete, then copy the required register values */
            if ((IOM_COMPLETED == ioPacket.status) ||
                (IOM_PENDING == ioPacket.status))
            {
                *buffer = cmd[0];
                buffer++;
                subAddr++;
                readRegFlag = FALSE;
            }
            else
            {
                readRegFlag = TRUE;
                break;
            }
        }
    }
    else
    {
        readRegFlag = TRUE;
    }
    return readRegFlag;
}


Bool codecReadReg16(Edc_ControlBusType edcControlBusType,
                  Uint8 slaveAddr,
                  Uint8 subAddr,
                  Uint16 *buffer,
                  Uint32 length)
{
    Int32 			readStatus = 340;
    I2c_DataParam 	readBuf;
    Int32 			readCount = 0;
    IOM_Packet 		ioPacket;
    Bool 			readRegFlag = TRUE;
    Uint8 			cmd[2];
    IOM_Fxns 		*iomFxns;

    /* Validate the input parameters                                          */
    assert(NULL != buffer);

    if (Edc_ControlBusType_I2C == edcControlBusType)
    {
        for (readCount = 0; readCount < length; readCount++)
        {
            /* The following the procedure to read data from encoder / decoder

               Step A: Write the address of the register to be read.
                       Note: The I2C stop should not be issued.
               Step B: Issue I2C restart.
               Step C: Read the value of the register.                        */

            /* Write Subaddress of Slave Device */
            cmd[0] = subAddr;

            /* Prepare the data to be written to the codec                  */
            readBuf.buffer    = &cmd[0];
            readBuf.bufLen    = 1u;
            readBuf.flags     = I2c_WRITE | I2c_MASTER | I2c_START;
            readBuf.param     = NULL;
            readBuf.slaveAddr = slaveAddr;

            memset(&ioPacket, 0x00, sizeof(IOM_Packet));

            ioPacket.addr   = &readBuf;
            ioPacket.size   = 1u;
            ioPacket.cmd    = (Uns)IOM_WRITE;
            ioPacket.status = IOM_COMPLETED;

            Semaphore_pend(syncSemObj, CODEC_I2C_TIMEOUT);

            iomFxns = DEV_getFxns(ctrlBusHandle);

            readStatus = ((IOM_Fxns *)iomFxns)->mdSubmitChan(
                            outCtrlBus,
                            &ioPacket);
            if (IOM_PENDING == readStatus)
            {
                if (Semaphore_pend(semObj, CODEC_I2C_TIMEOUT) != TRUE)
                {
                    readRegFlag = TRUE;
                }
                else
                {
                    readRegFlag = FALSE;
                }
            }

            /* If the write command is complete, read the registers of codec  */
            if ((IOM_COMPLETED == ioPacket.status) ||
                (IOM_PENDING == ioPacket.status))
            {
                ioPacket.cmd = IOM_READ;
                ioPacket.size   = 2u;	//ZZW For 16bit
                readBuf.bufLen  = 2u;	//ZZW For 16bit
                readBuf.flags = I2c_READ | I2c_MASTER | I2c_STOP | I2c_RESTART;

                readStatus = ((IOM_Fxns *)iomFxns)->mdSubmitChan(
                    									  inCtrlBus, &ioPacket);
                if (IOM_PENDING == readStatus)
                {
                    if (Semaphore_pend(semObj, CODEC_I2C_TIMEOUT) != TRUE)
                    {
                        readRegFlag = TRUE;
                    }
                    else
                    {
                        readRegFlag = FALSE;
                    }
                }
            }

            Semaphore_post((Semaphore_Handle)syncSemObj);

            /* If read is complete, then copy the required register values */
            if ((IOM_COMPLETED == ioPacket.status) ||
                (IOM_PENDING == ioPacket.status))
            {
                *buffer = (Uint16)(cmd[0]<<8) + cmd[1];
                buffer++;
                subAddr++;
                readRegFlag = FALSE;
            }
            else
            {
                readRegFlag = TRUE;
                break;
            }
        }
    }
    else
    {
        readRegFlag = TRUE;
    }
    return readRegFlag;
}

Int32 codecWriteRegAsync(CodecRegData *wrRegData, Edc_Data *cbData)
{
    Int32 			writeStatus;
    IOM_Packet 		*writeIoPkt = NULL;
    I2c_DataParam 	*wrBuf = NULL;
    Uint8 			*wrBuffer = NULL;
    IOM_Fxns 		*iomFxns;


    /* Validate the input parameters                                      */
    assert(NULL != wrRegData);
    assert(NULL != wrRegData->buffer);
    assert(wrRegData->length < CODEC_BUFFER_SIZE);
    assert(Edc_ControlBusType_I2C == wrRegData->edcControlBusType);
    
    if (TRUE == List_empty(txFreeQ))
    {
        writeStatus = IOM_ENOPACKETS;
    }
    else
    {
        Semaphore_pend(syncSemObj, CODEC_I2C_TIMEOUT);
        
        writeIoPkt = (IOM_Packet *)List_get(txFreeQ);
		codecAsyncCbData = cbData;
        wrBuf = writeIoPkt->addr;
        wrBuffer = wrBuf->buffer;
        
        /* Write to Slave Device. This should be one time write. */
        /* Prepare the data to be written to the codec */
        *wrBuffer = wrRegData->subAddr;
        memcpy(wrBuffer + 1, wrRegData->buffer, wrRegData->length);

        wrBuf->bufLen    = wrRegData->length + 1u;
        wrBuf->flags     = I2c_DEFAULT_WRITE;
        wrBuf->param     = NULL;
        wrBuf->slaveAddr = wrRegData->slaveAddr;

        /* Update dataparams */
        writeIoPkt->size   = wrRegData->length + 1u;
        writeIoPkt->cmd    = (Uns)IOM_WRITE;
        writeIoPkt->status = IOM_COMPLETED;
        /* Write the data to register */
        
        iomFxns = DEV_getFxns(ctrlBusHandle);
        
        writeStatus = ((IOM_Fxns *)iomFxns)->mdSubmitChan(
                        outAsyncCtrlBus,
                        writeIoPkt);
        Semaphore_post((Semaphore_Handle)syncSemObj);
    }
    /* Return the result of writing to registers */
    return writeStatus;
}


Int32 deInitCodecInterface(Edc_ControlBusType edcControlBusType)
{
    Int32 		retVal = IOM_COMPLETED;
    Int32 		deInitStatus = 340;
    UInt  		taskKey;
    IOM_Fxns 	*iomFxns;

    if (Edc_ControlBusType_I2C == edcControlBusType)
    {
        taskKey = Task_disable();
        if (initCount > 0)
        {
            initCount--;
        }

        /* Close driver if last i2c instance */
        if (0 == initCount)
        {
	        iomFxns = DEV_getFxns(ctrlBusHandle);
	        
            /* Close i2c driver and delete instance */
            deInitStatus = ((IOM_Fxns *)iomFxns)->mdDeleteChan(
                            outAsyncCtrlBus);
            /* The control bus handle is not valid anymore                    */
            outAsyncCtrlBus = NULL;
            
            if (IOM_COMPLETED != deInitStatus)
            {
                DBG_PRINT_ERR("CODEC I/F : I2C outAsyncCtrlBus Delete Failed!\n");
                retVal = IOM_EBADIO;
            }
            else
            {
                /* Close i2c driver and delete instance */
                deInitStatus = ((IOM_Fxns *)iomFxns)->mdDeleteChan(
                                outCtrlBus);
                /* The control bus handle is not valid anymore                */
                outCtrlBus = NULL;
                if (IOM_COMPLETED != deInitStatus)
                {
                    DBG_PRINT_ERR("CODEC I/F : I2C outCtrlBus Delete Failed!\n");
                    retVal = IOM_EBADIO;
                }
                else
                {
                    deInitStatus = ((IOM_Fxns *)iomFxns)->mdDeleteChan(
                                    inCtrlBus);
                    /* The control bus handle is not valid anymore            */
                    inCtrlBus = NULL;
                    if (IOM_COMPLETED != deInitStatus)
                    {
                        DBG_PRINT_ERR("CODEC I/F : I2C inCtrlBus Delete Failed!\n");
                        retVal = IOM_EBADIO;
                    }
                }
            }

            List_delete(&txFreeQ);
            List_delete(&txPendingQ);  
            
            Semaphore_delete(&semObj);
            Semaphore_delete(&syncSemObj);            
        }
        Task_restore(taskKey);
    }
    else
    {
        retVal = IOM_ENOTIMPL;
    }
    return retVal;
}

/**
 *  \brief   This function is the codec call back function invoked from the I2c
 *           driver on transfer completion.
 *
 *  \param   semHandle [IN] pointer to the Semaphore Handle
 *  \param   ioPacket  [IN] pointer to the completed ioPacket
 *
 *  \return  none
 */
static Void codecSyncCb(Ptr semHandle, IOM_Packet *ioPacket)
{
    Int32 status;
    assert((NULL != semHandle) && (NULL != ioPacket));
    /* Update the actual data transfer that was done. Let the submitter of the
       request decide what needs to be done after checking this.              */
    status = ioPacket->status;
    if (IOM_COMPLETED == status)
    {
        xferActual = ioPacket->size;
    }
    else
    {
        xferActual = 0;
    }
    Semaphore_post((Semaphore_Handle)semHandle);
    return;
}

/**
 *  \brief   This function is the codec call back function invoked from the I2c
 *           driver on transfer completion. This callback is for async operation
 *
 *  \param   unusedArg [IN] Unused argument
 *  \param   ioPacket  [IN] pointer to the completed ioPacket
 *
 *  \return  none
 */
static Void codecAsyncCb(Ptr unusedArg, IOM_Packet *ioPacket)
{
    Int32 status;
    assert(NULL != ioPacket);

    unusedArg = unusedArg; /* to remove compilation warning */
    /* Update the actual data transfer that was done. Let the submitter of the
       request decide what needs to be done after checking this.              */
    status = ioPacket->status;

    List_put(txFreeQ, (List_Elem *)ioPacket);

    codecAsyncCbData->cbFxn(codecAsyncCbData->cbData, &status);
    return;
}


/******************************************************************************/
/* End of file                                                                */
/******************************************************************************/
