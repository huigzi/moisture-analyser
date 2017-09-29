/*
 * MT9V024Local.h
 *
 * MT9V024 sensor Driver internal header file
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
 *  \file   MT9V024Local.h
 *
 *  \brief  MT9V024 external Image Sensor related parameters. This file contains
 *          the interfaces, data types and symbolic definitions that are
 *          required for the MT9V024 external image sensor interface.
 */

#ifndef _MT9V024LOCAL_H_
#define _MT9V024LOCAL_H_

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <Edc.h>
#include <MT9V024.h>

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

/* ========================================================================== */
/*                          MACRO DEFINITIONS                                 */
/* ========================================================================== */
/**\brief MT9V024 8bit I2C address.  */
#define MT9V024_IIC_ADDR                     (0xB8 >> 1)

/**
 *  \brief Defines for MT9V024 System Registers
 */
#define MT9V024_CHIPVER_REG            		(0x00u)
#define MT9V024_COLUMNSTART_REG           (0x01u)
#define MT9V024_ROWSTART_A_REG            (0x02u)
#define MT9V024_WINDOWHEIGHT_A_REG        (0x03u)
#define MT9V024_WINDOWWIDTH_A_REG         (0x04u)
#define MT9V024_HBLANK_A_REG            	(0x05u)
#define MT9V024_VBLANK_A_REG            	(0x06u)
#define MT9V024_CHIPCONTROL_REG           (0x07u)
#define MT9V024_SHUTWIDTH1_A_REG          (0x08u)
#define MT9V024_SHUTWIDTH2_A_REG          (0x09u)
#define MT9V024_SHUTWIDTHCTRL_A_REG       (0x0Au)
#define MT9V024_TOTALSHUTWIDTH_A_REG      (0x0Bu)
#define MT9V024_RESET_REG            			(0x0Cu)
#define MT9V024_READMODE_A_REG            (0x0Du)
#define MT9V024_READMODE_B_REG            (0x0Eu)
#define MT9V024_SENSORTYPE_REG            (0x0Fu)
#define MT9V024_LEDOUTCTRL_REG            (0x1Bu)
#define MT9V024_COPANDING_REG            	(0x1Cu)
#define MT9V024_VREFADCCTRL_REG           (0x2Cu)
#define MT9V024_V1_A_REG            			(0x31u)
#define MT9V024_V2_A_REG            			(0x32u)
#define MT9V024_V3_A_REG            			(0x33u)
#define MT9V024_V4_A_REG            			(0x34u)
#define MT9V024_ANALOGGAIN_A_REG          (0x35u)
#define MT9V024_ANALOGGAIN_B_REG          (0x36u)
#define MT9V024_V1_B_REG            			(0x39u)
#define MT9V024_V2_B_REG            			(0x3Au)
#define MT9V024_V3_B_REG            			(0x3Bu)
#define MT9V024_V4_B_REG            			(0x3Cu)
#define MT9V024_FRAMEDARKAVG_REG          (0x42u)
#define MT9V024_DARKAVGTHRES_REG          (0x46u)
#define MT9V024_BLCALIBCTRL_REG           (0x47u)
#define MT9V024_BLCVALUE_REG            	(0x48u)
#define MT9V024_BLCSTEPSIZE_REG           (0x4Cu)
#define MT9V024_ROWNOISECORRCTRL_REG      (0x70u)
#define MT9V024_ROWNOISECONST_REG         (0x71u)
#define MT9V024_PIXCLKCTRL_REG            (0x72u)
#define MT9V024_DIGITALTEST_REG           (0x7Fu)
#define MT9V024_GAINX0Y0_REG            	(0x80u)
#define MT9V024_GAINX1Y0_REG            	(0x81u)
#define MT9V024_GAINX2Y0_REG            	(0x82u)
#define MT9V024_GAINX3Y0_REG            	(0x83u)
#define MT9V024_GAINX4Y0_REG            	(0x84u)
#define MT9V024_GAINX0Y1_REG            	(0x85u)
#define MT9V024_GAINX1Y1_REG            	(0x86u)
#define MT9V024_GAINX2Y1_REG            	(0x87u)
#define MT9V024_GAINX3Y1_REG            	(0x88u)
#define MT9V024_GAINX4Y1_REG            	(0x89u)
#define MT9V024_GAINX0Y2_REG            	(0x8Au)
#define MT9V024_GAINX1Y2_REG            	(0x8Bu)
#define MT9V024_GAINX2Y2_REG            	(0x8Cu)
#define MT9V024_GAINX3Y2_REG            	(0x8Du)
#define MT9V024_GAINX4Y2_REG            	(0x8Eu)
#define MT9V024_GAINX0Y3_REG            	(0x8Fu)
#define MT9V024_GAINX1Y3_REG            	(0x90u)
#define MT9V024_GAINX2Y3_REG            	(0x91u)
#define MT9V024_GAINX3Y3_REG            	(0x92u)
#define MT9V024_GAINX4Y3_REG            	(0x93u)
#define MT9V024_GAINX0Y4_REG            	(0x94u)
#define MT9V024_GAINX1Y4_REG            	(0x95u)
#define MT9V024_GAINX2Y4_REG            	(0x96u)
#define MT9V024_GAINX3Y4_REG            	(0x97u)
#define MT9V024_GAINX4Y4_REG            	(0x98u)
#define MT9V024_TILECOORDX0_REG           (0x99u)
#define MT9V024_TILECOORDX1_REG           (0x9Au)
#define MT9V024_TILECOORDX2_REG           (0x9Bu)
#define MT9V024_TILECOORDX3_REG           (0x9Cu)
#define MT9V024_TILECOORDX4_REG           (0x9Du)
#define MT9V024_TILECOORDX5_REG           (0x9Eu)
#define MT9V024_TILECOORDY0_REG           (0x9Fu)
#define MT9V024_TILECOORDY1_REG           (0xA0u)
#define MT9V024_TILECOORDY2_REG           (0xA1u)
#define MT9V024_TILECOORDY3_REG           (0xA2u)
#define MT9V024_TILECOORDY4_REG           (0xA3u)
#define MT9V024_TILECOORDY5_REG           (0xA4u)
#define MT9V024_AECAGCDESIREBIN_REG       (0xA5u)
#define MT9V024_AECUPDATEFREQ_REG         (0xA6u)
#define MT9V024_AECLPF_REG            		(0xA8u)
#define MT9V024_AECUPDATEFREQ_REG         (0xA9u)
#define MT9V024_AGCLPF_REG            	  (0xAAu)
#define MT9V024_MAXANALOGGAIN_REG         (0xABu)
#define MT9V024_AECMINEXPOSURE_REG        (0xACu)
#define MT9V024_AECMAXEXPOSURE_REG        (0xADu)
#define MT9V024_BINDIFFTHRES_REG          (0xAEu)
#define MT9V024_AECAGCENABLE_REG          (0xAFu)
#define MT9V024_AECAGCPIXCOUNT_REG        (0xB0u)
#define MT9V024_LVDSMASTERCTRL_REG        (0xB1u)
#define MT9V024_LVDSSHIFTCLKCTRL_REG      (0xB2u)
#define MT9V024_LVDSDATACTRL_REG          (0xB3u)
#define MT9V024_DATASTREAMLATENCY_REG     (0xB4u)
#define MT9V024_LVDSINTERSYNC_REG         (0xB5u)
#define MT9V024_LVDSPAYLOADCTRL_REG       (0xB6u)
#define MT9V024_STEREOERRORCTRL_REG       (0xB7u)
#define MT9V024_STEREOERRORFLAG_REG       (0xB8u)
#define MT9V024_LVDSDATAOUTPUT_REG        (0xB9u)
#define MT9V024_AGCGAINOUTPUT_REG         (0xBAu)
#define MT9V024_AECGAINOUTPUT_REG         (0xBBu)
#define MT9V024_AGCAECCURRENTBIN_REG      (0xBCu)
#define MT9V024_INTERFILEDBLANK_REG       (0xBFu)
#define MT9V024_MONMODECAPTURECTRL_REG    (0xC0u)
#define MT9V024_ANTIECLIPSECTRL_REG       (0xC2u)
#define MT9V024_NTSCFVLVCTRL_REG      		(0xC6u)
#define MT9V024_NTSCHORIZBLANKCTRL_REG    (0xC7u)
#define MT9V024_NTSCVERTBLANKCTRL_REG     (0xC8u)
#define MT9V024_COLUMNSTART_B_REG      		(0xC9u)
#define MT9V024_ROWSTART_B_REG            (0xCAu)
#define MT9V024_WINDOWHEIGHT_B_REG        (0xCBu)
#define MT9V024_WINDOWWIDTH_B_REG         (0xCCu)
#define MT9V024_HBLANK_B_REG            	(0xCDu)
#define MT9V024_VBLANK_B_REG            	(0xCEu)
#define MT9V024_SHUTWIDTH1_B_REG          (0xCFu)
#define MT9V024_SHUTWIDTH2_B_REG          (0xD0u)
#define MT9V024_SHUTWIDTHCTRL_B_REG       (0xD1u)
#define MT9V024_TOTALSHUTWIDTH_B_REG      (0xD2u)
#define MT9V024_FINESW1_A_REG      				(0xD3u)
#define MT9V024_FINESW2_A_REG      				(0xD4u)
#define MT9V024_FINETOTALSHUTWIDTH_A_REG  (0xD5u)
#define MT9V024_FINESW1_B_REG      				(0xD6u)
#define MT9V024_FINESW2_B_REG      				(0xD7u)
#define MT9V024_FINETOTALSHUTWIDTH_B_REG  (0xD8u)
#define MT9V024_MONITORMODE_REG      			(0xD9u)
#define MT9V024_BYTEWISEADDR_REG      		(0xF0u)
#define MT9V024_REGISTERLOCK_REG      		(0xFEu)


/* ========================================================================== */
/*                              STRUCTURES                                    */
/* ========================================================================== */
/**
 *  \brief Instance State object
 *  Sensor object structure for MT9V024 external Image Sensor
 */
typedef struct MT9V024_SensorObj_t
{
    Int8                    sensorName[20];
    /**< Sensor name                                                          */
    Edc_ControlBusType      edcCtrlBusType;
    /**< Type of the control bus (SPI or I2C)                                 */
    Int8                    edcCtrlBusName[20];
    /**< Control bus (I2C or SPI) name                                        */
    Uint8                   edcCtrlDeviceAddr;
    /**< Sensor Control bus address                                           */
}MT9V024_SensorObj;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef _MT9V024LOCAL_H_ */

/******************************************************************************/
/* End of file                                                                */
/******************************************************************************/
