/**
 *   \file  hw_prcm_C6A811x.h
 *
 *   \brief This file contains the PRCM information for C6A811x SoC
 *
 *
 */

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


#ifndef _HW_PRCM_C6A811X_H_
#define _HW_PRCM_C6A811X_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************\
 * Register Definition Macros
\*************************************************************************/

/** @brief PRM_DEVICE register offsets */
#define PRM_DEVICE_PRM_RSTCTRL          (0xA0)
#define PRM_DEVICE_PRM_RSTTIME          (0xA4)
#define PRM_DEVICE_PRM_RSTST            (0xA8)

/** @brief CM_DEVICE register offsets */
#define CM_DEVICE_CM_CLKOUT_CTRL        (0x0)

/** @brief OCP_SOCKET_PRM register offsets */
#define OCP_SOCKET_PRM_REVISION_PRM     (0x0)

/** @brief CM_DPLL register offsets */
#define CM_DPLL_CM_SYSCLK3_CLKSEL       (0x8)
#define CM_DPLL_CM_SYSCLK10_CLKSEL      (0x24)
#define CM_DPLL_CM_VPB3_CLKSEL          (0x40)
#define CM_DPLL_CM_VPC1_CLKSEL          (0x44)
#define CM_DPLL_CM_VPD1_CLKSEL          (0x48)
#define CM_DPLL_CM_SYSCLK19_CLKSEL      (0x4C)
#define CM_DPLL_CM_SYSCLK20_CLKSEL      (0x50)
#define CM_DPLL_CM_SYSCLK21_CLKSEL      (0x54)
#define CM_DPLL_CM_SYSCLK22_CLKSEL      (0x58)
#define CM_DPLL_CM_APA_CLKSEL           (0x5C)
#define CM_DPLL_CM_SYSCLK14_CLKSEL      (0x70)
#define CM_DPLL_CM_SYSCLK16_CLKSEL      (0x74)
#define CM_DPLL_CM_SYSCLK18_CLKSEL      (0x78)
#define CM_DPLL_CM_AUDIOCLK_MCASP0_CLKSEL   (0x7C)
#define CM_DPLL_CM_AUDIOCLK_MCASP1_CLKSEL   (0x80)
#define CM_DPLL_CM_AUDIOCLK_MCASP2_CLKSEL   (0x84)
#define CM_DPLL_CM_AUDIOCLK_MCBSP_CLKSEL    (0x88)
#define CM_DPLL_CM_HDMI_CLKSEL          (0xAC)
#define CM_DPLL_CM_SYSCLK23_CLKSEL      (0xB0)

/** @brief CM_ACTIVE register offsets */
#define CM_ACTIVE_CM_GEM_CLKSTCTRL      (0x0)
#define CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL (0x20)

/** @brief CM_DEFAULT register offsets */
#define CM_DEFAULT_DMM_CLKCTRL          (0x28)
#define CM_DEFAULT_TPPSS_CLKCTRL        (0x54)
#define CM_DEFAULT_USB_CLKCTRL          (0x58)
#define CM_DEFAULT_DUCATI_CLKCTRL       (0x60)
#define CM_DEFAULT_PCI_CLKCTRL          (0x78)

/** @brief CM_DSS register offsets */
#define CM_DSS_CLKSTCTRL                (0x0)
#define CM_DSS_DSS_CLKCTRL              (0x20)
#define CM_DSS_HDMI_CLKCTRL             (0x24)

/** @brief CM_SGX register offsets */
#define CM_SGX_CLKSTCTRL                (0x0)
#define CM_SGX_SGX_CLKCTRL              (0x20)

/** @brief PRM_ACTIVE register offsets */
#define PRM_ACTIVE_PWRSTCTRL            (0x0)
#define PRM_ACTIVE_PWRSTST              (0x4)
#define PRM_ACTIVE_RSTCTRL              (0x10)
#define PRM_ACTIVE_RSTST                (0x14)

/** @brief PRM_DEFAULT register offsets */
#define PRM_DEFAULT_PWRSTCTRL           (0x0)
#define PRM_DEFAULT_RSTCTRL             (0x10)
#define PRM_DEFAULT_RSTST               (0x14)

/** @brief PRM_DSS register offsets */
#define PRM_DSS_PWRSTCTRL               (0x0)
#define PRM_DSS_PWRSTST                 (0x4)
#define PRM_DSS_RSTCTRL                 (0x10)
#define PRM_DSS_RSTST                   (0x14)

/** @brief PRM_SGX register offsets */
#define PRM_SGX_PWRSTCTRL               (0x0)
#define PRM_SGX_RSTCTRL                 (0x4)
#define PRM_SGX_PWRSTST                 (0x10)
#define PRM_SGX_RSTST                   (0x14)

/** @brief CM_ALWON register offsets */
#define CM_ALWON_L3_SLOW_CLKSTCTRL      (0x0)
#define CM_ALWON_ETHERNET_CLKSTCTRL     (0x4)
#define CM_ALWON_L3_MED_CLKSTCTRL       (0x8)
#define CM_ALWON_MMU_CLKSTCTRL          (0xC)
#define CM_ALWON_MMUCFG_CLKSTCTRL       (0x10)
#define CM_ALWON_OCMC_0_CLKSTCTRL       (0x14)
#define CM_ALWON_VCP_CLKSTCTRL          (0x18)
#define CM_ALWON_MPU_CLKSTCTRL          (0x1C)
#define CM_ALWON_SYSCLK4_CLKSTCTRL      (0x20)
#define CM_ALWON_SYSCLK5_CLKSTCTRL      (0x24)
#define CM_ALWON_SYSCLK6_CLKSTCTRL      (0x28)
#define CM_ALWON_RTC_CLKSTCTRL          (0x2C)
#define CM_ALWON_L3_FAST_CLKSTCTRL      (0x30)
#define CM_ALWON_MCASP0_CLKCTRL         (0x140)
#define CM_ALWON_MCASP1_CLKCTRL         (0x144)
#define CM_ALWON_MCASP2_CLKCTRL         (0x148)
#define CM_ALWON_MCBSP_CLKCTRL          (0x14C)
#define CM_ALWON_UART_0_CLKCTRL         (0x150)
#define CM_ALWON_UART_1_CLKCTRL         (0x154)
#define CM_ALWON_UART_2_CLKCTRL         (0x158)
#define CM_ALWON_GPIO_0_CLKCTRL         (0x15C)
#define CM_ALWON_GPIO_1_CLKCTRL         (0x160)
#define CM_ALWON_I2C_0_CLKCTRL          (0x164)
#define CM_ALWON_I2C_1_CLKCTRL          (0x168)
#define CM_ALWON_MCASP_3_4_5_CLKCTRL    (0x16C)
#define CM_ALWON_ATL_CLKCTRL            (0x170)
#define CM_ALWON_MLB_CLKCTRL            (0x174)
#define CM_ALWON_PATA_CLKCTRL           (0x178)
#define CM_ALWON_TIMER_4_CLKCTRL        (0x17C)
#define CM_ALWON_UART_3_CLKCTRL         (0x180)
#define CM_ALWON_UART_4_CLKCTRL         (0x184)
#define CM_ALWON_UART_5_CLKCTRL         (0x188)
#define CM_ALWON_WDTIMER_CLKCTRL        (0x18C)
#define CM_ALWON_SPI_CLKCTRL            (0x190)
#define CM_ALWON_MAILBOX_CLKCTRL        (0x194)
#define CM_ALWON_SPINBOX_CLKCTRL        (0x198)
#define CM_ALWON_MMUDATA_CLKCTRL        (0x19C)
#define CM_ALWON_MMUCFG_CLKCTRL         (0x1A8)
#define CM_ALWON_SDIO_CLKCTRL           (0x1B0)
#define CM_ALWON_OCMC_0_CLKCTRL         (0x1B4)
#define CM_ALWON_VCP_CLKCTRL            (0x1B8)
#define CM_ALWON_SMARTCARD_0_CLKCTRL    (0x1BC)
#define CM_ALWON_SMARTCARD_1_CLKCTRL    (0x1C0)
#define CM_ALWON_CONTROL_CLKCTRL        (0x1C4)
#define CM_ALWON_SECSS_CLKCTRL          (0x1C8)
#define CM_ALWON_GPMC_CLKCTRL           (0x1D0)
#define CM_ALWON_ETHERNET_0_CLKCTRL     (0x1D4)
#define CM_ALWON_MPU_CLKCTRL            (0x1DC)
#define CM_ALWON_DEBUGSS_CLKCTRL        (0x1E0)
#define CM_ALWON_L3_CLKCTRL             (0x1E4)
#define CM_ALWON_L4HS_CLKCTRL           (0x1E8)
#define CM_ALWON_L4LS_CLKCTRL           (0x1EC)
#define CM_ALWON_RTC_CLKCTRL            (0x1F0)
#define CM_ALWON_TPCC_CLKCTRL           (0x1F4)
#define CM_ALWON_TPTC0_CLKCTRL          (0x1F8)
#define CM_ALWON_TPTC1_CLKCTRL          (0x1FC)
#define CM_ALWON_TPTC2_CLKCTRL          (0x200)
#define CM_ALWON_TPTC3_CLKCTRL          (0x204)
#define CM_ALWON_SR_0_CLKCTRL           (0x208)
#define CM_ALWON_SR_1_CLKCTRL           (0x20C)
#define CM_ALWON_SR_2_CLKCTRL           (0x210)
#define CM_ALWON_SR_3_CLKCTRL           (0x214)
#define CM_ALWON_DCAN_0_1_CLKCTRL       (0x218)
#define CM_ALWON_MMCHS_0_CLKCTRL        (0x21C)
#define CM_ALWON_MMCHS_1_CLKCTRL        (0x220)
#define CM_ALWON_MMCHS_2_CLKCTRL        (0x224)
#define CM_ALWON_CUST_EFUSE_CLKCTRL     (0x228)

/** @brief PRM_ALWON register offsets */
#define PRM_ALWON_RSTST                 (0x14)

/**************************************************************************\ 
 * Field Definition Macros
\**************************************************************************/

/** @brief PRM_DEVICE_PRM_RSTCTRL register fields */

#define PRM_DEVICE_PRM_RSTCTRL_RST_GLOBAL_COLD_SW   (0x00000002u)
#define PRM_DEVICE_PRM_RSTCTRL_RST_GLOBAL_COLD_SW_SHIFT (0x1u)

#define PRM_DEVICE_PRM_RSTCTRL_RST_GLOBAL_WARM_SW   (0x00000001u)
#define PRM_DEVICE_PRM_RSTCTRL_RST_GLOBAL_WARM_SW_SHIFT (0x0u)

/** @brief PRM_DEVICE_PRM_RSTTIME register fields */

#define PRM_DEVICE_PRM_RSTTIME_RSTTIME2             (0x00001F00u)
#define PRM_DEVICE_PRM_RSTTIME_RSTTIME2_SHIFT       (0x8u)

#define PRM_DEVICE_PRM_RSTTIME_RSTTIME1             (0x000000FFu)
#define PRM_DEVICE_PRM_RSTTIME_RSTTIME1_SHIFT       (0x0u)

/** @brief PRM_DEVICE_PRM_RSTST register fields */

#define PRM_DEVICE_PRM_RSTST_ICEPICK_RST            (0x00000200u)
#define PRM_DEVICE_PRM_RSTST_ICEPICK_RST_SHIFT      (0x9u)

#define PRM_DEVICE_PRM_RSTST_EXTERNAL_WARM_RST      (0x00000020u)
#define PRM_DEVICE_PRM_RSTST_EXTERNAL_WARM_RST_SHIFT    (0x5u)

#define PRM_DEVICE_PRM_RSTST_SECURE_WDT_RST         (0x00000010u)
#define PRM_DEVICE_PRM_RSTST_SECURE_WDT_RST_SHIFT   (0x4u)

#define PRM_DEVICE_PRM_RSTST_MPU_WDT_RST            (0x00000008u)
#define PRM_DEVICE_PRM_RSTST_MPU_WDT_RST_SHIFT      (0x3u)

#define PRM_DEVICE_PRM_RSTST_MPU_SECURITY_VIOL_RST  (0x00000004u)
#define PRM_DEVICE_PRM_RSTST_MPU_SECURITY_VIOL_RST_SHIFT    (0x2u)

#define PRM_DEVICE_PRM_RSTST_GLOBAL_WARM_SW_RST     (0x00000002u)
#define PRM_DEVICE_PRM_RSTST_GLOBAL_WARM_SW_RST_SHIFT   (0x1u)

#define PRM_DEVICE_PRM_RSTST_GLOBAL_COLD_RST        (0x00000001u)
#define PRM_DEVICE_PRM_RSTST_GLOBAL_COLD_RST_SHIFT  (0x0u)

/** @brief CM_DEVICE_CM_CLKOUT_CTRL register fields */

#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN          (0x00000080u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2EN_SHIFT    (0x7u)

#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV         (0x00000038u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2DIV_SHIFT   (0x3u)

#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE      (0x00000003u)
#define CM_DEVICE_CM_CLKOUT_CTRL_CLKOUT2SOURCE_SHIFT    (0x0u)

/** @brief OCP_SOCKET_PRM_REVISION_PRM register fields */

#define OCP_SOCKET_PRM_REVISION_PRM_Rev             (0x000000FFu)
#define OCP_SOCKET_PRM_REVISION_PRM_Rev_SHIFT       (0x0u)

/** @brief CM_DPLL_CM_SYSCLK3_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK3_CLKSEL_CLKSEL            (0x00000007u)
#define CM_DPLL_CM_SYSCLK3_CLKSEL_CLKSEL_SHIFT      (0x0u)

/** @brief CM_DPLL_CM_SYSCLK10_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK10_CLKSEL_CLKSEL           (0x00000007u)
#define CM_DPLL_CM_SYSCLK10_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_VPB3_CLKSEL register fields */

#define CM_DPLL_CM_VPB3_CLKSEL_CLKSEL               (0x00000003u)
#define CM_DPLL_CM_VPB3_CLKSEL_CLKSEL_SHIFT         (0x0u)

/** @brief CM_DPLL_CM_VPC1_CLKSEL register fields */

#define CM_DPLL_CM_VPC1_CLKSEL_CLKSEL               (0x00000003u)
#define CM_DPLL_CM_VPC1_CLKSEL_CLKSEL_SHIFT         (0x0u)

/** @brief CM_DPLL_CM_VPD1_CLKSEL register fields */

#define CM_DPLL_CM_VPD1_CLKSEL_CLKSEL               (0x00000007u)
#define CM_DPLL_CM_VPD1_CLKSEL_CLKSEL_SHIFT         (0x0u)

/** @brief CM_DPLL_CM_SYSCLK19_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK19_CLKSEL_CLKSEL           (0x00000007u)
#define CM_DPLL_CM_SYSCLK19_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_SYSCLK20_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK20_CLKSEL_CLKSEL           (0x00000007u)
#define CM_DPLL_CM_SYSCLK20_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_SYSCLK21_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK21_CLKSEL_CLKSEL           (0x00000007u)
#define CM_DPLL_CM_SYSCLK21_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_SYSCLK22_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK22_CLKSEL_CLKSEL           (0x00000007u)
#define CM_DPLL_CM_SYSCLK22_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_APA_CLKSEL register fields */

#define CM_DPLL_CM_APA_CLKSEL_CLKSEL                (0x00000007u)
#define CM_DPLL_CM_APA_CLKSEL_CLKSEL_SHIFT          (0x0u)

/** @brief CM_DPLL_CM_SYSCLK14_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK14_CLKSEL_CLKSEL           (0x00000003u)
#define CM_DPLL_CM_SYSCLK14_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_SYSCLK16_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK16_CLKSEL_CLKSEL           (0x00000001u)
#define CM_DPLL_CM_SYSCLK16_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_SYSCLK18_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK18_CLKSEL_CLKSEL           (0x00000001u)
#define CM_DPLL_CM_SYSCLK18_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_DPLL_CM_AUDIOCLK_MCASP0_CLKSEL register fields */

#define CM_DPLL_CM_AUDIOCLK_MCASP0_CLKSEL_CLKSEL    (0x00000003u)
#define CM_DPLL_CM_AUDIOCLK_MCASP0_CLKSEL_CLKSEL_SHIFT  (0x0u)

/** @brief CM_DPLL_CM_AUDIOCLK_MCASP1_CLKSEL register fields */

#define CM_DPLL_CM_AUDIOCLK_MCASP1_CLKSEL_CLKSEL    (0x00000003u)
#define CM_DPLL_CM_AUDIOCLK_MCASP1_CLKSEL_CLKSEL_SHIFT  (0x0u)

/** @brief CM_DPLL_CM_AUDIOCLK_MCASP2_CLKSEL register fields */

#define CM_DPLL_CM_AUDIOCLK_MCASP2_CLKSEL_CLKSEL    (0x00000003u)
#define CM_DPLL_CM_AUDIOCLK_MCASP2_CLKSEL_CLKSEL_SHIFT  (0x0u)

/** @brief CM_DPLL_CM_AUDIOCLK_MCBSP_CLKSEL register fields */

#define CM_DPLL_CM_AUDIOCLK_MCBSP_CLKSEL_CLKSEL     (0x00000003u)
#define CM_DPLL_CM_AUDIOCLK_MCBSP_CLKSEL_CLKSEL_SHIFT   (0x0u)

/** @brief CM_DPLL_CM_HDMI_CLKSEL register fields */

#define CM_DPLL_CM_HDMI_CLKSEL_CLKSEL               (0x00000003u)
#define CM_DPLL_CM_HDMI_CLKSEL_CLKSEL_SHIFT         (0x0u)

/** @brief CM_DPLL_CM_SYSCLK23_CLKSEL register fields */

#define CM_DPLL_CM_SYSCLK23_CLKSEL_CLKSEL           (0x00000007u)
#define CM_DPLL_CM_SYSCLK23_CLKSEL_CLKSEL_SHIFT     (0x0u)

/** @brief CM_ACTIVE_CM_GEM_CLKSTCTRL register fields */

#define CM_ACTIVE_CM_GEM_CLKSTCTRL_CLKTRCTRL        (0x00000003u)
#define CM_ACTIVE_CM_GEM_CLKSTCTRL_CLKTRCTRL_SHIFT  (0x0u)

/** @brief CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL register fields */

#define CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL_STBYST      (0x00040000u)
#define CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL_STBYST_SHIFT    (0x12u)

#define CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL_IDLEST      (0x00030000u)
#define CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL_IDLEST_SHIFT    (0x10u)

#define CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL_MODULEMODE  (0x00000003u)
#define CM_ACTIVE_CM_ACTIVE_GEM_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_DEFAULT_DMM_CLKCTRL register fields */

#define CM_DEFAULT_DMM_CLKCTRL_IDLEST               (0x00030000u)
#define CM_DEFAULT_DMM_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_DEFAULT_DMM_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_DEFAULT_DMM_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_DEFAULT_TPPSS_CLKCTRL register fields */

#define CM_DEFAULT_TPPSS_CLKCTRL_STBYST             (0x00040000u)
#define CM_DEFAULT_TPPSS_CLKCTRL_STBYST_SHIFT       (0x12u)

#define CM_DEFAULT_TPPSS_CLKCTRL_IDLEST             (0x00030000u)
#define CM_DEFAULT_TPPSS_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_DEFAULT_TPPSS_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_DEFAULT_TPPSS_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_DEFAULT_USB_CLKCTRL register fields */

#define CM_DEFAULT_USB_CLKCTRL_STBYST               (0x00040000u)
#define CM_DEFAULT_USB_CLKCTRL_STBYST_SHIFT         (0x12u)

#define CM_DEFAULT_USB_CLKCTRL_IDLEST               (0x00030000u)
#define CM_DEFAULT_USB_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_DEFAULT_USB_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_DEFAULT_USB_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_DEFAULT_DUCATI_CLKCTRL register fields */

#define CM_DEFAULT_DUCATI_CLKCTRL_STBYST            (0x00040000u)
#define CM_DEFAULT_DUCATI_CLKCTRL_STBYST_SHIFT      (0x12u)

#define CM_DEFAULT_DUCATI_CLKCTRL_IDLEST            (0x00030000u)
#define CM_DEFAULT_DUCATI_CLKCTRL_IDLEST_SHIFT      (0x10u)

#define CM_DEFAULT_DUCATI_CLKCTRL_MODULEMODE        (0x00000003u)
#define CM_DEFAULT_DUCATI_CLKCTRL_MODULEMODE_SHIFT  (0x0u)

/** @brief CM_DEFAULT_PCI_CLKCTRL register fields */

#define CM_DEFAULT_PCI_CLKCTRL_STBYST               (0x00040000u)
#define CM_DEFAULT_PCI_CLKCTRL_STBYST_SHIFT         (0x12u)

#define CM_DEFAULT_PCI_CLKCTRL_IDLEST               (0x00030000u)
#define CM_DEFAULT_PCI_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_DEFAULT_PCI_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_DEFAULT_PCI_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_DSS_CLKSTCTRL register fields */

#define CM_DSS_CLKSTCTRL_CLKTRCTRL                  (0x00000003u)
#define CM_DSS_CLKSTCTRL_CLKTRCTRL_SHIFT            (0x0u)

/** @brief CM_DSS_DSS_CLKCTRL register fields */

#define CM_DSS_DSS_CLKCTRL_STBYST                   (0x00040000u)
#define CM_DSS_DSS_CLKCTRL_STBYST_SHIFT             (0x12u)

#define CM_DSS_DSS_CLKCTRL_IDLEST                   (0x00030000u)
#define CM_DSS_DSS_CLKCTRL_IDLEST_SHIFT             (0x10u)

#define CM_DSS_DSS_CLKCTRL_MODULEMODE               (0x00000003u)
#define CM_DSS_DSS_CLKCTRL_MODULEMODE_SHIFT         (0x0u)

/** @brief CM_DSS_HDMI_CLKCTRL register fields */

#define CM_DSS_HDMI_CLKCTRL_IDLEST                  (0x00030000u)
#define CM_DSS_HDMI_CLKCTRL_IDLEST_SHIFT            (0x10u)

#define CM_DSS_HDMI_CLKCTRL_MODULEMODE              (0x00000003u)
#define CM_DSS_HDMI_CLKCTRL_MODULEMODE_SHIFT        (0x0u)

/** @brief CM_SGX_CLKSTCTRL register fields */

#define CM_SGX_CLKSTCTRL_CLKACTIVITY_SGX_GCLK       (0x00000100u)
#define CM_SGX_CLKSTCTRL_CLKACTIVITY_SGX_GCLK_SHIFT (0x8u)

#define CM_SGX_CLKSTCTRL_CLKTRCTRL                  (0x00000003u)
#define CM_SGX_CLKSTCTRL_CLKTRCTRL_SHIFT            (0x0u)

/** @brief CM_SGX_SGX_CLKCTRL register fields */

#define CM_SGX_SGX_CLKCTRL_STBYST                   (0x00040000u)
#define CM_SGX_SGX_CLKCTRL_STBYST_SHIFT             (0x12u)

#define CM_SGX_SGX_CLKCTRL_IDLEST                   (0x00030000u)
#define CM_SGX_SGX_CLKCTRL_IDLEST_SHIFT             (0x10u)

#define CM_SGX_SGX_CLKCTRL_MODULEMODE               (0x00000003u)
#define CM_SGX_SGX_CLKCTRL_MODULEMODE_SHIFT         (0x0u)

/** @brief PRM_ACTIVE_PWRSTCTRL register fields */

#define PRM_ACTIVE_PWRSTCTRL_Active_MEM_ONState     (0x00030000u)
#define PRM_ACTIVE_PWRSTCTRL_Active_MEM_ONState_SHIFT   (0x10u)

#define PRM_ACTIVE_PWRSTCTRL_LowPowerStateChange    (0x00000010u)
#define PRM_ACTIVE_PWRSTCTRL_LowPowerStateChange_SHIFT  (0x4u)

#define PRM_ACTIVE_PWRSTCTRL_PowerState             (0x00000003u)
#define PRM_ACTIVE_PWRSTCTRL_PowerState_SHIFT       (0x0u)

/** @brief PRM_ACTIVE_PWRSTST register fields */

#define PRM_ACTIVE_PWRSTST_InTransition             (0x00100000u)
#define PRM_ACTIVE_PWRSTST_InTransition_SHIFT       (0x14u)

#define PRM_ACTIVE_PWRSTST_Active_MEM_StateSt       (0x00000030u)
#define PRM_ACTIVE_PWRSTST_Active_MEM_StateSt_SHIFT (0x4u)

#define PRM_ACTIVE_PWRSTST_LogicStateSt             (0x00000004u)
#define PRM_ACTIVE_PWRSTST_LogicStateSt_SHIFT       (0x2u)

#define PRM_ACTIVE_PWRSTST_PowerStateSt             (0x00000003u)
#define PRM_ACTIVE_PWRSTST_PowerStateSt_SHIFT       (0x0u)

/** @brief PRM_ACTIVE_RSTCTRL register fields */

#define PRM_ACTIVE_RSTCTRL_GEM_SW_RST               (0x00000002u)
#define PRM_ACTIVE_RSTCTRL_GEM_SW_RST_SHIFT         (0x1u)

#define PRM_ACTIVE_RSTCTRL_GEM_LRST                 (0x00000001u)
#define PRM_ACTIVE_RSTCTRL_GEM_LRST_SHIFT           (0x0u)

/** @brief PRM_ACTIVE_RSTST register fields */

#define PRM_ACTIVE_RSTST_EMULATION_GEM_RST          (0x00000010u)
#define PRM_ACTIVE_RSTST_EMULATION_GEM_RST_SHIFT    (0x4u)

#define PRM_ACTIVE_RSTST_GEM_LRST_REQ               (0x00000008u)
#define PRM_ACTIVE_RSTST_GEM_LRST_REQ_SHIFT         (0x3u)

#define PRM_ACTIVE_RSTST_GEM_GRST                   (0x00000002u)
#define PRM_ACTIVE_RSTST_GEM_GRST_SHIFT             (0x1u)

#define PRM_ACTIVE_RSTST_GEM_LRST                   (0x00000001u)
#define PRM_ACTIVE_RSTST_GEM_LRST_SHIFT             (0x0u)

/** @brief PRM_DEFAULT_PWRSTCTRL */

#define PRM_DEFAULT_PWRSTCTRL_POWERSTATE            (0x00000003u)
#define PRM_DEFAULT_PWRSTCTRL_POWERSTATE_SHIFT      (0x0u)

/** @brief PRM_DEFAULT_RSTCTRL register fields */

#define PRM_DEFAULT_RSTCTRL_PCI_LRST                (0x00000080u)
#define PRM_DEFAULT_RSTCTRL_PCI_LRST_SHIFT          (0x7u)

#define PRM_DEFAULT_RSTCTRL_DUCATI_RST3             (0x00000010u)
#define PRM_DEFAULT_RSTCTRL_DUCATI_RST3_SHIFT       (0x4u)

#define PRM_DEFAULT_RSTCTRL_DUCATI_M3_RST2          (0x00000008u)
#define PRM_DEFAULT_RSTCTRL_DUCATI_M3_RST2_SHIFT    (0x3u)

#define PRM_DEFAULT_RSTCTRL_DUCATI_M3_RST1          (0x00000004u)
#define PRM_DEFAULT_RSTCTRL_DUCATI_M3_RST1_SHIFT    (0x2u)

#define PRM_DEFAULT_RSTCTRL_TPPSS_SW_RST            (0x00000002u)
#define PRM_DEFAULT_RSTCTRL_TPPSS_SW_RST_SHIFT      (0x1u)

#define PRM_DEFAULT_RSTCTRL_TPPSS_LRST              (0x00000001u)
#define PRM_DEFAULT_RSTCTRL_TPPSS_LRST_SHIFT        (0x0u)

/** @brief PRM_DEFAULT_RSTST register fields */

#define PRM_DEFAULT_RSTST_ICECRUSHER_m3_2_RST       (0x00004000u)
#define PRM_DEFAULT_RSTST_ICECRUSHER_m3_2_RST_SHIFT (0xEu)

#define PRM_DEFAULT_RSTST_ICECRUSHER_M3_1_RST       (0x00002000u)
#define PRM_DEFAULT_RSTST_ICECRUSHER_M3_1_RST_SHIFT (0xDu)

#define PRM_DEFAULT_RSTST_EMULATION_M3_2_RST        (0x00001000u)
#define PRM_DEFAULT_RSTST_EMULATION_M3_2_RST_SHIFT  (0xCu)

#define PRM_DEFAULT_RSTST_EMULATION_M3_1_RST        (0x00000800u)
#define PRM_DEFAULT_RSTST_EMULATION_M3_1_RST_SHIFT  (0xBu)

#define PRM_DEFAULT_RSTST_ICECRUSHER_TPPSS_RST      (0x00000400u)
#define PRM_DEFAULT_RSTST_ICECRUSHER_TPPSS_RST_SHIFT    (0xAu)

#define PRM_DEFAULT_RSTST_EMULATION_TPPSS_RST       (0x00000200u)
#define PRM_DEFAULT_RSTST_EMULATION_TPPSS_RST_SHIFT (0x9u)

#define PRM_DEFAULT_RSTST_PCI_LRST                  (0x00000080u)
#define PRM_DEFAULT_RSTST_PCI_LRST_SHIFT            (0x7u)

#define PRM_DEFAULT_RSTST_DUCATI_RST3               (0x00000010u)
#define PRM_DEFAULT_RSTST_DUCATI_RST3_SHIFT         (0x4u)

#define PRM_DEFAULT_RSTST_DUCATI_M3_RST2            (0x00000008u)
#define PRM_DEFAULT_RSTST_DUCATI_M3_RST2_SHIFT      (0x3u)

#define PRM_DEFAULT_RSTST_DUCATI_M3_RST1            (0x00000004u)
#define PRM_DEFAULT_RSTST_DUCATI_M3_RST1_SHIFT      (0x2u)

#define PRM_DEFAULT_RSTST_TPPSS_RST                 (0x00000002u)
#define PRM_DEFAULT_RSTST_TPPSS_RST_SHIFT           (0x1u)

#define PRM_DEFAULT_RSTST_TPPSS_LRST                (0x00000001u)
#define PRM_DEFAULT_RSTST_TPPSS_LRST_SHIFT          (0x0u)

/** @brief PRM_DSS_PWRSTCTRL register fields */

#define PRM_DSS_PWRSTCTRL_DSS_MEM_ONState           (0x00030000u)
#define PRM_DSS_PWRSTCTRL_DSS_MEM_ONState_SHIFT     (0x10u)

#define PRM_DSS_PWRSTCTRL_LowPowerStateChange       (0x00000010u)
#define PRM_DSS_PWRSTCTRL_LowPowerStateChange_SHIFT (0x4u)

#define PRM_DSS_PWRSTCTRL_PowerState                (0x00000003u)
#define PRM_DSS_PWRSTCTRL_PowerState_SHIFT          (0x0u)

/** @brief PRM_DSS_PWRSTST register fields */

#define PRM_DSS_PWRSTST_InTransition                (0x00100000u)
#define PRM_DSS_PWRSTST_InTransition_SHIFT          (0x14u)

#define PRM_DSS_PWRSTST_DSS_MEM_StateSt             (0x00000030u)
#define PRM_DSS_PWRSTST_DSS_MEM_StateSt_SHIFT       (0x4u)

#define PRM_DSS_PWRSTST_LogicStateSt                (0x00000004u)
#define PRM_DSS_PWRSTST_LogicStateSt_SHIFT          (0x2u)

#define PRM_DSS_PWRSTST_PowerStateSt                (0x00000003u)
#define PRM_DSS_PWRSTST_PowerStateSt_SHIFT          (0x0u)

/** @brief PRM_DSS_RSTCTRL register fields */

#define PRM_DSS_RSTCTRL_DSS_RST                     (0x00000004u)
#define PRM_DSS_RSTCTRL_DSS_RST_SHIFT               (0x2u)

/** @brief PRM_DSS_RSTST register fields */

#define PRM_DSS_RSTST_DSS_RST                       (0x00000004u)
#define PRM_DSS_RSTST_DSS_RST_SHIFT                 (0x2u)

/** @brief PRM_SGX_PWRSTCTRL register fields */

#define PRM_SGX_PWRSTCTRL_SGX_MEM_ONState           (0x00030000u)
#define PRM_SGX_PWRSTCTRL_SGX_MEM_ONState_SHIFT     (0x10u)

#define PRM_SGX_PWRSTCTRL_LowPowerStateChange       (0x00000010u)
#define PRM_SGX_PWRSTCTRL_LowPowerStateChange_SHIFT (0x4u)

#define PRM_SGX_PWRSTCTRL_PowerState                (0x00000003u)
#define PRM_SGX_PWRSTCTRL_PowerState_SHIFT          (0x0u)

/** @brief PRM_SGX_RSTCTRL register fields */

#define PRM_SGX_RSTCTRL_SGX_RST                     (0x00000001u)
#define PRM_SGX_RSTCTRL_SGX_RST_SHIFT               (0x0u)

/** @brief PRM_SGX_PWRSTST register fields */

#define PRM_SGX_PWRSTST_InTransition                (0x00100000u)
#define PRM_SGX_PWRSTST_InTransition_SHIFT          (0x14u)

#define PRM_SGX_PWRSTST_SGX_MEM_StateSt             (0x00000030u)
#define PRM_SGX_PWRSTST_SGX_MEM_StateSt_SHIFT       (0x4u)

#define PRM_SGX_PWRSTST_LogicStateSt                (0x00000004u)
#define PRM_SGX_PWRSTST_LogicStateSt_SHIFT          (0x2u)

#define PRM_SGX_PWRSTST_PowerStateSt                (0x00000003u)
#define PRM_SGX_PWRSTST_PowerStateSt_SHIFT          (0x0u)

/** @brief PRM_SGX_RSTST register fields */

#define PRM_SGX_RSTST_SGX_RST                       (0x00000001u)
#define PRM_SGX_RSTST_SGX_RST_SHIFT                 (0x0u)

/** @brief CM_ALWON_L3_SLOW_CLKSTCTRL register fields */

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_SDIO_CLKADPI_GCLK    (0x08000000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_SDIO_CLKADPI_GCLK_SHIFT  (0x1Bu)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK  (0x04000000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK_SHIFT    (0x1Au)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER6_GCLK  (0x02000000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER6_GCLK_SHIFT    (0x19u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER5_GCLK  (0x01000000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER5_GCLK_SHIFT    (0x18u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER4_GCLK  (0x00800000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER4_GCLK_SHIFT    (0x17u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER3_GCLK  (0x00400000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER3_GCLK_SHIFT    (0x16u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK  (0x00200000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER2_GCLK_SHIFT    (0x15u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER1_GCLK  (0x00100000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER1_GCLK_SHIFT    (0x14u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER0_GCLK  (0x00080000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_TIMER0_GCLK_SHIFT    (0x13u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_SPI_GSYSCLK  (0x00020000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_SPI_GSYSCLK_SHIFT    (0x11u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_I2C_GSYSCLK  (0x00010000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_I2C_GSYSCLK_SHIFT    (0x10u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK    (0x00008000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_GPIO_1_GDBCLK_SHIFT  (0xFu)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_GPIO_0_GDBCLK    (0x00004000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_GPIO_0_GDBCLK_SHIFT  (0xEu)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_UART_GFCLK   (0x00002000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_UART_GFCLK_SHIFT (0xDu)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCBSP_AUX_GCLK   (0x00001000u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCBSP_AUX_GCLK_SHIFT (0xCu)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCASP2_AUX_GCLK  (0x00000800u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCASP2_AUX_GCLK_SHIFT    (0xBu)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCASP1_AUX_GCLK  (0x00000400u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCASP1_AUX_GCLK_SHIFT    (0xAu)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCASP0_AUX_GCLK  (0x00000200u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKACTIVITY_MCASP0_AUX_GCLK_SHIFT    (0x9u)

#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKTRCTRL        (0x00000003u)
#define CM_ALWON_L3_SLOW_CLKSTCTRL_CLKTRCTRL_SHIFT  (0x0u)

/** @brief CM_ALWON_ETHERNET_CLKSTCTRL register fields */

#define CM_ALWON_ETHERNET_CLKSTCTRL_CLKTRCTRL       (0x00000003u)
#define CM_ALWON_ETHERNET_CLKSTCTRL_CLKTRCTRL_SHIFT (0x0u)

/** @brief CM_ALWON_L3_MED_CLKSTCTRL register fields */

#define CM_ALWON_L3_MED_CLKSTCTRL_CLKTRCTRL         (0x00000003u)
#define CM_ALWON_L3_MED_CLKSTCTRL_CLKTRCTRL_SHIFT   (0x0u)

/** @brief CM_ALWON_MMU_CLKSTCTRL register fields */

#define CM_ALWON_MMU_CLKSTCTRL_CLKACTIVITY_MMU_GCLK (0x00000100u)
#define CM_ALWON_MMU_CLKSTCTRL_CLKACTIVITY_MMU_GCLK_SHIFT   (0x8u)

#define CM_ALWON_MMU_CLKSTCTRL_CLKTRCTRL            (0x00000003u)
#define CM_ALWON_MMU_CLKSTCTRL_CLKTRCTRL_SHIFT      (0x0u)

/** @brief CM_ALWON_MMUCFG_CLKSTCTRL register fields */

#define CM_ALWON_MMUCFG_CLKSTCTRL_CLKACTIVITY_MMU_CFG_GCLK  (0x00000100u)
#define CM_ALWON_MMUCFG_CLKSTCTRL_CLKACTIVITY_MMU_CFG_GCLK_SHIFT    (0x8u)

#define CM_ALWON_MMUCFG_CLKSTCTRL_CLKTRCTRL         (0x00000003u)
#define CM_ALWON_MMUCFG_CLKSTCTRL_CLKTRCTRL_SHIFT   (0x0u)

/** @brief CM_ALWON_OCMC_0_CLKSTCTRL register fields */

#define CM_ALWON_OCMC_0_CLKSTCTRL_CLKACTIVITY_VCP_GCLK  (0x00000100u)
#define CM_ALWON_OCMC_0_CLKSTCTRL_CLKACTIVITY_VCP_GCLK_SHIFT    (0x8u)

#define CM_ALWON_OCMC_0_CLKSTCTRL_CLKTRCTRL         (0x00000003u)
#define CM_ALWON_OCMC_0_CLKSTCTRL_CLKTRCTRL_SHIFT   (0x0u)

/** @brief CM_ALWON_VCP_CLKSTCTRL register fields */

#define CM_ALWON_VCP_CLKSTCTRL_CLKACTIVITY_OCMC_1_GCLK  (0x00000100u)
#define CM_ALWON_VCP_CLKSTCTRL_CLKACTIVITY_OCMC_1_GCLK_SHIFT    (0x8u)

#define CM_ALWON_VCP_CLKSTCTRL_CLKTRCTRL            (0x00000003u)
#define CM_ALWON_VCP_CLKSTCTRL_CLKTRCTRL_SHIFT      (0x0u)

/** @brief CM_ALWON_MPU_CLKSTCTRL register fields */

#define CM_ALWON_MPU_CLKSTCTRL_CLKTRCTRL            (0x00000003u)
#define CM_ALWON_MPU_CLKSTCTRL_CLKTRCTRL_SHIFT      (0x0u)

/** @brief CM_ALWON_SYSCLK4_CLKSTCTRL register fields */

#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_L3_F_EN_GCLK (0x00000800u)
#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_L3_F_EN_GCLK_SHIFT   (0xBu)

#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_L3_S_GCLK    (0x00000400u)
#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_L3_S_GCLK_SHIFT  (0xAu)

#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_L3_M_GCLK    (0x00000200u)
#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_L3_M_GCLK_SHIFT  (0x9u)

#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_SYSCLK4_GCLK (0x00000100u)
#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKACTIVITY_SYSCLK4_GCLK_SHIFT   (0x8u)

#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKTRCTRL        (0x00000003u)
#define CM_ALWON_SYSCLK4_CLKSTCTRL_CLKTRCTRL_SHIFT  (0x0u)

/** @brief CM_ALWON_SYSCLK5_CLKSTCTRL register fields */

#define CM_ALWON_SYSCLK5_CLKSTCTRL_CLKACTIVITY_DEBUG_CLKA_GCLK  (0x00000200u)
#define CM_ALWON_SYSCLK5_CLKSTCTRL_CLKACTIVITY_DEBUG_CLKA_GCLK_SHIFT    (0x9u)

#define CM_ALWON_SYSCLK5_CLKSTCTRL_CLKACTIVITY_SYSCLK5_GCLK (0x00000100u)
#define CM_ALWON_SYSCLK5_CLKSTCTRL_CLKACTIVITY_SYSCLK5_GCLK_SHIFT   (0x8u)

#define CM_ALWON_SYSCLK5_CLKSTCTRL_CLKTRCTRL        (0x00000003u)
#define CM_ALWON_SYSCLK5_CLKSTCTRL_CLKTRCTRL_SHIFT  (0x0u)

/** @brief CM_ALWON_SYSCLK6_CLKSTCTRL register fields */

#define CM_ALWON_SYSCLK6_CLKSTCTRL_CLKACTIVITY_SYSCLK6_GCLK (0x00000100u)
#define CM_ALWON_SYSCLK6_CLKSTCTRL_CLKACTIVITY_SYSCLK6_GCLK_SHIFT   (0x8u)

#define CM_ALWON_SYSCLK6_CLKSTCTRL_CLKTRCTRL        (0x00000003u)
#define CM_ALWON_SYSCLK6_CLKSTCTRL_CLKTRCTRL_SHIFT  (0x0u)

/** @brief CM_ALWON_RTC_CLKSTCTRL register fields */

#define CM_ALWON_RTC_CLKSTCTRL_CLKACTIVITY_RTC_GCLK (0x00000100u)
#define CM_ALWON_RTC_CLKSTCTRL_CLKACTIVITY_RTC_GCLK_SHIFT   (0x8u)

#define CM_ALWON_RTC_CLKSTCTRL_CLKTRCTRL            (0x00000003u)
#define CM_ALWON_RTC_CLKSTCTRL_CLKTRCTRL_SHIFT      (0x0u)

/** @brief CM_ALWON_L3_FAST_CLKSTCTRL register fields */

#define CM_ALWON_L3_FAST_CLKSTCTRL_CLKACTIVITY_FAST_GCLK    (0x00000100u)
#define CM_ALWON_L3_FAST_CLKSTCTRL_CLKACTIVITY_FAST_GCLK_SHIFT  (0x8u)

#define CM_ALWON_L3_FAST_CLKSTCTRL_CLKTRCTRL        (0x00000003u)
#define CM_ALWON_L3_FAST_CLKSTCTRL_CLKTRCTRL_SHIFT  (0x0u)

/** @brief CM_ALWON_MCASP0_CLKCTRL register fields */

#define CM_ALWON_MCASP0_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_MCASP0_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_MCASP0_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_MCASP0_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_MCASP1_CLKCTRL register fields */

#define CM_ALWON_MCASP1_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_MCASP1_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_MCASP1_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_MCASP1_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_MCASP2_CLKCTRL register fields */

#define CM_ALWON_MCASP2_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_MCASP2_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_MCASP2_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_MCASP2_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_MCBSP_CLKCTRL register fields */

#define CM_ALWON_MCBSP_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_MCBSP_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_MCBSP_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_MCBSP_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_UART_0_CLKCTRL register fields */

#define CM_ALWON_UART_0_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_UART_0_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_UART_0_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_UART_0_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_UART_1_CLKCTRL register fields */

#define CM_ALWON_UART_1_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_UART_1_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_UART_1_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_UART_1_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_UART_2_CLKCTRL register fields */

#define CM_ALWON_UART_2_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_UART_2_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_UART_2_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_UART_2_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_GPIO_0_CLKCTRL register fields */

#define CM_ALWON_GPIO_0_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_GPIO_0_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_GPIO_0_CLKCTRL_OPTFCLKEN_DBCLK     (0x00000100u)
#define CM_ALWON_GPIO_0_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT   (0x8u)

#define CM_ALWON_GPIO_0_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_GPIO_0_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_GPIO_1_CLKCTRL register fields */

#define CM_ALWON_GPIO_1_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_GPIO_1_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_GPIO_1_CLKCTRL_OPTFCLKEN_DBCLK     (0x00000100u)
#define CM_ALWON_GPIO_1_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT   (0x8u)

#define CM_ALWON_GPIO_1_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_GPIO_1_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_I2C_0_CLKCTRL register fields */

#define CM_ALWON_I2C_0_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_I2C_0_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_I2C_0_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_I2C_0_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_I2C_1_CLKCTRL register fields */

#define CM_ALWON_I2C_1_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_I2C_1_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_I2C_1_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_I2C_1_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_MCASP_3_4_5_CLKCTRL register fields */

#define CM_ALWON_MCASP_3_4_5_CLKCTRL_IDLEST         (0x00030000u)
#define CM_ALWON_MCASP_3_4_5_CLKCTRL_IDLEST_SHIFT   (0x10u)

#define CM_ALWON_MCASP_3_4_5_CLKCTRL_MODULEMODE     (0x00000003u)
#define CM_ALWON_MCASP_3_4_5_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_ATL_CLKCTRL register fields */

#define CM_ALWON_ATL_CLKCTRL_IDLEST                 (0x00030000u)
#define CM_ALWON_ATL_CLKCTRL_IDLEST_SHIFT           (0x10u)

#define CM_ALWON_ATL_CLKCTRL_MODULEMODE             (0x00000003u)
#define CM_ALWON_ATL_CLKCTRL_MODULEMODE_SHIFT       (0x0u)

/** @brief CM_ALWON_MLB_CLKCTRL register fields */

#define CM_ALWON_MLB_CLKCTRL_IDLEST                 (0x00030000u)
#define CM_ALWON_MLB_CLKCTRL_IDLEST_SHIFT           (0x10u)

#define CM_ALWON_MLB_CLKCTRL_MODULEMODE             (0x00000003u)
#define CM_ALWON_MLB_CLKCTRL_MODULEMODE_SHIFT       (0x0u)

/** @brief CM_ALWON_PATA_CLKCTRL register fields */

#define CM_ALWON_PATA_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_PATA_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_PATA_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_PATA_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_TIMER_4_CLKCTRL register fields */

#define CM_ALWON_TIMER_4_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_TIMER_4_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_TIMER_4_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_TIMER_4_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_UART_3_CLKCTRL register fields */

#define CM_ALWON_UART_3_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_UART_3_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_UART_3_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_UART_3_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_UART_4_CLKCTRL register fields */

#define CM_ALWON_UART_4_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_UART_4_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_UART_4_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_UART_4_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_UART_5_CLKCTRL register fields */

#define CM_ALWON_UART_5_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_UART_5_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_UART_5_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_UART_5_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_WDTIMER_CLKCTRL register fields */

#define CM_ALWON_WDTIMER_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_WDTIMER_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_WDTIMER_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_WDTIMER_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_SPI_CLKCTRL register fields */

#define CM_ALWON_SPI_CLKCTRL_IDLEST                 (0x00030000u)
#define CM_ALWON_SPI_CLKCTRL_IDLEST_SHIFT           (0x10u)

#define CM_ALWON_SPI_CLKCTRL_MODULEMODE             (0x00000003u)
#define CM_ALWON_SPI_CLKCTRL_MODULEMODE_SHIFT       (0x0u)

/** @brief CM_ALWON_MAILBOX_CLKCTRL register fields */

#define CM_ALWON_MAILBOX_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_MAILBOX_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_MAILBOX_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_MAILBOX_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_SPINBOX_CLKCTRL register fields */

#define CM_ALWON_SPINBOX_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_SPINBOX_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_SPINBOX_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_SPINBOX_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_MMUDATA_CLKCTRL register fields */

#define CM_ALWON_MMUDATA_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_MMUDATA_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_MMUDATA_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_MMUDATA_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_MMUCFG_CLKCTRL register fields */

#define CM_ALWON_MMUCFG_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_MMUCFG_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_MMUCFG_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_MMUCFG_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_SDIO_CLKCTRL register fields */

#define CM_ALWON_SDIO_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_SDIO_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_SDIO_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_SDIO_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_OCMC_0_CLKCTRL register fields */

#define CM_ALWON_OCMC_0_CLKCTRL_IDLEST              (0x00030000u)
#define CM_ALWON_OCMC_0_CLKCTRL_IDLEST_SHIFT        (0x10u)

#define CM_ALWON_OCMC_0_CLKCTRL_MODULEMODE          (0x00000003u)
#define CM_ALWON_OCMC_0_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_VCP_CLKCTRL register fields */

#define CM_ALWON_VCP_CLKCTRL_IDLEST                 (0x00030000u)
#define CM_ALWON_VCP_CLKCTRL_IDLEST_SHIFT           (0x10u)

#define CM_ALWON_VCP_CLKCTRL_MODULEMODE             (0x00000003u)
#define CM_ALWON_VCP_CLKCTRL_MODULEMODE_SHIFT       (0x0u)

/** @brief CM_ALWON_SMARTCARD_0_CLKCTRL register fields */

#define CM_ALWON_SMARTCARD_0_CLKCTRL_IDLEST         (0x00030000u)
#define CM_ALWON_SMARTCARD_0_CLKCTRL_IDLEST_SHIFT   (0x10u)

#define CM_ALWON_SMARTCARD_0_CLKCTRL_MODULEMODE     (0x00000003u)
#define CM_ALWON_SMARTCARD_0_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_SMARTCARD_1_CLKCTRL register fields */

#define CM_ALWON_SMARTCARD_1_CLKCTRL_IDLEST         (0x00030000u)
#define CM_ALWON_SMARTCARD_1_CLKCTRL_IDLEST_SHIFT   (0x10u)

#define CM_ALWON_SMARTCARD_1_CLKCTRL_MODULEMODE     (0x00000003u)
#define CM_ALWON_SMARTCARD_1_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_CONTROL_CLKCTRL register fields */

#define CM_ALWON_CONTROL_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_CONTROL_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_CONTROL_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_CONTROL_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_SECSS_CLKCTRL register fields */

#define CM_ALWON_SECSS_CLKCTRL_STBYST               (0x00040000u)
#define CM_ALWON_SECSS_CLKCTRL_STBYST_SHIFT         (0x12u)

#define CM_ALWON_SECSS_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_SECSS_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_SECSS_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_SECSS_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_GPMC_CLKCTRL register fields */

#define CM_ALWON_GPMC_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_GPMC_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_GPMC_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_GPMC_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_ETHERNET_0_CLKCTRL register fields */

#define CM_ALWON_ETHERNET_0_CLKCTRL_STBYST          (0x00040000u)
#define CM_ALWON_ETHERNET_0_CLKCTRL_STBYST_SHIFT    (0x12u)

#define CM_ALWON_ETHERNET_0_CLKCTRL_IDLEST          (0x00030000u)
#define CM_ALWON_ETHERNET_0_CLKCTRL_IDLEST_SHIFT    (0x10u)

#define CM_ALWON_ETHERNET_0_CLKCTRL_MODULEMODE      (0x00000003u)
#define CM_ALWON_ETHERNET_0_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief CM_ALWON_MPU_CLKCTRL register fields */

#define CM_ALWON_MPU_CLKCTRL_STBYST                 (0x00040000u)
#define CM_ALWON_MPU_CLKCTRL_STBYST_SHIFT           (0x12u)

#define CM_ALWON_MPU_CLKCTRL_IDLEST                 (0x00030000u)
#define CM_ALWON_MPU_CLKCTRL_IDLEST_SHIFT           (0x10u)

#define CM_ALWON_MPU_CLKCTRL_MODULEMODE             (0x00000003u)
#define CM_ALWON_MPU_CLKCTRL_MODULEMODE_SHIFT       (0x0u)

/** @brief CM_ALWON_DEBUGSS_CLKCTRL register fields */

#define CM_ALWON_DEBUGSS_CLKCTRL_STM_PMD_CLKDIVSEL  (0x38000000u)
#define CM_ALWON_DEBUGSS_CLKCTRL_STM_PMD_CLKDIVSEL_SHIFT    (0x1Bu)

#define CM_ALWON_DEBUGSS_CLKCTRL_TRC_PMD_CLKDIVSEL  (0x07000000u)
#define CM_ALWON_DEBUGSS_CLKCTRL_TRC_PMD_CLKDIVSEL_SHIFT    (0x18u)

#define CM_ALWON_DEBUGSS_CLKCTRL_STM_PMD_CLKSEL     (0x00C00000u)
#define CM_ALWON_DEBUGSS_CLKCTRL_STM_PMD_CLKSEL_SHIFT   (0x16u)

#define CM_ALWON_DEBUGSS_CLKCTRL_TRC_PMD_CLKSEL     (0x00300000u)
#define CM_ALWON_DEBUGSS_CLKCTRL_TRC_PMD_CLKSEL_SHIFT   (0x14u)

#define CM_ALWON_DEBUGSS_CLKCTRL_STBYST             (0x00040000u)
#define CM_ALWON_DEBUGSS_CLKCTRL_STBYST_SHIFT       (0x12u)

#define CM_ALWON_DEBUGSS_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_DEBUGSS_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_DEBUGSS_CLKCTRL_OPTCLK_DEBUG_CLKA  (0x00000200u)
#define CM_ALWON_DEBUGSS_CLKCTRL_OPTCLK_DEBUG_CLKA_SHIFT    (0x9u)

#define CM_ALWON_DEBUGSS_CLKCTRL_OPTCLK_DEBUG_SYSCLK    (0x00000100u)
#define CM_ALWON_DEBUGSS_CLKCTRL_OPTCLK_DEBUG_SYSCLK_SHIFT  (0x8u)

#define CM_ALWON_DEBUGSS_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_DEBUGSS_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_L3_CLKCTRL register fields */

#define CM_ALWON_L3_CLKCTRL_IDLEST                  (0x00030000u)
#define CM_ALWON_L3_CLKCTRL_IDLEST_SHIFT            (0x10u)

#define CM_ALWON_L3_CLKCTRL_MODULEMODE              (0x00000003u)
#define CM_ALWON_L3_CLKCTRL_MODULEMODE_SHIFT        (0x0u)

/** @brief CM_ALWON_L4HS_CLKCTRL register fields */

#define CM_ALWON_L4HS_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_L4HS_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_L4HS_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_L4HS_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_L4LS_CLKCTRL register fields */

#define CM_ALWON_L4LS_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_L4LS_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_L4LS_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_L4LS_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_RTC_CLKCTRL register fields */

#define CM_ALWON_RTC_CLKCTRL_IDLEST                 (0x00030000u)
#define CM_ALWON_RTC_CLKCTRL_IDLEST_SHIFT           (0x10u)

#define CM_ALWON_RTC_CLKCTRL_MODULEMODE             (0x00000003u)
#define CM_ALWON_RTC_CLKCTRL_MODULEMODE_SHIFT       (0x0u)

/** @brief CM_ALWON_TPCC_CLKCTRL register fields */

#define CM_ALWON_TPCC_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_TPCC_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_TPCC_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_TPCC_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_TPTC0_CLKCTRL register fields */

#define CM_ALWON_TPTC0_CLKCTRL_STBYST               (0x00040000u)
#define CM_ALWON_TPTC0_CLKCTRL_STBYST_SHIFT         (0x12u)

#define CM_ALWON_TPTC0_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_TPTC0_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_TPTC0_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_TPTC0_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_TPTC1_CLKCTRL register fields */

#define CM_ALWON_TPTC1_CLKCTRL_STBYST               (0x00040000u)
#define CM_ALWON_TPTC1_CLKCTRL_STBYST_SHIFT         (0x12u)

#define CM_ALWON_TPTC1_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_TPTC1_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_TPTC1_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_TPTC1_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_TPTC2_CLKCTRL register fields */

#define CM_ALWON_TPTC2_CLKCTRL_STBYST               (0x00040000u)
#define CM_ALWON_TPTC2_CLKCTRL_STBYST_SHIFT         (0x12u)

#define CM_ALWON_TPTC2_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_TPTC2_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_TPTC2_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_TPTC2_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_TPTC3_CLKCTRL register fields */

#define CM_ALWON_TPTC3_CLKCTRL_STBYST               (0x00040000u)
#define CM_ALWON_TPTC3_CLKCTRL_STBYST_SHIFT         (0x12u)

#define CM_ALWON_TPTC3_CLKCTRL_IDLEST               (0x00030000u)
#define CM_ALWON_TPTC3_CLKCTRL_IDLEST_SHIFT         (0x10u)

#define CM_ALWON_TPTC3_CLKCTRL_MODULEMODE           (0x00000003u)
#define CM_ALWON_TPTC3_CLKCTRL_MODULEMODE_SHIFT     (0x0u)

/** @brief CM_ALWON_SR_0_CLKCTRL register fields */

#define CM_ALWON_SR_0_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_SR_0_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_SR_0_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_SR_0_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_SR_1_CLKCTRL register fields */

#define CM_ALWON_SR_1_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_SR_1_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_SR_1_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_SR_1_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_SR_2_CLKCTRL register fields */

#define CM_ALWON_SR_2_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_SR_2_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_SR_2_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_SR_2_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_SR_3_CLKCTRL register fields */

#define CM_ALWON_SR_3_CLKCTRL_IDLEST                (0x00030000u)
#define CM_ALWON_SR_3_CLKCTRL_IDLEST_SHIFT          (0x10u)

#define CM_ALWON_SR_3_CLKCTRL_MODULEMODE            (0x00000003u)
#define CM_ALWON_SR_3_CLKCTRL_MODULEMODE_SHIFT      (0x0u)

/** @brief CM_ALWON_DCAN_0_1_CLKCTRL register fields */

#define CM_ALWON_DCAN_0_1_CLKCTRL_IDLEST            (0x00030000u)
#define CM_ALWON_DCAN_0_1_CLKCTRL_IDLEST_SHIFT      (0x10u)

#define CM_ALWON_DCAN_0_1_CLKCTRL_MODULEMODE        (0x00000003u)
#define CM_ALWON_DCAN_0_1_CLKCTRL_MODULEMODE_SHIFT  (0x0u)

/** @brief CM_ALWON_MMCHS_0_CLKCTRL register fields */

#define CM_ALWON_MMCHS_0_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_MMCHS_0_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_MMCHS_0_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_MMCHS_0_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_MMCHS_1_CLKCTRL register fields */

#define CM_ALWON_MMCHS_1_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_MMCHS_1_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_MMCHS_1_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_MMCHS_1_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_MMCHS_2_CLKCTRL register fields */

#define CM_ALWON_MMCHS_2_CLKCTRL_IDLEST             (0x00030000u)
#define CM_ALWON_MMCHS_2_CLKCTRL_IDLEST_SHIFT       (0x10u)

#define CM_ALWON_MMCHS_2_CLKCTRL_MODULEMODE         (0x00000003u)
#define CM_ALWON_MMCHS_2_CLKCTRL_MODULEMODE_SHIFT   (0x0u)

/** @brief CM_ALWON_CUST_EFUSE_CLKCTRL register fields */

#define CM_ALWON_CUST_EFUSE_CLKCTRL_IDLEST          (0x00030000u)
#define CM_ALWON_CUST_EFUSE_CLKCTRL_IDLEST_SHIFT    (0x10u)

#define CM_ALWON_CUST_EFUSE_CLKCTRL_MODULEMODE      (0x00000003u)
#define CM_ALWON_CUST_EFUSE_CLKCTRL_MODULEMODE_SHIFT    (0x0u)

/** @brief PRM_ALWON_RSTST register fields */

#define PRM_ALWON_RSTST_ICECRUSHER_SEC_M3_RST       (0x00000080u)
#define PRM_ALWON_RSTST_ICECRUSHER_SEC_M3_RST_SHIFT (0x7u)

#define PRM_ALWON_RSTST_ICECRUSHER_MPU_RST          (0x00000040u)
#define PRM_ALWON_RSTST_ICECRUSHER_MPU_RST_SHIFT    (0x6u)

#define PRM_ALWON_RSTST_EMULATION_MPU_RST           (0x00000020u)
#define PRM_ALWON_RSTST_EMULATION_MPU_RST_SHIFT     (0x5u)

#define PRM_ALWON_RSTST_EMULATION_SEC_M3_RST        (0x00000010u)
#define PRM_ALWON_RSTST_EMULATION_SEC_M3_RST_SHIFT  (0x4u)

/** @brief Common CLKCTRL register fields and tokens */

#define CM_X_CLKCTRL_MODULEMODE                     (0x00000003u)
#define CM_X_CLKCTRL_MODULEMODE_SHIFT               (0x0u)
#define CM_X_CLKCTRL_MODULEMODE_DISABLE             (0x0u)
#define CM_X_CLKCTRL_MODULEMODE_ENABLE              (0x2u)

#define CM_X_CLKCTRL_IDLEST                         (0x00030000u)
#define CM_X_CLKCTRL_IDLEST_SHIFT                   (0x10u)
#define CM_X_CLKCTRL_IDLEST_FUNC                    (0x0u)
#define CM_X_CLKCTRL_IDLEST_TRANS                   (0x1u)
#define CM_X_CLKCTRL_IDLEST_IDLE                    (0x2u)
#define CM_X_CLKCTRL_IDLEST_DISABLE                 (0x3u)

#define CM_X_CLKCTRL_STBYST                         (0x00040000u)
#define CM_X_CLKCTRL_STBYST_SHIFT                   (0x12u)
#define CM_X_CLKCTRL_STBYST_FUNC                    (0x0u)
#define CM_X_CLKCTRL_STBYST_STANDBY                 (0x1u)

#define CM_X_CLKCTRL_OPTFCLKEN_DBCLK                (0x00000100u)
#define CM_X_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT          (0x8u)
#define CM_X_CLKCTRL_OPTFCLKEN_DBCLK_FCLK_DIS       (0x0u)
#define CM_X_CLKCTRL_OPTFCLKEN_DBCLK_FCLK_EN        (0x1u)

#ifdef __cplusplus
}
#endif

#endif /* _HW_PRCM_C6A811X_H_ */
