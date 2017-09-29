/*
 * MT9V024.c
 *
 * This file contains Driver Layer Interface implementation for MT9V024 sensor
 * driver. MT9V024 sensor driver provides Driver Layer Interface to do
 * operations on the MT9V024 sensor like open, close and control commands for
 * peripheral specific operations etc
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
 *  \file   MT9V024.c
 *
 *  \brief  This file contains interface functions for MT9V024 external Image
 *          Sensor.
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */
#include <xdc/std.h>
#include <ti/sysbios/io/iom.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <VpifDebug.h>

#include <Fvid.h>
#include <Edc.h>
#include <MT9V024.h>
#include <MT9V024Local.h>
#include <CodecInterfaceLocal.h>

/* ========================================================================== */
/*                          MACRO DEFINITIONS                                 */
/* ========================================================================== */
/** \brief Macro for lower byte mask */
//#define MT9V024_I2C_TXRX_DATA_MASK		        (0x00FF)
//#define MT9V024_I2C_ADDR_MASK		        (0x00FF)
/** \brief Macro for upper byte mask */
//#define MT9V024_I2C_TXRX_DATA_MASK_UPPER	    (0xFF00)
//#define MT9V024_I2C_ADDR_MASK_UPPER	    (0xFF00)
/** \brief Data shift macro for getting second byte */
//#define MT9V024_I2C_TXRX_DATA_SHIFT		        (8)
//#define MT9V024_I2C_ADDR_SHIFT		        (8)

/* ========================================================================== */
/*                        LOCAL FUNCTION PROTOTYPES                           */
/* ========================================================================== */
static Int32 MT9V024SetDefaultParams(MT9V024_SensorObj      *MT9V024handle,
                                     MT9V024_StandardFormat stdFormat);

//static Int32 MT9V024SetStd(MT9V024_SensorObj      *MT9V024handle,
//                           MT9V024_StandardFormat stdFormat);
//
//static Int32 MT9V024WriteReg(MT9V024_SensorObj *MT9V024handle,
//                             Edc_RegData *data);
//
//static Int32 MT9V024SetFormat(MT9V024_SensorObj    *MT9V024handle,
//                              MT9V024_FormatParams *MT9V024FmtParams);

static Int32 MT9V024PowerDown(MT9V024_SensorObj *MT9V024handle,
                              Bool powerDownEnable);

static Int32 MT9V024Reset(MT9V024_SensorObj *MT9V024handle);

/* ========================================================================== */
/*                            FUNCTION TABLE                                  */
/* ========================================================================== */
/** MT9V024 EDC function table */
static EDC_Handle MT9V024_open(String devName, Ptr optArg);
static Int32 MT9V024_close(EDC_Handle handle);
static Int32 MT9V024_ctrl(EDC_Handle handle, Uns cmd, Ptr param);

EDC_Fxns MT9V024_Fxns =
{
    &MT9V024_open,
    &MT9V024_close,
    &MT9V024_ctrl,
    NULL
};

/* ========================================================================== */
/*                            LOCAL VARIABLES                                 */
/* ========================================================================== */
/** Local structure array to contain channel objects, semaphore handles
 * and channel open count
 */
static MT9V024_SensorObj MT9V024Obj =
{
    "\0", Edc_ControlBusType_UNKNOWN, "\0", 0
};

/* ========================================================================== */
/*                      LOCAL FUNCTION DEFINITIONS                            */
/* ========================================================================== */
/**
 * \brief To configure MT9V024 default parameter
 */

//Uint16 dataBuf[256];

static Int32 MT9V024SetDefaultParams(MT9V024_SensorObj      *MT9V024handle,
                                     MT9V024_StandardFormat stdFormat)
{
    Uint8 setDefAddrI2c = 0, i;
    Uint32 setDefNumBytes = 2u;
    Bool setDefFlag;
    Int32 retVal = IOM_COMPLETED;

    Uint8 MT9V024AfterResetNTSCReg[][3] =
    {
        {MT9V024_SENSORTYPE_REG, 0x08,0x00},	//monochrome
        {MT9V024_COLUMNSTART_REG, 0x00,0x11},	//coloum start:17.752-720=32,32/2=16
        {MT9V024_ROWSTART_A_REG, 0x00,0x04},	//row start:4
        {MT9V024_WINDOWHEIGHT_A_REG, 0x01,0xE0},//height:480
        {MT9V024_WINDOWWIDTH_A_REG, 0x02,0xD0},	//width:720
        {MT9V024_TOTALSHUTWIDTH_A_REG, 0x03,0x7D},
        {MT9V024_AECAGCENABLE_REG, 0x00,0x00},
        //{MT9V024_COPANDING_REG, 0x00,0x03}//enable auto Exposure;Disable Automatic Gain
    };

    VPIF_DEBUG("Entered ---> MT9V024SetDefaultParams\n");
    assert(NULL != MT9V024handle);
    setDefAddrI2c = MT9V024handle->edcCtrlDeviceAddr;

//    codecReadReg16(MT9V024handle->edcCtrlBusType,
//                             setDefAddrI2c,
//                             0x0,
//                             dataBuf,
//                             256);

    for (i = 0; i < 7; i++)
    {
        setDefFlag |= codecWriteReg(MT9V024handle->edcCtrlBusType,
                         setDefAddrI2c,
                         MT9V024AfterResetNTSCReg[i][0],
                         &MT9V024AfterResetNTSCReg[i][1],
                         setDefNumBytes);
    }

    if (TRUE == setDefFlag)
    {
        DBG_PRINT_ERR("MT9V024: Error from MT9V024SetDefaultParams\n");
        retVal = IOM_EBADIO;
    }
    else
    {
        retVal = IOM_COMPLETED;
    }

    return retVal;
}


/**
 * \brief Write to MT9V024 Sensor
 */
//static Int32 MT9V024WriteReg(MT9V024_SensorObj *MT9V024handle,
//                             Edc_RegData *data)
//{
//    Int32 wStatus = IOM_COMPLETED;
//    Bool wFlag;
//    Uint32 i;
//
//    VPIF_DEBUG("Entered ---> MT9V024WriteReg\n");
//
//    assert(NULL != MT9V024handle);
//    assert(NULL != data);
//
//    for (i = 0; i < data->noRegToRW; i++)
//    {
//        wFlag = codecWriteReg(MT9V024handle->edcCtrlBusType,
//                    MT9V024handle->edcCtrlDeviceAddr,
//                    (Uint8)(data->startReg + i),
//                    data->value,
//                    2u);
////                    data->noRegToRW + 2u);
//        if (wFlag == TRUE)
//        {
//            DBG_PRINT_ERR("MT9V024: Error from MT9V024_ctrl\n");
//            wStatus = IOM_EBADIO;
//            break;
//        }
//        else
//        {
//            wStatus = IOM_COMPLETED;
//        }
//    }
//
//    VPIF_DEBUG("Exited ---> MT9V024WriteReg\n");
//    return wStatus;
//}


/**
 *  \brief  Power Up or Power Down MT9V024. Sets devices power state to
 *          requested state, if possible.
 *
 *  \param  MT9V024handle   [In] MT9V024 channel parameters
 *  \param  powerDownEnable [In] Flag to power-up or power-down MT9V024
 *
 *  \return IOM_COMPLETED on successful operation
 *          IOM_EBADARGS if error occurred
 */
static Int32 MT9V024PowerDown(MT9V024_SensorObj *MT9V024handle,
                              Bool powerDownEnable)
{
    Uint8 pwrDnBuffer[2] = {0, 0};
//    Uint16 pwrDnBuffer;	//ZZW
    Uint8 pwrDnAddrI2c = 0;
    Bool pwrDnFlag;
    Int32 retVal = IOM_COMPLETED;
    int i;

    VPIF_DEBUG("Entered ---> MT9V024PowerDown\n");
    VPIF_DEBUG2("MT9V024_SensorObj = 0x%0.8X, powerDownEnable = %d \n",
               MT9V024handle,
               powerDownEnable);

    assert(NULL != MT9V024handle);
    pwrDnAddrI2c = MT9V024handle->edcCtrlDeviceAddr;

    /* Write to Reset Register */
    pwrDnBuffer[0] = 0x00;
    pwrDnBuffer[1] = 0x01;	//reset
    pwrDnFlag = codecWriteReg(MT9V024handle->edcCtrlBusType,
                     pwrDnAddrI2c,
                     MT9V024_RESET_REG,
                     &pwrDnBuffer[0],
                     2u);

    /* Check for Power Up */
    if (FALSE == powerDownEnable)
    {
    	//delay for about 10ms;
    	for(i=0;i<100000;i++);
        /* Power Up Sequence */
        pwrDnBuffer[0] = 0x00;
        pwrDnBuffer[1] = 0x00;	//normal operation
        pwrDnFlag |= codecWriteReg(MT9V024handle->edcCtrlBusType,
                         pwrDnAddrI2c,
                         MT9V024_RESET_REG,
                         &pwrDnBuffer[0],
                         2u);
    }

    if (TRUE == pwrDnFlag)
    {
        DBG_PRINT_ERR("MT9V024: Error from MT9V024PowerDown\n");
        retVal = IOM_EBADIO;
    }
    else
    {
        retVal = IOM_COMPLETED;
    }
    VPIF_DEBUG("Exited ---> MT9V024PowerDown\n");
    return retVal;
}


/**
 *  \brief  Reset MT9V024
 *
 *  \param  MT9V024handle  [In]  MT9V024 channel parameters
 *
 *  \return IOM_COMPLETED on successful operation
 *          IOM_EBADARGS if error occurred
 */
static Int32 MT9V024Reset(MT9V024_SensorObj *MT9V024handle)
{
    /* Reset MT9V024 */
    return MT9V024PowerDown(MT9V024handle, FALSE);
}

/* ========================================================================== */
/*                     MT9V024 GLOBAL FUNCTION DEFINITIONS                    */
/* ========================================================================== */
/**
 *  \brief  MT9V024 Close
 *
 *  This Function is used to deinitialize the MT9V024 external image sensor.
 *
 *  \param  handle [IN]  Handle of MT9V024 driver
 *
 *  \return  Success    IOM_COMPLETED
 *           Error      IOM_EBADIO
 */
static Int32 MT9V024_close(EDC_Handle handle)
{
    MT9V024_SensorObj *closeDevObj;
    Int32 closeStatus = IOM_EBADARGS;

    VPIF_DEBUG("Entered ---> MT9V024_close\n");
    VPIF_DEBUG1("EDC_Handle = 0x%0.8x\n", handle);

    /* First Check if the Handle/params are correct */
    assert(NULL != handle);
    closeDevObj = (MT9V024_SensorObj *)handle;
    assert(MT9V024_IIC_ADDR == closeDevObj->edcCtrlDeviceAddr);
    assert(Edc_ControlBusType_UNKNOWN != closeDevObj->edcCtrlBusType);

    /*Put MT9V024 in power down mode */
    closeStatus = MT9V024PowerDown(closeDevObj, TRUE);
    if (IOM_COMPLETED == closeStatus)
    {
        /*close I2C channel*/
        closeStatus = deInitCodecInterface(closeDevObj->edcCtrlBusType);
    }
    memset(&MT9V024Obj, 0x0, sizeof(MT9V024_SensorObj));
    closeDevObj->edcCtrlBusType = Edc_ControlBusType_UNKNOWN;

    VPIF_DEBUG("Exited ---> MT9V024_close\n");
    return closeStatus;
}


/**
 *  \brief  MT9V024 Ioctls
 *
 *  This Function is to configure and change parameters of MT9V024 image sensor
 *  runtime.
 *
 *  \param  handle [IN]  Handle of MT9V024 image sensor
 *  \param  cmd    [IN]  IOCTL to be performed (mostly enum).
 *  \param  param  [IN]  Argument as required by Ioctl
 *
 *  \return  Success    IOM_COMPLETED
 *           Error      IOM_EBADIO
 */
static Int32 MT9V024_ctrl(EDC_Handle handle, Uns cmd, Ptr param)
{

    MT9V024_SensorObj *ctrlDevObj;
    Int32 mtCtrlStatus = IOM_COMPLETED;
    MT9V024_ConfParams *stdFmt;
    Edc_RegData *regRw = NULL;
    Bool tvpCtrlFlag;

    VPIF_DEBUG("Entered ---> MT9V024_ctrl\n");
    VPIF_DEBUG2("EDC_Handle = 0x%0.8X, Arg = 0x%0.8X\n", handle, param);

    /* First Check if the Handle/params are correct */
    assert(NULL != handle);
    ctrlDevObj = (MT9V024_SensorObj *)handle;
    assert(MT9V024_IIC_ADDR == ctrlDevObj->edcCtrlDeviceAddr);

    if (Edc_IOCTL_CONFIG == cmd)
    {
        VPIF_DEBUG("MT9V024: Command: Edc_IOCTL_CONFIG\n");
        assert(NULL != param);
        stdFmt = (MT9V024_ConfParams *)param;
//        if (NULL == stdFmt->fmtParams)
//        {
//            mtCtrlStatus = MT9V024SetStd(ctrlDevObj, stdFmt->stdFormat);
//        }
//        else
//        {
//            mtCtrlStatus = MT9V024SetFormat(ctrlDevObj, stdFmt->fmtParams);
//        }
    }
    else if (Edc_IOCTL_RESET == cmd)
    {
        VPIF_DEBUG("MT9V024: Command: Edc_IOCTL_RESET\n");
        mtCtrlStatus = MT9V024Reset(ctrlDevObj);
    }
    else if (Edc_IOCTL_SET_REG == cmd)
    {
        VPIF_DEBUG("MT9V024: Command: Edc_IOCTL_SET_REG\n");
        assert(NULL != param);
        //mtCtrlStatus = MT9V024WriteReg(ctrlDevObj, (Edc_RegData *)param);
        //ZZW
        regRw = (Edc_RegData *)param;
        assert(NULL != regRw);
        tvpCtrlFlag = codecWriteReg(ctrlDevObj->edcCtrlBusType,
        							ctrlDevObj->edcCtrlDeviceAddr,
        							regRw->startReg,
        							regRw->value,
        							regRw->noRegToRW);
        if (TRUE == tvpCtrlFlag)
        {
            DBG_PRINT_ERR("MT9V024: Error from MT9V024_ctrl\n");
            mtCtrlStatus = IOM_EBADIO;
        }
        else
        {
        	mtCtrlStatus = IOM_COMPLETED;
        }
    }
    else if (Edc_IOCTL_GET_REG == cmd)
    {
//        mtCtrlStatus = IOM_ENOTIMPL;
    	//ZZW
        VPIF_DEBUG("MT9V024: Command: Edc_IOCTL_GET_REG\n");
        assert(NULL != param);
        regRw = (Edc_RegData *)param;
        assert(NULL != regRw);
        tvpCtrlFlag = codecReadReg16(ctrlDevObj->edcCtrlBusType,
        							ctrlDevObj->edcCtrlDeviceAddr,
        							regRw->startReg,
        							regRw->value,
        							regRw->noRegToRW);
        if (TRUE == tvpCtrlFlag)
        {
            DBG_PRINT_ERR("MT9V024: Error from MT9V024_ctrl\n");
            mtCtrlStatus = IOM_EBADIO;
        }
        else
        {
        	mtCtrlStatus = IOM_COMPLETED;
        }

    }
    else
    {
        VPIF_DEBUG("MT9V024: Command: default\n");
        mtCtrlStatus = IOM_EBADARGS;
    }

    VPIF_DEBUG("Exited ---> MT9V024_ctrl\n");
    return mtCtrlStatus;
}


/**
 *  \brief  MT9V024 device open
 *
 *  This Function is used to initialize the MT9V024 external image sensor.
 *  It returns MT9V024 handle.
 *
 *  \param  devName [IN]  External device name
 *  \param  optArg  [IN]  Optional argument (not used here)
 *
 *  \return  handle  EDC channel handle when success
 *                   NULL when unsuccessful
 */
static EDC_Handle MT9V024_open(String devName, Ptr optArg)
{
    MT9V024_SensorObj *handle = NULL;
    Int8 MT9V024Str[20] = "MT9V024";
    Int8 i2cDevice[20] = "\0";
    Int8 senName[20] = "\0";
    /** Default configuration of MT9V024 */
    static MT9V024_StandardFormat openStdFormat = MT9V024_MODE_NTSC;

    VPIF_DEBUG("Entered ---> MT9V024_open\n");
    VPIF_DEBUG2("devName = %s, Arg = 0x%0.8X\n", devName, optArg);

    assert(NULL != devName);
    optArg = optArg; /* to remove compilation warning */
    /* Check if the address is correct */
    if (devName[0] != '/')
    {
        handle = (MT9V024_SensorObj *)NULL;
    }
    else
    {
        /*only copy 5 chars into positions 0-4 for /I2C0*/
        strncpy((char*)i2cDevice, devName, 5u);
        /* position 5 gets the terminator */
        i2cDevice[5] = '\0';

        devName += 5;
        /* Check if the address is correct*/
        if ('/' == devName[0])
        {
            devName++;
            /*only copy 6 chars into positions 0-5 for devName*/
            strncpy((char*)senName, devName, 7u); // strncpy(senName, devName, 6u);	//zzw
            /* position 7 gets the terminator */
            senName[7] = '\0';//senName[6] = '\0';	//

            devName += 7;	//devName += 6;	//
            /* Compare devName with "MT9V024" */
            if (0 == strcmp((char*)senName, MT9V024Str))
            {
                strncpy(MT9V024Obj.sensorName, MT9V024Str, 20u);
                /* check if already opened  */
                if (('/' == devName[0]) && (0 == MT9V024Obj.edcCtrlDeviceAddr))
                {
                    devName++;
                    MT9V024Obj.edcCtrlDeviceAddr = (Uint8)strtol(
                                                              devName + 2,
                                                              NULL,
                                                              16);
                    if (MT9V024_IIC_ADDR == MT9V024Obj.edcCtrlDeviceAddr)
                    {
                        strncpy(MT9V024Obj.edcCtrlBusName, i2cDevice, 20u);
                        if (0 == strcmp(i2cDevice, "/i2c0"))
                        {
                            MT9V024Obj.edcCtrlBusType = Edc_ControlBusType_I2C;
                        }
                        else
                        {
                            MT9V024Obj.edcCtrlBusType = \
                                Edc_ControlBusType_UNKNOWN;
                        }
                        /* assigning channel object structure */
                        handle = &MT9V024Obj;
                    }
                    else
                    {
                        /* wrong i2c address */
                        handle = (MT9V024_SensorObj *)NULL;
                        MT9V024Obj.sensorName[0] = '\0';
                    }

                }
                else
                {
                    /* no i2c address in the string or device already open*/
                    handle = (MT9V024_SensorObj *)NULL;
                    MT9V024Obj.sensorName[0] = '\0';
                }
            }
            else
            {
                /* Sensor name incorrect */
                handle = (MT9V024_SensorObj *)NULL;
            }
        }
        else
        {
            /* no Sensor name */
            handle = (MT9V024_SensorObj *)NULL;
        }
    }
    if (handle != NULL)
    {
        /* open I2C channel */
        if (IOM_COMPLETED != initCodecInterface(
                                (String)MT9V024Obj.edcCtrlBusName))
        {
            handle = (MT9V024_SensorObj *)NULL;
        }
        /* power on sensor */
        if (handle != NULL)
        {
            if (IOM_COMPLETED != MT9V024Reset(handle))
            {
                    deInitCodecInterface(MT9V024Obj.edcCtrlBusType);
                    handle = (MT9V024_SensorObj *)NULL;
                    MT9V024Obj.edcCtrlDeviceAddr = 0;
            }
            else
            {
                /* Configure MT9V024 for default video standard */
                if (IOM_COMPLETED != MT9V024SetDefaultParams(handle,
                                         openStdFormat))
                {
                    deInitCodecInterface(MT9V024Obj.edcCtrlBusType);
                    handle = (MT9V024_SensorObj *)NULL;
                    MT9V024Obj.edcCtrlDeviceAddr = 0;
                }
            }
        }
        else
        {
            DBG_PRINT_ERR("MT9V024: ERR ---> edcSensor_open\n");
        }
    }

    VPIF_DEBUG("Exited ---> MT9V024_open\n");
    return (EDC_Handle)handle;
}

/******************************************************************************/
/* End of file                                                                */
/******************************************************************************/
