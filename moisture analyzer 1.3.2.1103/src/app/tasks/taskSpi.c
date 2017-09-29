#include <stdio.h>
#include <xdc/std.h>
#include <string.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <Spi.h>
#include <scom.h>
#include <gooao_c6748.h>
#include <Psc.h>
#include <Spi_evmInit.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/iom.h>
#include <cslr/soc_C6748.h>
#include <cslr/cslr.h>
#include <ti/mathlib/mathlib.h>
#include <algorithm.h>
Spi_Params       spiParams;
extern EDMA3_DRV_Handle hEdma;
GIO_Handle  spiHandle  = NULL;
double tempo_temper = 0, ntc_for_control = 0;

typedef enum{
	NOT_AVAILABLE,
	R1_READY,
	NTC_READY,
	ALL_READY
}Spi_status;

void SpiProcess(void)
{
	Spi_DataParam       dataparam1, dataparam2;
	SizeT               size1 = 0, size2 = 0;
	Error_Block         eb;
	uint8_t DATA[8] = {0}, PT100[2] = {0}, R1[2] = {0}, NTC[2] = {0}, Ready_flag[2] = {0}, MSB[2] ,loopWrite[8] = {0};
	Error_init(&eb);
	intmax_t spi_tempo_count = 0;
	double PT100_V = 0, R1K_V = 0, PT100_R = 0, NTC_V = 0, NTC_R = 0;
	SCOM_Handle hs_In2Spi, hs_Spi2Proc;
	ScomMessage *SpiMsgBuf;

	hs_In2Spi = SCOM_open("IN2SPI");
	hs_Spi2Proc = SCOM_open("SPI2P");
	Spi_status spi_runtime_status = NOT_AVAILABLE;

	if( !hs_In2Spi || !hs_Spi2Proc )
	{
		for(;;);
	}

	/* clear the spi params data structure                                    */
	memset(&dataparam1,0x00, sizeof(Spi_DataParam));
	memset(&dataparam2,0x00, sizeof(Spi_DataParam));

	loopWrite[0] = 0x07;
	loopWrite[1] = 0x31;
	loopWrite[2] = 0x03;
	loopWrite[3] = 0x45;
	loopWrite[4] = 0x02;
	loopWrite[5] = 0xAF;
	loopWrite[6] = 0x01;
	loopWrite[7] = 0x03;

	DATA[0] = 0x02;
	DATA[1] = 0xAF;
	DATA[2] = 0x02;
	DATA[3] = 0x8F;
	DATA[4] = 0x02;
	DATA[5] = 0x9F;
	DATA[6] = 0x40;
	DATA[7] = 0x44;

	dataparam1.inBuffer     = NULL;
	dataparam1.outBuffer    = (Uint8*)&loopWrite[0];
	dataparam1.dataFormat   = Spi_DataFormat_0;
	dataparam1.flags        = 0;
	dataparam1.bufLen       = 8u;
	size1 = dataparam1.bufLen;

	dataparam2.inBuffer     = &MSB[0];
	dataparam2.outBuffer    = NULL;
	dataparam2.bufLen       = 1u;
	dataparam2.dataFormat   = Spi_DataFormat_0;
	dataparam2.flags        = Spi_CSHOLD;
	size2 = dataparam2.bufLen;

	GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

	while(1)
	{
		SpiMsgBuf = SCOM_getMsg( hs_In2Spi, BIOS_WAIT_FOREVER );

		if(spi_tempo_count == 0)
		{
			spi_runtime_status = NOT_AVAILABLE;
			spi_tempo_count++;
		}
		else if(spi_tempo_count == 1)
		{
			spi_runtime_status = R1_READY;
			spi_tempo_count++;
		}
		else if(spi_tempo_count == 2)
		{
			spi_runtime_status = NTC_READY;
			spi_tempo_count = 0;
		}

		if(spi_runtime_status == NOT_AVAILABLE)
		{
			do
			{
				dataparam1.outBuffer  = (Uint8*)&DATA[6];
				dataparam1.bufLen  = 1u;
				GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

				dataparam2.inBuffer  = &Ready_flag[0];
				GIO_submit(spiHandle,IOM_WRITE, &dataparam2, &size2, NULL);
			}
			while((Ready_flag[0]&0x80) != 0x80);

			dataparam1.outBuffer  = (Uint8*)&DATA[7];
			dataparam1.bufLen  = 1u;
			GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

			dataparam2.inBuffer     = &R1[0];
			dataparam2.bufLen       = 2u;
			GIO_submit(spiHandle,IOM_WRITE, &dataparam2, &size2, NULL);


			dataparam1.outBuffer  = (Uint8*)&DATA[4];
			dataparam1.bufLen  = 2u;
			GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

		}

		if(spi_runtime_status == R1_READY)
		{
			do
			{
				dataparam1.outBuffer  = (Uint8*)&DATA[6];
				dataparam1.bufLen  = 1u;
				GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

				dataparam2.inBuffer  = &Ready_flag[0];
				GIO_submit(spiHandle,IOM_WRITE, &dataparam2, &size2, NULL);
			}
			while((Ready_flag[0]&0x80) != 0x80);

			dataparam1.outBuffer  = (Uint8*)&DATA[7];
			dataparam1.bufLen  = 1u;
			GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

			dataparam2.inBuffer     = &NTC[0];
			dataparam2.bufLen       = 2u;
			GIO_submit(spiHandle,IOM_WRITE, &dataparam2, &size2, NULL);

			dataparam1.outBuffer  = (Uint8*)&DATA[2];
			dataparam1.bufLen  = 2u;
			GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

		}

		if(spi_runtime_status == NTC_READY)
		{
			do
			{
				dataparam1.outBuffer  = (Uint8*)&DATA[6];
				dataparam1.bufLen  = 1u;
				GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

				dataparam2.inBuffer  = &Ready_flag[0];
				GIO_submit(spiHandle,IOM_WRITE, &dataparam2, &size2, NULL);
			}
			while((Ready_flag[0]&0x80) != 0x80);

			dataparam1.outBuffer  = (Uint8*)&DATA[7];
			dataparam1.bufLen  = 1u;
			GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

			dataparam2.inBuffer     = &PT100[0];
			dataparam2.bufLen       = 2u;
	    	GIO_submit(spiHandle,IOM_WRITE, &dataparam2, &size2, NULL);

	    	R1K_V = (double)(R1[0]*256+R1[1]);
	    	PT100_V =(double)(PT100[0]*256+PT100[1]);
	    	PT100_R = PT100_V/R1K_V * 10;
	    	NTC_V = (double)(NTC[0]*256+NTC[1]);
	    	NTC_V = NTC_V / 65536 * 3.3 * 1.0248 ;
	    	NTC_R = NTC_V / (3.3 - NTC_V) * 10;


	    	tempo_temper = NTC_Black_Iteration(PT100_R);
	    	SpiMsgBuf->PT100_Temparation = tempo_temper;

	    	tempo_temper = NTC_Iteration(NTC_R);
	    	SpiMsgBuf->NTC_Temparation = tempo_temper;
	    	ntc_for_control = tempo_temper;

	    	dataparam1.outBuffer  = (Uint8*)&DATA[0];
	        dataparam1.bufLen  = 2u;
	    	GIO_submit(spiHandle,IOM_WRITE, &dataparam1, &size1, NULL);

		}

	   	SCOM_putMsg(hs_Spi2Proc, SpiMsgBuf);
	}
}

void tskSpi(void)
{
	Error_Block 		eb;
	Spi_ChanParams      chanParams;
	GIO_Params 			ioParams;

	Error_init(&eb);

	/*
	 * Initialize channel attributes.
	 */
	 GIO_Params_init(&ioParams);

	 /* initialize the stream attributes                                       */

	 chanParams.hEdma 	= hEdma;
	 ioParams.chanParams = &chanParams;

	 /* create SPI channel for transmission */
	 spiHandle = GIO_create("/spi0", GIO_INOUT, &ioParams, &eb);

	 if (NULL == spiHandle)
	 {
	     printf("SPI Driver Handle creation Failed\n");
	 }
	 else
	 {
	     SpiProcess();
	 }
}

void spi_init(void)
{
	Spi_init();

	spiParams = Spi_PARAMS;

	spiParams.hwiNumber = 8;
	spiParams.spiHWCfgData.intrLevel = FALSE;
	spiParams.opMode = Spi_OpMode_POLLED;

	spiParams.outputClkFreq     = 1000000;
	spiParams.loopbackEnabled   = FALSE;
	spiParams.edmaHandle        = NULL;

	spiParams.spiHWCfgData.pinOpModes = Spi_PinOpMode_3PIN;

	spiParams.spiHWCfgData.configDatafmt[0].charLength   = 8;
	spiParams.spiHWCfgData.configDatafmt[1].charLength   = 16;
	spiParams.spiHWCfgData.configDatafmt[0].clkHigh      = TRUE;
	spiParams.spiHWCfgData.configDatafmt[0].lsbFirst     = FALSE;
	spiParams.spiHWCfgData.configDatafmt[0].oddParity    = FALSE;
	spiParams.spiHWCfgData.configDatafmt[0].parityEnable = FALSE ;
	spiParams.spiHWCfgData.configDatafmt[0].phaseIn      = FALSE ;
	spiParams.spiHWCfgData.configDatafmt[0].waitEnable   = FALSE;
	//spiParams.spiHWCfgData.configDatafmt[0].wdelay       = 0;
	spiParams.spiHWCfgData.intrLevel     = TRUE;

	if(Spi_OpMode_POLLED == spiParams.opMode)
	{
		System_printf("Spi is configured in polled mode");
	}
	else
	{
		System_printf("Error: unknown mode of operation!!!!!!!!!!");
	}

	return;
}
