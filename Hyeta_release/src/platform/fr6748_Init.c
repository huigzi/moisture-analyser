/*
 * fr6748_Init.c
 *
 * This file contains the board specific code for enabling the use of drivers.
 * 2016-9-13 整合SPI模块和PWM模块
 * 2016-10-4 添加看门狗
 * 2016-10-10 焊接方法  面对 PWM引出线方向   左侧6PIN引脚左侧  右侧 6PIN引脚居中，此时DIR_IN为0时制冷为1时加热
 */

#include <xdc/std.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/io/iom.h>
#include <ti/sysbios/io/GIO.h>
#include <assert.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

#include <fr6748_Init.h>
#include <cslr/cslr_syscfg0_C6748.h>
#include <cslr/soc_C6748.h>
#include <Psc.h>
#include <cslr/cslr_gpio.h>
#include <cslr/cslr_ehrpwm.h>
#include <cslr/cslr_tmr.h>
#include <I2c.h>
#include <VpifDebug.h>

#define PINMUX0_VALUE 	0x44488888	//gpio-0
#define PINMUX1_VALUE 	0x88888888
#define PINMUX2_VALUE 	0x88888888	//emac
#define PINMUX3_VALUE 	0x88888888	//emac
#define PINMUX4_VALUE 	0x22222288	//i2c0 UART1 UART2
#define PINMUX5_VALUE 	0x88888888
#define PINMUX6_VALUE 	0x11111181	//ema
#define PINMUX7_VALUE 	0x10110010	//EMIF_C
#define PINMUX8_VALUE 	0x00000000	//EMIF_D8-15
#define PINMUX9_VALUE 	0x11111111	//EMIF_D0-7
#define PINMUX10_VALUE 	0x80222222	//MMCSD0
#define PINMUX11_VALUE 	0x88800000	//EMIF_A
#define PINMUX12_VALUE 	0x01100000	//emif_a
#define PINMUX13_VALUE 	0x00880000
#define PINMUX14_VALUE 	0x11111181	//vpif
#define PINMUX15_VALUE 	0x11111111
#define PINMUX16_VALUE 	0x11111111
//#define PINMUX17_VALUE 	0x11111111
#define PINMUX17_VALUE 	0x88111111
//#define PINMUX18_VALUE 	0x00000011
#define PINMUX18_VALUE 	0x00000088
#define PINMUX19_VALUE 	0x00001100

#define PINMUX4_CS_ENABLE        0x00000040u
#define PINMUX0_AD_RDY           0x00000008u
#define PINMUX5_PWM              0x00000020u
#define PINMUX13_FAN             0x00000008u

/* Address of the KICK0 and KICK1 register                                    */
#define KICK0                   (*((volatile Uint32 *)(0x01C14038u)))
#define KICK1                   (*((volatile Uint32 *)(0x01C1403Cu)))

/* Unlock/Lock code for KICK0 and KICK1 register                              */
#define KICK0_UNLOCK_CODE       0x83E70B13u
#define KICK1_UNLOCK_CODE       0x95A4F1E0u

I2c_Params   vpifI2cParams;

 CSL_SyscfgRegsOvly syscfgRegs = (CSL_SyscfgRegsOvly)CSL_SYSCFG_0_REGS;
 CSL_GpioRegsOvly     gpioRegs = (CSL_GpioRegsOvly)CSL_GPIO_0_REGS;
 CSL_EhrpwmRegsOvly pwmRegs = (CSL_EhrpwmRegsOvly)CSL_EHRPWM_1_REGS;
 CSL_TmrRegsOvly wathdogRegs = (CSL_TmrRegsOvly)CSL_TMR_1_REGS;

/* ========================================================================== */
/*                          STATIC VARIABLES                                  */
/* ========================================================================== */
/* ========================================================================== */
/*                       LOCAL FUNCTION PROTOTYPES                            */
/* ========================================================================== */

/* ========================================================================== */
/*                       GLOBAL FUNCTION PROTOTYPES                           */
/* ========================================================================== */

/* ========================================================================== */
/*                        LOCAL FUNCTION DEFINITIONS                          */
/* ========================================================================== */
/**
 *  \brief I2C init function called when creating the driver.
 */
Void vpifUserI2cInit()
{
    I2c_init();

    vpifI2cParams 			= I2c_PARAMS;
    vpifI2cParams.busFreq 	= 400000u;
    vpifI2cParams.hwiNumber = 11u;	//8

    /* Configure I2C for interrupt mode                                       */
    vpifI2cParams.opMode = I2c_OpMode_INTERRUPT;

    /* No I2C 0 PSC for C6748                                              */
}

void configureGuaoC6748(void)
{
  //  CSL_SyscfgRegsOvly syscfgRegs = (CSL_SyscfgRegsOvly)CSL_SYSCFG_0_REGS;
  //  CSL_GpioRegsOvly     gpioRegs = (CSL_GpioRegsOvly)(CSL_GPIO_0_REGS);

    /* Unlock BOOTCFG module before pinmux configuration                      */
    KICK0 = KICK0_UNLOCK_CODE;
    KICK1 = KICK1_UNLOCK_CODE;

    syscfgRegs->PINMUX0 = (PINMUX0_VALUE |PINMUX0_AD_RDY);
    syscfgRegs->PINMUX1 = PINMUX1_VALUE;
    syscfgRegs->PINMUX2 = PINMUX2_VALUE;
    syscfgRegs->PINMUX3 = PINMUX3_VALUE;
    syscfgRegs->PINMUX4 = (PINMUX4_VALUE | PINMUX4_CS_ENABLE);
    syscfgRegs->PINMUX5 = PINMUX5_VALUE;
    syscfgRegs->PINMUX6 = PINMUX6_VALUE ;
    syscfgRegs->PINMUX7 = PINMUX7_VALUE ;
    syscfgRegs->PINMUX8 = PINMUX8_VALUE ;
    syscfgRegs->PINMUX9 = PINMUX9_VALUE ;
    syscfgRegs->PINMUX10 = PINMUX10_VALUE ;
    syscfgRegs->PINMUX11 = PINMUX11_VALUE ;
    syscfgRegs->PINMUX12 = PINMUX12_VALUE ;
    syscfgRegs->PINMUX13 = (PINMUX13_VALUE | PINMUX13_FAN);
    syscfgRegs->PINMUX14 = PINMUX14_VALUE ;
    syscfgRegs->PINMUX15 = PINMUX15_VALUE ;
    syscfgRegs->PINMUX16 = PINMUX16_VALUE ;
    syscfgRegs->PINMUX17 = PINMUX17_VALUE ;
    syscfgRegs->PINMUX18 = PINMUX18_VALUE ;
    syscfgRegs->PINMUX19 = PINMUX19_VALUE ;

    /* enable the pinmux registers for Spi                                    */
    /* Only SOMI, CLK and CS0 are used                                   */

    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_GPIO_0, CSL_PSC_GPIO, TRUE);
//    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_UART_1, CSL_PSC_UART1, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_UART_2, CSL_PSC_UART2, TRUE);
//    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_USB_0, CSL_PSC_USB0,TRUE);
//    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_USB_1, CSL_PSC_USB1, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_EMAC_0, CSL_PSC_EMAC, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_DDR2_MDDR_0, CSL_PSC_DDR2_MDDR, TRUE);
//    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_SPI_1, CSL_PSC_SPI1, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_I2C_1, CSL_PSC_I2C1, TRUE);
//    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_UPP_0, CSL_PSC_UPP, TRUE);
//    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_MMCSD_0, CSL_PSC_MMCSD0, TRUE);
//    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_EMIFA_0, CSL_PSC_EMIFA, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_SPI_0, CSL_PSC_SPI0, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_EHRPWM_0, CSL_PSC_EHRPWM , TRUE);

    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR15,1);	//INTn(8710A)		GP0(15)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR22,0);   //AD_SC(out)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR11,0);	//AD_RST(out)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR12,0);	//DIR_IN(out)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR15,1);	//AD_RDY(in)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR31,0);	//DSP_LED(out)
    CSL_FINS(gpioRegs->BANK[1].DIR,GPIO_DIR_DIR15,0);	//RS485_DE/TE(out)
    CSL_FINS(gpioRegs->BANK[3].DIR,GPIO_DIR_DIR6,0);	//CMOS_PWRDOWN(out)
    CSL_FINS(gpioRegs->BANK[3].DIR,GPIO_DIR_DIR10,0);	//CMOS_RESET(out)
    CSL_FINS(gpioRegs->BANK[3].DIR,GPIO_DIR_DIR15,0);   //FAN(out)


    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT11,1);	//AD_RST(out)
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT12,1);	//DIR_IN(out)
    CSL_FINS(gpioRegs->BANK[1].OUT_DATA,GPIO_OUT_DATA_OUT15,1);	//RE#
    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT6,0);	//standby-CMOS_PWRDOWN(out)
    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT10,0);	//exposure-CMOS_RESET(out)
    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT15,1); //FAN(out)

    //text boot start
    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT16,0);
    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT17,0);
    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT18,0);
    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT19,0);
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT22,0);


    syscfgRegs->CFGCHIP1 =CSL_FMK(SYSCFG_CFGCHIP1_TBCLKSYNC,CSL_SYSCFG_CFGCHIP1_TBCLKSYNC_ENABLE);

//    wathdogRegs->TIM12 = CSL_FMK(TMR_TIM12_TIM12,0);
//    wathdogRegs->TIM34 = CSL_FMK(TMR_TIM34_TIM34,0);
//    wathdogRegs->TCR = CSL_FMK(TMR_TCR_CLKSRC12, CSL_TMR_TCR_CLKSRC12_INTERNAL);
//    wathdogRegs->TGCR = CSL_FMK(TMR_TGCR_TIMMODE,CSL_TMR_TGCR_TIMMODE_64BIT_WDT)
//    							|CSL_FMK(TMR_TGCR_TIM12RS, CSL_TMR_TGCR_TIM12RS_RESET)
//    							|CSL_FMK(TMR_TGCR_TIM34RS, CSL_TMR_TGCR_TIM34RS_RESET)
//    							|CSL_FMK(TMR_TGCR_PLUSEN, CSL_TMR_TGCR_PLUSEN_ENABLE);
//    wathdogRegs->PRD12 = CSL_FMK(TMR_PRD12_PRD12,0x0E00);
//    wathdogRegs->PRD34 = CSL_FMK(TMR_PRD34_PRD34,0x0727);
//    wathdogRegs->WDTCR = CSL_FMK(TMR_WDTCR_WDEN,CSL_TMR_WDTCR_WDEN_ENABLE)
//								|CSL_FMK(TMR_WDTCR_WDFLAG , CSL_TMR_WDTCR_WDFLAG_NO_TIMEOUT)
//    		                    |CSL_FMK(TMR_WDTCR_WDKEY, CSL_TMR_WDTCR_WDKEY_CMD1)
//    		                    |CSL_FMK(TMR_WDTCR_WDKEY, CSL_TMR_WDTCR_WDKEY_CMD2);


//    for(j=0;j<30;j++)
//    {
//		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,0);	//led
//		for(i=0;i<1000000;i++);
//		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,1);	//led
//		for(i=0;i<1000000;i++);
//    }

	/* Wait Until PHY Clock is Good */
//	while ((syscfgRegs->CFGCHIP2 & 0x00020000) == 0); // Wait Until PHY Clock is Good.

}
