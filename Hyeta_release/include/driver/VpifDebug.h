/*
 * VpifDebug.h
 *
 * This file is used for debugging VPIF and external devices like encoders and
 * decoders.
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
 *  \file   VpifDebug.h
 *
 *  \brief  This file contains macros for debugging of external devices
 */

#ifndef _VPIFDEBUG_H_
#define _VPIFDEBUG_H_

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */
#include <xdc/runtime/System.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

/* ========================================================================== */
/*                          MACRO DEFINITIONS                                 */
/* ========================================================================== */
/*#define ENABLE_VPIF_DEBUG*/
/*#define LOG_TRACE*/
/*#define ENABLE_VPIF_ERR_DEBUG*/
/*#define ENABLE_VPIF_INFO_DEBUG*/

#define VPIF_DEBUG(a)            System_printf(a)
#define VPIF_DEBUG1(a,b)         System_printf(a, b)
#define VPIF_DEBUG2(a,b,c)       System_printf(a, b, c)
#define VPIF_DEBUG3(a,b,c,d)     System_printf(a, b, c, d)

#define DBG_PRINT_ERR(a)        System_printf("*ERROR* Line: %d, File: %s - ", \
                                        __LINE__, __FILE__); \
                                System_printf(a);
#define DBG_PRINT_ERR1(a,b)     System_printf("*ERROR* Line: %d, File: %s - ", \
                                        __LINE__, __FILE__); \
                                System_printf(a,b);
#define DBG_PRINT_ERR2(a,b,c)   System_printf("*ERROR* Line: %d, File: %s - ", \
                                        __LINE__, __FILE__); \
                                System_printf(a,b,c);
#define DBG_PRINT_ERR3(a,b,c,d) System_printf("*ERROR* Line: %d, File: %s - ", \
                                        __LINE__, __FILE__); \
                                System_printf(a,b,c,d);
    
#define VPIF_INFO(a)            System_printf(a)
#define VPIF_INFO1(a,b)         System_printf(a,b)
#define VPIF_INFO2(a,b,c)       System_printf(a,b,c)
#define VPIF_INFO3(a,b,c,d)     System_printf(a,b,c,d)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* _VPIFDEBUG_H_ */

/******************************************************************************/
/* End of file                                                                */
/******************************************************************************/
