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
*\*\file i2c_eeprom.c
*\*\author Nations 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x.h"
#include "n32h47x_48x_dma.h"
#include "i2c_eeprom.h"
#include "string.h"
#include "stdbool.h"
#include "n32h47x_48x_i2c.h"
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_gpio.h"

/** I2C_EEPROM **/

/* when EEPROM is writing data inside,it won't response the request from the master.check the ack,
if EEPROM response,make clear that EEPROM finished the last data-writing,allow the next operation */
static bool check_begin = FALSE;
static bool OffsetDone  = FALSE;

u32 sEETimeout = sEE_LONG_TIMEOUT;

static u8 MasterDirection = Transmitter;
static u16 SlaveADDR;
static u16 DeviceOffset = 0x0;

u16 I2C_NumByteToWrite   = 0;
u8 I2C_NumByteWritingNow = 0;
u8* I2C_pBuffer          = 0;
u16 I2C_WriteAddr        = 0;

static u8 SendBuf[8]          = {0};
static u16 BufCount           = 0;
static u16 Int_NumByteToWrite = 0;
static u16 Int_NumByteToRead  = 0;
/* global state variable i2c_comm_state */
volatile I2C_STATE i2c_comm_state;

/**
*\*\name    sEE_TIMEOUT_UserCallback.
*\*\fun     Timeout callback used by the I2C EEPROM driver.
*\*\param   none
*\*\return  none 
**/
void sEE_TIMEOUT_UserCallback(void)
{
    printf("error!!!\r\n");
    /* Block communication and all processes */
    IIC_RCCReset();
}

/**
*\*\name    I2C_EE_Init.
*\*\fun     Initializes I2C\GPIO\NVIC\RCC used by the I2C EEPROM driver.
*\*\param   none
*\*\return  none 
**/
void I2C_EE_Init(void)
{
    /** GPIO configuration and clock enable */
    GPIO_InitType GPIO_InitStructure;
    I2C_InitType I2C_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    
    /** enable peripheral clk*/
    I2Cx_peripheral_clk_en();
    I2C_DeInit(I2Cx);
    I2Cx_scl_clk_en();
    I2Cx_sda_clk_en();
    I2C_GPIO->POD |= (I2Cx_SCL_PIN | I2Cx_SDA_PIN);
		/* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);
	
    GPIO_InitStructure.Pin        = I2Cx_SCL_PIN ;
    GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
	GPIO_InitStructure.GPIO_Alternate = I2Cx_SCL_AF;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_OD;
	GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitPeripheral(I2C_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin        = I2Cx_SDA_PIN;
    GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
	GPIO_InitStructure.GPIO_Alternate = I2Cx_SDA_AF;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_OD;
	GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitPeripheral(I2C_GPIO, &GPIO_InitStructure);

    /** I2C periphral configuration */
    I2C_DeInit(I2Cx);
    I2C_InitStruct(&I2C_InitStructure); 
    I2C_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C_InitStructure.OwnAddr1    = 0xff;
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = I2C_Speed;
    I2C_Init(I2Cx, &I2C_InitStructure);
    
			
    /** I2C NVIC configuration */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel                   = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel                   = I2C1_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
*\*\name  I2C_EE_WriteBuffer.
*\*\fun   Writes buffer of data to the I2C EEPROM.
*\*\param pBuffer pointer to the buffer  containing the data to be
*\*\                  written to the EEPROM.
*\*\param WriteAddr EEPROM's internal address to write to.
*\*\param NumByteToWrite number of bytes to write to the EEPROM.
**/
void I2C_EE_WriteBuffer(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
{
    if (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
    {
        return;
    }
    I2C_pBuffer        = pBuffer;
    I2C_WriteAddr      = WriteAddr;
    I2C_NumByteToWrite = NumByteToWrite;

    while (I2C_NumByteToWrite > 0)
    {
        I2C_EE_WriteOnePage(I2C_pBuffer, I2C_WriteAddr, I2C_NumByteToWrite);
    }
}

/**
*\*\name  I2C_EE_WriteOnePage.
*\*\fun   Writes a page of data to the I2C EEPROM, general called by
*\*\         I2C_EE_WriteBuffer.
*\*\param pBuffer pointer to the buffer  containing the data to be
*\*\                  written to the EEPROM.
*\*\param WriteAddr EEPROM's internal address to write to.
*\*\param NumByteToWrite number of bytes to write to the EEPROM.
**/
void I2C_EE_WriteOnePage(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
{
    u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

    Addr        = WriteAddr % I2C_PageSize;
    count       = I2C_PageSize - Addr;
    NumOfPage   = NumByteToWrite / I2C_PageSize;
    NumOfSingle = NumByteToWrite % I2C_PageSize;

    I2C_NumByteWritingNow = 0;
    /** If WriteAddr is I2C_PageSize aligned */
    if (Addr == 0)
    {
        /** If NumByteToWrite < I2C_PageSize */
        if (NumOfPage == 0)
        {
            I2C_NumByteWritingNow = NumOfSingle;
            I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
        /** If NumByteToWrite > I2C_PageSize */
        else
        {
            I2C_NumByteWritingNow = I2C_PageSize;
            I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
        }
    }
    /** If WriteAddr is not I2C_PageSize aligned */
    else
    {
        /* If NumByteToWrite < I2C_PageSize */
        if (NumOfPage == 0)
        {
            I2C_NumByteWritingNow = NumOfSingle;
            I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
        /* If NumByteToWrite > I2C_PageSize */
        else
        {
            if (count != 0)
            {
                I2C_NumByteWritingNow = count;
                I2C_EE_PageWrite(pBuffer, WriteAddr, count);
            }
        }
    }
}

/**
*\*\name  I2C_EE_PageWrite.
*\*\fun   Writes more than one byte to the EEPROM with a single WRITE
*\*\         cycle. The number of byte can't exceed the EEPROM page size.
*\*\param pBuffer pointer to the buffer containing the data to be
*\*\                  written to the EEPROM.
*\*\param WriteAddr EEPROM's internal address to write to (1-16).
*\*\param NumByteToWrite number of bytes to write to the EEPROM.
**/
void I2C_EE_PageWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite)
{
    /** initialize static parameter */
    MasterDirection = Transmitter;
    i2c_comm_state  = COMM_PRE;
    /** initialize static parameter according to input parameter */
    SlaveADDR    = EEPROM_ADDRESS; /// this byte shoule be send by F/W (in loop or INTSTS way)
    DeviceOffset = WriteAddr;      /// this byte can be send by both F/W and DMA
    OffsetDone   = FALSE;
    memcpy(SendBuf, pBuffer, NumByteToWrite);
    BufCount           = 0;
    Int_NumByteToWrite = NumByteToWrite;
    I2C_ConfigAck(I2Cx, ENABLE);
    I2C_ConfigInt(I2Cx, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);

    /** Send START condition */
    sEETimeout = sEE_LONG_TIMEOUT;
    while (I2C_GetFlag(I2Cx, I2C_FLAG_BSF))
    {
        if ((sEETimeout--) == 0)
				{
            sEE_TIMEOUT_UserCallback();
					  return;
				}
    }
    I2C_GenerateStart(I2Cx, ENABLE);
    I2C_EE_WaitOperationIsCompleted();
    I2C_EE_WriteOnePageCompleted();
}

/**
*\*\name    I2C_EE_WriteOnePageCompleted.
*\*\fun     Process Write one page completed.
*\*\param   none
*\*\return  none 
**/
void I2C_EE_WriteOnePageCompleted(void)
{
    I2C_pBuffer += I2C_NumByteWritingNow;
    I2C_WriteAddr += I2C_NumByteWritingNow;
    I2C_NumByteToWrite -= I2C_NumByteWritingNow;
}

/**
*\*\name  I2C_EE_ReadBuffer.
*\*\fun   Reads a block of data from the EEPROM.
*\*\param pBuffer pointer to the buffer that receives the data read
*\*\                  from the EEPROM.
*\*\param ReadAddr EEPROM's internal address to read from.
*\*\param NumByteToRead number of bytes to read from the EEPROM.
**/
void I2C_EE_ReadBuffer(u8* pBuffer, u16 ReadAddr, u16 NumByteToRead)
{
    I2C_pBuffer     = pBuffer;
    MasterDirection = Receiver;

    /** initialize static parameter according to input parameter*/
    SlaveADDR      = EEPROM_ADDRESS;
    DeviceOffset   = ReadAddr;
    OffsetDone     = FALSE;
    i2c_comm_state = COMM_PRE;
    I2C1->CTRL1 &= I2C_NACK_POS_CURRENT; // reset ACKPOS
    I2C_ConfigAck(I2Cx, ENABLE);
    I2C_ConfigInt(I2Cx, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);
    Int_NumByteToRead = NumByteToRead;

    sEETimeout = sEE_LONG_TIMEOUT;
    while (I2C_GetFlag(I2Cx, I2C_FLAG_BSF))
    {
        if ((sEETimeout--) == 0)
				{
            sEE_TIMEOUT_UserCallback();
					  return;
				}
    }
    I2C_GenerateStart(I2Cx, ENABLE);
    I2C_EE_WaitOperationIsCompleted();
}

/**
*\*\name    I2C_EE_WaitOperationIsCompleted.
*\*\fun     wait operation is completed.
*\*\param   none
*\*\return  none 
**/
void I2C_EE_WaitOperationIsCompleted(void)
{
    sEETimeout = sEE_LONG_TIMEOUT;
    while (i2c_comm_state != COMM_DONE)
    {
        if ((sEETimeout--) == 0)
				{
            sEE_TIMEOUT_UserCallback();
					  return;
				}
    }
}
/**
*\*\name    I2C1_EV_IRQHandler.
*\*\fun     I2c1 event interrupt Service Routines.
*\*\param   none
*\*\return  none 
**/
void I2C1_EV_IRQHandler(void)
{
    uint32_t lastevent = I2C_GetLastEvent(I2C1);
    switch (lastevent)
    {
    /** Master Invoke */
    case I2C_EVT_MASTER_MODE_FLAG: /// EV5
        if (!check_begin)
        {
            i2c_comm_state = COMM_IN_PROCESS;
        }
        if (MasterDirection == Receiver)
        {
            if (!OffsetDone)
            {
                I2C_SendAddr7bit(I2C1, SlaveADDR, I2C_DIRECTION_SEND);
            }
            else
            {
                /** Send slave Address for read */
                I2C_SendAddr7bit(I2C1, SlaveADDR, I2C_DIRECTION_RECV);
                OffsetDone = FALSE;
            }
        }
        else
        {
            /** Send slave Address for write */
            I2C_SendAddr7bit(I2C1, SlaveADDR, I2C_DIRECTION_SEND);
        }
        break;
    /** Master Receiver events */
    case I2C_EVT_MASTER_RXMODE_FLAG: /// EV6
            if (Int_NumByteToRead == 1)
            {
                I2C_ConfigAck(I2C1, DISABLE);
                I2C_GenerateStop(I2C1, ENABLE);
            }
            else if (Int_NumByteToRead == 2)
            {
                I2C1->CTRL1 |= I2C_NACK_POS_NEXT; /// set ACKPOS
                I2C_ConfigAck(I2C1, DISABLE);
            }
        break;
    case I2C_EVT_MASTER_DATA_RECVD_FLAG: /// EV7
    case I2C_EVT_MASTER_SFT_DATA_RECVD_FLAG: // BUSY, MSMODE(Master) and Data register not empty, BSF(Byte transfer finished)flags.
        *I2C_pBuffer = I2C_RecvData(I2C1);
        I2C_pBuffer++;
        Int_NumByteToRead--;
        if (Int_NumByteToRead == 1)
        {
            /** Disable Acknowledgement */
            I2C_ConfigAck(I2C1, DISABLE);
            I2C_GenerateStop(I2C1, ENABLE);
        }
        if (Int_NumByteToRead == 0)
        {
            I2C_ConfigInt(I2C1, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, DISABLE);
            i2c_comm_state = COMM_DONE;
        }
        break;
    /** Master Transmitter events */
    case I2C_EVT_MASTER_TXMODE_FLAG: /// EV8 just after EV6
        if (check_begin)
        {
            check_begin = FALSE;
            I2C_ConfigInt(I2C1, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, DISABLE);
            I2C_GenerateStop(I2C1, ENABLE);
            i2c_comm_state = COMM_DONE;
            break;
        }
        I2C_SendData(I2C1, DeviceOffset);
        OffsetDone = TRUE;
        break;
    case I2C_EVT_MASTER_DATA_SENDING: ///  EV8 I2C_EVENT_MASTER_DATA_TRANSMITTING
        if (MasterDirection == Receiver)
        {
            I2C_GenerateStart(I2C1, ENABLE);
        }
        break;
    case I2C_EVT_MASTER_DATA_SENDED: /// EV8-2
        if (MasterDirection == Transmitter)
        {
            if (Int_NumByteToWrite == 0)
            {
                I2C_GenerateStop(I2C1, ENABLE);
                sEETimeout = sEE_LONG_TIMEOUT;
                while (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
                {
                    if ((sEETimeout--) == 0)
										{
                        sEE_TIMEOUT_UserCallback();
											  return;
										}
                }
                check_begin = TRUE;
                I2C_GenerateStart(I2C1, ENABLE);
            }
            else
            {
                I2C_SendData(I2C1, SendBuf[BufCount++]);
                Int_NumByteToWrite--;
            }
        }
        break;
    }
}

/**
*\*\name    I2C1_ER_IRQHandler.
*\*\fun     I2c1 error interrupt Service Routines.
*\*\param   none
*\*\return  none 
**/
void I2C1_ER_IRQHandler(void)
{
    if (I2C_GetFlag(I2C1, I2C_FLAG_ACKFAIL))
    {
        if (check_begin) /// EEPROM write busy
        {
            I2C_GenerateStart(I2C1, ENABLE);
        }
        else if (I2C1->STS2 & 0x01) /// real fail
        {
            I2C_GenerateStop(I2C1, ENABLE);
            i2c_comm_state = COMM_EXIT;
        }
        I2C_ClrFlag(I2C1, I2C_FLAG_ACKFAIL);
    }

    if (I2C_GetFlag(I2C1, I2C_FLAG_BUSERR))
    {
        if (I2C1->STS2 & 0x01)
        {
            I2C_GenerateStop(I2C1, ENABLE);
            i2c_comm_state = COMM_EXIT;
        }
        I2C_ClrFlag(I2C1, I2C_FLAG_BUSERR);
    }
}

/**
*\*\name    I2C_EE_WaitEepromStandbyState.
*\*\fun     Wait eeprom standby state.
*\*\param   none
*\*\return  none 
**/
void I2C_EE_WaitEepromStandbyState(void)
{
    __IO uint16_t tmpSR1    = 0;
    __IO uint32_t sEETrials = 0;

    /** While the bus is busy */
    sEETimeout = sEE_LONG_TIMEOUT;
    while (I2C_GetFlag(I2Cx, I2C_FLAG_BUSY))
    {
        if ((sEETimeout--) == 0)
				{
            sEE_TIMEOUT_UserCallback();
					  return;
				}
    }

    /** Keep looping till the slave acknowledge his address or maximum number
       of trials is reached (this number is defined by sEE_MAX_TRIALS_NUMBER) */
    while (1)
    {
        /** Send START condition */
        I2C_GenerateStart(I2Cx, ENABLE);

        /** Test on EV5 and clear it */
        sEETimeout = sEE_LONG_TIMEOUT;
        while (!I2C_CheckEvent(I2Cx, I2C_EVT_MASTER_MODE_FLAG))
        {
            if ((sEETimeout--) == 0)
						{
                sEE_TIMEOUT_UserCallback();
							  return;
						}
        }

        /** Send EEPROM address for write */
        I2C_SendAddr7bit(I2Cx, EEPROM_ADDRESS, I2C_DIRECTION_SEND);
        /** Wait for ADDR flag to be set (Slave acknowledged his address) */
        sEETimeout = sEE_LONG_TIMEOUT;
        do
        {
            /** Get the current value of the STS1 register */
            tmpSR1 = I2Cx->STS1;

            /** Update the timeout value and exit if it reach 0 */
            if ((sEETimeout--) == 0)
						{
                sEE_TIMEOUT_UserCallback();
							  return;
						}
        }
        /** Keep looping till the Address is acknowledged or the AF flag is
           set (address not acknowledged at time) */
        while ((tmpSR1 & (I2C_STS1_ADDRF | I2C_STS1_ACKFAIL)) == 0);

        /** Check if the ADDR flag has been set */
        if (tmpSR1 & I2C_STS1_ADDRF)
        {
            /** Clear ADDR Flag by reading STS1 then STS2 registers (STS1 have already
               been read) */
            (void)I2Cx->STS2;

            /** STOP condition */
            I2C_GenerateStop(I2Cx, ENABLE);

            /** Exit the function */
            return;
        }
        else
        {
            /** Clear AF flag */
            I2C_ClrFlag(I2Cx, I2C_FLAG_ACKFAIL);
        }

        /** Check if the maximum allowed numbe of trials has bee reached */
        if (sEETrials++ == sEE_MAX_TRIALS_NUMBER)
        {
            /** If the maximum number of trials has been reached, exit the function */
            sEE_TIMEOUT_UserCallback();
					  return;
        }
    }
}



