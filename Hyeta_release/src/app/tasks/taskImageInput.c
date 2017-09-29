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

#define MODE_NTSC                   (1)/* 720 x 480 aka NTSC */
#define MODE_PAL                    (2)/* 720 x 576 aka PAL */

/* Different connector types */
#define CONN_SVIDEO                 (1)
#define CONN_COMPOSITE              (2)

/* Different storage types - valid only for interlaced mode of operation*/
#define STORAGE_FIELD               (1)
#define STORAGE_FRAME               (2)

#define NUM_FRAME_BUFFERS           (4u)
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

/* currently processed packet count                                           */
intmax_t  pktCount = 1;
Vpif_Params   vpifParams;
int32_t k=0;
extern CSL_GpioRegsOvly     gpioRegs;
double Average_Gray = 0, Average_Gray_Tempo = 0;
uint8_t *ptr[10];

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
    Int bufCount;
    Vpif_StdInfo        capParams;
    Uint32              capheight, capwidth,sizeimage;
    int32_t i;
    Edc_RegData regval;
    ScomMessage scomMsg;
    SCOM_Handle hs_Proc2In, hs_In2Proc;
	Char *vpifCapStrings = "/Vpif0/0/i2c0/MT9V024/0x5C";
    hs_Proc2In  = SCOM_open("P2IN");
    hs_In2Proc   = SCOM_open("IN2P");

    if( !hs_Proc2In || !hs_In2Proc)
    {
        for(;;);
    }

    System_printf("VPIF_SAMPLE :Starting Sample Application...\r\n");

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
                ptr[bufCount] = (uint8_t*)capChInfo.frame->frame.rpFrm.buf;
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
        while (1)
        {

        	//CSL_FMK(TMR_WDTCR_WDKEY, CSL_TMR_WDTCR_WDKEY_CMD1);
        	Cache_inv(capChInfo.frame->frame.rpFrm.buf,
                        sizeimage,
                        Cache_Type_ALL,
                        TRUE);

        	status = FVID_exchange(capChInfo.chanHandle, &(capChInfo.frame));
        	if (IOM_COMPLETED != status)
        		break;
        	scomMsg.bufLinear = capChInfo.frame->frame.rpFrm.buf;
        	scomMsg.sizeLinear = sizeimage;
        	scomMsg.ptkcount = pktCount;

        	SCOM_putMsg(hs_In2Proc, &scomMsg);
        	SCOM_getMsg(hs_Proc2In, BIOS_WAIT_FOREVER);
        	pktCount = scomMsg.ptkcount;
        	//CSL_FMK(TMR_WDTCR_WDKEY, CSL_TMR_WDTCR_WDKEY_CMD2);
        	pktCount++;
        }
    }
}

