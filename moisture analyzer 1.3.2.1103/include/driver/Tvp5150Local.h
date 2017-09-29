/**
 *  \file   Tvp5150Local.h file
 *
 *  \brief  This file contains internal structures and defines for TVP5150
 *          decoder
 */

#ifndef _TVP5150LOCAL_H_
#define _TVP5150LOCAL_H_

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */
#include <Edc.h>
#include <Tvp5150.h>

#ifdef __cplusplus
extern "C" {
#endif /* extern "C" */

/* ========================================================================== */
/*                          MACRO DEFINITIONS                                 */
/* ========================================================================== */
/**\brief Indicates two TVP5150 decoders                                      */
#define NUM_DECODERS                    (2)
/**\brief Number of channels supported by one decoder                         */
#define NUM_CHANNELS                    (1)
/**\brief TVP5150 #0 I2C address (write)*/
#define TVP5150_0_IIC_ADDR             (0xB8 >> 1)
/**\brief TVP5150 #1 I2C address (write)*/
#define TVP5150_1_IIC_ADDR             (0xBA >> 1)

//brief TVP5150 #0 I2C address (read)
#define TVP5150_0_IIC_ADDR_R			(0xB9 >> 1)
//brief TVP5150 #1 I2C address (read)
#define TVP5150_1_IIC_ADD_R				(0xBB >> 1)

//brief Defines for TVP5150 register address
#define TVP5150_VIDEO_INPUT_SEL									(0x00u)
#define TVP5150_ANALOG_CHAN_CTRL								(0x01u)
#define TVP5150_OPERATION_MODE_CTRL								(0x02u)
#define TVP5150_MISCELLANEOUS_CTRL								(0x03u)
#define TVP5150_AUTOSWITCH_MASK									(0x04u)
#define TVP5150_SOFTWARE_RESET									(0x05u)
#define TVP5150_COLOR_KILLER_THRESHOLD_CTRL						(0x06u)
#define TVP5150_LUM_CTRL1										(0x07u)
#define TVP5150_LUM_CTRL2										(0x08u)
#define TVP5150_BRIGHT_CTRL										(0x09u)
#define TVP5150_COLOR_SATURATION_CTRL							(0x0Au)
#define TVP5150_HUE_CTRL										(0x0Bu)
#define TVP5150_CONTRAST_CTRL									(0x0Cu)
#define TVP5150_OUTPUTS_DATA_RATES_SEL							(0x0Du)
#define TVP5150_LUM_CTRL3										(0x0Eu)
#define TVP5150_CONFIG_SHARED_PINS								(0x0Fu)
//0X10 IS RESERVED
#define TVP5150_ACTIVE_VIDEO_CROPPING_START_MSB					(0x11u)
#define TVP5150_ACTIVE_VIDEO_CROPPING_START_LSB					(0x12u)
#define TVP5150_ACTIVE_VIDEO_CROPPING_STOP_MSB					(0x13u)
#define TVP5150_ACTIVE_VIDEO_CROPPING_STOP_LSB					(0x14u)
#define TVP5150_GENLOCK_RTC										(0x15u)
#define TVP5150_HORIZONTAL_SYNC_START							(0x16u)
//0X17 IS RESERVED
#define TVP5150_VERTICAL_BLANKING_START							(0x18u)
#define TVP5150_VERTICAL_BLANKING_STOP							(0x19u)
#define TVP5150_CHROMINANCE_PROCESS_CTRL1						(0x1Au)
#define TVP5150_CHROMINANCE_PROCESS_CTRL2						(0x1Bu)
#define TVP5150_INTER_RESET_REG_B								(0x1Cu)
#define TVP5150_INTER_ENABLE_REG_B								(0x1Du)
#define TVP5150_INTER_CONFIG_REG_B								(0x1Eu)
//0X1F - 0X27 IS RESERVED
#define TVP5150_VIDEO_STANDARD									(0x28u)
//0x29 - 0x7f is reserved
#define TVP5150_MSB_DEVICE_ID									(0x80u)
#define TVP5150_LSB_DEVICE_ID									(0x81u)
#define TVP5150_ROM_VERSION										(0x82u)
#define TVP5150_RAM_PATCH_CODE_VERSION							(0x83u)
#define TVP5150_VERTICAL_LINE_COUNT_MSB							(0x84u)
#define TVP5150_VERTICAL_LINE_COUNT_LSB							(0x85u)
#define TVP5150_INTER_STATUS_REG_B								(0x86u)
#define TVP5150_INTER_ACTIVE_REG_B								(0x87u)
#define TVP5150_INTER_STATUS_REG1								(0x88u)
#define TVP5150_INTER_STATUS_REG2								(0x89u)
#define TVP5150_INTER_STATUS_REG3								(0x8Au)
#define TVP5150_INTER_STATUS_REG4								(0x8Bu)
#define TVP5150_INTER_STATUS_REG5								(0x8Cu)
//0X8D - 0X8F IS RESERVED

//TVP5150 closed caption data registers
#define TVP5150_CLOSED_CAPTION_DATA_REG1						(0x90u)
#define TVP5150_CLOSED_CAPTION_DATA_REG2						(0x91u)
#define TVP5150_CLOSED_CAPTION_DATA_REG3						(0x92u)
#define TVP5150_CLOSED_CAPTION_DATA_REG4						(0x93u)

//TVP5150 WSS data registers
#define TVP5150_WSS_DATA_REG11									(0x94u)
#define TVP5150_WSS_DATA_REG12									(0x95u)
#define TVP5150_WSS_DATA_REG13									(0x96u)
#define TVP5150_WSS_DATA_REG21									(0x97u)
#define TVP5150_WSS_DATA_REG22									(0x98u)
#define TVP5150_WSS_DATA_REG23									(0x99u)

//VPS data registers
#define TVP5150_VPS_DATA_REG1									(0x9Au)
#define TVP5150_VPS_DATA_REG2									(0x9Bu)
#define TVP5150_VPS_DATA_REG3									(0x9Cu)
#define TVP5150_VPS_DATA_REG4									(0x9Du)
#define TVP5150_VPS_DATA_REG5									(0x9Eu)
#define TVP5150_VPS_DATA_REG6									(0x9Fu)
#define TVP5150_VPS_DATA_REG7									(0xA0u)
#define TVP5150_VPS_DATA_REG8									(0xA1u)
#define TVP5150_VPS_DATA_REG9									(0xA2u)
#define TVP5150_VPS_DATA_REG10									(0xA3u)
#define TVP5150_VPS_DATA_REG11									(0xA4u)
#define TVP5150_VPS_DATA_REG12									(0xA5u)
#define TVP5150_VPS_DATA_REG13									(0xA6u)

//VITC data registers
#define TVP5150_VITC_DATA_REG1									(0xA7u)
#define TVP5150_VITC_DATA_REG2									(0xA8u)
#define TVP5150_VITC_DATA_REG3									(0xA9u)
#define TVP5150_VITC_DATA_REG4									(0xAAu)
#define TVP5150_VITC_DATA_REG5									(0xABu)
#define TVP5150_VITC_DATA_REG6									(0xACu)
#define TVP5150_VITC_DATA_REG7									(0xADu)
#define TVP5150_VITC_DATA_REG8									(0xAEu)
#define TVP5150_VITC_DATA_REG9									(0xAFu)

#define TVP5150_VBI_FIFO_READ_DATA_REG							(0xB0u)

//Teletext filter and mask registers
#define TVP5150_TELETEXT_FILTER_MASK_REG1						(0xB1u)
#define TVP5150_TELETEXT_FILTER_MASK_REG2						(0xB2u)
#define TVP5150_TELETEXT_FILTER_MASK_REG3						(0xB3u)
#define TVP5150_TELETEXT_FILTER_MASK_REG4						(0xB4u)
#define TVP5150_TELETEXT_FILTER_MASK_REG5						(0xB5u)
#define TVP5150_TELETEXT_FILTER_MASK_REG6						(0xB6u)
#define TVP5150_TELETEXT_FILTER_MASK_REG7						(0xB7u)
#define TVP5150_TELETEXT_FILTER_MASK_REG8						(0xB8u)
#define TVP5150_TELETEXT_FILTER_MASK_REG9						(0xB9u)
#define TVP5150_TELETEXT_FILTER_MASK_REG10						(0xBAu)

#define TVP5150_TELETEXT_FILTER_ENABLE							(0xBBu)
//0XBC - 0XBF IS RESERVED
#define TVP5150_INTER_STATUS_REG_A								(0xC0u)
#define TVP5150_INTER_ENABLE_REG_A								(0xC1u)
#define TVP5150_INTER_CONFIG									(0xC2u)
#define TVP5150_VDP_CONFIG_RAM_DATA								(0xC3u)
#define TVP5150_CONFIG_RAM_ADDR_L								(0xC4u)
#define TVP5150_CONFIG_RAM_ADDR_H								(0xC5u)
#define TVP5150_VDP_STATUS_REG									(0xC6u)
#define TVP5150_FIFO_WORD_COUNT									(0xC7u)
#define TVP5150_FIFO_INTER_THRESHOLD							(0xC8u)
#define TVP5150_FIFO_RESET										(0xC9u)
#define TVP5150_LINE_NUM_INTER									(0xCAu)
#define TVP5150_PIXEL_ALIGN_REG_L								(0xCBu)
#define TVP5150_PIXEL_ALIGN_REG_H								(0xCCu)
#define TVP5150_FIFO_OUTPUT_CTRL								(0xCDu)
#define TVP5150_AUTO_INIT										(0xCEu)
#define TVP5150_FULL_FIELD_ENABLE								(0xCFu)

//Line mode registers
#define TVP5150_LINE_MODE_REG1									(0xD0u)
#define TVP5150_LINE_MODE_REG2									(0xD1u)
#define TVP5150_LINE_MODE_REG3									(0xD2u)
#define TVP5150_LINE_MODE_REG4									(0xD3u)
#define TVP5150_LINE_MODE_REG5									(0xD4u)
#define TVP5150_LINE_MODE_REG6									(0xD5u)
#define TVP5150_LINE_MODE_REG7									(0xD6u)
#define TVP5150_LINE_MODE_REG8									(0xD7u)
#define TVP5150_LINE_MODE_REG9									(0xD8u)
#define TVP5150_LINE_MODE_REG10									(0xD9u)
#define TVP5150_LINE_MODE_REG11									(0xDAu)
#define TVP5150_LINE_MODE_REG12									(0xDBu)
#define TVP5150_LINE_MODE_REG13									(0xDCu)
#define TVP5150_LINE_MODE_REG14									(0xDDu)
#define TVP5150_LINE_MODE_REG15									(0xDEu)
#define TVP5150_LINE_MODE_REG16									(0xDFu)
#define TVP5150_LINE_MODE_REG17									(0xE0u)
#define TVP5150_LINE_MODE_REG18									(0xE1u)
#define TVP5150_LINE_MODE_REG19									(0xE2u)
#define TVP5150_LINE_MODE_REG20									(0xE3u)
#define TVP5150_LINE_MODE_REG21									(0xE4u)
#define TVP5150_LINE_MODE_REG22									(0xE5u)
#define TVP5150_LINE_MODE_REG23									(0xE6u)
#define TVP5150_LINE_MODE_REG24									(0xE7u)
#define TVP5150_LINE_MODE_REG25									(0xE8u)
#define TVP5150_LINE_MODE_REG26									(0xE9u)
#define TVP5150_LINE_MODE_REG27									(0xEAu)
#define TVP5150_LINE_MODE_REG28									(0xEBu)
#define TVP5150_LINE_MODE_REG29									(0xECu)
#define TVP5150_LINE_MODE_REG30									(0xEDu)
#define TVP5150_LINE_MODE_REG31									(0xEEu)
#define TVP5150_LINE_MODE_REG32									(0xEFu)
#define TVP5150_LINE_MODE_REG33									(0xF0u)
#define TVP5150_LINE_MODE_REG34									(0xF1u)
#define TVP5150_LINE_MODE_REG35									(0xF2u)
#define TVP5150_LINE_MODE_REG36									(0xF3u)
#define TVP5150_LINE_MODE_REG37									(0xF4u)
#define TVP5150_LINE_MODE_REG38									(0xF5u)
#define TVP5150_LINE_MODE_REG39									(0xF6u)
#define TVP5150_LINE_MODE_REG40									(0xF7u)
#define TVP5150_LINE_MODE_REG41									(0xF8u)
#define TVP5150_LINE_MODE_REG42									(0xF9u)
#define TVP5150_LINE_MODE_REG43									(0xFAu)
#define TVP5150_LINE_MODE_REG44									(0xFBu)

#define TVP5150_FULL_FIELD_MODE_REG								(0xFCu)
//0xFD - 0xFF is reserved.



////brief: TVP5150 DEFAULT
#define TVP5150_VIDEO_INPUT_SEL_DEFAULT									(0x00u)
#define TVP5150_ANALOG_CHAN_CTRL_DEFAULT								(0x15u)
#define TVP5150_OPERATION_MODE_CTRL_DEFAULT								(0x00u)
#define TVP5150_MISCELLANEOUS_CTRL_DEFAULT								(0x01u)
#define TVP5150_AUTOSWITCH_MASK_DEFAULT									(0x00u)
#define TVP5150_SOFTWARE_RESET_DEFAULT									(0x00u)
#define TVP5150_COLOR_KILLER_THRESHOLD_CTRL_DEFAULT						(0x10u)
#define TVP5150_LUM_CTRL1_DEFAULT										(0x20u)
#define TVP5150_LUM_CTRL2_DEFAULT										(0x00u)
#define TVP5150_BRIGHT_CTRL_DEFAULT										(0x80u)
#define TVP5150_COLOR_SATURATION_CTRL_DEFAULT							(0x80u)
#define TVP5150_HUE_CTRL_DEFAULT										(0x00u)
#define TVP5150_CONTRAST_CTRL_DEFAULT									(0x80u)
#define TVP5150_OUTPUTS_DATA_RATES_SEL_DEFAULT							(0x47u)
#define TVP5150_LUM_CTRL3_DEFAULT										(0x00u)
#define TVP5150_CONFIG_SHARED_PINS_DEFAULT								(0x08u)
#define TVP5150_ACTIVE_VIDEO_CROPPING_START_MSB_DEFAULT					(0x00u)
#define TVP5150_ACTIVE_VIDEO_CROPPING_START_LSB_DEFAULT					(0x00u)
#define TVP5150_ACTIVE_VIDEO_CROPPING_STOP_MSB_DEFAULT					(0x00u)
#define TVP5150_ACTIVE_VIDEO_CROPPING_STOP_LSB_DEFAULT					(0x00u)
#define TVP5150_GENLOCK_RTC_DEFAULT										(0x01u)
#define TVP5150_HORIZONTAL_SYNC_START_DEFAULT							(0x80u)
#define TVP5150_VERTICAL_BLANKING_START_DEFAULT							(0x00u)
#define TVP5150_VERTICAL_BLANKING_STOP_DEFAULT							(0x00u)
#define TVP5150_CHROMINANCE_PROCESS_CTRL1_DEFAULT						(0x0cu)
#define TVP5150_CHROMINANCE_PROCESS_CTRL2_DEFAULT						(0x14u)
#define TVP5150_INTER_RESET_REG_B_DEFAULT								(0x00u)
#define TVP5150_INTER_ENABLE_REG_B_DEFAULT								(0x00u)
#define TVP5150_INTER_CONFIG_REG_B_DEFAULT								(0x00u)
#define TVP5150_VIDEO_STANDARD_DEFAULT									(0x00u)
#define TVP5150_MSB_DEVICE_ID_DEFAULT									(0x51u)
#define TVP5150_LSB_DEVICE_ID_DEFAULT									(0x50u)
#define TVP5150_ROM_VERSION_DEFAULT										(0x02u)
#define TVP5150_RAM_PATCH_CODE_VERSION_DEFAULT							(0x10u)
#define TVP5150_INTER_ACTIVE_REG_B_DEFAULT								(0x00u)
#define TVP5150_TELETEXT_FILTER_MASK_REG_DEFAULT						(0x00u)
#define TVP5150_TELETEXT_FILTER_ENABLE_DEFAULT							(0x00u)
#define TVP5150_INTER_STATUS_REG_A_DEFAULT								(0x00u)
#define TVP5150_INTER_ENABLE_REG_A_DEFAULT								(0x00u)
#define TVP5150_INTER_CONFIG_DEFAULT									(0x00u)
#define TVP5150_VDP_CONFIG_RAM_DATA_DEFAULT								(0xDCu)
#define TVP5150_CONFIG_RAM_ADDR_L_DEFAULT								(0x0Fu)
#define TVP5150_CONFIG_RAM_ADDR_H_DEFAULT								(0x00u)
#define TVP5150_FIFO_INTER_THRESHOLD_DEFAULT							(0x80u)
#define TVP5150_FIFO_RESET_DEFAULT										(0x00u)
#define TVP5150_LINE_NUM_INTER_DEFAULT									(0x00u)
#define TVP5150_PIXEL_ALIGN_REG_L_DEFAULT								(0x59u)
#define TVP5150_PIXEL_ALIGN_REG_H_DEFAULT								(0x03u)
#define TVP5150_FIFO_OUTPUT_CTRL_DEFAULT								(0x01u)
#define TVP5150_AUTO_INIT_DEFAULT										(0x00u)
#define TVP5150_FULL_FIELD_ENABLE_DEFAULT								(0x00u)
#define TVP5150_LINE_MODE_REG_DEFAULT									(0xFFu)
#define TVP5150_FULL_FIELD_MODE_REG_DEFAULT								(0x7Fu)



/* masks                                                                      */
/* defines for configuration values                                           */
#define TVP5150_LOST_LOCK_MASK                                  (0x10u)
/* mask to enable auto switch for all standards                               */

#define TVP5150_AUTOSWITCH_MASK_VALUE                           (0x7Fu)
#define TVP5150_COMPOSITE_INPUT                                 (0x00u)
#define TVP5150_SVIDEO_INPUT                                    (0x01u)


/* The TVP chip ID values                                                     */
#define TVP5150_CHIP_ID_MSB_VALUE                               (0x51)
#define TVP5150_CHIP_ID_LSB_VALUE                               (0x50)

#define VIDEO_STD_MASK                                          (0x0Fu)
#define VIDEO_STD_AUTO_SWITCH_BIT                               (0x00)
#define VIDEO_STD_NTSC_MJ_BIT                                   (0x01)
#define VIDEO_STD_PAL_BDGHIN_BIT                                (0x03)
#define VIDEO_STD_PAL_M_BIT                                     (0x05)
#define VIDEO_STD_PAL_Nc_BIT                         			(0x07)
#define VIDEO_STD_NTSC_4_43_BIT                                 (0x09)
#define VIDEO_STD_SECAM_BIT                                     (0x0A)

/*
 * Status bit
 */
#define STATUS_TV_VCR_BIT                                       (1<<0)
#define STATUS_HORZ_SYNC_LOCK_BIT                               (1<<1)
#define STATUS_VIRT_SYNC_LOCK_BIT                               (1<<2)
#define STATUS_CLR_SUBCAR_LOCK_BIT                              (1<<3)
#define STATUS_LOST_LOCK_DETECT_BIT                             (1<<4)
#define STATUS_FEILD_RATE_BIT                                   (1<<5)
#define STATUS_LINE_ALTERNATING_BIT                             (1<<6)
#define STATUS_PEAK_WHITE_DETECT_BIT                            (1<<7)
/* DEFAULTS */

#define TVP5150_OPERATION_MODE_RESET                            (0x1u)
#define TVP5150_OPERATION_MODE_DEFAULT                          (0x0)
#define TVP5150_AFE_GAIN_CTRL_DEFAULT                           (0x15u)
#define TVP5150_COLOR_KILLER_DEFAULT                            (0x10u)
#define TVP5150_LUMA_CONTROL1_DEFAULT                           (0x00u)
#define TVP5150_LUMA_CONTROL2_DEFAULT                           (0x00u)
#define TVP5150_LUMA_CONTROL3_DEFAULT                           (0x02u)
#define TVP5150_BRIGHTNESS_DEFAULT                              (0x80u)
#define TVP5150_CONTRAST_DEFAULT                                (0x80u)
#define TVP5150_SATURATION_DEFAULT                              (0x80u)
#define TVP5150_HUE_DEFAULT                                     (0x00u)
#define TVP5150_CHROMA_CONTROL1_DEFAULT                         (0x00u)
#define TVP5150_CHROMA_CONTROL2_DEFAULT                         (0x0Eu)
#define TVP5150_OUTPUT_DEFAULT                                  (0x47u)
#define TVP5150_FIFO_OUTPUT_CTRL_DEFAULT                        (0x01u)

#define TVP5150_VBUS_DATA_ACCESS                                (0xE0u)
#define TVP5150_VBUS_DATA_ACCESS_AUTO_INCR                      (0xE1u)

#define TVP5150_LINE_ADDRESS_START                              (0x80u)
#define TVP5150_LINE_ADDRESS_MIDDLE                             (0x06u)
#define TVP5150_LINE_ADDRESS_END                                (0x00u)

#define TVP5150_LINE_ADDRESS_DEFAULT                            (0x00)
#define TVP5150_LINE_MODE_DEFAULT                               (0xFFu)

/** \brief Macro for maximum number of slice services supported */
#define TVP5150_VBI_NUM_SERVICES                                (3)

/* ========================================================================== */
/*                              STRUCTURES                                    */
/* ========================================================================== */
/**
 *  \brief TVP5150 VDP register structure
 */
typedef struct Tvp5150_VdpReg_t
{
    Uint8 fifoLineAddr[3];
    /**< Sub address of Line Address Register                                 */
    Uint8 fifoModeVal;
    /**< Line mode register value                                             */
}Tvp5150_VdpReg;

/**
 *  \brief Slice service register structure
 */
typedef struct Tvp5150_ServiceReg_t
{
    Uint32                  service;
    /**< Slice service type                                                   */
    Uint8                   lineNo;
    /**< Line number to be processed by a VDP set by a line mode register     */
    Uint8                   lineStart;
    /**< VDP line starting address                                            */
    Uint8                   lineEnd;
    /**< VDP stop line address                                                */
    Tvp5150_VdpReg          field[2];
    /**< VDP reg for both fields                                              */
    Tvp5150_Std             std;
    /**< Video standard                                                       */
}Tvp5150_ServiceReg;


/**
 *  \brief Structure holding value of Slice Service data address registers
 *         required per field. This structure holds the no of registers required
 *         to be read to get the Slice VBI data.
 */
typedef struct Tvp5150_FieldAddr_t
{
    Uint8                   addr[3];
    /**< Subaddress of VDP Data Register per field                            */
}Tvp5150_FieldAddr;

/**
 *  \brief Structure for reading Slice services data
 */
typedef struct Tvp5150_ServiceDataReg_t
{
    Uint32                  tvpSliceService;
    /**< Slice service type                                                   */
    Tvp5150_FieldAddr       tvpSliceField[2];
    /**< Slice service data register address for even and odd fields          */
    Uint8                   bytestoread;
    /**< Bytes of Slice data                                                  */
}Tvp5150_ServiceDataReg;

/**
 *  \brief  TVP5150 decoder object structure
 *  Decoder object structure for TVP5150 decoder
 */
typedef struct Tvp5150_DecObj_t
{
    Int8                    codecName[20];
    /**< Decoder name                                                         */
    Edc_ControlBusType      edcCtrlBusType;
    /**< Type of the control bus (SPI or I2C)                                 */
    Int8                    edcCtrlBusName[20];
    /**< Control bus (I2C or SPI) name                                        */
    Uint8                   edcCtrlDeviceAddr;
    /**< Decoder Control bus address - I2C slave address or SPI CS number     */
    Int32                   decNum;
    /**< Decoder number to which channel belongs to                           */
    Uint32                  servicesSet;
    /**< Slice VBI service set for decoder                                    */
    Uint8                   numServices;
    /**< Number of slice vbi service set                                      */
    Tvp5150_Std             currentVideoStd;
    /**< Current standard for Video                                           */
}Tvp5150_DecObj;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* #ifndef __TVP5150LOCAL_H_ */

/******************************************************************************/
/* End of file                                                                */
/******************************************************************************/
