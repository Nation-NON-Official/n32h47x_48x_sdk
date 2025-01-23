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
#include "n32h47x_48x.h"
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_dvp.h"
#include "bsp_dvp.h"
#include "main.h"
#include "log.h"
#include "lcd.h"

extern uint16_t lcd_width;
extern uint16_t lcd_height;
extern uint16_t lcd_id;
extern const image_t pic_logo1;
extern const image_t pic_logo2;

static uint32_t DBG_SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
                                                               
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M4 System Interrupts */
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;
  return (0);                                                  /* Function successful */
}

void SysTick_Delay_Ms( __IO uint32_t ms)
{
    uint32_t i;	
    RCC_ClocksType RCC_Clocks;

    RCC_GetClocksFreqValue(&RCC_Clocks);

    DBG_SysTick_Config(RCC_Clocks.SysclkFreq / 1000);

    for(i=0;i<ms;i++)
    {
        while( !((SysTick->CTRL)&(1<<16)) );
    }
    SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_Us( __IO uint32_t us)
{
    uint32_t i;
    RCC_ClocksType RCC_Clocks;

    RCC_GetClocksFreqValue(&RCC_Clocks);
    DBG_SysTick_Config(RCC_Clocks.SysclkFreq / 1000000);

    for(i=0;i<us;i++)
    {
        while( !((SysTick->CTRL)&(1<<16)) );
    }
    SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

int main(void)
{
    log_init();
    /* LCD configuration */
    LCD_Configuration();
    LCD_GramScan(6);
    LCD_SetColors(RED,BLACK);
    LCD_Clear(0,0,lcd_width,lcd_height);  
    LCD_Logo_init();
    /* DVP configuration */    
    DVPDemo_Init();
    DVP_EnablePort(ENABLE);
        
    while (1)
    {

    }

}


void LCD_Logo_init(void)
{
    LCD_SetFont(&Font8x16);
    LCD_SetColors(RED,BLACK);
    LCD_Clear(0,0,lcd_width,lcd_height); 
    if(lcd_id==0x9341)
    {
        lcd_draw_image((lcd_width - pic_logo1.width) / 2, lcd_height / 4, &pic_logo1);
        lcd_draw_image((lcd_width - pic_logo2.width) / 2, lcd_height / 3 * 2, &pic_logo2);
    }
    else if(lcd_id==0x9806)
    {
        lcd_draw_image((lcd_width - pic_logo1.width) / 2, lcd_height / 8, &pic_logo1);
        lcd_draw_image((lcd_width - pic_logo2.width) / 2, lcd_height / 5 * 4, &pic_logo2);
    }
    else
    {
    }    
}
