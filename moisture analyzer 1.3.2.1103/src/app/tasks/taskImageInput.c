/* BIOS6 include */
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/task.h>
#include <ti/sysbios/io/DEV.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/hal/cache.h>

#include <string.h>
#include <scom.h>
#include <stdlib.h>
#include <gooao_c6748.h>
#include <cslr/cslr_gpio.h>
#include <cslr/cslr_tmr.h>

#include <Fvid.h>
#include <Vpif.h>
#include <Edc.h>

#include <MT9V024.h>
#include <MT9V024Local.h>
#include <CodecInterfaceLocal.h>

#include <algorithm.h>

#define MODE_NTSC                   (1)/* 720 x 480 aka NTSC */
#define MODE_PAL                    (2)/* 720 x 576 aka PAL */

/* Different connector types */
#define CONN_SVIDEO                 (1)
#define CONN_COMPOSITE              (2)

/* Different storage types - valid only for interlaced mode of operation*/
#define STORAGE_FIELD               (1)
#define STORAGE_FRAME               (2)

#define NUM_FRAME_BUFFERS           (3u)
#define VIDEO_MODE                  (MODE_NTSC)

#define CAPTURE_CONNECTOR           (CONN_COMPOSITE)
#define VIDEO_STORAGE               (STORAGE_FRAME)

/* Structure to store each driver channel information                         */
typedef struct ChannelInfo_t
{
    FVID_Handle chanHandle;     /* Channel handle                             */
    FVID_Frame *frame;          /* Current FVID frame buffer pointer          */
}ChannelInfo;

/* ========================================================================== */
/*                          LOCAL VARIABLES                                   */
/* ========================================================================== */
extern Semaphore_Handle semIn2P;	//input->Process
extern Semaphore_Handle semP2In;

/* currently processed packet count                                           */
intmax_t pktCount = 0;
Vpif_Params   vpifParams;
static uint8_t *tempo_pic[4];
static uint8_t average_4_pic[720*480];
static uint8_t press_pic[360*240];
int k=0;
extern CSL_GpioRegsOvly     gpioRegs;
double Average_Gray = 0, Average_Gray_Tempo = 0;
static Abandon_pixel_tag abandon_pixel_min[1024];
Void userVpif0Init()
{
    Vpif_init();
    vpifParams 				= Vpif_PARAMS;
    vpifParams.hwiNumber 	= 9u;
    vpifParams.dmaReqSize 	= Vpif_DmaReqSize_256BYTE;
}

Void tskImageInput(Void)
{
    Vpif_CapChanParams  vCapParamsChan;
    ChannelInfo capChInfo;
    Int status = IOM_COMPLETED;
    int32_t  bufCount;
    Vpif_StdInfo        capParams;
    uint32_t              capheight, capwidth,sizeimage;
    uint16_t integration_value_tempo = 0x37D;
    uint8_t integration_value[2] = {0x03, 0x7D};
    int32_t i, j;
    Edc_RegData regval;
    Uint8 MT9V024Reg[][3] =
    {
            {MT9V024_TOTALSHUTWIDTH_A_REG, 0x03,0x7D},//Total integration time in number of rows 0-7ffd manulcontrol
    };
    ScomMessage scomMsg;
    SCOM_Handle hs_Proc2In, hs_In2Spi, hs_Timer2In;
	Char *vpifCapStrings = "/Vpif0/0/i2c0/MT9V024/0x5C";

	hs_Timer2In = SCOM_open("T2IN");
    hs_Proc2In  = SCOM_open("P2IN");
    hs_In2Spi   = SCOM_open("IN2SPI");

    for(j = 0;j < 4; j++)
    {
    	tempo_pic[j]= (unsigned char*)malloc(720*480*sizeof(unsigned char));
    }
    memset((void*)average_4_pic, 0, sizeof(average_4_pic));
    memset((void*)press_pic, 0, sizeof(press_pic));

    if( !hs_Proc2In || !hs_In2Spi ||!hs_Timer2In)
    {
        for(;;);
    }

    System_printf("VPIF_SAMPLE :Starting Sample Application...\r\n");

    //cmos供电使能
//    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT13,0);
//    for(i=0;i<1000000;i++);
//    CSL_FINS(gpioRegs->BANK[3].OUT_DATA,GPIO_OUT_DATA_OUT13,1);

    /* Create and configure capture drivers */
    vCapParamsChan.capEdcTbl                    = &MT9V024_Fxns;
    vCapParamsChan.capChannelIoMode             = Vpif_IoMode_RAW_CAP;	//Vpif_IoMode_CAP;
    vCapParamsChan.capFbParams.frmBufAlignment  = 128u;
    vCapParamsChan.capFbParams.frmBufHeapHandle = NULL;/* Create from system heap*/

#if !(VIDEO_MODE == MODE_NTSC)
        vCapParamsChan.capStdMode = Vpif_VideoMode_RAW_576P;	//Vpif_VideoMode_PAL;
#else
        vCapParamsChan.capStdMode = Vpif_VideoMode_RAW_480P;	//Vpif_VideoMode_NTSC;
#endif /* #if !(VIDEO_MODE == MODE_NTSC) */

#if !(VIDEO_STORAGE == STORAGE_FRAME)
        vCapParamsChan.capStorageMode = Vpif_SdramStorage_FIELD;
#else
        vCapParamsChan.capStorageMode = Vpif_SdramStorage_FRAME;
#endif /* #if !(VIDEO_STORAGE == STORAGE_FRAME) */

	vCapParamsChan.capDataSize = Vpif_RawCaptureDataWidth_8BITS;
	vCapParamsChan.capFieldPol = Vpif_RawCapturePinPol_SAME;
	vCapParamsChan.capVPixPol = Vpif_RawCapturePinPol_SAME;
	vCapParamsChan.capHPixPol = Vpif_RawCapturePinPol_SAME;
    vCapParamsChan.capVideoParams = NULL;
    vCapParamsChan.capVbiService  = Vpif_VbiServiceType_NONE;

    capChInfo.chanHandle = FVID_create(vpifCapStrings,
                                       GIO_INPUT,
                                       &status,
                                       &vCapParamsChan,
                                       NULL);
    if ((IOM_COMPLETED != status) || (NULL == capChInfo.chanHandle))
    {
        System_printf("Failed to create capture raw channels");
    }

    if (IOM_COMPLETED == status)
    {
        status = FVID_control(capChInfo.chanHandle,
                              Vpif_IOCTL_CMD_GET_CHANNEL_STD_INFO,
                              &capParams);
        if (IOM_COMPLETED != status)
        {
             System_printf("Failed to get capture RAW channel info\r\n");
        }
    }
    else
    {
        System_printf("Failed to open - capture channel\r\n");
    }

    capheight  = capParams.activeLines;   //height
    capwidth   = capParams.activePixels;   //width or bytesperline
    sizeimage   = capheight * capwidth;   //sizeimage

    /* Allocate and Queue buffers for display & capture channel */
    if (IOM_COMPLETED == status)
    {
        for (bufCount = 0; bufCount < NUM_FRAME_BUFFERS; bufCount++)
        {
            /* Allocate Frame buffer for capture driver */
            status = FVID_allocBuffer(capChInfo.chanHandle, &(capChInfo.frame));
            if (IOM_COMPLETED != status)
            {
                System_printf("Failed to allocate buffer for capture\r\n");
            }
            else
            {
                System_printf("Cap: Alloc frame->frame.rpFrm = 0x%x\r\n", capChInfo.frame->frame.rpFrm.buf);
                System_printf("Cap: Alloc capChInfo.frame = 0x%x\r\n", capChInfo.frame);

            	memset((Uint8 *)capChInfo.frame->frame.rpFrm.buf,
                        0x80,
                        sizeimage);

                /* Queue the frame buffers for capture */
                status = FVID_queue(capChInfo.chanHandle, &(capChInfo.frame));
                if (IOM_COMPLETED != status)
                {
                    System_printf("Failed to Queue capture buffer\r\n");
                }
            }

            if (IOM_COMPLETED != status)
            {
                break;
            }
        }
    }
    else
    {
        System_printf("Failed to get params - capture channel\r\n");
    }

    /* Start capture operations */
    if (IOM_COMPLETED == status)
    {
       status = FVID_control(capChInfo.chanHandle, Vpif_IOCTL_CMD_START, NULL);
       if (IOM_COMPLETED != status)
       {
           System_printf("Failed to start capture channel device\r\n");
       }
    }
    else
    {
        System_printf("Failed to configure enc/dec\r\n");
    }

    /* Request a frame buffer from display & capture driver */
    if (IOM_COMPLETED == status)
    {
      status = FVID_dequeue(capChInfo.chanHandle, &(capChInfo.frame));
      if (IOM_COMPLETED != status)
       {
           System_printf("Failed to dequeue capture channel device\r\n");
       }
       System_printf("DQ Cap vpifFrm.rpFrm = 0x%x\r\n", capChInfo.frame->frame.rpFrm.buf);
    }
    else
    {
        System_printf("Failed to start display/capture driver\r\n");
    }

    if (IOM_COMPLETED == status)
    {
    	pktCount = 0;
        while (1)
        {
        	CSL_FMK(TMR_WDTCR_WDKEY, CSL_TMR_WDTCR_WDKEY_CMD1);
        	for(j = 0; j < 4; j++)
        	{
        	  Cache_inv(capChInfo.frame->frame.rpFrm.buf,
                        sizeimage,
                        Cache_Type_ALL,
                        TRUE);

        	  status = FVID_exchange(capChInfo.chanHandle, &(capChInfo.frame));
        	  if (IOM_COMPLETED != status)
        		  break;
        	  memcpy(tempo_pic[j], (capChInfo.frame->frame.rpFrm.buf), sizeof(average_4_pic));
        	}


        	Average_Gray_Tempo = 0;

        	for(j = 0; j < 720*480; j++)
        	{
        		average_4_pic[j] = (*(tempo_pic[0]+j) + *(tempo_pic[1]+j) + *(tempo_pic[2]+j) +*(tempo_pic[3]+j)) / 4;
        		//Average_Gray_Tempo += (double)average_4_pic[j];
        	}

        	for(i = 0; i < 1024; i++)
            {
        		abandon_pixel_min[i].grey =average_4_pic[i];
                abandon_pixel_min[i].position = i;
            }

        	BuildHeap_MIN(1024, abandon_pixel_min);

        	for(i = 1024; i < 720*480; i++)
        	{
                if(average_4_pic[i] < abandon_pixel_min->grey)
                {
                	abandon_pixel_min->grey = average_4_pic[i];
                	abandon_pixel_min->position = i;
                	HeapAdjust_MIN(0, 1024, abandon_pixel_min);
                }
        	}

        	for(i = 0; i < 1024; i++)
        	{
        		Average_Gray_Tempo += abandon_pixel_min[i].grey;
        	}

        	Average_Gray = Average_Gray_Tempo / 1024;

        	if(Average_Gray < 50 || Average_Gray > 70)
        	{
        		integration_value_tempo = integration_value_tempo / Average_Gray  * 60;
        		if(integration_value_tempo > 0x7ff)
        		{
        			integration_value_tempo = 0x7ff;
        		}
        		integration_value[0] = integration_value_tempo / 256;
        		integration_value[1] = integration_value_tempo % 256;
        		MT9V024Reg[0][1] = integration_value[0];
        		MT9V024Reg[0][2] = integration_value[1];

        		for(i = 0; i < 1; i++)
        		{
        			regval.startReg = MT9V024Reg[i][0];
        			regval.noRegToRW = 2u;
        			regval.value = &MT9V024Reg[i][1];
                  	status = FVID_control(capChInfo.chanHandle,Vpif_IOCTL_CMD_MAX + Edc_IOCTL_SET_REG,(Ptr)&regval);

                  	if(IOM_COMPLETED != status)
                  	{
                	  System_printf("Failed to set reg. of decoder");
                  	}
        		}
        	}
        	k = 0;
        	for(j = 0; j <= 720*480; j++)
        	{
        		if((j / 720) % 2 == 0 && (j % 720) % 2 == 0 && (j / 720 + 1) < 480 && (j % 720 + 1) < 720 )

        		{
        			press_pic[k] = (average_4_pic[j+1] + average_4_pic[j] + average_4_pic[j+720] + average_4_pic[j+721]) / 4;
        			k++;
        		}
        	}

//        	for(i = 119; i < 360; i++)
//        	{
//        		memcpy(press_pic + k, average_4_pic + i * 720 +180, 360);
//
        	k = k + 360;
//        	}
        	scomMsg.bufLinear = press_pic;

        	SCOM_putMsg(hs_In2Spi, &scomMsg);
        	SCOM_getMsg(hs_Proc2In, BIOS_WAIT_FOREVER);
        	SCOM_getMsg(hs_Timer2In, BIOS_WAIT_FOREVER);
        	pktCount++;
        }
    }
}

