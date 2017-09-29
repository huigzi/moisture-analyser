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
	unsigned char localid[4];   	//����ID
	unsigned char serverip[4];  	//������IP
	unsigned char localip[4];   	//����IP
	unsigned char LocalIPMask[4]; //����MASK
	unsigned char GatewayIP[4]; 	//GateWay
	unsigned char DNSIP[4]; 		//DNS
	unsigned char localmac[6];  	//����MAC
	unsigned char serverport[2];  //�˿ں�
	unsigned char bootversion[2]; //dspbooter�汾��
	unsigned char appversion[6]; 	//�ͻ�Ӧ�ó���汾��
	unsigned char AppSize[4];     //Ӧ�ó����С��0-û��Ӧ�ó���
}LOCALINFO;	//44Bytes

typedef struct SMTWORKINFO{
	unsigned char dspHardVer[2];   	//DSPӲ���汾��
	unsigned char dspSoftVer[2];   	//DSP����汾��
	unsigned char fpgaVer[2];   	//FPGA�汾��
	unsigned char licenseData[4];  	//��Ȩʱ�䣨������Ȩ��0x0�����ޣ�0x01XXXXXX/�����գ�
									//�뵱ǰRTCʱ�����������������Ȩ��0x0�� ������>256�죺0x01000000; ������<256�죺0x02xxXXXX��
	unsigned int onBoardSN;  	//�ڼ�PCB��ţ�0-���ڼ죩
	unsigned int onBoardDate;   //�ڼ�PCB���ڣ��趨��
	unsigned char onBoardCisCnt; 	//�ڼ�PCB��CIS����
	unsigned short onBoardScanLine;	//�ڼ�PCBɨ���ٶȣ���/�룩
	unsigned char cisBlack_1; 		//CIS-1����ƽ
	unsigned char cisWhite_1;  		//CIS-1����ƽ
	unsigned char cisBlack_2; 		//CIS-2����ƽ
	unsigned char cisWhite_2;  		//CIS-2����ƽ
	unsigned char cisAdjustMax;  	//CIS����������
	unsigned char cisSkew; 			//CIS����б�Ƕ�
	unsigned short cisPitch_1; 	//CIS-1�����Ƕ�
	unsigned short cisPitch_2; 	//CIS-2�����Ƕ�
									//CIS��Ч��������밲װ�йأ���У���н����趨
	unsigned short cis0_ValidStart;	//��С0
	unsigned short cis0_ValidEnd;	//���5184��216mm/600dpi��
	unsigned short cis1_ValidStart;
	unsigned short cis1_ValidEnd;	//���5184
}SMTWORKINFO;	//39Bytes

typedef struct SMTPCBINFO{
  unsigned int PCBSN;  			//PCB��ţ�0-���ڼ죩
  unsigned int PCBDate;   		//PCB���ڣ��趨��
  unsigned char PCBUnit; 		//PCB��λ0-mm��1-inch
  unsigned int PCBLength;		//PCB����
  unsigned int PCBWidth;		//PCB���
  unsigned short PCBDir; 		//PCB����2λС����
  unsigned char PCBJointNum[2];  //PCBƴ��ģʽX-1B*Y-1B�����256��256��Ĭ��1��1-��ƴ�壩
  unsigned short PCBJointL; 	//ƴ�쳤�ȷ���ߴ�
  unsigned short PCBJointW; 	//ƴ�쳤�ȷ���ߴ�
  unsigned char PCBedgeMode;  	//PCB���ձ�ģʽ������λ��Ч��0b0X-��X-��X-��X-��
  unsigned short PCBedgeL; 		//PCB���ձ߳ߴ���
  unsigned short PCBedgeR; 		//PCB���ձ߳ߴ���
  unsigned short PCBedgeT; 		//PCB���ձ߳ߴ���
  unsigned short PCBedgeB; 		//PCB���ձ߳ߴ���
//  unsigned int NANDIPT[4];		//Nand��������3B-block��1B-Page
//  unsigned int NANDPOS[4];		//Nand��λ�ñ�3B-block��1B-Page
}SMTPCBINFO;	//34Bytes

//ʵʱSMT��Ϣ��CIS/PCB��������ʱ�仯
typedef struct RTSMTINFO{
	unsigned short cis_LineSize;	//cis���д�С����Ч���ݣ�<5192��������CIS�غϲ��ּ�ͷβ�����Ѿ������
	unsigned short cis_LineNum;		//һ֡��������252/24=10.5mm̫С
	float cis_dpi;					//ÿ���صĵ�λ

	unsigned int cis_LineAll;		//����PCB��С�ɼ������Ҫ��cis����
	unsigned int cis_frameCurrent;	//cisͼ��֡��

	unsigned int cis_LineCurrent;	//��ǰ�Ѵ���cis��������������pad��
	unsigned short cis_LineReback;	//��Ҫ������cis���������ְ���pad��

	unsigned char *pre_cisImage;	//ǰһ֡cisImage����cis_LineReback��ֵʱ��Ҫʹ��
	unsigned char *cur_cisImage;	//��ǰcisImage
	//ʵʱPCB��Ϣ������ʱ�仯
	unsigned short PcbRotate;	//PCB ��ת�Ƕ�
	unsigned short PcbState;	//PCB���״̬��0-δ��⣻1-�Ѽ�⵽��ߣ�2-�Ѽ�⵽λ�˶�λ����-ɢ��С��3-�Ѽ�⵽λ�˶�λ����-ɢ�ȴ�
	unsigned int curPadXmax;	//��ǰͼҪ�����pad��ţ�Xmax��
	unsigned int curPadXmin;	//��ǰͼҪ�����pad��ţ�Xmin��
	unsigned int nextPadXmax;	//�·�ͼ��ʼ�����pad��ţ�Xmax��
	unsigned int nextPadXmin;	//�·�ͼ��ʼ�����pad��ţ�Xmin��

}RTSMTINFO;

//-----------------------------------------------------------------------------
//�����Ķ���
typedef struct PNT_FR{
	int x;
	int y;
}PNT_FR;

//�������
typedef struct PointList{
	struct PointList *pre;
	struct PointList *next;
	struct PNT_FR point;
}PointList;

//���̵�
typedef struct PAD_FR{
	struct PNT_FR Pnt_centor;
	int moment;	//��
	unsigned int padArea;
	unsigned int padLength;
	unsigned int padWidth;
	unsigned int padRotate;
	unsigned char padStyle;
}PAD_FR;

//��������
typedef struct ParaList{
	struct ParaList *pre;
	struct ParaList *next;
	int ParaMeter;
}ParaList;

//gerb��������Ҫ���ں�Ķ��壬ÿ����Ķ����в���������һ��
typedef struct GERBIPT{
	struct GERBIPT *pre;
	struct GERBIPT *next;
	unsigned short gerbName;
	unsigned char paraNumber;	//��������
	struct ParaList *parList;
}GERBIPT;

//-------------------------------��������Ϣ����------------------------------------------
//gerb��������Ϣ
typedef struct GERBIPTInfo{
	unsigned char *gerbBuf;
	unsigned short gerbDNumber;
}GERBIPTInfo;

//gerb��������Ϣ�⹹-12Byte
typedef struct GERBIPTINDEX{
	unsigned short bufIndex;
	unsigned short gerbName;
	unsigned char gerbTyple;	//�������ͣ�R/C/O/P/M
	unsigned int MacroPrimNumber;//��gerbTyple=Mʱ��Ч��������Ȧ����ϣ�ÿ5λΪһ�飬���6��������Ȧ���
	unsigned char paraNumber;	//��������
	unsigned short paraLength;	//�������ݳ��ȣ��ֽڣ������65536�ֽ�
}GERBIPTINDEX;

//Macro����
typedef struct GerbMacroList{
	unsigned short MacroID;
	unsigned char MacroPrimNumber;	//Macro ��ʼ���ͺ��룺1/2/20/21/4/5/6/7
	void *GerbMacro;			//Macro�ṹָ��
	unsigned char paraNumber;	//��������
	unsigned char paraLength;	//�������ݳ��ȣ��ֽڣ�
}GerbMacroList;

//Macro ��ʼ���ͺ��룺1
typedef struct GerbMacroC_1{
	unsigned char FlagVarible;	//����Ϊ����/�������ӵ�λ��Ӧbit3-0
	unsigned char Exposure;
	unsigned int  Diameter;	//ֱ��
	struct PNT_FR Pnt_centor;//���ĵ�����
}GerbMacroC_1;

//Macro ��ʼ���ͺ��룺2/20
typedef struct GerbMacroVL_2_20{
	unsigned char FlagVarible;	//����Ϊ����/�������ӵ�λ��Ӧbit6-0
	unsigned char Exposure;
	unsigned int  LineWidth;	//�߿�
	struct PNT_FR Pnt_start;	//�������
	struct PNT_FR Pnt_end;		//�յ�����
	short rotate;				//��ת�Ƕ�
}GerbMacroVL_2_20;

//Macro ��ʼ���ͺ��룺21
typedef struct GerbMacroCL_21{
	unsigned char FlagVarible;	//����Ϊ����/�������ӵ�λ��Ӧbit5-0
	unsigned char Exposure;
	unsigned int  RecWidth;		//�߿�
	unsigned int  RecLength;	//�߿�
	struct PNT_FR Pnt_centor;	//���ĵ�����
	short rotate;				//��ת�Ƕ�
}GerbMacroCL_21;

//Macro ��ʼ���ͺ��룺22
typedef struct GerbMacroLLL_22{
	unsigned char FlagVarible;	//����Ϊ����/�������ӵ�λ��Ӧbit5-0
	unsigned char Exposure;
	unsigned int  RecWidth;		//�߿�
	unsigned int  RecLength;	//�߿�
	struct PNT_FR Pnt_lowerleft;//���½�����
	short rotate;				//��ת�Ƕ�
}GerbMacroLLL_22;

//Macro ��ʼ���ͺ��룺4
typedef struct GerbMacroOutline_4{
	unsigned char FlagVarible;	//����Ϊ����/�������ӵ�λ��Ӧbit2-0
	unsigned char Exposure;
	unsigned short subseqNumber;//The number of subsequent points n (n��1)
	struct PointList *pntList;
	short rotate;				//��ת�Ƕ�
}GerbMacroOutline_4;

//Macro ��ʼ���ͺ��룺5
typedef struct GerbMacroPolygon_5{
	unsigned char FlagVarible;	//����Ϊ����/�������ӵ�λ��Ӧbit5-0
	unsigned char Exposure;
	unsigned int  vertices;		//Number of vertices n, 3 �� n �� 12
	struct PNT_FR Pnt_centor;	//���ĵ�����
	unsigned int  Diameter;		//Diameter of the circumscribed circle, �� 0
	short rotate;				//��ת�Ƕ�
}GerbMacroPolygon_5;

//--------------------------------λ����Ϣ����-------------------------------------
//gerbλ�ñ���Ϣ
typedef struct GERBPOSInfo{
	unsigned char *gerbPosBuf;
	unsigned short gerbPNumber;
}GERBPOSInfo;

//gerbλ����Ϣ�ṹ������ʱ���򼰴���
typedef struct GERBPOS{
	unsigned short iptIndex;	//����������,���64K
	unsigned short gerbName;	//D����
	unsigned char Processed;	//���pcb������е���
	unsigned char valid;		//�Ƿ���Ч�����ֺ��̲���Ҫ���ӣ�Ҳ������м��
	struct PNT_FR Pnt_centor;	//���ĵ�����
	int	X_min;					//PCB������С���θ��ǣ����жϸú��̵��б�����Ƿ��ڵ�ǰͼ����
	int X_max;
	int	Y_min;
	int Y_max;
}GERBPOS;	//7.5��4=30Bytes

//--------------------------------��������-------------------------------------

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
