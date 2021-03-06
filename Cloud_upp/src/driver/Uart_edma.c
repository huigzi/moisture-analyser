/*
 * Uart_edma.c
 *
 * This file contains local functions for the UART driver which contain implemen-
 * tation for EDMA operation specifc calls like starting an EDMA transfer for 
 * for UART peripheral, EDMA completion and/or error callbacks etc
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
 *  \file   uart_edma.c
 *
 *  \brief  This files contains the edma functions required for the Uart driver
 *          to function in the EDMA mode.
 *
 *
 *   (C) Copyright 2009, Texas Instruments, Inc
 *
 *
 *   \version 0.1     Newly created for C6748/OMAPL138 platform.
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */



#include <string.h>
#include <assert.h>

#include <xdc/std.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/iom.h>
#include <ti/sysbios/hal/Cache.h>

#include <ti/sdo/edma3/drv/edma3_drv.h>

#include <Uart.h>
#include <UartLocal.h>
#include <Psc.h>
#include <cslr/cslr_uart.h>

#ifdef CHIP_C6748
    #include <cslr/soc_C6748.h>
#endif

#ifdef CHIP_OMAPL138
    #include <cslr/soc_OMAPL138.h>
#endif

extern Uint32 Uart_edmaChanNum;
extern Uint16 Uart_dummyParamSetAddr;
/* ========================================================================== */
/*                        LOCAL FUNCTION PROTOTYPES                           */
/* ========================================================================== */

static Int32 uartStartEdmaTxTransfer(Uart_ChanObj *chanHandle);
static Int32 uartStartEdmaRxTransfer(Uart_ChanObj *chanHandle);

/* ========================================================================== */
/*                       FUNCTION DEFINITIONS                                 */
/* ========================================================================== */
/**
 *  \brief  Edma transfer
 *
 *          This function initiates Edma mode of operation
 *
 *  \note   As this function is also executed in interrupt context
 *          validation of the retVal is not done. Once this is tested
 *          there  should be no issues, unless DMA is changed
 *
 *  \param  chanHandle  [IN]  Handle of the Channel Object
 *  \param  cmd         [IN]  Read\Write cmd
 *
 *  \return If successful, returns IOM_COMPLETED else IOM Error code
 *
 *  \enter  chanHandle  must be a valid pointer and should not be null.
 *          cmd         must be a valid READ/WRITE command.
 *
 *  \leave  Not Implemented.
 *
 */

Int32 Uart_localStartEdmaTransfer(Uart_ChanObj *chanHandle, UInt32 cmd)
{
    Int32      retVal        = IOM_COMPLETED;

    assert(NULL != chanHandle);

    chanHandle->ioCompleted = FALSE;

    if (IOM_READ == cmd)
    {
        retVal = uartStartEdmaRxTransfer(chanHandle);
    }
    else if (IOM_WRITE == cmd)
    {
        retVal = uartStartEdmaTxTransfer(chanHandle);
    }
    else
    {
        retVal = IOM_ENOTIMPL;
    }

    return retVal;
}


/**
 *  \brief  Callback for the receive transaction
 *
 *          This function is the callback for the receive operation when
 *          it is completed
 *
 *  \param  tcc     [IN]   Handle of the Edma Object
 *  \param  status  [IN]   Error code returned by the Edma
 *  \param  appData [IN]   Data passed Edma during initiation
 *
 *  \return None
 *
 *  \enter  tcc       must be a valid interrupt event channel.
 *          status    must be a valid error code status.
 *          appData   must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 *
 */
Void Uart_localIsrEdma(UInt32 tcc, EDMA3_RM_TccStatus status, Ptr appData)
{
    Uart_ChanObj      *chanHandle  = NULL;
    Uart_Object       *instHandle  = NULL;
    UInt32             value       = 0;
    Bool               bFalseWhile = TRUE;
    UInt32             key         = 0;
#ifdef BIOS_PWRM_ENABLE
    Power_Status       retVal     = Power_SOK;
    UInt32             count      = 0x00;
#endif

    assert(NULL != appData);
    chanHandle = (Uart_ChanObj*)appData;

    assert(NULL != (chanHandle->devHandle));
    instHandle = (Uart_Object *)chanHandle->devHandle;

    assert(NULL != instHandle);
    
    /* To remove the compiler warning                                         */
    tcc = tcc;

    /* enter critical section                                         		  */
    key = (UInt32)_disable_interrupts();

    if (EDMA3_RM_XFER_COMPLETE == status)
    {
        chanHandle->ioCompleted = TRUE;
    }

    EDMA3_DRV_disableLogicalChannel(
         (EDMA3_DRV_Handle)chanHandle->hEdma,
         chanHandle->edmaChId,
         EDMA3_DRV_TRIG_MODE_EVENT);

    do
    {
	    /* Write into FCR (Disable only DMAMODE but do not clear the FIFO     *
	     * in UART														      */ 
	  	if (TRUE == instHandle->devParams.fifoEnable) 
	    {
	        value &= ~(CSL_UART_FCR_DMAMODE1_MASK | 
				CSL_UART_FCR_TXCLR_MASK   | 
				CSL_UART_FCR_RXCLR_MASK);
	    }
		/* Do not Disable FIFO	*/
		value |= CSL_UART_FCR_FIFOEN_MASK;

	 	(instHandle->deviceInfo.baseAddress)->FCR = value; 
	
		value = 0x00;
	
	    switch (instHandle->devParams.rxThreshold)
	    {
	        case Uart_RxTrigLvl_1:
	             value |= CSL_UART_FCR_RXFIFTL_CHAR1;
	             /* Receive FIFO trigger level 1 byte                     	  */
	             break;
	
	        case Uart_RxTrigLvl_4:
	             value |= CSL_UART_FCR_RXFIFTL_CHAR4
	                         << CSL_UART_FCR_RXFIFTL_SHIFT;
	             /* Receive FIFO trigger level 4 byte                     	  */
	             break;
	
	        case Uart_RxTrigLvl_8:
	             value |= CSL_UART_FCR_RXFIFTL_CHAR8
	                         << CSL_UART_FCR_RXFIFTL_SHIFT;
	             /* Receive FIFO trigger level 8 byte                     	  */
	             break;
	
	        case Uart_RxTrigLvl_14:
	             value |= CSL_UART_FCR_RXFIFTL_CHAR14
	                         << CSL_UART_FCR_RXFIFTL_SHIFT;
	             /* Receive FIFO trigger level 14 byte                    	  */
	             break;
	        default:
	        /* Cant be default. Becz already this param is validated      	  */
	            break;
	    }

		/* Re Enable DMA */
	    value |= (CSL_UART_FCR_DMAMODE1_MASK
					| CSL_UART_FCR_FIFOEN_MASK);

	    (instHandle->deviceInfo.baseAddress)->FCR = value;

        bFalseWhile = FALSE;

        if (EDMA3_RM_XFER_COMPLETE != status)
        {
            /* Ensure to clear the error bits of EDMA channel                 */
            EDMA3_DRV_clearErrorBits(chanHandle->hEdma,chanHandle->edmaChId);

            if (TRUE == chanHandle->ioCompleted)
            {
                break;
            }

            if (NULL != chanHandle->activeIOP)
            {
                /* Update the current errors status                           */
                chanHandle->errors++;
                Uart_localCompleteCurrentIO (chanHandle);
            }
        }
        else
        {
            if (Uart_INPUT == chanHandle->mode)
            {
                instHandle->stats.rxBytes += chanHandle->bytesRemaining;
            }
            else
            {
                instHandle->stats.txBytes += chanHandle->bytesRemaining;
            }

            chanHandle->ioCompleted = FALSE;

            if (NULL != chanHandle->activeIOP)
            {
                Uart_localCompleteCurrentIO (chanHandle);
            }
        }

#ifdef BIOS_PWRM_ENABLE
        if (FALSE == instHandle->pwrmInfo.ioSuspend)
        {
#endif
            Uart_loadPendedIops(chanHandle);
#ifdef BIOS_PWRM_ENABLE
        }
        else
        {
            if (TRUE == instHandle->devParams.pscPwrmEnable)
            {
                /* set the current active IOP as NULL                         */
                chanHandle->activeIOP = NULL;
                instHandle->devState = Uart_DriverState_PWRM_SUSPEND;

                if ((NULL == instHandle->rcvChanObj.activeIOP) &&
                    (NULL == instHandle->xmtChanObj.activeIOP))
                {
                    /* if both the channels are inactive then reset the       *
                     * io suspend flag                                        */
                    instHandle->pwrmInfo.ioSuspend = FALSE;
                    
                    if ((Power_GOINGTOSLEEP == instHandle->pwrmInfo.pwrmEvent) ||
                        (Power_GOINGTODEEPSLEEP == instHandle->pwrmInfo.pwrmEvent))
                    {
                        /* reduce the dependency count                            */
                        retVal = Power_getDependencyCount(
                                   (Power_Resource)instHandle->deviceInfo.pwrmLpscId,
                                    &count);
                    
                        instHandle->pwrmInfo.dependencyCount = count;
                    
                        if (Power_SOK == retVal)
                        {
                            while (count > 0)
                            {
                                retVal = Power_releaseDependency(
                                            (Power_Resource)
                                                instHandle->deviceInfo.pwrmLpscId);
                    
                                if (Power_SOK != retVal)
                                {
                                    break;
                                }
                                count--;
                            }
                        }
                    }
                                    
                    /* call the delayed completion function                   */
                    (instHandle->pwrmInfo.delayedCompletionFxn  \
                        [instHandle->pwrmInfo.pwrmEvent])();
                }
            }
        }
#endif        
    }while (bFalseWhile);

    /* exit critical section                                          		  */
    _restore_interrupts(key);
}

/**
 *  \brief  process the RX edma transfer start command
 *
 *          This function starts the RX side edma transfers
 *
 *  \param  chanHandle  [IN]   Handle to the channel
 *
 *  \return IOM_COMPLETED or error code
 *
 *  \enter  chanHandle  must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int32 uartStartEdmaRxTransfer(Uart_ChanObj *chanHandle)
{
    Int32               retVal      = IOM_COMPLETED;
    EDMA3_DRV_Handle    hEdma       = NULL;
    Uart_Object        *instHandle  = NULL;
    EDMA3_DRV_PaRAMRegs paramSet    = {0,0,0,0,0,0,0,0,0,0,0,0};

    assert(NULL != chanHandle);

    hEdma      = (EDMA3_DRV_Handle )chanHandle->hEdma;
    instHandle = (Uart_Object*)chanHandle->devHandle;

    assert((NULL != hEdma) && (NULL != instHandle));

    if (TRUE == instHandle->enableCache)
    {
        /* Move the data to physical memory and invalidate the cache line     */
        Cache_wbInv (
            (Ptr)chanHandle->activeBuf,
            (UInt32)chanHandle->bytesRemaining,
            Cache_Type_ALL,
            TRUE);
    }

    /* Get the PaRAM set for default parameters                               */
    EDMA3_DRV_getPaRAM ((EDMA3_DRV_Handle)hEdma, chanHandle->edmaChId, &paramSet);

    if (FALSE == chanHandle->optFlag)
    {
        chanHandle->optFlag  = TRUE;
        chanHandle->optValue = paramSet.opt;
    }
    paramSet.opt = chanHandle->optValue;

    paramSet.srcAddr   = (unsigned int)
                             (&((instHandle->deviceInfo.baseAddress)->RBR));
    paramSet.destAddr  = (unsigned int)(chanHandle->activeBuf);
    paramSet.aCnt       = 1;
    paramSet.bCnt       = instHandle->devParams.rxThreshold;
    paramSet.srcBIdx    = 0;
    paramSet.srcCIdx    = 0;
    paramSet.destBIdx   = 1;
    paramSet.destCIdx   = instHandle->devParams.rxThreshold;

    if (chanHandle->bytesRemaining <= 0xFFFF)
    {
        paramSet.cCnt  = 
            (Uint16)chanHandle->bytesRemaining/instHandle->devParams.rxThreshold;
    }
    else
    {
        retVal = IOM_EBADIO;
    }

    paramSet.bCntReload = 0;
    paramSet.linkAddr   = 0xFFFFu;

    /* Src is in CONST addr mode & Dest is in INCR addr modes                 */
    paramSet.opt &= 0xFFFFFFFDu;
    paramSet.opt |= 0x00000001u;

    /* FIFO width is 8 bit                                                    */
    paramSet.opt &= 0xFFFFF8FFu;

    /* EDMA3_DRV_SYNC_AB                                                      */
    paramSet.opt &= 0xFFFFFFFFu;
    paramSet.opt |= 0x00000004;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                            */
    paramSet.opt |= (1 << Uart_OPT_TCINTEN_SHIFT);

    if (IOM_COMPLETED == retVal)
    {
        /* Now, write the PaRAM Set.                                          */
        retVal = EDMA3_DRV_setPaRAM((EDMA3_DRV_Handle)hEdma, 
        						chanHandle->edmaChId, &paramSet);
    }

    if (IOM_COMPLETED != EDMA3_DRV_enableTransfer(
                             (EDMA3_DRV_Handle)hEdma,
                             chanHandle->edmaChId,
                             EDMA3_DRV_TRIG_MODE_EVENT))
    {
        retVal = IOM_EBADARGS;
    }
    return (retVal);
}


/**
 *  \brief  process the TX edma transfer start command
 *
 *          This function process the TX edma transfer starting.
 *
 *  \param  chanHandle  [IN]   Handle to the channel
 *
 *  \return IOM_COMPLETED or error code
 *
 *  \enter  chanHandle  must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
 static Int32 uartStartEdmaTxTransfer(Uart_ChanObj *chanHandle)
 {
    Int32               retVal      = IOM_COMPLETED;
    EDMA3_DRV_Handle    hEdma       = NULL;
    Uart_Object        *instHandle  = NULL;
    EDMA3_DRV_PaRAMRegs paramSet    = {0,0,0,0,0,0,0,0,0,0,0,0};

    assert(NULL != chanHandle);

    hEdma      = (EDMA3_DRV_Handle )chanHandle->hEdma;
    instHandle = (Uart_Object*)chanHandle->devHandle;

    assert((NULL != hEdma) && (NULL != instHandle));

    if (TRUE == instHandle->enableCache)
    {
        Cache_wb (
            (Ptr)chanHandle->activeBuf,
            chanHandle->bytesRemaining,
            Cache_Type_ALL,
            TRUE);
    }

    /* Get the PaRAM set for default parameters                               */
    EDMA3_DRV_getPaRAM ((EDMA3_DRV_Handle)hEdma, chanHandle->edmaChId, &paramSet);

    if (FALSE == chanHandle->optFlag)
    {
        chanHandle->optFlag  = TRUE;
        chanHandle->optValue = paramSet.opt;
    }
    paramSet.opt = chanHandle->optValue;

    paramSet.srcAddr   = (unsigned int)(chanHandle->activeBuf);
    paramSet.destAddr  = (unsigned int)
                             (&((instHandle->deviceInfo.baseAddress)->THR));

    paramSet.aCnt       = 1;
    paramSet.bCnt       = instHandle->devParams.softTxFifoThreshold;
    paramSet.srcBIdx    = 1;
    paramSet.srcCIdx    = instHandle->devParams.softTxFifoThreshold;
    paramSet.destBIdx   = 0;
    paramSet.destCIdx   = 0;

    if (chanHandle->bytesRemaining <= 0xFFFF)
    {
        paramSet.cCnt  = (Uint16)chanHandle->bytesRemaining/instHandle->devParams.softTxFifoThreshold;
    }
    else
    {
        retVal = IOM_EBADIO;
    }

    paramSet.bCntReload = 0;
    paramSet.linkAddr   = (Uint16)(Uart_dummyParamSetAddr & 0x0000FFFF);

    /* Src is in INCR mode & Dest is in FIFO modes                            */
    paramSet.opt &= 0xFFFFFFFEu;
    paramSet.opt |= 0x00000002u;

    /* FIFO width is 8 bit                                                    */
    paramSet.opt &= 0xFFFFF8FFu;

    /* EDMA3_DRV_SYNC_AB                                                      */
    paramSet.opt &= 0xFFFFFFFFu;
    paramSet.opt |= 0x00000004;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                            */
    paramSet.opt |= (1u << Uart_OPT_TCINTEN_SHIFT);

    if (IOM_COMPLETED == retVal)
    {
        /* Now, write the PaRAM Set.                                      */
        retVal = EDMA3_DRV_setPaRAM(hEdma, chanHandle->edmaChId, &paramSet);
    }

    retVal = EDMA3_DRV_getPaRAM (chanHandle->hEdma,
                        Uart_edmaChanNum,
                        &paramSet);

    paramSet.aCnt     = 1u;
    paramSet.linkAddr = 0xFFFF;
    paramSet.opt      &= ~(0x01 << 3);

    if (IOM_COMPLETED == retVal)
    {
        /* Now, write the dummy PaRAM Set.                                    */
        retVal = EDMA3_DRV_setPaRAM(chanHandle->hEdma,
                                    Uart_edmaChanNum,
                                    &paramSet);
    }

    if (IOM_COMPLETED == retVal)
    {
        retVal = EDMA3_DRV_linkChannel(chanHandle->hEdma,
                                   chanHandle->edmaChId,
                                   Uart_edmaChanNum);
    }
    
    if (IOM_COMPLETED == retVal)
    {
        /* In order not to modify the existing RX trigger settings (which     *
         * might have been already set and is in use we will reassign to      *
         * be sure that we are not modfying these values(Please note that     *
         * the RXFIFTL bit is only writable and also the system can work      *
         * in full duplex mode)                                               */
        if (IOM_COMPLETED != EDMA3_DRV_enableTransfer(
                               (EDMA3_DRV_Handle)hEdma,
                               chanHandle->edmaChId,
                               EDMA3_DRV_TRIG_MODE_EVENT))
        {
            retVal = IOM_EBADARGS;
        }
    }
    return (retVal);
}

/* ========================================================================== */
/*                            END OF FILE                                     */
/* ========================================================================== */
