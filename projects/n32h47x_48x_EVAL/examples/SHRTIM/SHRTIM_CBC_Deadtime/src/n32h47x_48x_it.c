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
*\*\file n32h47x_48x_it.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "n32h47x_48x_it.h"

/**
*\*\name    NMI_Handler.
*\*\fun     This function handles NMI exception.
*\*\return  none
**/
void NMI_Handler(void)
{
}

/**
*\*\name    HardFault_Handler.
*\*\fun     This function handles Hard Fault exception.
*\*\return  none
**/
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
*\*\name    MemManage_Handler.
*\*\fun     This function handles Memory Manage exception.
*\*\return  none
**/
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
*\*\name    BusFault_Handler.
*\*\fun     This function handles Bus Fault exception.
*\*\return  none
**/
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
*\*\name    UsageFault_Handler.
*\*\fun     This function handles Usage Fault exception.
*\*\return  none
**/
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
*\*\name    SVC_Handler.
*\*\fun     This function handles SVCall exception.
*\*\return  none
**/
void SVC_Handler(void)
{
}

/**
*\*\name    DebugMon_Handler.
*\*\fun     This function handles Debug Monitor exception.
*\*\return  none
**/
void DebugMon_Handler(void)
{
}

/**
*\*\name    PendSV_Handler.
*\*\fun     This function handles Pendable request for system service.
*\*\return  none
**/

void PendSV_Handler(void)
{
}

/**
*\*\name    SysTick_Handler.
*\*\fun     This function handles SysTick Handler.
*\*\return  none
**/
void SysTick_Handler(void)
{
}

/**
*\*\name    SHRT1_TIMD_IRQHandler.
*\*\fun     This function handles SHRTIM1 TIMD Handler.
*\*\return  none
**/
void SHRT1_TIMD_IRQHandler(void)
{
    uint32_t __IO CurrentDuty;

    SHRTIM_ClearFlag_REP(SHRTIM1, SHRTIM_TIMER_D);

    CurrentDuty = SHRTIM_TIM_GetCompare3(SHRTIM1, SHRTIM_TIMER_D);
    if (CurrentDuty < 0x9000)
    {
        CurrentDuty++;
        SHRTIM_TIM_SetCompare3(SHRTIM1, SHRTIM_TIMER_D, CurrentDuty);
    }
    else
    {
        SHRTIM_TIM_SetCompare3(SHRTIM1, SHRTIM_TIMER_D, 0x0220);
    }
}
