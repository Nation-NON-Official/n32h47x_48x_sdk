/**
*     Copyright (c) 2023, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file main.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "main.h"

#define TxBufferSize1 (countof(TxBuffer1) - 1)
#define TxBufferSize2 (countof(TxBuffer2) - 1)
#define DYMMY_BYTE    0x00

#define countof(a) (sizeof(a) / sizeof(*(a)))

USART_InitType USART_InitStructure;
USART_ClockInitType USART_ClockInitStructure;

uint8_t TxBuffer1[] = "USART Synchronous Example: USARTy -> SPIy using TXE and RXNE Flags";
uint8_t TxBuffer2[] = "USART Synchronous Example: SPIy -> USARTy using TXE and RXNE Flags";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
__IO uint8_t NbrOfDataToRead1 = TxBufferSize2;
__IO uint8_t NbrOfDataToRead2 = TxBufferSize1;
__IO uint8_t TxCounter1 = 0, RxCounter1 = 0;
__IO uint8_t TxCounter2 = 0, RxCounter2 = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();
    
    /* Configure the GPIO ports */
    GPIO_Configuration();
    
    /* Configure the SPI */
    SPI_Configuration();
    
    /* USARTy configuration */
	USART_ClockStructInit(&USART_ClockInitStructure);
    USART_ClockInitStructure.Clock    = USART_CLK_ENABLE;
    USART_ClockInitStructure.Polarity = USART_CLKPOL_LOW;
    USART_ClockInitStructure.Phase    = USART_CLKPHA_2EDGE;
    USART_ClockInitStructure.LastBit  = USART_CLKLB_ENABLE;
    USART_ClockInit(USARTy, &USART_ClockInitStructure);
    
	USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.OverSampling        = USART_16OVER;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure USARTy */
    USART_Init(USARTy, &USART_InitStructure);

    /* Enable the USARTy */
    USART_Enable(USARTy, ENABLE);

    while(NbrOfDataToRead2--)
    {
        /* Write one byte in the USARTy Transmit Data Register */
        USART_SendData(USARTy, TxBuffer1[TxCounter1++]);
        /* Wait until end of transmit */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_TXC) == RESET)
        {
        }

        /* Wait the byte is entirely received by SPIy */
        while (SPI_I2S_GetStatus(SPIy, SPI_I2S_RNE_FLAG) == RESET)
        {
        }
        /* Store the received byte in the RxBuffer2 */
        RxBuffer2[RxCounter2++] = SPI_I2S_ReceiveData(SPIy);
    }

    /* Clear the USARTy Data Register */
    USART_ReceiveData(USARTy);

    while (NbrOfDataToRead1--)
    {
        /* Wait until end of transmit */
        while (SPI_I2S_GetStatus(SPIy, SPI_I2S_TE_FLAG) == RESET)
        {
        }
        /* Write one byte in the SPIy Transmit Data Register */
        SPI_I2S_TransmitData(SPIy, TxBuffer2[TxCounter2++]);

        /* Send a Dummy byte to generate clock to slave */
        USART_SendData(USARTy, DYMMY_BYTE);
        /* Wait until end of transmit */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_TXC) == RESET)
        {
        }
        /* Wait the byte is entirely received by USARTy */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_RXDNE) == RESET)
        {
        }
        /* Store the received byte in the RxBuffer1 */
        RxBuffer1[RxCounter1++] = USART_ReceiveData(USARTy);
    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);
    /* TransferStatus = PASSED, if the data transmitted from USARTy and
       received by SPIy are the same */
    /* TransferStatus = FAILED, if the data transmitted from USARTy and
       received by SPIy are different */
    TransferStatus2 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);
    /* TransferStatus = PASSED, if the data transmitted from SPIy and
       received by USARTy are the same */
    /* TransferStatus = FAILED, if the data transmitted from SPIy and
       received by USARTy are different */

    while (1)
    {
    }
}


/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_EnableAHB1PeriphClk(USARTy_GPIO_CLK | SPIy_GPIO_CLK ,ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO,ENABLE);
    /* Enable USARTy Clock */
    USARTy_APBxClkCmd(USARTy_CLK,ENABLE);
    /* Enable SPIy Clock */
    SPIy_APBxClkCmd(SPIy_CLK,ENABLE);
}


/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\param   none
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* Configure USARTy TX and USARTy CK pins as alternate function push-pull */
    GPIO_InitStructure.Pin            = USARTy_TxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = USARTy_Tx_GPIO_AF;
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitPeripheral(USARTy_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin            = USARTy_ClkPin;
    GPIO_InitStructure.GPIO_Alternate = USARTy_Clk_GPIO_AF;
    GPIO_InitPeripheral(USARTy_GPIO, &GPIO_InitStructure);
    
    /* Configure SPI1 pins: SCK, MISO and MOSI */
    GPIO_InitStructure.Pin            = SPIy_SCKPin;
    GPIO_InitStructure.GPIO_Alternate = SPIy_SCK_GPIO_AF;
    GPIO_InitPeripheral(SPIy_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = SPIy_MISOPin;
    GPIO_InitStructure.GPIO_Alternate = SPIy_MISO_GPIO_AF;
    GPIO_InitPeripheral(SPIy_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.Pin            = SPIy_MOSIPin;
    GPIO_InitStructure.GPIO_Alternate = SPIy_MOSI_GPIO_AF;
    GPIO_InitPeripheral(SPIy_GPIO, &GPIO_InitStructure);

    /* Configure USARTy Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = USARTy_RxPin;
    GPIO_InitStructure.GPIO_Alternate = USARTy_Rx_GPIO_AF;
    GPIO_InitPeripheral(USARTy_GPIO, &GPIO_InitStructure);  
}


/**
*\*\name    SPI_Configuration.
*\*\fun     Configures the SPI.
*\*\param   none
*\*\return  none
**/
void SPI_Configuration(void)
{
    SPI_InitType SPI_InitStructure;

    /* Initialize SPI_InitStructure */
    SPI_InitStruct(&SPI_InitStructure);

    SPI_I2S_DeInit(SPIy);

    /* SPIy Config */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_SLAVE;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.FirstBit      = SPI_FB_LSB;

    /* Configure SPIy */
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIy enable */
    SPI_Enable(SPIy,ENABLE);
}

/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1
*\*\param   pBuffer2
*\*\param   BufferLength
*\*\return  PASSED or FAILED
**/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

