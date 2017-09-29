

/**
 *  @Component:   PRM
 *
 *  @Filename:    ../../CredDataBase/prcmCRED/prm_per_cred.h
 *
 ============================================================================ */
/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
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



#ifndef _HW_PRM_PER_H_
#define _HW_PRM_PER_H_


/***********************************************************************\
 * Register arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundle arrays Definition
\***********************************************************************/


/***********************************************************************\
 * Bundles Definition
\***********************************************************************/



/*************************************************************************\
 * Registers Definition
\*************************************************************************/

#define PRM_PER_RM_PER_RSTCTRL   (0x0)
#define PRM_PER_RM_PER_RSTST   (0x4)
#define PRM_PER_PM_PER_PWRSTST   (0x8)
#define PRM_PER_PM_PER_PWRSTCTRL   (0xc)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/* RM_PER_RSTCTRL */
#define PRM_PER_RM_PER_RSTCTRL_ICSS_LRST   (0x00000002u)
#define PRM_PER_RM_PER_RSTCTRL_ICSS_LRST_SHIFT   (0x00000001u)
#define PRM_PER_RM_PER_RSTCTRL_ICSS_LRST_ASSERT   (0x1u)
#define PRM_PER_RM_PER_RSTCTRL_ICSS_LRST_CLEAR   (0x0u)

#define PRM_PER_RM_PER_RSTCTRL_PCI_LRST   (0x00000001u)
#define PRM_PER_RM_PER_RSTCTRL_PCI_LRST_SHIFT   (0x00000000u)
#define PRM_PER_RM_PER_RSTCTRL_PCI_LRST_ASSERT   (0x1u)
#define PRM_PER_RM_PER_RSTCTRL_PCI_LRST_CLEAR   (0x0u)


/* RM_PER_RSTST */
#define PRM_PER_RM_PER_RSTST_PCI_LRST   (0x00000020u)
#define PRM_PER_RM_PER_RSTST_PCI_LRST_SHIFT   (0x00000005u)
#define PRM_PER_RM_PER_RSTST_PCI_LRST_RESET_NO   (0x0u)
#define PRM_PER_RM_PER_RSTST_PCI_LRST_RESET_YES   (0x1u)


/* PM_PER_PWRSTST */
#define PRM_PER_PM_PER_PWRSTST_ICSS_MEM_STATEST   (0x01800000u)
#define PRM_PER_PM_PER_PWRSTST_ICSS_MEM_STATEST_SHIFT   (0x00000017u)
#define PRM_PER_PM_PER_PWRSTST_ICSS_MEM_STATEST_MEM_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTST_ICSS_MEM_STATEST_MEM_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTST_ICSS_MEM_STATEST_RESERVED   (0x2u)

#define PRM_PER_PM_PER_PWRSTST_INTRANSITION   (0x00100000u)
#define PRM_PER_PM_PER_PWRSTST_INTRANSITION_SHIFT   (0x00000014u)
#define PRM_PER_PM_PER_PWRSTST_INTRANSITION_NO   (0x0u)
#define PRM_PER_PM_PER_PWRSTST_INTRANSITION_ONGOING   (0x1u)

#define PRM_PER_PM_PER_PWRSTST_LOGICSTATEST   (0x00000004u)
#define PRM_PER_PM_PER_PWRSTST_LOGICSTATEST_SHIFT   (0x00000002u)
#define PRM_PER_PM_PER_PWRSTST_LOGICSTATEST_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTST_LOGICSTATEST_ON   (0x1u)

#define PRM_PER_PM_PER_PWRSTST_PER_MEM_STATEST   (0x00060000u)
#define PRM_PER_PM_PER_PWRSTST_PER_MEM_STATEST_SHIFT   (0x00000011u)
#define PRM_PER_PM_PER_PWRSTST_PER_MEM_STATEST_MEM_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTST_PER_MEM_STATEST_MEM_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTST_PER_MEM_STATEST_RESERVED   (0x2u)

#define PRM_PER_PM_PER_PWRSTST_POWERSTATEST   (0x00000003u)
#define PRM_PER_PM_PER_PWRSTST_POWERSTATEST_SHIFT   (0x00000000u)
#define PRM_PER_PM_PER_PWRSTST_POWERSTATEST_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTST_POWERSTATEST_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTST_POWERSTATEST_RESERVED1   (0x2u)
#define PRM_PER_PM_PER_PWRSTST_POWERSTATEST_RET   (0x1u)

#define PRM_PER_PM_PER_PWRSTST_RAM_MEM_STATEST   (0x00600000u)
#define PRM_PER_PM_PER_PWRSTST_RAM_MEM_STATEST_SHIFT   (0x00000015u)
#define PRM_PER_PM_PER_PWRSTST_RAM_MEM_STATEST_MEM_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTST_RAM_MEM_STATEST_MEM_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTST_RAM_MEM_STATEST_RESERVED   (0x2u)


/* PM_PER_PWRSTCTRL */
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_ONSTATE   (0x00000060u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_ONSTATE_SHIFT   (0x00000005u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_ONSTATE_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_ONSTATE_RESERVED   (0x2u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_ONSTATE_RESERVED1   (0x1u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_ONSTATE_RESERVED2   (0x0u)

#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_RETSTATE   (0x00000080u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_RETSTATE_SHIFT   (0x00000007u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_RETSTATE_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTCTRL_ICSS_MEM_RETSTATE_RET   (0x1u)

#define PRM_PER_PM_PER_PWRSTCTRL_LOGICRETSTATE   (0x00000008u)
#define PRM_PER_PM_PER_PWRSTCTRL_LOGICRETSTATE_SHIFT   (0x00000003u)
#define PRM_PER_PM_PER_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET   (0x1u)

#define PRM_PER_PM_PER_PWRSTCTRL_LOWPOWERSTATECHANGE   (0x00000010u)
#define PRM_PER_PM_PER_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT   (0x00000004u)
#define PRM_PER_PM_PER_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS   (0x0u)
#define PRM_PER_PM_PER_PWRSTCTRL_LOWPOWERSTATECHANGE_EN   (0x1u)

#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_ONSTATE   (0x06000000u)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_ONSTATE_SHIFT   (0x00000019u)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_ONSTATE_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_ONSTATE_RESERVED   (0x2u)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_ONSTATE_RESERVED1   (0x1u)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_ONSTATE_RESERVED2   (0x0u)

#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_RETSTATE   (0x20000000u)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_RETSTATE_SHIFT   (0x0000001Du)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_RETSTATE_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTCTRL_PER_MEM_RETSTATE_RET   (0x1u)

#define PRM_PER_PM_PER_PWRSTCTRL_POWERSTATE   (0x00000003u)
#define PRM_PER_PM_PER_PWRSTCTRL_POWERSTATE_SHIFT   (0x00000000u)
#define PRM_PER_PM_PER_PWRSTCTRL_POWERSTATE_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTCTRL_POWERSTATE_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTCTRL_POWERSTATE_RESERVED   (0x2u)
#define PRM_PER_PM_PER_PWRSTCTRL_POWERSTATE_RET   (0x1u)

#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_ONSTATE   (0xC0000000u)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_ONSTATE_SHIFT   (0x0000001Eu)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_ONSTATE_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_ONSTATE_ON   (0x3u)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_ONSTATE_RESERVED   (0x2u)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_ONSTATE_RET   (0x1u)

#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_RETSTATE   (0x08000000u)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_RETSTATE_SHIFT   (0x0000001Bu)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_RETSTATE_OFF   (0x0u)
#define PRM_PER_PM_PER_PWRSTCTRL_RAM_MEM_RETSTATE_RET   (0x1u)



#endif
