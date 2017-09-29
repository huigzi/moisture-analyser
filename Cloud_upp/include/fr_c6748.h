//-----------------------------------------------------------------------------
// \file    evmomapl138.h
// \brief   OMAP-L138 internal registers & bit definitions.
//
//-----------------------------------------------------------------------------

#ifndef FR_C6748_H
#define FR_C6748_H

#include <ti/sysbios/knl/Queue.h>
#include <nand.h>
//-----------------------------------------------------------------------------
// bit manipulation macros and bitval lookup table declarations.
//-----------------------------------------------------------------------------
#define SETBIT(dest,mask)     (dest |= mask)
#define CLRBIT(dest,mask)     (dest &= ~mask)
#define TGLBIT(dest,mask)     (dest ^= mask)
#define CHKBIT(dest,mask)     (dest & mask)
extern const uint32_t bitval_u32[32];

#define NAND_APP_PROG_LOAD_ADDR 0xc3000000

//NAND Address MAP(logic):
#define NAND_DSPBOOT_PROG_OFFSET 	0x0		//2MB
#define NAND_APP_PROG_OFFSET		0x10	//2MB
#define NAND_APP_USER_OFFSET		0x20	//after 4MB...

//-----------------------------------------------------------------------------
// bitmask defines for EMUMGT.
//-----------------------------------------------------------------------------
#define SOFT                  (0x00000002)   // bit 1
#define FREE                  (0x00000001)   // bit 0

//-----------------------------------------------------------------------------
// Return Error Defines
//-----------------------------------------------------------------------------
#define SY_ERROR		(-1)
#define SY_SUCCESS	    (0)

#define ERR_NO_ERROR             (0)
#define ERR_FAIL                 (1)
#define ERR_INIT_FAIL            (2)
#define ERR_NO_UI_BOARD          (3)
#define ERR_INVALID_PARAMETER    (4)
#define ERR_TIMEOUT_1            (5)
#define ERR_UART_RX_FIFO_EMPTY   (6)
#define ERR_SPI_BUS_ERROR        (7)
#define ERR_ENET_LINK_INACTIVE   (8)
#define ERR_ENET_PKT_TOO_LARGE   (9)
#define ERR_ENET_Q_EMPTY         (10)
#define ERR_ENET_RX_ERROR        (11)
#define ERR_FLASH_VERIFY         (12)
#define ERR_MMCSD_TIMEOUT        (13)
#define ERR_NAND_BAD_BLOCK       (14)
#define ERR_UIDB_NUM_DEVICES     (15)    //for UI databus muxing control
#define ERR_UIDB_INCOMPAT_DEV    (16)
#define ERR_UIDB_INVALID_DEVICE  (17)

#define ERR_SIZE  				 0x01	//for net data size
#define ERR_UDIPT  				 0x01	//for undefined ipt unit
#define ERR_MACRO_NUM  		     0x02	//macro number > 6

//-----------------------------------------------------------------------------
// Utility Print Defines
//-----------------------------------------------------------------------------
#define PRINT_NONE                  (0)
#define PRINT_DURING_VERIFY         (1)
#define PRINT_HEADER                (0)
#define PRINT_CONTINUE              (1)

//-----------------------------------------------------------------------------
// power and sleep config registers
//-----------------------------------------------------------------------------
#define PSC0_REG_BASE         (0x01C10000)
#define PSC1_REG_BASE         (0x01E27000)

//-----------------------------------------------------------------------------
// system config registers
//-----------------------------------------------------------------------------
#define SYSCONFIG_REG_BASE    (0x01C14000)

//-----------------------------------------------------------------------------
// PLL registers
//-----------------------------------------------------------------------------
#define PLL0_REG_BASE         (0x01C11000)
#define PLL1_REG_BASE         (0x01E1A000)

//-----------------------------------------------------------------------------
// DDR registers
//-----------------------------------------------------------------------------
#define DDR_REG_BASE          (0xB0000000)
#define DDR_MEM_BASE          (0xC0000000)
#define DDR_MEM_SIZE          (0x08000000)	// 128MB

//-----------------------------------------------------------------------------
// EMIFA registers
//-----------------------------------------------------------------------------
#define EMIFA_REG_BASE        (0x68000000)

//-----------------------------------------------------------------------------
// GPIO registers
//-----------------------------------------------------------------------------
#define GPIO_REG_BASE         (0x01E26000)
#define GPIO_BANK_OFFSET      (0x28)

#define GPIO_REV              (GPIO_REG_BASE)
#define GPIO_BINTEN           (GPIO_REG_BASE + 0x08)

#define GPIO_BANK01_BASE      (GPIO_REG_BASE + 0x10)
#define GPIO_BANK23_BASE      (GPIO_BANK01_BASE + GPIO_BANK_OFFSET)
#define GPIO_BANK45_BASE      (GPIO_BANK23_BASE + GPIO_BANK_OFFSET)
#define GPIO_BANK67_BASE      (GPIO_BANK45_BASE + GPIO_BANK_OFFSET)
#define GPIO_BANK8_BASE       (GPIO_BANK67_BASE + GPIO_BANK_OFFSET)

#define GPIO_BUFF_OE_BANK        (2)
#define GPIO_BUFF_OE_PIN         (6)
#define PINMUX_GPIO_BUFF_OE_REG  (6)
#define PINMUX_GPIO_BUFF_OE_MASK (0x000000F0)
#define PINMUX_GPIO_BUFF_OE_VAL  (0x00000080)

//-----------------------------------------------------------------------------
// Timer registers
//-----------------------------------------------------------------------------
#define TIMER0_REG_BASE       (0x01C20000)
#define TIMER1_REG_BASE       (0x01C21000)

//-----------------------------------------------------------------------------
// UART registers
//-----------------------------------------------------------------------------
#define UART0_REG_BASE        (0x01C42000)
#define UART1_REG_BASE        (0x01D0C000)
#define UART2_REG_BASE        (0x01D0D000)

//-----------------------------------------------------------------------------
// SPI registers
//-----------------------------------------------------------------------------
#define SPI0_REG_BASE         (0x01C41000)
#define SPI1_REG_BASE         (0x01F0E000)

//-----------------------------------------------------------------------------
// I2C registers
//-----------------------------------------------------------------------------
#define I2C0_REG_BASE         (0x01C22000)
#define I2C1_REG_BASE         (0x01E28000)

//-----------------------------------------------------------------------------
// EMAC registers
//-----------------------------------------------------------------------------
#define EMAC_RAM_BASE         (0x01E20000)
#define EMAC_CTRL_REG_BASE    (0x01E22000)
#define EMAC_REG_BASE         (0x01E23000)
#define MDIO_REG_BASE         (0x01E24000)

//-----------------------------------------------------------------------------
// MMCSD registers
//-----------------------------------------------------------------------------
#define MMCSD0_REG_BASE       (0x01C40000)
#define MMCSD1_REG_BASE       (0x01E1B000)

//-----------------------------------------------------------------------------
// MCASP registers
//-----------------------------------------------------------------------------
#define MCASP_REG_BASE        (0x01D00000)

//-----------------------------------------------------------------------------
// USB registers
//-----------------------------------------------------------------------------
#define USB_OTG_REG_BASE      (0x01E00000)
#define USB_HOST_REG_BASE     (0x01E25000)

//-----------------------------------------------------------------------------
// VPIF registers
//-----------------------------------------------------------------------------
#define VPIF_REG_BASE            (0x01E17000)
#define VPIF_CAP_CH0_REG_BASE    (0x01E17040)
#define VPIF_CAP_CH1_REG_BASE    (0x01E17080)
#define VPIF_DISP_CH2_REG_BASE   (0x01E170C0)
#define VPIF_DISP_CH3_REG_BASE   (0x01E17140)

//-----------------------------------------------------------------------------
// LCDC registers
//-----------------------------------------------------------------------------
#define LCDC_REG_BASE         (0x01E13000)

//-----------------------------------------------------------------------------
// uPP registers
//-----------------------------------------------------------------------------
#define UPP_REG_BASE          (0x01E16000)

//-----------------------------------------------------------------------------
// RTC registers
//-----------------------------------------------------------------------------
#define RTC_REG_BASE          (0x01C23000)

typedef struct _ScomMessage {
    Queue_Elem queElem;                    // must be first field.
    int  sizeLinear;
    void *bufLinear;

} ScomMessage;

typedef struct LOCALINFO{
	unsigned char localid[4];   	//本地ID
	unsigned char serverip[4];  	//服务器IP
	unsigned char localip[4];   	//本地IP
	unsigned char LocalIPMask[4]; //本地MASK
	unsigned char GatewayIP[4]; 	//GateWay
	unsigned char DNSIP[4]; 		//DNS
	unsigned char localmac[6];  	//本地MAC
	unsigned char serverport[2];  //端口号
	unsigned char bootversion[2]; //dspbooter版本号
	unsigned char appversion[6]; 	//客户应用程序版本号
	unsigned char AppSize[4];     //应用程序大小，0-没有应用程序
}LOCALINFO;	//44Bytes

typedef struct SMTWORKINFO{
	unsigned char dspHardVer[2];   	//DSP硬件版本号
	unsigned char dspSoftVer[2];   	//DSP软件版本号
	unsigned char fpgaVer[2];   	//FPGA版本号
	unsigned char licenseData[4];  	//授权时间（永久授权：0x0；有限：0x01XXXXXX/年月日，
									//与当前RTC时间计算后输出：永久授权：0x0， 有期限>256天：0x01000000; 有期限<256天：0x02xxXXXX）
	unsigned int onBoardSN;  	//在检PCB编号（0-无在检）
	unsigned int onBoardDate;   //在检PCB日期（设定）
	unsigned char onBoardCisCnt; 	//在检PCB的CIS个数
	unsigned short onBoardScanLine;	//在检PCB扫描速度（线/秒）
	unsigned char cisBlack_1; 		//CIS-1暗电平
	unsigned char cisWhite_1;  		//CIS-1亮电平
	unsigned char cisBlack_2; 		//CIS-2暗电平
	unsigned char cisWhite_2;  		//CIS-2亮电平
	unsigned char cisAdjustMax;  	//CIS变形最大比率
	unsigned char cisSkew; 			//CIS间倾斜角度
	unsigned short cisPitch_1; 	//CIS-1俯仰角度
	unsigned short cisPitch_2; 	//CIS-2俯仰角度
									//CIS有效检测区域，与安装有关，在校正中进行设定
	unsigned short cis0_ValidStart;	//最小0
	unsigned short cis0_ValidEnd;	//最大5184（216mm/600dpi）
	unsigned short cis1_ValidStart;
	unsigned short cis1_ValidEnd;	//最大5184
}SMTWORKINFO;	//39Bytes

typedef struct SMTPCBINFO{
  unsigned int PCBSN;  			//PCB编号（0-无在检）
  unsigned int PCBDate;   		//PCB日期（设定）
  unsigned char PCBUnit; 		//PCB单位0-mm，1-inch
  unsigned int PCBLength;		//PCB长度
  unsigned int PCBWidth;		//PCB宽度
  unsigned short PCBDir; 		//PCB方向（2位小数）
  unsigned char PCBJointNum[2];  //PCB拼板模式X-1B*Y-1B（最大256×256，默认1×1-无拼板）
  unsigned short PCBJointL; 	//拼缝长度方向尺寸
  unsigned short PCBJointW; 	//拼缝长度方向尺寸
  unsigned char PCBedgeMode;  	//PCB工艺边模式，低四位有效：0b0X-左X-右X-上X-下
  unsigned short PCBedgeL; 		//PCB工艺边尺寸左
  unsigned short PCBedgeR; 		//PCB工艺边尺寸右
  unsigned short PCBedgeT; 		//PCB工艺边尺寸上
  unsigned short PCBedgeB; 		//PCB工艺边尺寸下
//  unsigned int NANDIPT[4];		//Nand中描述表3B-block，1B-Page
//  unsigned int NANDPOS[4];		//Nand中位置表3B-block，1B-Page
}SMTPCBINFO;	//34Bytes

//实时SMT信息（CIS/PCB），运行时变化
typedef struct RTSMTINFO{
	unsigned short cis_LineSize;	//cis的行大小（有效数据：<5192），两个CIS重合部分及头尾部分已经处理过
	unsigned short cis_LineNum;		//一帧的行数：252/24=10.5mm太小
	float cis_dpi;					//每像素的单位

	unsigned int cis_LineAll;		//根据PCB大小可计算出需要的cis行数
	unsigned int cis_frameCurrent;	//cis图像帧数

	unsigned int cis_LineCurrent;	//当前已处理cis行数（完整包含pad）
	unsigned short cis_LineReback;	//需要保留的cis行数（部分包含pad）

	unsigned char *pre_cisImage;	//前一帧cisImage，当cis_LineReback有值时需要使用
	unsigned char *cur_cisImage;	//当前cisImage
	//实时PCB信息，运行时变化
	unsigned short PcbRotate;	//PCB 旋转角度
	unsigned short PcbState;	//PCB检测状态：0-未检测；1-已检测到板边；2-已检测到位姿定位焊盘-散度小；3-已检测到位姿定位焊盘-散度大
	unsigned int curPadXmax;	//当前图要处理的pad序号（Xmax）
	unsigned int curPadXmin;	//当前图要处理的pad序号（Xmin）
	unsigned int nextPadXmax;	//下幅图开始处理的pad序号（Xmax）
	unsigned int nextPadXmin;	//下幅图开始处理的pad序号（Xmin）

}RTSMTINFO;

//-----------------------------------------------------------------------------
//坐标点的定义
typedef struct PNT_FR{
	int x;
	int y;
}PNT_FR;

//点的序列
typedef struct PointList{
	struct PointList *pre;
	struct PointList *next;
	struct PNT_FR point;
}PointList;

//焊盘点
typedef struct PAD_FR{
	struct PNT_FR Pnt_centor;
	int moment;	//矩
	unsigned int padArea;
	unsigned int padLength;
	unsigned int padWidth;
	unsigned int padRotate;
	unsigned char padStyle;
}PAD_FR;

//参数链表
typedef struct ParaList{
	struct ParaList *pre;
	struct ParaList *next;
	int ParaMeter;
}ParaList;

//gerb描述表，主要用于宏的定义，每个宏的定义中参数个数不一样
typedef struct GERBIPT{
	struct GERBIPT *pre;
	struct GERBIPT *next;
	unsigned short gerbName;
	unsigned char paraNumber;	//参数个数
	struct ParaList *parList;
}GERBIPT;

//-------------------------------描述表信息处理------------------------------------------
//gerb描述表信息
typedef struct GERBIPTInfo{
	unsigned char *gerbBuf;
	unsigned short gerbDNumber;
}GERBIPTInfo;

//gerb描述表信息解构-12Byte
typedef struct GERBIPTINDEX{
	unsigned short bufIndex;
	unsigned short gerbName;
	unsigned char gerbTyple;	//参数类型：R/C/O/P/M
	unsigned int MacroPrimNumber;//当gerbTyple=M时有效，基本光圈号组合，每5位为一组，最多6个基本光圈组合
	unsigned char paraNumber;	//参数个数
	unsigned short paraLength;	//参数数据长度（字节），最大65536字节
}GERBIPTINDEX;

//Macro链表
typedef struct GerbMacroList{
	unsigned short MacroID;
	unsigned char MacroPrimNumber;	//Macro 初始类型号码：1/2/20/21/4/5/6/7
	void *GerbMacro;			//Macro结构指针
	unsigned char paraNumber;	//参数个数
	unsigned char paraLength;	//参数数据长度（字节）
}GerbMacroList;

//Macro 初始类型号码：1
typedef struct GerbMacroC_1{
	unsigned char FlagVarible;	//各项为常量/变量？从低位对应bit3-0
	unsigned char Exposure;
	unsigned int  Diameter;	//直径
	struct PNT_FR Pnt_centor;//中心点坐标
}GerbMacroC_1;

//Macro 初始类型号码：2/20
typedef struct GerbMacroVL_2_20{
	unsigned char FlagVarible;	//各项为常量/变量？从低位对应bit6-0
	unsigned char Exposure;
	unsigned int  LineWidth;	//线宽
	struct PNT_FR Pnt_start;	//起点坐标
	struct PNT_FR Pnt_end;		//终点坐标
	short rotate;				//旋转角度
}GerbMacroVL_2_20;

//Macro 初始类型号码：21
typedef struct GerbMacroCL_21{
	unsigned char FlagVarible;	//各项为常量/变量？从低位对应bit5-0
	unsigned char Exposure;
	unsigned int  RecWidth;		//线宽
	unsigned int  RecLength;	//线宽
	struct PNT_FR Pnt_centor;	//中心点坐标
	short rotate;				//旋转角度
}GerbMacroCL_21;

//Macro 初始类型号码：22
typedef struct GerbMacroLLL_22{
	unsigned char FlagVarible;	//各项为常量/变量？从低位对应bit5-0
	unsigned char Exposure;
	unsigned int  RecWidth;		//线宽
	unsigned int  RecLength;	//线宽
	struct PNT_FR Pnt_lowerleft;//左下角坐标
	short rotate;				//旋转角度
}GerbMacroLLL_22;

//Macro 初始类型号码：4
typedef struct GerbMacroOutline_4{
	unsigned char FlagVarible;	//各项为常量/变量？从低位对应bit2-0
	unsigned char Exposure;
	unsigned short subseqNumber;//The number of subsequent points n (n≥1)
	struct PointList *pntList;
	short rotate;				//旋转角度
}GerbMacroOutline_4;

//Macro 初始类型号码：5
typedef struct GerbMacroPolygon_5{
	unsigned char FlagVarible;	//各项为常量/变量？从低位对应bit5-0
	unsigned char Exposure;
	unsigned int  vertices;		//Number of vertices n, 3 ≤ n ≤ 12
	struct PNT_FR Pnt_centor;	//中心点坐标
	unsigned int  Diameter;		//Diameter of the circumscribed circle, ≥ 0
	short rotate;				//旋转角度
}GerbMacroPolygon_5;

//--------------------------------位置信息处理-------------------------------------
//gerb位置表信息
typedef struct GERBPOSInfo{
	unsigned char *gerbPosBuf;
	unsigned short gerbPNumber;
}GERBPOSInfo;

//gerb位置信息结构，运行时排序及处理
typedef struct GERBPOS{
	unsigned short iptIndex;	//描述表索引,最大64K
	unsigned short gerbName;	//D代码
	unsigned char Processed;	//针对pcb方向进行调整
	unsigned char valid;		//是否有效？部分焊盘不需要焊接，也不需进行检测
	struct PNT_FR Pnt_centor;	//中心点坐标
	int	X_min;					//PCB方向最小矩形覆盖，以判断该焊盘的判别次序及是否在当前图像中
	int X_max;
	int	Y_min;
	int Y_max;
}GERBPOS;	//7.5×4=30Bytes

//--------------------------------函数声明-------------------------------------

//input/output control
void fr_OutCtrl(unsigned char outValue);
unsigned int fr_InGet(void);

//I2C API
Int32 fr_I2cInit(String i2cDevName);
Int32 fr_I2cDeInit(Void);
Int32 fr_I2cWriteE2prom(Uint8 subAddr, const Uint8 *buffer, Uint8 len);
Int32 fr_I2cReadE2prom(Uint8 subAddr, Uint8 *buffer, Uint8 len);
Int32 fr_boardVerify(Uint8 *seed);
void SetDefaultIP(void);

void fr_Nand_BBMinit(NAND_InfoHandle hNandInfo);
Int32 fr_NandWriteBlock(NAND_InfoHandle hNandInfo,Uint8 *writeBuf, Uint32 blockStart, Uint32 pageStart,Uint32 pageCount);
Int32 fr_NandReadBlock(NAND_InfoHandle hNandInfo,Uint8 *readBuf, Uint32 blockStart, Uint32 pageStart,Uint32 pageCount);
Int32 fr_Nand_BlockUsable(NAND_InfoHandle hNandInfo);

#endif
