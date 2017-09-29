/*
 * guao6748_Init.c
 *
 * This file contains the board specific code for enabling the use of drivers.
 */

#include <xdc/std.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/io/iom.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>

#include <guao6748_Init.h>
#include <cslr/cslr_syscfg0_C6748.h>
#include <cslr/soc_C6748.h>
#include <Psc.h>
#include <cslr/cslr_gpio.h>
//#include <cslr/cslr_emifa2.h>

#define PINMUX0_VALUE 	0x88888888	//gp0(8-15)
#define PINMUX1_VALUE 	0x88888888	//gp0(0-7)
#define PINMUX2_VALUE 	0x88888888	//emac
#define PINMUX3_VALUE 	0x88888888	//emac
#define PINMUX4_VALUE 	0x22222288	//uart/i2c/mdio
#define PINMUX5_VALUE 	0x11111111	//spi1
#define PINMUX6_VALUE 	0x11111181	//ema
#define PINMUX7_VALUE 	0x11111111	//EMIF_C
#define PINMUX8_VALUE 	0x11111111	//EMIF_D
#define PINMUX9_VALUE 	0x11111111	//EMIF_D
#define PINMUX10_VALUE 	0x88222222	//MMCSD0
#define PINMUX11_VALUE 	0x88888888	//gp5(8-15)
#define PINMUX12_VALUE 	0x11111118	//gp5(0-7)
#define PINMUX13_VALUE 	0x44440010	//uppA
#define PINMUX14_VALUE 	0x44444400	//upp d(10-15)
#define PINMUX15_VALUE 	0x44444444	//upp d(2-9)
#define PINMUX16_VALUE 	0x11111144	//vpout(2-7)/upp d(0-1)
#define PINMUX17_VALUE 	0x88888811	//gp7(2-6)/vpout(0-1)
#define PINMUX18_VALUE 	0x88444488	//gp8(10-11)/uppB/gp7(0-1)
#define PINMUX19_VALUE 	0x00001108	//vp2clk

//#define PINMUX13_VALUE     0x44440000u
//#define PINMUX14_VALUE     0x44444400u
//#define PINMUX15_VALUE     0x44444444u
//#define PINMUX16_VALUE     0x44444444u
//#define PINMUX17_VALUE     0x44444444u
//#define PINMUX18_VALUE     0x00444444u

/* Address of the KICK0 and KICK1 register                                    */
#define KICK0                   (*((volatile Uint32 *)(0x01C14038u)))
#define KICK1                   (*((volatile Uint32 *)(0x01C1403Cu)))

/* Unlock/Lock code for KICK0 and KICK1 register                              */
#define KICK0_UNLOCK_CODE       0x83E70B13u
#define KICK1_UNLOCK_CODE       0x95A4F1E0u

CSL_SyscfgRegsOvly syscfgRegs = (CSL_SyscfgRegsOvly)CSL_SYSCFG_0_REGS;
CSL_GpioRegsOvly     gpioRegs = (CSL_GpioRegsOvly)(CSL_GPIO_0_REGS);

void configureGuaoC6748(void)
{
	int i,j;


//    CSL_EmifaRegsOvly     emifaRegs = (CSL_EmifaRegsOvly)(CSL_EMIFA_0_REGS);

    /* Unlock BOOTCFG module before pinmux configuration                      */
    KICK0 = KICK0_UNLOCK_CODE;
    KICK1 = KICK1_UNLOCK_CODE;

    syscfgRegs->PINMUX0 = PINMUX0_VALUE ;
    syscfgRegs->PINMUX1 = PINMUX1_VALUE ;
    syscfgRegs->PINMUX2 = PINMUX2_VALUE ;
    syscfgRegs->PINMUX3 = PINMUX3_VALUE ;
    syscfgRegs->PINMUX4 = PINMUX4_VALUE ;
    syscfgRegs->PINMUX5 = PINMUX5_VALUE ;
    syscfgRegs->PINMUX6 = PINMUX6_VALUE ;
    syscfgRegs->PINMUX7 = PINMUX7_VALUE ;
    syscfgRegs->PINMUX8 = PINMUX8_VALUE ;
    syscfgRegs->PINMUX9 = PINMUX9_VALUE ;
    syscfgRegs->PINMUX10 = PINMUX10_VALUE ;
    syscfgRegs->PINMUX11 = PINMUX11_VALUE ;
    syscfgRegs->PINMUX12 = PINMUX12_VALUE ;
    syscfgRegs->PINMUX13 = PINMUX13_VALUE ;
    syscfgRegs->PINMUX14 = PINMUX14_VALUE ;
    syscfgRegs->PINMUX15 = PINMUX15_VALUE ;
    syscfgRegs->PINMUX16 = PINMUX16_VALUE ;
    syscfgRegs->PINMUX17 = PINMUX17_VALUE ;
    syscfgRegs->PINMUX18 = PINMUX18_VALUE ;
    syscfgRegs->PINMUX19 = PINMUX19_VALUE ;

    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_GPIO_0, CSL_PSC_GPIO, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_UART_1, CSL_PSC_UART1, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_UART_2, CSL_PSC_UART2, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_EMAC_0, CSL_PSC_EMAC, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_DDR2_MDDR_0, CSL_PSC_DDR2_MDDR, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_SPI_1, CSL_PSC_SPI1, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_I2C_1, CSL_PSC_I2C1, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_UPP_0, CSL_PSC_UPP, TRUE);
    Psc_ModuleClkCtrl((Psc_DevId)CSL_LPSC_INST_MMCSD_0, CSL_PSC_MMCSD0, TRUE);

	CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR31,0);	//dsp-led(out)		GP1(15)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR15,1);	//INTn(8710A)		GP0(15)
    CSL_FINS(gpioRegs->BANK[4].DIR,GPIO_DIR_DIR11,0);	//ADV7391_rst(out) 	GP8(11)
    CSL_FINS(gpioRegs->BANK[4].DIR,GPIO_DIR_DIR10,1);	//vpif_sfl			GP8(10)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR12,0);	//RS485_DE/TE(out)	GP0(12)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR13,0);	//UART1_CS(out)		GP0(13)	//rs232/RS485
    CSL_FINS(gpioRegs->BANK[2].DIR,GPIO_DIR_DIR0,1);	//TF_DET(in)		GP4(0)
    CSL_FINS(gpioRegs->BANK[2].DIR,GPIO_DIR_DIR23,0);	//FPGA_INIT_B(out)	GP5(7)
    CSL_FINS(gpioRegs->BANK[2].DIR,GPIO_DIR_DIR24,0);	//FPGA_DIN(out)		GP5(8)
    CSL_FINS(gpioRegs->BANK[2].DIR,GPIO_DIR_DIR25,0);	//FPGA_CCLK(out)	GP5(9)
    CSL_FINS(gpioRegs->BANK[2].DIR,GPIO_DIR_DIR26,0);	//FPGA_PROG(out)	GP5(10)
    CSL_FINS(gpioRegs->BANK[2].DIR,GPIO_DIR_DIR27,1);	//FPGA_DONE(in)		GP5(11)

    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR0,0);	//MCBSP1_CLKS/FPGA_RST(out)			GP0(0)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR1,0);	//MCBSP1_DX/CMOS_PWDN(out)			GP0(1)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR2,0);	//MCBSP1_DR/TAU_NEXT_F(out)			GP0(2)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR3,0);	//MCBSP1_FSX/CMOS_RST(out)			GP0(3)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR4,0);	//MCBSP1_FSR/CMOS_NEXT_F(out)			GP0(4)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR5,0);	//MCBSP1_CLKX/UPP_CTRL_CMOS(out)	GP0(5)
    CSL_FINS(gpioRegs->BANK[0].DIR,GPIO_DIR_DIR6,0);	//MCBSP1_CLKR/UPP_CTRL_TAU(out)		GP0(6)

    //init gpio
    CSL_FINS(gpioRegs->BANK[4].OUT_DATA,GPIO_OUT_DATA_OUT11,1);	//ADV7391_rst(out)
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT12,0);	//RE#
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT13,0);	//RS232

    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT1,0);	//CMOS_PWDN = 0
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT2,0);	//TAU_NEXT_F = 0
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT3,0);	//CMOS_RST = 0
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT4,0);	//CMOS_NEXT_F = 0
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT5,0);	//UPP_CTRL_CMOS = 0
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT6,0);	//UPP_CTRL_TAU = 0

    //generate a reset pulse
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT0,0);	//FPGA_RST = 0
    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT0,1);	//FPGA_RST = 1

    CSL_FINS(gpioRegs->BANK[2].OUT_DATA,GPIO_OUT_DATA_OUT23,0);	//FPGA_INIT_B
    CSL_FINS(gpioRegs->BANK[2].OUT_DATA,GPIO_OUT_DATA_OUT24,0);	//FPGA_DIN
    CSL_FINS(gpioRegs->BANK[2].OUT_DATA,GPIO_OUT_DATA_OUT25,0);	//FPGA_CCLK
    CSL_FINS(gpioRegs->BANK[2].OUT_DATA,GPIO_OUT_DATA_OUT26,0);	//FPGA_PROG

    for(j=0;j<30;j++)	//led 3 times
	{
		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,0);
		for(i=0;i<5000000;i++);
		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,1);
		for(i=0;i<5000000;i++);
	}

    //    syscfgRegs->CFGCHIP2 = 0x000029f2;  // Internal USB clock, 24MHz system clock, out of reset, force host

	//wait for stay
	//for(i=0;i<500000;i++) asm(" nop");

	/* Wait Until PHY Clock is Good */
//	while ((syscfgRegs->CFGCHIP2 & 0x00020000) == 0); // Wait Until PHY Clock is Good.

}
