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

#pragma DATA_SECTION(baseMap,".TImage_Data");
#pragma DATA_ALIGN(baseMap, 128);
uint8_t baseMap[345600] = {0};

#pragma DATA_SECTION(bufCopy,".TImage_Data");
#pragma DATA_ALIGN(bufCopy, 128);
uint8_t bufCopy[345600] = {0};

#pragma DATA_SECTION(baseSum,".TImage_Data");
#pragma DATA_ALIGN(baseSum, 128);
uint16_t baseSum[345600] = {0};

#pragma DATA_SECTION(diffMap,".TImage_Data");
#pragma DATA_ALIGN(diffMap, 128);
uint8_t diffMap[21600] = {0};

//#pragma DATA_SECTION(diffMap_test,".TImage_Data");
//#pragma DATA_ALIGN(diffMap_test, 128);
//uint8_t diffMap_test[21600] = {0};

//uint8_t inBuf_test[345600] = {0};

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
	  	  	  	  	  	  	  	  	  	  	  	 0x0D, 0x46, 0x05, 0x00, 0xff, 0x08, 0x46, 0x05,
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
    size_t lenthTemp = 0;
    uint16_t x_leftTemp, x_rightTemp, y_topTemp, y_bottomTemp, xTemp;
    int32_t startTime;
    int32_t i, j = 0, k = 0,m = 0, ret, fan_count = 2000, p, q;
    intmax_t picNum = 0;
    uint8_t numDrop = 0;
    uint32_t dataLenth = 0, rain_dataLenth = 0;
    Runtime_Status runtimeStatus = NOTHING;
    RainParameter tempComponent  = (struct RainParameter_){0};
    RainParameter rainBuf[40];

    hs_In2Proc  = SCOM_open("IN2P");
    hs_Proc2In  = SCOM_open("P2IN");
    hs_N2Proc = SCOM_open("NET2P");
    hs_Proc2N = SCOM_open("P2NET");

    if( !hs_In2Proc || !hs_Proc2In || !hs_N2Proc || !hs_Proc2N)
    {
        for(;;);
    }

/* ========================================================================== */
/*                             为避免反复计算大小图像的坐标，将计算结果提前保存到数组                                */
/* ========================================================================== */

	#pragma MUST_ITERATE(21600)
    for(i = 0; i < 21600; i++)
    {
    	index[i] = (i / 180) * 2880 + (i % 180) * 4;
    }
    memcpy(sendBuf, random_num, 32);

    while(1)
    {
 /* ========================================================================== */
 /*                             接收Input线程的信号量                               */
 /* ========================================================================== */
    	pMsgBuf = SCOM_getMsg( hs_In2Proc, BIOS_WAIT_FOREVER );
    	imageSize = pMsgBuf->sizeLinear;
    	inBuf = pMsgBuf->bufLinear;
    	picNum = pMsgBuf->ptkcount;
//    	memset(inBuf_test, 0x80, sizeof(inBuf_test));
//    	imageSize = 720*480;
//    	inBuf = (void*)inBuf_test;
//    	picNum++;
    	led_flag = 1 - led_flag;

    	memcpy(bufCopy, inBuf, 345600);

    	CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT31,led_flag);	//led

 /* ========================================================================== */
 /*                              初始状态获取第一幅底图并且丢掉，开始获得的底图数据错误                                   */
 /* ========================================================================== */

        if( runtimeStatus == NOTHING)
    	{
    		memcpy(baseMap + j*21600, inBuf + j*21600 , 21600);
    		j++;
    		j = j * (j < 16);

    		if (j == 0)
    		{
    			runtimeStatus = FIRST_BASEMAP_DONE;
    		}
    		goto leave;
    	}
/* ========================================================================== */
/*                              获取能用的底图，每256幅图构成一幅新的底图                                   */
/* ========================================================================== */
    	if( runtimeStatus == FIRST_BASEMAP_DONE || runtimeStatus == FATCHING)
    	{
    		j++;
    		CalSumMap(baseSum, (uint8_t*)inBuf, k);
    		k++;
    		k = k * (k < 16);
    	}

    	if( j > 255)
    	{
#ifdef TEST_TIME_1
    	Timestamp_getFreq(&freq);
    	startTime = Timestamp_get32();
#endif
    		CalBaseMap(baseSum, baseMap);
#ifdef TEST_TIME_1
    	 printf("base_average time is %f ms\n", ((double)(Timestamp_get32() - startTime)/(double)freq.lo)*1000);
#endif
    		memset(baseSum, 0, sizeof(baseSum));
    		j = 0;
    		runtimeStatus = FATCHING;
    	}
/* ========================================================================== */
/*                                      通过阈值判断出哪里有目标值，并放入压缩图                                   */
/* ========================================================================== */
#ifdef TEST_TIME_2
    	Timestamp_getFreq(&freq);
    	startTime = Timestamp_get32();
#endif

    	 CalDiffMap(baseMap, (uint8_t*)inBuf, diffMap, index);

#ifdef TEST_TIME_2
    	 printf("search component time is %f ms\n", ((double)(Timestamp_get32() - startTime)/(double)freq.lo)*1000);
#endif
/* ========================================================================== */
/*                              当底图可用时，开始通过压缩图求解前N个最大雨滴,所有寻找到的范围扩大7个像素                             */
/* ========================================================================== */
    	if(runtimeStatus == FATCHING)
    	{
    		numDrop = 0;
    		for(i = 0; i < 40; i++)
    		{
    			rainBuf[i] = (struct  RainParameter_){0};
    		}

    		for(i = 0; i < 21600; i++)
    		{
    			if(diffMap[i] == 0xff)
    			{
    				x_leftTemp = i % 180;
    				x_rightTemp = i % 180;
    				y_topTemp = i / 180;
    				y_bottomTemp = i / 180;

    				do{
    					ret = SearchComponent(&x_leftTemp, &x_rightTemp, &y_topTemp, &y_bottomTemp, diffMap);
    				}
    				while(ret);

    				lenthTemp = (size_t)(x_rightTemp - x_leftTemp + 1);
    				xTemp = x_leftTemp;
    				for(m = y_topTemp; m <  y_bottomTemp + 1; m++)
    				{
    			    		memset(&diffMap[0] +180 * m + xTemp , 0 , lenthTemp);
    				}

#ifdef TEST_Component
    				for(n = x_leftTemp; n < x_rightTemp + 1; n++)
    				{
    					diffMap_test[y_topTemp * 180 + n] = 0xff;
    					diffMap_test[y_bottomTemp * 180 + n] = 0xff;
    				}

    				for(n = y_topTemp; n < y_bottomTemp + 1; n++)
    				{
    					diffMap_test[n * 180 + x_leftTemp] = 0xff;
    					diffMap_test[n * 180 + x_rightTemp] = 0xff;
    				}
#endif

    				tempComponent.left = x_leftTemp*4 - 7*((int16_t)(x_leftTemp*4 - 7) >= 0);
    				tempComponent.right = x_rightTemp*4 + 7*((x_rightTemp*4 + 7) < 720);
    				tempComponent.top = y_topTemp*4 - 7*((int16_t)(y_topTemp*4 - 7) >= 0);
    				tempComponent.bottom = y_bottomTemp*4 + 7*((y_bottomTemp*4 + 7) < 480);
    				tempComponent.area = (tempComponent.right - tempComponent.left + 1) * (tempComponent.bottom - tempComponent.top + 1);

    				if(tempComponent.area > rainBuf[0].area)
    				{
    					memcpy(rainBuf, &tempComponent, sizeof(tempComponent));
    					BubbleSort(40, rainBuf);
    					numDrop = numDrop + 1*(numDrop <40);
    				}
    			}
    		}
    	}
/* ========================================================================== */
/*                              风扇控制                                   */
/* ========================================================================== */
    	fan_count--;
    	if(rainBuf[37].area > 280)//280为大约3*3像素的雨滴
    	{
    		fan_count = 2000;
    		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT0,1);
    	}

    	if(fan_count <= 0)
    	{
    		fan_count = 0;
    		CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT0,0);
    	}
/* ========================================================================== */
/*                              发送得到的雨滴数据                                   */
/* ========================================================================== */
    	dataLenth = 0;
    	offset = 32;

    	if(picNum <= 2000)
    	{
    		for(i = 40; i > 40 - numDrop ; i--)
    		{
    			dataLenth += rainBuf[i - 1].area +12;
    		}

    		dataLenth += 1;
    		memcpy(sendBuf+offset, &dataLenth, 4);
    		offset += 4;
    		sendBuf[offset] = numDrop;
    		offset +=1;

    		for(i = 40; i > 40 - numDrop; i--)
    		{
    			rain_dataLenth = rainBuf[i - 1].area + 8;
    			memcpy(sendBuf+offset, &rain_dataLenth, 4);			//拷贝第n个雨滴的数据所占字节总数
    			offset += 4;
    			memcpy(sendBuf+offset, &rainBuf[i - 1], 8);		//拷贝第n个雨滴的左坐标
    			offset += 8;

    			lenthTemp = (size_t)(rainBuf[i - 1].right - rainBuf[i - 1].left + 1);
    			xTemp = rainBuf[i - 1].left;

    			for(m = rainBuf[i - 1].top; m <  rainBuf[i - 1].bottom + 1; m++)
    			{
    				memcpy(sendBuf+offset, bufCopy + 720*m + xTemp, lenthTemp);
    				//memcpy(sendBuf+offset, inBuf + 720*m + xTemp, lenthTemp);
    				offset +=  lenthTemp;
    			}
    		}
    	}
/* ========================================================================== */
/*                              每6000帧发送一副最新的底图，其灰度值为阈值                                   */
/* ========================================================================== */
    	if(picNum > 2000)
    	{
    		pMsgBuf->ptkcount = 0;
    		//picNum = 0;
    		memcpy(sendBuf, send_baseMap, 49);
    		memcpy(sendBuf+49, baseMap, 345600);
    		offset = 345649;
    	}

        memcpy((void*)temple_frame[read_frame], sendBuf, offset);
        frame_avaliable[read_frame] = 1;
        read_frame++;
        read_frame = read_frame*(read_frame < 20);
/* ========================================================================== */
/*                              进入网络线程，发送数据                                                                      */
/* ========================================================================== */
        SCOM_putMsg( hs_Proc2N, pMsgBuf );
        pMsgBuf = SCOM_getMsg( hs_N2Proc, BIOS_WAIT_FOREVER );
leave:
       SCOM_putMsg( hs_Proc2In, pMsgBuf );
    }
}

