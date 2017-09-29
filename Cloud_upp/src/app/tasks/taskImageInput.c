/* BIOS6 include */
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/io/DEV.h>
#include <ti/sysbios/io/GIO.h>

#include "string.h"
#include <stdio.h>
#include <Upp.h>
#include <UppLocal.h>
#include <scom.h>
#include <gooao_c6748.h>
#include <cslr/cslr_gpio.h>
#include <I2c.h>
#include <MT9V024Local.h>

extern CSL_GpioRegsOvly     gpioRegs ;//= (CSL_GpioRegsOvly)(CSL_GPIO_0_REGS);

Upp_Params     uppParams;
DEV_Handle uppDevHandle;

#define WORK_IMAGECAP(a)		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT6,a) //GP0_6
//#define WORK_CMOS(a)		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT5,a) //GP0_5
#define IMAGE_CS(a)		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT2,a) //GP0_2
#define STARTFRAME_PULSE(a)		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT4,a) //GP0_4
#define FPGA_RST(a)		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT0,a) //GP0_0
#define UPP_ERR         CSL_FEXT(gpioRegs->BANK[1].IN_DATA,GPIO_IN_DATA_IN11)	//GP2_11

unsigned int tCount;
#define NUM_BUFS              1         // Max of 1 outstanding requests
#define BUFALIGN              128       // align buffers to 128 bytes
#define BUFFER_SIZE           260

#define TAU_IMAGE_LSIZE       640		// image line size(16bit)
#define TAU_IMAGE_LNUM        512       // image lines

#define CMOS_IMAGE_LSIZE       720		// image line size(16bit)
#define CMOS_IMAGE_LNUM        480      // image lines

#define NORMIMAGE_LSIZE       640		// normalize image line size(16bit)
#define NORMIMAGE_LNUM        480       // image lines

#define IMAGEBUFSIZE          2*NORMIMAGE_LSIZE*NORMIMAGE_LNUM	//16bit 2*image size
#define TAU_IMAGEBUFSIZE          2*TAU_IMAGE_LSIZE*TAU_IMAGE_LNUM	//16bit 2*image size
#define CMOS_IMAGEBUFSIZE          2*CMOS_IMAGE_LSIZE*CMOS_IMAGE_LNUM	//16bit 2*image size
/* ========================================================================== */
/*                          LOCAL VARIABLES                                   */
/* ========================================================================== */
/* Handles for the TX and RX channels                                         */
GIO_Handle uppInHandle;
GIO_Handle uppInHandleB;
extern Upp_Params     uppParams;
extern DEV_Handle uppDevHandle;
extern Uint8 integration_value[2];

/* I2C channel handles  */
GIO_Handle      i2c_outHandle;                 /* handle to the TX channel */
GIO_Handle      i2c_inHandle;                  /* handle to the RX channel */
I2c_Params   i2cParams;

#pragma DATA_ALIGN(imageBufferTau, 128);
static uint8_t imageBufferTau[TAU_IMAGEBUFSIZE] = {0};	//16BIT
#pragma DATA_ALIGN(imageBufferCmos, 128);
static uint8_t imageBufferCmos[CMOS_IMAGEBUFSIZE] = {0};	//16BIT
uint8_t Value_imageBufferCmos[CMOS_IMAGEBUFSIZE] = {0};
uint8_t Quarter_Value_imageBufferCmos[CMOS_IMAGEBUFSIZE] = {0};
uint8_t *ImageBuf;
double Average_Gray_Tempo = 0, Average_Gray = 0;
/* array to hold the pointer to the allocated buffers                         */
Ptr buf[2 * NUM_BUFS];

/* Data structures to be used for submit                                      */
Upp_transParam  transParam[2];

/* currently processed packet count                                           */
Uint32 pktCount = 0;

/* parameters for channel A Receive image                                                  */
Upp_ChanParams uppChanparamARcv =
{
    TRUE,
    Upp_ChanSel_A,
    Upp_bitWidth_16,
    Upp_dataRate_SINGLE,
    Upp_ChanMode_NORMAL,
    Upp_dataPackFmt_RJZE,
    75000000,
    0xFFFF,
    NULL,
    NULL,
    NULL,
    NULL,
    Upp_fifoThreshold_64,
    {
        TRUE,
        Upp_polarity_ACTIVE_HIGH,
        TRUE,
        Upp_polarity_ACTIVE_HIGH,
        TRUE,
        Upp_polarity_ACTIVE_HIGH,
        Upp_clkPol_RISING_EDGE_SYNC,
        Upp_PinIdleState_IDLE_VAL,
    }
};

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */
void user_upp_init();
extern Void uart2_process(void);
extern IOM_Fxns Upp_IOMFXNS;

/* ===========================upp configuration=============================================== */
void user_upp_init()	//for receive
{
    Upp_init();

    uppParams = Upp_PARAMS;
    uppParams.devMode = Upp_DevMode_CHAN_A_RCV;	//Upp_DevMode_CHAN_AB_RCV;	//receive mode
    uppParams.dlbMode = Upp_Loopback_DISABLE;	//disable loopback,Upp_Loopback_DISABLE
    uppParams.emulationMode = Upp_EmuMode_RTEMU;//Upp_EmuMode_SOFT_STOP
    uppParams.pllDomain = Upp_pllDomain_0;	//Upp_pllDomain_NONE
    uppParams.pscPwrmEnable = FALSE;	//FALSE
//    uppParams.inputFreq = CSL_SYSCLK_2_FREQ;
//    uppParams.instHandlerSel = Upp_intHandlerSel_ECM;
    uppParams.hwiNumber = 7;
}

void UPPDEV_init(void)
{
	DEV_Params devParams;
	Error_Block eb;
	DEV_Params_init(&devParams);
	devParams.devid = 0;
	devParams.deviceParams = &uppParams;
	devParams.initFxn = &user_upp_init;

	Error_init(&eb);
	uppDevHandle = DEV_create("/upp0", &Upp_IOMFXNS, &devParams, &eb);
}
//---------------------------CMOS configuration-------------------------------
/*
 * I2C0 init function called when creating the driver.
 */
void user_i2c_init()
{
    I2c_init();

    i2cParams = I2c_PARAMS;
    i2cParams.busFreq = 100000;
    i2cParams.hwiNumber = 8;

    /* configure I2c for interrupt mode */
    i2cParams.opMode = I2c_OpMode_POLLED;

	if(I2c_OpMode_POLLED == i2cParams.opMode)
	{
		System_printf("I2c is configured in polled mode");
	}
	else if (I2c_OpMode_INTERRUPT == i2cParams.opMode)
	{
		System_printf("I2c is configured in interrupt mode");
	}
	else if (I2c_OpMode_DMAINTERRUPT == i2cParams.opMode)
	{
		System_printf("I2c is configured in dma mode");
	}
	else
	{
		System_printf("Error: unknown mode of operation!!!!!!!!!!");
	}
}

Void CodecI2cInit(Void)
{
	Error_Block 		eb;
    I2c_ChanParams     	chanParams;
 	GIO_Params 			ioParams;

    Error_init(&eb);

    /*
     * Initialize channel attributes.
     */
    GIO_Params_init(&ioParams);

    chanParams.hEdma = NULL;
    chanParams.masterOrSlave = I2c_CommMode_MASTER;

    ioParams.chanParams = &chanParams;

    System_printf("\r\nI2C  :Start of I2C sample application\n");

    /* Create the I2C Channels for the TX and RX communication                */
    i2c_outHandle = GIO_create("/i2c0", GIO_OUTPUT, &ioParams, &eb);
    System_printf("Stream_create(outHandle) returned status = %d\n", Error_getCode(&eb));

    i2c_inHandle  = GIO_create("/i2c0", GIO_INPUT, &ioParams, &eb);
    System_printf( "Stream_create(inHandle) returned status = %d\n", Error_getCode(&eb));

    if ((NULL == i2c_outHandle) || (NULL == i2c_inHandle) )
    {
    	System_printf("\r\nI2C : I2C Handle Create Failed.......!\n");
    }
}

Bool codecI2cWriteReg(Uint8 slaveAddr,
                   Uint8 subAddr,
                   const Uint8 *buffer,
                   Uint32 length)
{
    Uint8 			writeBuffer[BUFFER_SIZE + 1];
    I2c_DataParam	writeBuf;
    Bool 			writeRegFlag = IOM_COMPLETED;

	Error_Block 		eb;
    Error_init(&eb);

	/* Write to Slave Device */
	if (length <= BUFFER_SIZE)
	{
		/* Prepare the data to be written to the codec */
		writeBuffer[0] = subAddr;
		memcpy(&writeBuffer[1], buffer, length);

		writeBuf.buffer    = &writeBuffer[0];
		writeBuf.bufLen    = length + 1u;
		writeBuf.flags     = I2c_DEFAULT_WRITE;
		writeBuf.param     = NULL;
		writeBuf.slaveAddr = slaveAddr;

		GIO_submit(i2c_outHandle,
							IOM_WRITE,
							&writeBuf,
							&writeBuf.bufLen,
							NULL);

		if ((TRUE == Error_check(&eb)))
		{
			System_printf("I2c Write: Data Write Failed: %d\n",Error_getCode(&eb));
			writeRegFlag = IOM_EBADIO;
		}
	}

    /* Return the result of writing to registers */
    return writeRegFlag;
}

Bool codecI2cReadReg16(Uint8 slaveAddr,
                  Uint8 subAddr,
                  Uint16 *buffer,
                  Uint32 length)
{
    I2c_DataParam 	readBuf;
    Int32 			readCount = 0;
    Bool 			readRegFlag = IOM_COMPLETED;
    Uint8 			cmd[2];
	Error_Block 		eb;
    Error_init(&eb);

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

		//write command,send register address
		GIO_submit(i2c_outHandle,
							IOM_WRITE,
							&readBuf,
							&readBuf.bufLen,
							NULL);

		readBuf.bufLen    = 2;	//read 2 Byte for 16bit
		readBuf.flags     = I2c_READ | I2c_MASTER | I2c_START | I2c_STOP;

		/* read the data                                          */
		GIO_submit(i2c_inHandle,
							IOM_READ,
							&readBuf,
							&readBuf.bufLen,
							NULL);

		if ((TRUE == Error_check(&eb)))
		{
			System_printf("I2c Read: Data Read Failed: %d\n",Error_getCode(&eb));
			readRegFlag = IOM_EBADIO;
			break;
		}

        *buffer = (Uint16)(cmd[0]<<8) + cmd[1];	//*buffer = cmd[0];	//data get
		buffer++;
		subAddr++;
	}

     return readRegFlag;
}

Int32 MT9V024SetDefaultParams(void)
{
    Uint8 i;
    Uint32 setDefNumBytes = 2u;
    Bool setDefFlag;
    Int32 retVal = IOM_COMPLETED;

    Uint8 MT9V024AfterResetNTSCReg[][3] =
    {
        {MT9V024_SENSORTYPE_REG, 0x08,0x15},	//monochrome 黑白0x00
        {MT9V024_COLUMNSTART_REG, 0x00,0x11},	//coloum start:17.752-720=32,32/2=16
        {MT9V024_ROWSTART_A_REG, 0x00,0x04},	//row start:4
        {MT9V024_WINDOWHEIGHT_A_REG, 0x01,0xE0},//height:480
        {MT9V024_WINDOWWIDTH_A_REG, 0x02,0xD0},	//width:720
        {MT9V024_TOTALSHUTWIDTH_A_REG, 0x00,0x10},//Total integration time in number of rows 0-7ffd manulcontrol 0x41
        {MT9V024_AECAGCENABLE_REG, 0x00,0x00},	//0x01 enable auto Exposure/0x00 disable auto Exposure;Disable Automatic Gain
    };

    //configuration
    for (i = 0; i < 7; i++)
    {
        setDefFlag |= codecI2cWriteReg(MT9V024_IIC_ADDR,
                         MT9V024AfterResetNTSCReg[i][0],
                         &MT9V024AfterResetNTSCReg[i][1],
                         setDefNumBytes);	//2Bytes for 16bit
    }

    if (TRUE == setDefFlag)
    {
    	System_printf("MT9V024: Error from MT9V024SetDefaultParams\n");
        retVal = IOM_EBADIO;
    }
    else
    {
        retVal = IOM_COMPLETED;
    }

    return retVal;
}

Int32 MT9V024SetIntegration(void)
{
    Uint8 i;
    Uint32 setDefNumBytes = 2u;
    Bool setDefFlag;
    Int32 retVal = IOM_COMPLETED;

    //Total integration time in number of rows 0-7ffd manulcontrol 0x41
    Uint8 MT9V024AfterResetNTSCReg[0][3] = {MT9V024_TOTALSHUTWIDTH_A_REG, integration_value[0],integration_value[1]};

    setDefFlag |= codecI2cWriteReg(MT9V024_IIC_ADDR,
                     MT9V024AfterResetNTSCReg[0][0],
                    &MT9V024AfterResetNTSCReg[0][1],
                     setDefNumBytes);	//2Bytes for 16bit

    if (TRUE == setDefFlag)
    {
    	System_printf("MT9V024: Error from MT9V024SetDefaultParams\n");
        retVal = IOM_EBADIO;
    }
    else
    {
        retVal = IOM_COMPLETED;
    }

    return retVal;
}
/**
 *  @brief  Power Up or Power Down MT9V024. Sets devices power state to
 *          requested state, if possible.
 *
 *  @param  powerDownEnable [In] Flag to power-up or power-down MT9V024
 *
 *  @return IOM_COMPLETED on successful operation
 *          IOM_EBADARGS if error occurred
 */
static Int32 MT9V024PowerDown(Bool powerDownEnable)
{
    Uint8 pwrDnBuffer[2] = {0, 0};
    Bool pwrDnFlag;
    Int32 retVal = IOM_COMPLETED;
    int i;

    /* Write to Reset Register */
    pwrDnBuffer[0] = 0x00;
    pwrDnBuffer[1] = 0x01;	//reset
    pwrDnFlag = codecI2cWriteReg(MT9V024_IIC_ADDR,
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
        pwrDnFlag |= codecI2cWriteReg(MT9V024_IIC_ADDR,
                         MT9V024_RESET_REG,
                         &pwrDnBuffer[0],
                         2u);
    }

    if (TRUE == pwrDnFlag)
    {
    	System_printf("MT9V024: Error from MT9V024PowerDown\n");
        retVal = IOM_EBADIO;
    }
    else
    {
        retVal = IOM_COMPLETED;
    }
    System_printf("Exited ---> MT9V024PowerDown\n");
    return retVal;
}

/**
 *  \brief  Reset MT9V024
 *
 *  \return IOM_COMPLETED on successful operation
 *          IOM_EBADARGS if error occurred
 */
static Int32 MT9V024Reset(void)
{
    /* Reset MT9V024 */
    return MT9V024PowerDown(FALSE);
}

//--------------------------------task image input---------------------------------
//注意此函数中的tau配置是否开启
Void tskImageInput(Void)
{

    Upp_transParam    *rcv       = NULL;
    //uint32_t             count     = 0;
    int32_t              nmadus0   = 0;
    int32_t             status     = IOM_COMPLETED;
    SizeT size;
    int32_t i;
    uint16_t integration_value_tempo = 0x0010;
    uint8_t image_select = 1; //1 is CMOS ,0 is tau

    enum
    {
    	NON,
    	Value_Done,
    	Quarter_Done
    }image_status;

    ScomMessage scomMsg;
    SCOM_Handle hs_In2Proc,hs_Proc2In;

    Error_Block 		eb;
 	GIO_Params 			ioParams;
    Error_init(&eb);

    hs_In2Proc  = SCOM_open("IN2P");
    hs_Proc2In  = SCOM_open("P2IN");

    if( !hs_In2Proc || !hs_Proc2In )
    {
        for(;;);
    }

    image_status = NON;

    //uart2_process();//tau初始化配置

    //cmos configuration
    CodecI2cInit();
    MT9V024Reset();
    MT9V024SetDefaultParams();

    //upp configuration
    UPPDEV_init();		//receive upp mode

    GIO_Params_init(&ioParams);
    ioParams.chanParams = (Ptr)&uppChanparamARcv;
    ioParams.model = GIO_Model_ISSUERECLAIM;
    ioParams.numPackets = NUM_BUFS;

    uppInHandle  = GIO_create("/upp0", GIO_INPUT, &ioParams, &eb);
    if (NULL == uppInHandle) System_printf("Stream Creation Failed");

    transParam[0].windowAddr = imageBufferTau;
    transParam[0].bytesPerLine = TAU_IMAGE_LSIZE*2;
    transParam[0].lineCount = TAU_IMAGE_LNUM;
    transParam[0].lineOffset = TAU_IMAGE_LSIZE*2;

    transParam[1].windowAddr = imageBufferCmos;
    transParam[1].bytesPerLine = CMOS_IMAGE_LSIZE*2;
    transParam[1].lineCount = CMOS_IMAGE_LNUM;
    transParam[1].lineOffset = CMOS_IMAGE_LSIZE*2;

    if(!image_select)
    {
    	IMAGE_CS(0);
    	status = GIO_issue(uppInHandle, (Ptr)&transParam[0], TAU_IMAGEBUFSIZE, NULL);
    	scomMsg.sizeLinear = TAU_IMAGEBUFSIZE;
        if(status < 0)
        	System_printf("Issue to output stream failed.\n");
        scomMsg.camCelect = 0;
    }
    else
    {
    	IMAGE_CS(1);
    	status = GIO_issue(uppInHandle, (Ptr)&transParam[1], CMOS_IMAGEBUFSIZE, NULL);
    	scomMsg.sizeLinear = CMOS_IMAGEBUFSIZE;
        if(status < 0)
        	System_printf("Issue to output stream failed.\n");
        scomMsg.camCelect = 1;
    }
    WORK_IMAGECAP(0);	    //disable image capture
    FPGA_RST(0);	        //reset fpga all fsms
    FPGA_RST(1);
    WORK_IMAGECAP(1);	//    enable image capture
    STARTFRAME_PULSE(1);	//start pulse of capture one frame
    STARTFRAME_PULSE(0);

    while(1)
    {
		nmadus0 = GIO_reclaim(uppInHandle, (Ptr *)&rcv, &size, NULL);
		if (nmadus0 < 0) System_printf("\r\nError reclaiming full buffer from the input stream");

//	    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT4,1);	//enable TAU_NEXT_F
//	    CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT4,0);	//disable TAU_NEXT_F

	    ImageBuf = (unsigned char *)rcv->windowAddr;
        scomMsg.bufLinear = rcv->windowAddr;

        if(image_select == 1)
        {
        	if(image_status == NON)
        	{
        		memcpy(Value_imageBufferCmos, ImageBuf, sizeof(Value_imageBufferCmos));
        		image_status = Value_Done;

        		integration_value_tempo = (integration_value[0] *256 + integration_value[1]) / 5;
        		integration_value[0] = integration_value_tempo / 256;
        		integration_value[1] = integration_value_tempo % 256;
        		MT9V024SetIntegration();

        		IMAGE_CS(1);
        		status = GIO_issue(uppInHandle, (Ptr)&transParam[1], CMOS_IMAGEBUFSIZE, NULL);
        		if(status < 0)
        			System_printf("Issue to output stream failed.\n");

        		FPGA_RST(0);
        		FPGA_RST(1);

        		STARTFRAME_PULSE(1);
        		STARTFRAME_PULSE(0);
        		continue;
        	}
        	if(image_status == Value_Done)
        	{
        		memcpy(Quarter_Value_imageBufferCmos, ImageBuf, sizeof(Quarter_Value_imageBufferCmos));
        		image_status = Quarter_Done;

        		integration_value_tempo *= 5;
        		integration_value[0] = integration_value_tempo / 256;
        		integration_value[1] = integration_value_tempo % 256;
        	}
        }

        scomMsg.camCelect = image_select;
        printf("input ready to send msg\n");
        SCOM_putMsg( hs_In2Proc, &scomMsg );
        SCOM_getMsg( hs_Proc2In, BIOS_WAIT_FOREVER );
        printf("input has received the msg\n");
        image_status = NON;

        MT9V024SetIntegration();

        image_select = scomMsg.camCelect ;

        //if need to change image channel
        if(!image_select)
        {
        	IMAGE_CS(0);
        	status = GIO_issue(uppInHandle, (Ptr)&transParam[0], TAU_IMAGEBUFSIZE, NULL);
        	scomMsg.sizeLinear = TAU_IMAGEBUFSIZE;
        	if(status < 0)
        		System_printf("Issue to output stream failed.\n");
        }
        else
        {
        	IMAGE_CS(1);
        	status = GIO_issue(uppInHandle, (Ptr)&transParam[1], CMOS_IMAGEBUFSIZE, NULL);
        	scomMsg.sizeLinear = CMOS_IMAGEBUFSIZE;
        	if(status < 0)
        		System_printf("Issue to output stream failed.\n");
        }

        FPGA_RST(0);
        FPGA_RST(1);

        STARTFRAME_PULSE(1);
        STARTFRAME_PULSE(0);
        pktCount++;
    }
}


