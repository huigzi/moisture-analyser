/**
 *  \file   Tvp5150.h
 *
 *  \brief  This file contains configuration structure and enums for TVP5150
 *          decoder.
 *          User-programmable VBI formats for TVP5150 :
 *          Sliced VBI data during a vertical blanking period or active video
 *          period (full field mode)
 *            - CC and extended data service (EDS)
 *            - Wide screen signaling (WSS)
 *            - Copy generation management system (CGMS)
 *
 */

#ifndef _TVP5150_H_
#define _TVP5150_H_

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */
#include <xdc/std.h>
#include <Edc.h>

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

/* ========================================================================== */
/*                             TVP5150 DEFINES                                */
/* ========================================================================== */

/* ========================================================================== */
/*                             TVP5150 ENUMS                                  */
/* ========================================================================== */
/**
 *  \brief  TVP5150 Ioctl commands
 * Following IOCTL commands will be used to perform control operation on TVP5150
 * device. The following Ioctl commands are specifically for TVP5150. The
 * IOCTL command is passed as second argument to ctrl() function pointer of the
 * TVP5150 decoder device
 * NOTE: These IOCTL's will be available only if user adds Vpif_IOCTL_CMD_MAX
 * and Edc_IOCTL_CMD_MAX to these IOCTL calls, from application.
 *
 */
typedef enum Tvp5150_IOCTL_t
{
    Tvp5150_IOCTL_POWERDOWN = 0,
    /**< TVP5150 power down command.
     *   This ioctl will power down the TVP5150 decoder. Only this ioctl command
     *   needs passed as second argument in ctrl() function. This doesn't take
     *   any argument.                                                        */
    Tvp5150_IOCTL_POWERUP,
    /**< TVP5150 power up command.
     *   This ioctl will power up the TVP5150 decoder. Only this ioctl command
     *   needs passed as second argument in ctrl() function. This doesn't take
     *   any argument.                                                        */
    Tvp5150_IOCTL_SET_CONTROL,
    /**< Set control for TVP5150.
     *   Application has to pass pointer to Tvp5150_Control structure variable
     *   as a third argument in ctrl() function.
     *   For example
     *   Tvp5150_Control control;
     *   control.tvpVidtype = Edc_VideoType_SD;
     *   control.tvpCtrlId = Tvp5150_ControlId_BRIGHTNESS;
     *   control.tvpValue = 128;
     *   cmdArg = (&control);                                                 */
    Tvp5150_IOCTL_SET_SLICE_VBI_SERVICE,
    /**< Set Slice VBI services for TVP5150.
     *   Application has to pass pointer to Int32 structure variable
     *   as a third argument in ctrl() function. Available values for this
     *   field are defined with TVP5150 Slice VBI Service title.
     *   NOTE : This ioctl does not check whether current set standard supports
     *   the slice service or not. It just sets them.
     *   For example
     *   Uint32 services;
     *   services = Fvid_SLICE_VBI_SERVICES_CC_NTSC;
     *   cmdArg = (&services);                                                */
    Tvp5150_IOCTL_CMD_MAX
    /**< Book-keep - Max ioctl's                                              */
}Tvp5150_IOCTL;

/**
 * Apart from above IOCTLS the following generic EDC IOCTLS are supported
 *
 * Edc_IOCTL_CONFIG     - Argument is a pointer to Tvp5150_ConfParams structure
 * Edc_IOCTL_RESET      - Doesn't take any argument
 * Edc_IOCTL_SET_REG    - Argument is a pointer to Edc_RegData structure
 * Edc_IOCTL_GET_REG    - Argument is a pointer to Edc_RegData structure
 * Edc_IOCTL_READ_SLICE_VBI_DATA  - Argument is a pointer to FVID_SliceFrame
 *                                  structure
 *
 */

/**
 *  \brief  Tvp5150_ControlId - Constants used for control settings for TVP5150.
 */
typedef enum Tvp5150_ControlId_t
{
    Tvp5150_ControlId_AUTO_GAIN,
    /**< Gain control. A value of 0 sets Manual gain, and value of 1 enables
         auto gain. Auto gain is either 0 or 1.                               */
    Tvp5150_ControlId_BRIGHTNESS,
    /**< Brightness control. A value of 255 (bright), 128 (default), 0 (dark).
         Brightness supported is (0-255).                                     */
    Tvp5150_ControlId_CONTRAST,
    /**< Contrast control(Luminance Contrast). A value of 255(maximum contrast),
         128 (default), 0 (minimum contrast).
         Contrast supported is - 0 - 255 (Default - 128)                      */
    Tvp5150_ControlId_HUE,
    /**< Hue control. A value of 0x80(-180 degrees) or 0x7F(+180 degrees) or
         0(0 degrees) can be used. HUE does not apply to component video.
         Hue Supported is - 0 - 255 (Default - 0)                             */
    Tvp5150_ControlId_SATURATION
    /**< Saturation(Chrominance Saturation). Control A value of 255 (maximum),
         128 (default), 0 (no color)
         Saturation supported is - 0 - 255 (Default - 128)                    */
}Tvp5150_ControlId;


/**
 *  \brief Tvp5150 video operation mode
 *  This enum gives available operation mode for Tvp5150 decoder
 */
typedef enum Tvp5150_Std_t
{
    Tvp5150_Std_INVALID = -1,
    /**< Invalid Video Mode                                                   */
    Tvp5150_Std_AUTO,
    /**< Use auto switch mode of operation. The standard will be detected
    automatically                                                             */
    Tvp5150_Std_NTSC720,
    /**< NTSC 720 pixels                                                      */
    Tvp5150_Std_PAL720
    /**< PAL 720 pixels                                                       */
}Tvp5150_Std;


/**
 *  \brief Tvp5150 analog format
 *  This enum gives available analog format selection with Tvp5150 decoder
 */
typedef enum Tvp5150_AnalogFormat_t
{
    Tvp5150_AnalogFormat_SVIDEO = 0,
    /**< SVIDEO(Y/C) IN cable used                                            */
    Tvp5150_AnalogFormat_COMPOSITE
    /**< CVBS IN cable used                                                   */
}Tvp5150_AnalogFormat;

/**
 *  \brief Tvp5150 output format
 *  This enum gives available output format for Tvp5150 decoder
 */
typedef enum Tvp5150_OutputFormat_t
{
    Tvp5150_OutputFormat_YCBCR422
    /**< Interlaced YCbCr 422 output                                          */
}Tvp5150_OutputFormat;

/* ========================================================================== */
/*                             TVP5150 STRUCTURES                             */
/* ========================================================================== */
/**
 *  \brief Setting Control data structure for Tvp5150
 */
typedef struct Tvp5150_Control_t
{
    Edc_VideoType                       tvpVidtype;
    /**< Video Type for this control feature                                  */
    Tvp5150_ControlId                   tvpCtrlId;
    /**< Control Id defined for TVP5150                                       */
    Uint32                              tvpValue;
    /**< Value to be write to the control reg                                 */
}Tvp5150_Control;

/**
 *  \brief TVP5150 configuration structure
 *  This structure contains configuration parameters for TVP5150 decoder
 */
typedef struct Tvp5150_ConfParams_t
{
    Tvp5150_AnalogFormat                    tvpAnaFmt;
    /**< Indicates analog input format for TVP5150                            */
    Tvp5150_Std                             tvpMode;
    /**< Indicates operation mode(NTSC/PAL) for TVP5150                       */
    Tvp5150_OutputFormat                    tvpOutFmt;
    /**< Indicates output format for TVP5150                                  */
    Uint32                                  tvpServices;
    /**< Type of Slice VBI service. Available values for this field are defined
         in "Fvid.h" file with FVID Slice VBI Service title. This should
         be passed appropriately  according to the Video standard mode desired.
         CAUTION : If wrong service is sent, the driver does not verify its
         validity                                                             */
}Tvp5150_ConfParams;

/* ========================================================================== */
/*                             TVP5150 EXTERNS                                */
/* ========================================================================== */
/** \brief Decoder (TVP5150) driver function table                            */
extern EDC_Fxns TVP5150_Fxns;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  /* #ifndef _TVP5150_H_ */

/******************************************************************************/
/* End of file                                                                */
/******************************************************************************/
