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
*\*\file usb_user.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "usbd_user.h"


USBD_User_cb_TypeDef USER_cb = {
  USBD_USER_Init,
  USBD_USER_DeviceReset,
  USBD_USER_DeviceConfigured,
  USBD_USER_DeviceSuspended,
  USBD_USER_DeviceResumed,

  USBD_USER_DeviceConnected,
  USBD_USER_DeviceDisconnected,
};

#define USER_INFORMATION1      (uint8_t*)"[Key]:switch On/Off Button[ReportID 5] "
#define USER_INFORMATION2      (uint8_t*)"[Leds]:switch on/off Leds [ReportID 1:4]"
#define USER_INFORMATION3      (uint8_t*)"[Potentiometer]:[ReportID 7]"

/**
*\*\name   USBD_USER_Init.
*\*\fun    host lib initialization.
*\*\param  none.
*\*\param  none.
*\*\return none.
*/
void USBD_USER_Init(void)
{
    /* Setup SysTick Timer for 20 msec interrupts This interrupt is used to probe the joystick */
    SysTick_Config(SystemCoreClock / 50u);  /* 20ms */
}

/**
*\*\name   USBD_USER_DeviceReset.
*\*\fun    device Reset Event.
*\*\param  speed : device speed.
*\*\param  none.
*\*\return none.
*/
void USBD_USER_DeviceReset(uint8_t speed)
{
    switch (speed)
    {
        case USB_SPEED_HIGH:
        break;

        case USB_SPEED_FULL:
        break;
        default:
        break;
    }
}

/**
*\*\name   USBD_USER_DeviceConfigured.
*\*\fun    device configuration Event.
*\*\param  none.
*\*\param  none.
*\*\return none.
*/
void USBD_USER_DeviceConfigured(void)
{

}

/**
*\*\name   USBD_USER_DeviceConnected.
*\*\fun    device connection Event.
*\*\param  none.
*\*\param  none.
*\*\return none.
*/
void USBD_USER_DeviceConnected(void)
{
}

/**
*\*\name   USBD_USER_DeviceDisconnected.
*\*\fun    device disconnection Event.
*\*\param  none.
*\*\param  none.
*\*\return none.
*/
void USBD_USER_DeviceDisconnected(void)
{
}

/**
*\*\name   USBD_USER_DeviceSuspended.
*\*\fun    device suspend Event.
*\*\param  none.
*\*\param  none.
*\*\return none.
*/
void USBD_USER_DeviceSuspended(void)
{
  /* Users can do their application actions here for the USB-Reset */
}

/**
*\*\name   USBD_USER_DeviceResumed.
*\*\fun    device resume Event.
*\*\param  none.
*\*\param  none.
*\*\return none.
*/
void USBD_USER_DeviceResumed(void)
{
  /* Users can do their application actions here for the USB-Reset */
}
