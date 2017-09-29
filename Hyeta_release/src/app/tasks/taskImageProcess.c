/* BIOS6 include */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Timestamp.h>
#include<xdc/runtime/Types.h>
#include <ti/sysbios/hal/cache.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <scom.h>
#include <gooao_c6748.h>
#include <cslr/cslr_gpio.h>
#include <fr_uart.h>
#include <string.h>
#include <inttypes.h>
#include <algorithm.h>
//#define TEST_TIME_1
//#define TEST_TIME_2
extern CSL_GpioRegsOvly     gpioRegs;

uint8_t frame_avaliable[20] = {0};
int32_t index[21600] = {0};
int16_t led_flag = 0;
Types_FreqHz freq;

/* ========================================================================== */
/*                             手动设置图像数据保存位置，并且设定DMA的读取宽度为128字节                                 */
 /* ========================================================================== */

#pragma DATA_ALIGN(sendBuf, 128);
uint8_t temple_frame[20][350000] = {0};

#pragma DATA_SECTION(sendBuf,".TImage_Data");
#pragma DATA_ALIGN(sendBuf, 128);
uint8_t sendBuf[350000] = {0};

#pragma DATA_SECTION(sendBuf,".TImage_Data");
#pragma DATA_ALIGN(test_cmos_send, 128);
uint8_t test_cmos_send[21649] = {0};

/* ========================================================================== */
/*                             帧头固定的随机数组                                 */
 /* ========================================================================== */

uint8_t random_num[32] = {0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
						  0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
						  0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
						  0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A};

uint8_t send_baseMap[49]= {0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
	  	  	  	  	  	  	  	  	  	  	  	 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
	  	  	  	  	  	  	  	  	  	  	  	 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
	  	  	  	  	  	  	  	  	  	  	  	 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
	  	  	  	  	  	  	  	  	  	  	  	 0x0D, 0x46, 0x05, 0x00, 0x01, 0x08, 0x46, 0x05,
	  	  	  	  	  	  	  	  	  	  	  	 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF, 0x02, 0xDF,
	  	  	  	  	  	  	  	  	  	  	  	 0x01};

uint8_t random_test[49] = {0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
		  	  	  	  	  0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
		  	  	  	  	  0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
		  	  	  	  	  0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
						  0x6D, 0x54, 0x00, 0x00, 0x01, 0x68, 0x54, 0x00,
						  0x00, 0x00, 0x00, 0x00, 0x00, 0xB3, 0x00, 0x77,
						  0x00};

typedef enum {
    	NOTHING,
    	FIRST_BASEMAP_DONE,
    	FATCHING,
    	ERROR
}Runtime_Status;

void tskImageProcess(void)
{
/* ========================================================================== */
/*                             C程序应尽量避免使用全局变量                                 */
 /* ========================================================================== */
    void *inBuf;
	ScomMessage *pMsgBuf;
    SCOM_Handle hs_In2Proc,hs_Proc2In,hs_N2Proc, hs_Proc2N;
    int32_t imageSize, read_frame = 0 , offset = 32;
    int32_t i, j = 0, k = 0,m = 0;

    hs_In2Proc  = SCOM_open("IN2P");
    hs_Proc2In  = SCOM_open("P2IN");
    hs_N2Proc = SCOM_open("NET2P");
    hs_Proc2N = SCOM_open("P2NET");

    if( !hs_In2Proc || !hs_Proc2In || !hs_N2Proc || !hs_Proc2N)
    {
        for(;;);
    }

    memcpy(sendBuf, send_baseMap, 49);
    memcpy(test_cmos_send, random_test, 49);

    while(1)
    {
 /* ========================================================================== */
 /*                             接收Input线程的信号量                               */
 /* ========================================================================== */
    	pMsgBuf = SCOM_getMsg( hs_In2Proc, BIOS_WAIT_FOREVER );
    	imageSize = pMsgBuf->sizeLinear;
    	inBuf = pMsgBuf->bufLinear;
    	led_flag = 1 - led_flag;

    	CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,led_flag);	//led


		#pragma MUST_ITERATE(21600);
    	for(i = 0; i < 21600; i++)
    	{
    	    *(test_cmos_send+i+49) = *(uint8_t*)(inBuf+(i/180)*4*720+(i%180)*4);
    	}
    	memcpy((void*)temple_frame[read_frame], test_cmos_send, 21649);

    	//memcpy(sendBuf+49, inBuf, 345600);
        //memcpy((void*)temple_frame[read_frame], sendBuf, 345649);

        frame_avaliable[read_frame] = 1;
        read_frame++;
        read_frame = read_frame*(read_frame < 20);
/* ========================================================================== */
/*                              进入网络线程，发送数据                                                                      */
/* ========================================================================== */
        SCOM_putMsg( hs_Proc2N, pMsgBuf );
        pMsgBuf = SCOM_getMsg( hs_N2Proc, BIOS_WAIT_FOREVER );

        SCOM_putMsg( hs_Proc2In, pMsgBuf );
    }
}

