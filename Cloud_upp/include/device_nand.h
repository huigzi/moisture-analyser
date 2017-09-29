/*
 * TI Booting and Flashing Utilities
 *
 * Provides device differentiation for the project files. This file MUST be
 * modified to match the device specifics.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* --------------------------------------------------------------------------
  AUTHOR      : Daniel Allred
 --------------------------------------------------------------------------- */

#ifndef _DEVICE_NAND_H_
#define _DEVICE_NAND_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern "c" {	//extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

#define DEVICE_NAND_DATA_OFFSET         (0x00)
#define DEVICE_NAND_ALE_OFFSET          (0x08)
#define DEVICE_NAND_CLE_OFFSET          (0x10)
#define DEVICE_NAND_TIMEOUT             (10240)

#define DEVICE_NAND_MAX_BYTES_PER_OP       (512)   // Max Bytes per operation (EMIF IP constrained)
#define DEVICE_NAND_MAX_SPAREBYTES_PER_OP  (16)    // Max Spare Bytes per operation
#define DEVICE_NAND_MIN_SPAREBYTES_PER_OP  (10)    // Min Spare Bytes per operation (ECC operation constrained)

// Defines which NAND blocks the RBL will search in for a UBL image
#define DEVICE_NAND_RBL_SEARCH_START_BLOCK     (1)
#define DEVICE_NAND_ARM_UBL_SEARCH_START_BLOCK (2)
#define DEVICE_ARMBOOT_NAND_UBOOT_SEARCH_START_BLOCK   (2)
#define DEVICE_DSPBOOT_NAND_UBOOT_SEARCH_START_BLOCK   (4)
#define DEVICE_NAND_SEARCH_END_BLOCK           (24)

/******************************************************
* Global Typedef declarations                         *
******************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // End _DEVICE_NAND_H_

/* --------------------------------------------------------------------------
    HISTORY
       v1.00  -  DJA  -  04-Mar-2008
         Initial Release
 ----------------------------------------------------------------------------- */
