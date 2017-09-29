/* BIOS6 include
 * 2016-10-12 由于线程溢出错误将熵值计算移到此线程内，扩大此线程栈空间至8192
 * 2016-10-13 增加了图形坏点判定，将底图的16384个最大最小的点全部去掉
 * 2016-10-15 点数删除范围过大，保留算法程序，暂停功能
 * @author 苏伟
 * */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <scom.h>
#include <gooao_c6748.h>
#include <fr_uart.h>
#include <stdlib.h>
#include <string.h>
#include <cslr/cslr_gpio.h>
#include <cslr/cslr_ehrpwm.h>
#include <cslr/cslr_tmr.h>
#include <math.h>
#include <ti/imglib/imglib.h>
#include <ti/mathlib/mathlib.h>
#include <algorithm.h>
#include <stdint.h>

//#include other image process algorithms head files

extern CSL_GpioRegsOvly     gpioRegs;
extern CSL_EhrpwmRegsOvly   pwmRegs;
extern intmax_t pktCount;

uint8_t Basemap[360*240] = {0};
uint8_t test_map[360*240] = {0};
uint8_t SOBEL_Basemap[360*240] = {0};
uint8_t SOBEL_Newpattern[360*240] = {0};
uint8_t new_pattern[360*240] = {0};
uint8_t Pattern_ConDomain[360*240] = {0};
double tempo_count3 = 0, sobel_power;
intmax_t tempo_count1 = 0, tempo_count2 = 0;
int16_t   histImage[360*240] = {0};
double high_level_count=0, high_level_ini=0, high_level_buf = 0;
double Moving_sequence_High[20] = {0}, Moving_sequence_Low[100] = {0};
double GLCM_Tempo[64], Difference_AG_Tempo = 0;
int16_t GLAM_Distance = 5, ConnectDomain_Flag = 0, mutex = 0;
volatile double PWM_Control_Buf = 0, last_PWM_Control_Buf = 0, Heat_Control_Buf = 0, ntc_buf = 0, KD_Control_Buf = 0, pt100_buf = 0;
//mul用来控制结露量
double KP = 1000, KI = 2, KD = 0, Slope_High = 0, Slope_Low = 0, mul = 2, connect_domain_value = 0;// 常温 400 2 2|-40  4000 16 8|-20 2000 8 4|-10 800 4 2|-30 3000 12 6
static Abandon_pixel_tag abandon_pixel_top[4096];

typedef enum{
	START_HEAT,
	NATURE_COOL,
	INITIAL_STATE_ACQUISITION,
	NORMAL_CONTROL,
	PWM_CONTROL
}C6748_Runtime_Status;

typedef enum{
	SEARCH_DEW_POINT_RANGE,
	ACCURACY_CONTROL
}Accuracy_Control_Status;

typedef enum{
	NOISE_ACQUISTION_READY,
	NEED_NOISE_ACQUISTION
}Noise_Acquistion_Status;


void tskImageProcess(void)
{
	C6748_Runtime_Status runtime_status = START_HEAT;
	Accuracy_Control_Status refrigeration_status = SEARCH_DEW_POINT_RANGE;
	Noise_Acquistion_Status noise_status = NEED_NOISE_ACQUISTION;
	int32_t i;
	void *inBuf = NULL;
	double entropy = 0, contrast = 0;
	double control_quantity = 0, control_quantity_tempo = 0, control_quantity_noise = 0, last_control_quantity = 0, sum_control_quantity = 0, final_control_quantity = 0, last_KI = 0;

	ScomMessage *pMsgBuf = NULL;
    SCOM_Handle hs_Proc2In;
    SCOM_Handle hs_Proc2UM,hs_UM2Proc;
    SCOM_Handle hs_Spi2Proc;


    hs_Proc2In  = SCOM_open("P2IN");
    hs_Proc2UM = SCOM_open("P2UM");
    hs_UM2Proc = SCOM_open("UM2P");
    hs_Spi2Proc = SCOM_open("SPI2P");


    if( !hs_Proc2In || !hs_Proc2UM || !hs_UM2Proc || !hs_Spi2Proc )
    {
        for(;;);
    }

    while(1)
    {
    	memset((void*)new_pattern, 0, sizeof(new_pattern));

    	// Get Input Buffer and image buffer size
        pMsgBuf = SCOM_getMsg( hs_Spi2Proc, BIOS_WAIT_FOREVER );
        inBuf = pMsgBuf->bufLinear;
        ntc_buf = pMsgBuf->NTC_Temparation;
        pt100_buf = pMsgBuf->PT100_Temparation;

        //确定露点仪工作状态
        if(pktCount <= 60)
        {
        	runtime_status = START_HEAT;
        }
        else if(pktCount > 60 && pktCount <= 120)
        {
            runtime_status = NATURE_COOL;
        }
        else if(pktCount > 120 && pktCount <= 125)
        {
        	runtime_status = INITIAL_STATE_ACQUISITION;
        }
        else if(pktCount > 125 && pktCount < 10000)
        {
            runtime_status = NORMAL_CONTROL;
        }
        else
        {
        	runtime_status = PWM_CONTROL;
        }

        //加热状态，PWM暂时以150递增， 温度若高于80摄氏度，停止加热
        if(runtime_status == START_HEAT)
        {
        	CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT12,1);

        	Heat_Control_Buf += 150;
        	if(Heat_Control_Buf > 20000)
        	{
        	    Heat_Control_Buf = 20000;
        	}

        	if(pMsgBuf->NTC_Temparation > 80)
        	{
        		Heat_Control_Buf = 0;
        	}

        	CSL_FINS(pwmRegs->CMPB,EHRPWM_CMPB_CMPB,(int)Heat_Control_Buf);
        	refrigeration_status = SEARCH_DEW_POINT_RANGE;
        }

        //自然降温状态，此时继电器跳转
        if(runtime_status == NATURE_COOL)
        {
        	CSL_FINS(pwmRegs->CMPB,EHRPWM_CMPB_CMPB,0);
        	Heat_Control_Buf = 0;
        }

        //初始图像获取状态，剔除高光点
        if(runtime_status == INITIAL_STATE_ACQUISITION)
        {
        	memset((void*)Basemap, 0, sizeof(Basemap));
        	memcpy(Basemap, inBuf, sizeof(Basemap));

        	CSL_FINS(gpioRegs->BANK[0].OUT_DATA,GPIO_OUT_DATA_OUT12,0);

        	IMG_sobel_3x3_8(Basemap, SOBEL_Basemap, 360, 240);

        	for(i = 0; i < 4096; i++)
        	{
        		abandon_pixel_top[i].grey = SOBEL_Basemap[i];
        	    abandon_pixel_top[i].position = i;
        	}

        	BuildHeap_MAX(4096, abandon_pixel_top);

        	for(i = 4096; i < 360*240; i++)
        	{
        		if(SOBEL_Basemap[i] > abandon_pixel_top->grey)
        	    {
        			abandon_pixel_top->grey = SOBEL_Basemap[i];
        	        abandon_pixel_top->position = i;
        	        HeapAdjust_MAX(0, 4096, abandon_pixel_top);
        	    }
        	}
        	high_level_ini = 0;

        	for(i = 0; i <360*240; i++)
        	{
        		if(Basemap[i] > 200)
                {
        			high_level_ini++;
                }
        	}
        }

        //正常制冷状态或者手动控制制冷PWM输出状态
        if(runtime_status == NORMAL_CONTROL || runtime_status == PWM_CONTROL)
        {
        	memcpy(new_pattern, inBuf, sizeof(new_pattern));
//        	memcpy(SOBEL_Newpattern, inBuf, sizeof(SOBEL_Newpattern));
        	high_level_count = 0;

        	for(i = 0; i < 360*240; i++)
        	{
        		if(new_pattern[i] > 200)
        		{
        			high_level_count++;
        		}
        	}

        	IMG_sobel_3x3_8(new_pattern, SOBEL_Newpattern, 360, 240);

        	//统计高光点，屏蔽
        	for(i = 2048; i < 4096; i++)
        	{
        		SOBEL_Newpattern[abandon_pixel_top[i].position] = 0;

        		if(abandon_pixel_top[i].position+1 < 360*240)
        			SOBEL_Newpattern[abandon_pixel_top[i].position+1] = 0;

        		if(abandon_pixel_top[i].position-1 >= 0)
        			SOBEL_Newpattern[abandon_pixel_top[i].position-1] = 0;

        		if(abandon_pixel_top[i].position+360 < 360*240)
        			SOBEL_Newpattern[abandon_pixel_top[i].position+360] = 0;

        		if(abandon_pixel_top[i].position-360 >= 0)
        			SOBEL_Newpattern[abandon_pixel_top[i].position-360] = 0;

        		if(abandon_pixel_top[i].position+361 < 360*240)
        		    SOBEL_Newpattern[abandon_pixel_top[i].position+361] = 0;

        		if(abandon_pixel_top[i].position+359 < 360*240)
        			SOBEL_Newpattern[abandon_pixel_top[i].position+359] = 0;

        		if(abandon_pixel_top[i].position-359 >= 0)
        		    SOBEL_Newpattern[abandon_pixel_top[i].position-359] = 0;

        		if(abandon_pixel_top[i].position-361 >= 0)
        		    SOBEL_Newpattern[abandon_pixel_top[i].position-361] = 0;
        	}


        	memset((void*)GLCM_Tempo, 0, sizeof(GLCM_Tempo));
        	memset((void*)histImage, 0, sizeof(histImage));

			#pragma MUST_ITERATE (86400);

        	for(i = 0; i < 360*240; i++)
        	{
        		if(i % 360 == 0)
        			SOBEL_Newpattern[i] = 0;

        		if(i % 360 == 359)
        		    SOBEL_Newpattern[i] = 0;

        		if(i / 360 == 0)
        			SOBEL_Newpattern[i] = 0;

        		if(i / 360 == 239)
        			SOBEL_Newpattern[i] = 0;

        		if(SOBEL_Newpattern[i] < 12)
        		{
        			SOBEL_Newpattern[i] = 0;
        		}

        		//熵值图像分级
        		histImage[i] = SOBEL_Newpattern[i]  / 25;

        		if(histImage[i] > 7)
        		{
        			histImage[i] = 7;
        		}
        	}

        	if(ConnectDomain_Flag == 0)
        	{
        		memcpy(Pattern_ConDomain, SOBEL_Newpattern, 360*240);
        	    ConnectDomain_Flag = 1;
        	}

        	//计算灰度共生矩阵，共三个方向
			#pragma MUST_ITERATE (86400);

        	for(i = 0; i < 360*240; i++)
        	{
        		tempo_count1 = histImage[i];

        		if(i%360+GLAM_Distance >= 0 && i%360+GLAM_Distance < 360)
        		{
        			tempo_count2 = histImage[i + GLAM_Distance];
        			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
        		}

        		if(i%360-GLAM_Distance >= 0 && i%360-GLAM_Distance < 360)
        		{
        			tempo_count2 = histImage[i - GLAM_Distance];
        			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
        		}
        	}

			#pragma MUST_ITERATE (86400);

        	for(i = 0; i < 360*240; i++)
        	{
        		tempo_count1 =histImage[i];

        		if(i/360+GLAM_Distance >= 0 && i/360+GLAM_Distance < 240)
        		{
        			tempo_count2 = histImage[i + GLAM_Distance*360];
        			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
        		}

        		if(i/360-GLAM_Distance >= 0 && i/360-GLAM_Distance < 240)
        		{
        			tempo_count2 = histImage[i - GLAM_Distance*360];
        			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
        		}
       		}

			#pragma MUST_ITERATE (86400);

       		for(i = 0; i < 360*240; i++)
       		{
       			tempo_count1 = histImage[i];

       			if(i/360+GLAM_Distance >= 0 && i/360+GLAM_Distance < 240 && i%360+GLAM_Distance >= 0 && i%360+GLAM_Distance < 360)
       			{
       				tempo_count2 = histImage[i + GLAM_Distance*360 + GLAM_Distance];
       				GLCM_Tempo[tempo_count1*8+tempo_count2]++;
       			}

       			if(i/360-GLAM_Distance >= 0 && i/360-GLAM_Distance < 240 && i%360-GLAM_Distance >= 0 && i%360-GLAM_Distance < 360)
       			{
        			tempo_count2 = histImage[i - GLAM_Distance*360 - GLAM_Distance];
        			GLCM_Tempo[tempo_count1*8+tempo_count2]++;
        		}
        	}

        	for(i = 0; i <sizeof(GLCM_Tempo); i++)
        	{
        		tempo_count3 += GLCM_Tempo[i];
        	}

        	//计算熵值等表征参数
        	for(i = 0; i <sizeof(GLCM_Tempo); i++)
        	{
        		GLCM_Tempo[i] = GLCM_Tempo[i] / (double)tempo_count3;
        		entropy -= GLCM_Tempo[i] * log10dp(GLCM_Tempo[i]);
        		contrast += GLCM_Tempo[i] * powdp((i%8 - i/8), (double)2);
        	}

        	control_quantity_tempo = (entropy + contrast / 30) ;

        	if(noise_status == NEED_NOISE_ACQUISTION)
        	{
        		control_quantity_noise = control_quantity_tempo ;
        		noise_status = NOISE_ACQUISTION_READY;
        	}

        	control_quantity_tempo = control_quantity_tempo - control_quantity_noise;

        	if(control_quantity_tempo < 0)
        	{
        		control_quantity_tempo = 0;
        	}

        	mutex = 1;
        	high_level_buf = high_level_count-high_level_ini;
            high_level_buf = high_level_buf * (high_level_buf >= 0);
        	control_quantity = control_quantity_tempo * mul  + connect_domain_value / 1000 + (high_level_buf) / 5000;
        	mutex = 0;

        	for(i = 0; i < 19; i++)
        	{
        		Moving_sequence_High[i] = Moving_sequence_High[i+1];
        	}

        	Moving_sequence_High[19] = control_quantity;

#ifdef _TEST_SLOPE_
        	for(i = 0; i < 100; i++)
        	{
        		Moving_sequence_Low[i] = Moving_sequence_Low[i+1];
        	}

        	Moving_sequence_Low[99] = control_quantity;

        	Slope_Low = Lsqe(Moving_sequence_Low, 100);
#endif

        	Slope_High = Lsqe(Moving_sequence_High, 20);
        	if(runtime_status == NORMAL_CONTROL)
        	{

        		pktCount = 200;

        		//快速搜寻露点
        		if (refrigeration_status == SEARCH_DEW_POINT_RANGE)
        		{
        			if(control_quantity < 0.3)
        			{
        				PWM_Control_Buf += 30;

        				if(PWM_Control_Buf > 20000)
        				{
        					PWM_Control_Buf = 20000;
        				}
        			}
        			else
        			{
        				//搜索到露点附近后进行精确控制
        				refrigeration_status = ACCURACY_CONTROL;

        				if(ntc_buf >= 40)
        				{
        					KP = 200;
        				    KI = 2;
        				}
        				else if(ntc_buf < 40 && ntc_buf >=0)
        				{
        				    KP = -5 * ntc_buf + 400;
        				    KI = 2;
        				}
        				else if(ntc_buf < 0 && ntc_buf >= -10)
        				{
        				   KP = -40 * ntc_buf + 400;
        				   KI = ntc_buf / (-5) + 2;
        				}
        				else if(ntc_buf < -10 && ntc_buf >= -20)
        				{
        				       KP = -120 * ntc_buf - 400;
        				       KI = -2 * ntc_buf / 5;
        				}
        				else
        				{
        				       KP = 2000;
        				       KI = 8;
        				}

        				//快速搜寻露点后需要继承之前的控制量
        				sum_control_quantity = ( PWM_Control_Buf - 0.8 * KP ) / KI;
        				//sum_control_quantity = 0;
        				if(PWM_Control_Buf < 0)
        				{
        					PWM_Control_Buf = 0;
        				}
        			}

        			if(ntc_buf >= 40)
        			{
        				mul = 1;
        			}
        			else if(ntc_buf >=0 && ntc_buf <40)
        			{
        				mul = 2 - ntc_buf / 40;
        			}
        			else if(ntc_buf >= -20 && ntc_buf < 0)
        			{
        				mul = 2;
        			}
        			else if(ntc_buf < -20 && ntc_buf > -40)
        			{
        				mul = ntc_buf / (-5) - 2;
        			}
        			else
        			{
        				mul = 6;
        			}
        		}
        		else
        		{
        			if(ntc_buf >= 40)
        			{
        				KP = 200;
        				KI = 2;
        				KD = 0;
        				mul = 1;
        			}
        			else if(ntc_buf < 40 && ntc_buf >=0)
        			{
        				KP = -5 * ntc_buf + 400;
        				KI = 2;
        				KD = 0;
        				mul = 2 - ntc_buf / 40;
        			}
        			else if(ntc_buf < 0 && ntc_buf >= -10)
        			{
        				KP = -40 * ntc_buf + 400;
        				KI = ntc_buf / (-5) + 2;
        				KD = 0;
        				mul = 2;
        			}
        			else if(ntc_buf < -10 && ntc_buf >= -20)
        			{
        				KP = -40 * ntc_buf+400 ;
        				KI = -2 * ntc_buf / 5;
        				KD = 0;
        				mul = 2;//ntc_buf / (-5);
        			}
        			else if(ntc_buf < -20 && ntc_buf >= -40)
        			{
        				KP = -60 * ntc_buf;
//        				KI = -2 * ntc_buf / 5;
        				KI = 8;
        				KD = 0;
        				mul = ntc_buf / (-5) - 2;
        			}
        			else
        			{
        			     KP = 2400;
        			     KI = 8;
        			     KD = 0;
        			     mul = 6;
        			}


#ifdef _TEST_SLOPE_
        			if(ntc_buf <= -30)
        			{
        				KD_Control_Buf = Slope_Low;
        			}
        			else if(ntc_buf >= 0)
        			{
        				KD_Control_Buf = Slope_High;
        			}
        			else
        			{
        				KD_Control_Buf = (ntc_buf / 30 + 1) * Slope_High + ntc_buf / -30 * Slope_Low;
        			}
#endif

//        			PWM_Control_Buf += KI * (2 - control_quantity)   + KP * (2 - control_quantity - last_control_quantity)  -
//        					KD * (Slope_High)  / 2  ;

        			final_control_quantity = 2 - control_quantity;

        			if(final_control_quantity < -2)
        			{
        				final_control_quantity = -2;
        			}

        			sum_control_quantity*=last_KI;
        			sum_control_quantity/=KI;
        			sum_control_quantity+=final_control_quantity;

        			PWM_Control_Buf = KP * final_control_quantity + KI * sum_control_quantity;

        			if(PWM_Control_Buf - last_PWM_Control_Buf > 150)
        			{
        				PWM_Control_Buf = last_PWM_Control_Buf + 150;
        			}
        			else if(PWM_Control_Buf - last_PWM_Control_Buf < -150)
        			{
        				PWM_Control_Buf = last_PWM_Control_Buf - 150;
        			}

        			if(PWM_Control_Buf > 20000)
        			{
        				PWM_Control_Buf = 20000;
        			}
        			if(PWM_Control_Buf < 0)
        			{
        			    PWM_Control_Buf = 0;
        			}
        		}
        		last_KI = KI;
        		//sum_control_quantity += final_control_quantity;
        		last_control_quantity = final_control_quantity;
        		last_PWM_Control_Buf = PWM_Control_Buf;
        		pMsgBuf->PWM_value = (uint16_t)PWM_Control_Buf;

        		//防止PWM变化过快
        		if (sum_control_quantity > 20000 / KI)
        		{
        			sum_control_quantity = 20000/KI;
        		}

        		if (sum_control_quantity < -4000/KI)
        		{
        			sum_control_quantity = -4000/KI;
        		}

        		CSL_FINS(pwmRegs->CMPB, EHRPWM_CMPB_CMPB, (int)PWM_Control_Buf);
        	}

        	if(runtime_status == PWM_CONTROL)
        	{
        		CSL_FINS(pwmRegs->CMPB, EHRPWM_CMPB_CMPB, (int)PWM_Control_Buf);
        		pktCount = 20000;
        	}

        	pMsgBuf->control_quantity = control_quantity;
        	printf("Entropy = %f PWM count = %d contrast = %f control_quantity = %f NTC = %f PT100 = %f H = %f\n" ,entropy,
        			(int)PWM_Control_Buf, contrast, control_quantity, ntc_buf, pt100_buf, high_level_count);

        	entropy = 0;
        	contrast = 0;
        	tempo_count3 = 0;
        	tempo_count1 = 0;
        }
        SCOM_putMsg(hs_Proc2UM, pMsgBuf);
        SCOM_getMsg(hs_UM2Proc, BIOS_WAIT_FOREVER);
        CSL_FMK(TMR_WDTCR_WDKEY, CSL_TMR_WDTCR_WDKEY_CMD2);
        SCOM_putMsg(hs_Proc2In, pMsgBuf);
    }
}

