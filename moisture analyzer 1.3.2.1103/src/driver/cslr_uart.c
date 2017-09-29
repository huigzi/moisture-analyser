//-----------------------------------------------------------------------------
// \file    evmomapl138_uart.c
// \brief   implementation of a uart driver for OMAP-L138.
//
//-----------------------------------------------------------------------------
/* HW Macros */
#include <xdc/std.h>
#include "hw_types.h"
#include "fr_uart.h"
#include "gooao_c6748.h"
#include "cslr/soc_C6748.h"
#include "cslr/cslr_uart.h"
static uint32_t getStringLength(unsigned char *in_string);

/**************************************************************************/
/*                     API FUNCTION DEFINITIONS                           */
/**************************************************************************/

/**
 * \brief   Configures the following parameters: \n
 *           1> Baud Rate.\n
 *           2> Data Length in bits in each frame.\n
 *           3> Number of stop bits per frame.\n
 *           4> Parity selection(one among NO,ODD or EVEN parity. \n
 *             and Stick Parity bit selection).\n
 *
 * \param     baseAdd         Memory address of the UART instance used.\n
 * \param     uartClk         Frequency of the clock supplied to the UART module.\n
 * \param     baudrate        Required baud rate of communication.\n
 * \param     config          Logical OR of the appropriate macros related to
 *                            parity, number of stop bits and number of data
 *                            bits per frame.\n
 * \param     overSampRate    Over-sampling rate(either 13x or 16x).\n
 *
 * \return                    None.\n
 *
 * \note     The baud rate is configured by setting the divisor values derived
 *           from the module input clock \uartClk and the over sampling rate
 *           \overSampleRate. The module input clock depends on the PLL
 *           configurations and the system clock tree.
 */

void UARTConfigSetExpClk (unsigned int baseAdd, unsigned int uartClk,
                          unsigned int baudrate, unsigned int config,
                          unsigned int overSampRate)
{
    unsigned int divisor = 0;

    /* Calculating the divisor value */
    switch (overSampRate)
    {
        case UART_OVER_SAMP_RATE_13:
            divisor = uartClk/(baudrate * 13);
            HWREG(baseAdd + UART_MDR) = UART_OVER_SAMP_RATE;
        break;

        case UART_OVER_SAMP_RATE_16:
        default:
            divisor = uartClk/(baudrate * 16);
            HWREG(baseAdd + UART_MDR) &= ~UART_OVER_SAMP_RATE;
        break;
    }

    /*
    ** Writing the divisor value onto the Divisor Latch registers.
    ** Programming the divisor latch registers with an appropriate value sets
    ** the corresponding baud rate of communication for the device.
    */
    HWREG(baseAdd + UART_DLL) = ((divisor & 0xFF));
    HWREG(baseAdd + UART_DLH) = ((divisor & 0xFF00) >> 8);

    /*
    ** Write only relevant values to the LCR. LCR controls the number of data
    ** bits and stop bits per frame, parity enable feature, type of parity
    ** (even of odd), stick parity enable feature, Break control and DLAB
    ** selection bits.
    */

    HWREG(baseAdd + UART_LCR) = (config & ( UART_STOP_BIT | UART_WORDL |          \
                                            UART_PARITY | UART_SET_PARITY_TYPE |  \
                                            UART_STICK_PARITY | UART_BREAK_CTRL | \
                                            UART_DLAB));
}

/**
 * \brief   This function gets the following parameters from the registers.\n
 *          1> Baud Rate.\n
 *          2> Data Length in bits in each frame.\n
 *          3> Number of stop bits per frame.\n
 *          4> Parity selection.\n
 *
 * \param    baseAdd      Memory address of the UART instance used.\n
 * \param    uartClk      Frequency of clock supplied to the UART module.\n
 * \param    pBaud        Pointer to the storage of the UART baud rate.\n
 * \param    pConfig      Pointer to the storage of the configuration
 *                        parameters.\n
 *
 * \return   None.\n
 *
 */

void UARTConfigGetExpClk (unsigned int baseAdd, unsigned int uartClk,
                          unsigned int *pBaud,  unsigned int *pConfig)
{
   unsigned int overSampRate = 0;
   unsigned int divisor = 0;

   divisor = HWREG(baseAdd + UART_DLL);
   divisor |= HWREG(baseAdd + UART_DLH) << 8;

   if (HWREG(baseAdd + UART_MDR) & UART_OVER_SAMP_RATE)
   {
      overSampRate = 13;
   }
   else
   {
      overSampRate = 16;
   }

   /* Deriving the baudrate */
   *pBaud = (uartClk)/ (divisor * overSampRate);

   *pConfig = HWREG(baseAdd + UART_LCR);
   /* Get relevant data here stop bit information here. */
   *pConfig &= ( UART_WORDL | UART_STOP_BIT | UART_PARITY |
                 UART_SET_PARITY_TYPE | UART_STICK_PARITY |
                 UART_BREAK_CTRL | UART_DLAB);
}


/**
 *  \brief    This function sets the receiver FIFO trigger level.\n
 *
 *  \param    baseAdd     Memory address of the UART instance used.\n
 *  \param    rxLevel     This contains the settings for the FIFO threshold
 *                        level. While setting the FIFO threshold, it shall be
 *                        assumed that the FIFO is being enabled.This can take
 *                        one of the four following values:
 *                        1> UART_RX_TRIG_LEVEL_1
 *                        2> UART_RX_TRIG_LEVEL_4
 *                        3> UART_RX_TRIG_LEVEL_8
 *                        4> UART_RX_TRIG_LEVEL_14
 *  \return   None.\n
 *
 *  \note   This API needs needs to be called to configure the FIFO without
 *          enabling the DMA mode. If DMA mode is being used, the
 *          UARTDMAEnable() should be used to configure the FIFO.
 *
 * \note    FIFO Control Register(FCR) and the Interrupt Identification Register
 *          (IIR) share a common offset address. FCR register has write-only \n
 *          permissions and IIR register has read-only permissions. Therefore,
 *          reading from this address will read the value in IIR register and \n
 *          writing to this address will write the value into the FCR register.
 *          Since these share the same address, the integrity of bits in FCR \n
 *          register are at risk if we read from IIR register, modify this value
 *          and write the new value into the FCR register. Thus, we retain the \n
 *          status of the FIFOEN bit and the RXFIFTL bit in the FCR register by
 *          reinstating them to their previous values.\n


 */

void UARTFIFOLevelSet (unsigned int baseAdd, unsigned int rxLevel)
{
     HWREG(baseAdd + UART_FCR) = ((rxLevel & (UART_RX_TRIG_LEVEL)) |
                                              UART_FIFO_MODE);
}


/**
 * \brief    This function enables the DMA mode of operation.\n
 *
 * \param    baseAdd    Memory address of the UART instance used.\n
 * \param    flags      This should MANDATORILY contain the following two
 *                      macros:
 *                      UART_FIFO_MODE - which enables the FIFO mode of operation,
 *                      UART_DMAMODE - which enables the DMA mode of operation.
 *
 *                      This can also contain the Rx FIFO threshold value.\n
 *                      This can take any one of the four following values:
 *                      1> UART_RX_TRIG_LEVEL_1 - one byte trigger level.\n
 *                      2> UART_RX_TRIG_LEVEL_4 - 4 bytes trigger level. \n
 *                      3> UART_RX_TRIG_LEVEL_8 - 8 bytes trigger level. \n
 *                      4> UART_RX_TRIG_LEVEL_14 - 14 bytes trigger level.\n
 *
 * \return   None.\n
 *
 * \note    FIFO Control Register(FCR) and the Interrupt Identification Regsiter
 *          (IIR) share a common offset address. FCR register has write-only \n
 *          permissions and IIR register has read-only permissions. Therefore,
 *          reading from this address will read the value in IIR register and \n
 *          writing to this address will write the value into the FCR register.
 *          Since these share the same address, the integrity of bits in FCR \n
 *          register are at risk if we read from IIR register, modify this value
 *          and write the new value into the FCR register. Thus, we retain the \n
 *          status of the FIFOEN bit and the RXFIFTL bit in the FCR register by
 *          reinstating them to their previous values. Also, since the DMA mode \n
 *          requires that the FIFO be enabled, FIFO is enabled here. \n
 */

void UARTDMAEnable (unsigned int baseAdd, unsigned int flags)
{
    HWREG(baseAdd + UART_FCR) = (flags & (UART_FIFO_MODE | \
                                          UART_DMAMODE | \
                                          UART_RX_TRIG_LEVEL));
}

/**
 * \brief     This function disables the DMA mode of operation.\n
 *
 * \param     baseAdd     Memory address of the UART instance used.\n
 * \param     flags       This contains the bit-map values for FIFO enable and
 *                        Receiver FIFO Trigger Level values.
 *                        These bit-map values are:
 *
 *                        UART_FIFO_MODE - which enables the FIFO mode of operation.
 *                        This can take any one of the four following values:
 *                        1> UART_RX_TRIG_LEVEL_1 - one byte trigger level.\n
 *                        2> UART_RX_TRIG_LEVEL_4 - 4 bytes trigger level. \n
 *                        3> UART_RX_TRIG_LEVEL_8 - 8 bytes trigger level. \n
 *                        4> UART_RX_TRIG_LEVEL_14 - 14 bytes trigger level.\n
 *
 *
 * \return    None.\n
 *
 * \note      Refer to the note mentioned in the comments section of the function
 *            UARTDMAEnable(). \n
 *
 */

void UARTDMADisable (unsigned int baseAdd, unsigned int flags)
{
    /* Enabling the FIFO mode of operation.*/
    HWREG(baseAdd + UART_FCR) = (flags & (UART_FIFO_MODE | UART_RX_TRIG_LEVEL));
}

/**
 * \brief    Configures the parity mode required for transmission.\n
 *
 * \param    baseAdd     Memory address of the UART instance used.\n
 * \param    parityMode  This contains the settings for parity enable/disable,
 *                       stick parity, odd/even parity.\n
 *
 * \return   None. \n
 *
 */

void UARTParityModeSet(unsigned int baseAdd, unsigned int parityMode)
{
    /* Clearing the Parity related bits.*/
    HWREG(baseAdd + UART_LCR) &= ~(UART_PARITY  | UART_SET_PARITY_TYPE |
                                   UART_STICK_PARITY);
    /* Setting the Parity related bits depending upon 'parityMode'.*/
    HWREG(baseAdd + UART_LCR) |= (parityMode & (UART_PARITY |
                                                UART_SET_PARITY_TYPE |
                                                UART_STICK_PARITY));
}


/**
 * \brief    This function gets the parity mode currently being used.\n
 *
 * \param    baseAdd   Memory address of the UART instance used.\n
 *
 * \return   A value which when appropriately decoded in the application
 *           program would tell whether: \n
 *           a> No, odd or even parity is selected.\n
 *           b> Stick parity is selected.\n
 */

unsigned int UARTParityModeGet(unsigned int baseAdd)
{
    unsigned int mask;

    mask = (UART_PARITY | UART_SET_PARITY_TYPE | UART_STICK_PARITY);

    return (HWREG(baseAdd + UART_LCR)& mask);
}


/**
 * \brief  This function does the following three operations:\n
 *         1> Enables the FREE running mode for the UART.\n
 *         2> Enables the transmitter.\n
 *         3> Enables the receiver.\n
 *
 * \param    baseAdd      Memory address of the UART instance used.\n
 *
 * \return   None.\n
 */

void UARTEnable (unsigned int baseAdd)
{
    /* Enable the Tx, Rx and the free running mode of operation. */
    HWREG(baseAdd + UART_PWREMU_MGMT) = (UART_FREE_MODE  |       \
                                         UART_RX_RST_ENABLE |    \
                                         UART_TX_RST_ENABLE);
}


/**
 * \brief     This function does the following operations.\n
 *            1> Disables and resets the transmitter.\n
 *            2> Disables the resets the receiver.\n
 *            3> Disables the FREE running mode of operation of the UART. \n
 *
 * \param    baseAdd     Memory address of the UART instance used.
 *
 * \return   None.
 *
 */

void UARTDisable (unsigned int baseAdd)
{
    /* Disable the Tx, Rx and Free running mode of operation.*/
    HWREG(baseAdd + UART_PWREMU_MGMT) &= ~(UART_FREE_MODE |      \
                                           UART_RX_RST_ENABLE |  \
                                           UART_TX_RST_ENABLE);
}


/**
 * \brief   This function does the following operations.
 *          1> Enable the FIFO.
 *          2> Clears the transmitter FIFO and resets the transmitter FIFO
 *             counter.
 *          3> Clears the receiver FIFO and resets the receiver FIFO counter.
 *
 * \param   baseAdd        Memory address of the UART instance used.
 *
 * \return  None.
 *
 * \note    This enable the FIFO and the trigger levels are set to the default
 *          values. The TX and the RX FIFO are also cleared. If the FIFO needs
 *          to be enabled, with different settings then one should call
 *          \UARTFIFOLevelSet after this API call.
 *
 */

void UARTFIFOEnable(unsigned int baseAdd)
{
    HWREG(baseAdd + UART_FCR) = (UART_FIFO_MODE | UART_RX_CLEAR |
                                 UART_TX_CLEAR);
}


/**
 * \brief    This function disables the FIFO mode of operation.
 *
 * \param    baseAdd       Memory address of the UART instance used.
 *
 * \return   None.
 *
 * \note     This clears all the settings of the FIFO control Register(FCR)
 *           and disables the FIFO.
 *
 */

void UARTFIFODisable(unsigned int baseAdd)
{
    HWREG(baseAdd + UART_FCR) = 0;
}


/**
 * \brief   This function checks if the transmitter is empty by checking for
 *          the emptiness of Transmitter Holding Register(THR) and the
 *          Transmit Shift regsiter(TSR).
 *
 *
 * \param   baseAdd   Memory address of the UART instance used.
 *
 * \return            Returns TRUE if Transmitter FIFO(or THR register
 *                    for non-FIFO mode) is empty. Else it returns FALSE.
 */

unsigned int UARTSpaceAvail(unsigned int baseAdd)
{
    unsigned int retVal = FALSE;

    /*
    ** Checking if THRE or TEMT bits in Line Status Register (LSR) are set.
    ** THRE bit is set when the Transmitter FIFO is empty( THR register in
    ** non-FIFO mode). TEMT bit is set when both Transmitter FIFO and the
    ** Transmitter Shift Register(TSR)are empty(THR and TSR registers in
    ** non-FIFO mode).
    */

    if (HWREG(baseAdd + UART_LSR) & (UART_THR_TSR_EMPTY | UART_THR_EMPTY))
    {
        retVal = TRUE;
    }

    return retVal;
}


/**
 * \brief   This function checks if: \n
 *          a> the Receiver Buffer Register(RBR) has data and it is ready to
 *             be read (for non-FIFO mode) or\n
 *          b> the Receiver FIFO has atleast one byte of data to be read
 *             (FIFO mode). \n
 *
 * \param     baseAdd   Memory address of the UART instance used.
 *
 * \return    Returns TRUE if there is atleast one byte to be read.
 *            Else it returns FALSE.
 *
 */

unsigned int UARTCharsAvail(unsigned int baseAdd)
{
    unsigned int retVal = FALSE;

    if (HWREG(baseAdd + UART_LSR) & UART_DATA_READY)
    {
        retVal = TRUE;
    }

    return retVal;
}


/**
 * \brief   This function gives the status of error bits.
 *
 * \param   baseAdd     Memory address of the UART instance used.
 *
 * \return              The return value could be one or a combination of
 *                      the following macros:
 *                      UART_OVERRUN_ERROR - indicating an Overrun Error.
 *                      UART_PARITY_ERROR - indicating a Parity Error.
 *                      UART_FRAME_ERROR - indicating a Frame Error.
 *                      UART_BREAK_IND - indicating a Break Indicator
 *                                       has been generated.
 */

unsigned int UARTRxErrorGet(unsigned int baseAdd)
{
    return (HWREG(baseAdd + UART_LSR) & (UART_OVERRUN_ERROR | UART_PARITY_ERROR |
                                         UART_FRAME_ERROR | UART_BREAK_IND));
}


/**
 * \brief    This function attempts to write a byte into Transmitter Holding
 *           Register (THR). This API checks only once if the transmitter
 *           is empty. If yes, it puts the byte, else it returns FALSE.
 *
 * \param    baseAdd     Memory address of the UART instance being used.
 * \param    byteWrite   Byte to be written into the THR register.
 *
 * \return   TRUE if the transmitter FIFO(or THR register in non-FIFO mode)
 *           is empty and the character was written. Else it returns FALSE.
 */

unsigned int UARTCharPutNonBlocking(unsigned int baseAdd,
                                    unsigned char byteWrite)
{
    unsigned int retVal = FALSE;

    if (HWREG(baseAdd + UART_LSR) & (UART_THR_TSR_EMPTY | UART_THR_EMPTY))
    {
       HWREG(baseAdd + UART_THR) = byteWrite;
       retVal = TRUE;
    }

    return retVal;
 }


/**
 * \brief    This function reads a byte from the Receiver Buffer Register
 *           (RBR). This API checks if any character is ready to be read.
 *            If ready then returns the read byte, else it returns -1.
 *
 * \param    baseAdd   Memory address of the UART instance being used.
 *
 * \return   The character in the RBR register typecasted as integer.
 *           If no character is found in the RBR register, -1
 *           is returned.
 */

int UARTCharGetNonBlocking(unsigned int baseAdd)
{
    int retVal = -1;

    if(HWREG(baseAdd + UART_LSR) & UART_DATA_READY)
    {
       retVal = HWREG(baseAdd + UART_RBR);
    }

    return retVal;
}


/**
 * \brief      This function waits indefinitely for the arrival of a byte in
 *             the receiver FIFO. Once a byte has arrived, it returns that
 *             byte typecasted as integer.
 *
 * \param      baseAdd     Memory address of the UART instance being used.
 *
 * \return     The byte in the RBR register typecasted as integer.
 *
 */

int UARTCharGet(unsigned int baseAdd)
{
    int data = 0;

    /*
    ** Busy check if data is available in receiver FIFO(RBR regsiter in non-FIFO
    ** mode) so that data could be read from the RBR register.
    */
    while ((HWREG(baseAdd + UART_LSR) & UART_DATA_READY) == 0);

    data = (int)HWREG(baseAdd + UART_RBR);

    return data;
}

/**
 * \brief   This function checks indefinitely whether the Transmitter FIFO
 *          (THR regsiter in non-FIFO mode)is empty. If found empty, a byte
 *          is written into the THR register.
 *
 * \param   baseAdd         Memory address of the UART instance being used.
 * \param   byteTx          Byte to be transmitted.
 *
 * \return  None.
 *
 */


void UARTCharPut(unsigned int baseAdd, unsigned char byteTx)
{
   unsigned int txEmpty;

   txEmpty = (UART_THR_TSR_EMPTY | UART_THR_EMPTY);

   /*
   ** Here we check for the emptiness of both the Trasnsmitter Holding
   ** Register(THR) and Transmitter Shift Register(TSR) before writing
   ** data into the Transmitter FIFO(THR for non-FIFO mode).
   */

   while (txEmpty != (HWREG(baseAdd + UART_LSR) & txEmpty));

   /*
   ** Transmitter FIFO(THR register in non-FIFO mode) is empty.
   ** Write the byte onto the THR register.
   */
   HWREG(baseAdd + UART_THR) = byteTx;
}


/**
 * \brief   This function enables the specified interrupts of the UART module.
 *          The interrupts that can be enabled are the receive interrupt,
 *          transmit interrupt, line status interrupt and the modem status
 *          interrupt.
 *
 * \param   baseAdd    Memory address of the UART instance being used.
 * \param   intFlags   This is a bitwise OR of the interrupts that need to be
 *                     enabled

 * \return  None.
 *
 */

void UARTIntEnable(unsigned int baseAdd, unsigned int intFlags)
{
    HWREG(baseAdd + UART_IER) |=
            (intFlags & (UART_INT_MODEM_STAT | UART_INT_LINE_STAT |
                         UART_INT_TX_EMPTY | UART_INT_RXDATA_CTI));
}


/**
 * \brief   This function disables the specified interrupts of the UART module.
 *
 * \param   baseAdd    Memory address of the UART instance being used.
 * \param   intFlags   This is bitwise OR of interrupts that need to be
 *                     disabled.
 *
 * \return  None.
 *
 */

void UARTIntDisable(unsigned int baseAdd, unsigned int intFlags)
{
    HWREG(baseAdd + UART_IER) &= ~(intFlags & (UART_INT_MODEM_STAT |
                                               UART_INT_LINE_STAT |
                                               UART_INT_TX_EMPTY |
                                               UART_INT_RXDATA_CTI));
}


/**
 * \brief   This function returns highest priority UART interrupt for service
 *
 * \param   baseAdd    Memory address of the UART instance being used.
 *
 * \return  Contents of the Interrupt Type field of IIR register.
 *          This function returns one of the following macros:
 *          1> UART_INTID_TX_EMPTY.
 *          2> UART_INTID_RX_DATA.
 *          3> UART_INTID_RX_LINE_STAT.
 *          4> UART_INTID_CTI.
 *
 */

unsigned int UARTIntStatus(unsigned int baseAdd)
{
    unsigned int iirValue = 0;

    iirValue = HWREG(baseAdd + UART_IIR);
    iirValue &= UART_INTID;
    iirValue >>= UART_IIR_INTID_SHIFT;

    return iirValue;
}

/**
 * \brief   This function is used to transmit Break condition to the receiving
 *          UART and also to release the Break condition depending on the value
 *          of the 'breakState' variable
 *
 * \param   baseAdd      Memory address of the UART instance being used.
 * \param   BreakState   TRUE for transmitting the Break condition to the
 *                       receiving UART.
 *                       FALSE for releasing the receiver from the Break
 *                       condition.
 *
 * \return  None.
 *
 */

void UARTBreakCtl(unsigned int baseAdd, unsigned int breakState)
{
   if(TRUE == breakState)
   {
        HWREG(baseAdd + UART_LCR) |= UART_BREAK_CTRL;
   }
   else
   {
       HWREG(baseAdd + UART_LCR) &= ~UART_BREAK_CTRL;
   }

   return;
}

/**
 * \brief  This function is intended to set the Autoflow Control Enable(AFE)
 *         bit and Request To Send(RTS) bit in the Modem Control Register(MCR).
 *
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  ctrlFlags    This contains bitwise OR of the AFE enable  bit and
 *                      RTS bit in the MCR register.
 *
 * \return  None.
 *
 */

void UARTModemControlSet(unsigned int baseAdd, unsigned int ctrlFlags)
{
   /* Reading the Modem Control Register(MCR).*/
   HWREG(baseAdd + UART_MCR) &= ~(UART_AUTOFLOW | UART_RTS);

   HWREG(baseAdd + UART_MCR) |= (ctrlFlags & (UART_AUTOFLOW | UART_RTS));
}


/**
 * \brief    This function is intended to clear the Autoflow control
 *           enable(AFE) bit and the Request To Send(RTS) bit in the
 *           Modem Control Register(MCR).
 *
 * \param    baseAdd     Memory address of the UART instance being used.
 * \param    ctrlFlags   This is a bitwise OR of AFE bit and the RTS bit in MCR
 *
 * \return   None.
 *
 */

void UARTModemControlClear(unsigned int baseAdd, unsigned int ctrlFlags)
{
    HWREG(baseAdd + UART_MCR) &= ~(ctrlFlags & (UART_AUTOFLOW | UART_RTS));
}

/**
 * \brief   This function gets the status of the RTS and AFE bits
 *          in the MCR register.
 *
 * \param   baseAdd   Memory address of the UART instance being used.
 *
 * \return  The status of RTS and AFE bits if MCR
 *
 */
unsigned int UARTModemControlGet(unsigned int baseAdd)
{
   return HWREG(baseAdd + UART_MCR) & (UART_AUTOFLOW | UART_RTS);
}

/**
 * \brief   This function returns the UART modem status.
 *
 * \param   baseAdd    Memory address of the UART instance being used.
 *
 * \return  This function returns the status of DCD, CTS, DSR and RI
 *          bits of the Modem Status Register(MSR).
 */
unsigned int UARTModemStatusGet(unsigned int baseAdd)
{
   return HWREG(baseAdd + UART_MSR) & (UART_RI | UART_DSR |
                                       UART_CTS | UART_DCD);

}

//-----------------------------------------------------------------------------
// \brief   initialize the given serial port.
//
// \param   uart_regs_t *uart - pointer to register struct for the desired uart.
//
// \param   uint32_t baud_rate - desired baud rate for serial port.
//
// \return  uint32_t
//    ERR_NO_ERROR - everything is ok...uart ready to use.
//    ERR_INIT_FAIL - something happened during initialization.
//-----------------------------------------------------------------------------
uint32_t UART_init(unsigned int baseAdd, uint32_t baud_rate)
{
   uint32_t divisor;

   CSL_UartRegsOvly uartRegs = (CSL_UartRegsOvly)baseAdd;

   // put xmtr/rcvr in reset.
   uartRegs->PWREMU_MGMT = 0;

   // set baud rate...assumes default 16x oversampling.
   divisor = CSL_SYSCLK_2_FREQ / (baud_rate * 16);
   uartRegs->DLH = (divisor & 0x0000FF00) >> 8;
   uartRegs->DLL = divisor & 0x000000FF;

   // enable xmtr/rcvr fifos.
   uartRegs->FCR = 0;
   SETBIT(uartRegs->FCR, FIFOEN);
   SETBIT(uartRegs->FCR, RXCLR | TXCLR | DMAMODE1);

   // disable interrupts, flow control, and loop back.
   //注意,要打开UART中断!
   uartRegs->IER = 0x01;
   uartRegs->MCR = 0;
   uartRegs->MDR = 0;

   // config LCR for no parity, one stop bit, 8 data bits, no flow control.
   uartRegs->LCR = 0;
   SETBIT(uartRegs->LCR, WLS_8);

   // take xmtr/rcvr out of reset.
   SETBIT(uartRegs->PWREMU_MGMT, UTRST | URRST | FREE);

   return (ERR_NO_ERROR);
}

//-----------------------------------------------------------------------------
// \brief   transmit a byte out the debug serial port.
//
// \param   uart_regs_t *uart - pointer to register struct for the desired uart.
//
// \param   uint8_t in_data - the byte to transmit.
//
// \return  uint32_t
//    ERR_NO_ERROR - input in bounds, byte transmitted.
//    ERR_INVALID_PARAMETER - null pointers.
//-----------------------------------------------------------------------------
uint32_t UART_txByte(unsigned int baseAdd, unsigned char in_data)
{
	UARTCharPut(baseAdd, in_data);

	return NULL;
}

//-----------------------------------------------------------------------------
// \brief   transmit an array of bytes out a serial port.
//
// \param   uart_regs_t *uart - pointer to register struct for the desired uart.
//
// \param   uint8_t *in_data - pointer to the array to transmit.
//
// \param   uint32_t in_length - number of bytes to transmit.
//
// \return  uint32_t
//    ERR_NO_ERROR - input in bounds, array transmitted.
//    ERR_INVALID_PARAMETER - null pointers.
//-----------------------------------------------------------------------------
uint32_t UART_txArray(unsigned int baseAdd, unsigned char *in_data, uint32_t in_length)
{
   uint32_t rtn = ERR_INVALID_PARAMETER;
   uint32_t i;

   if ((baseAdd != 0) && (in_data != 0))
   {
      for (i = 0; i < in_length; i++)
      {
         (void)UART_txByte(baseAdd, in_data[i]);
      }

      rtn = ERR_NO_ERROR;
   }

   return (rtn);
}

//-----------------------------------------------------------------------------
// \brief   transmit a string out a serial port.
//
// \param   uart_regs_t *uart - pointer to register struct for the desired uart.
//
// \param   uint8_t *in_data - pointer to the string to transmit.
//
// \return  uint32_t
//    ERR_NO_ERROR - input in bounds, string transmitted.
//    ERR_INVALID_PARAMETER - null pointers.
//-----------------------------------------------------------------------------
uint32_t UART_txString(unsigned int baseAdd, unsigned char *in_data)
{
   uint32_t rtn = ERR_INVALID_PARAMETER;

   if ((baseAdd != 0) && (in_data != 0))
   {
      uint32_t numBytes = getStringLength(in_data);

      rtn = UART_txArray(baseAdd, (uint8_t *)in_data, numBytes);
   }

   return (rtn);
}

//-----------------------------------------------------------------------------
// \brief   transmit a hex byte out a serial port.
//
// \param   uart_regs_t *uart - pointer to register struct for the desired uart.
//
// \param   uint8_t in_data - the uint8 to transmit.
//
// \return  uint32_t
//    ERR_NO_ERROR - input in bounds, byte transmitted.
//    ERR_INVALID_PARAMETER - null pointers.
//-----------------------------------------------------------------------------
uint32_t UART_txUint8(unsigned int baseAdd, unsigned char in_data)
{
   uint32_t rtn = ERR_INVALID_PARAMETER;

   if (baseAdd != 0)
   {
      uint8_t tmp_array[5];

      //#ifndef BOOT
	  //sprintf((char *)tmp_array, "0x%02X", in_data);
      //#endif

	  tmp_array[0] = in_data;
      //rtn = UART_txArray(uart, tmp_array, 4);
	  rtn = UART_txArray(baseAdd, tmp_array, 1);
   }

   return (rtn);
}

//-----------------------------------------------------------------------------
// Private Function Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// helper function to compute the number of bytes in a string.
//-----------------------------------------------------------------------------
static uint32_t getStringLength(unsigned char *in_string)
{
   uint32_t numBytes = 0;

   while (in_string[numBytes] != 0)
   {
      numBytes++;
   }

   return numBytes;
}
