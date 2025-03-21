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
 * @file usbfsd_prop.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBFSD_PROP_H__
#define __USBFSD_PROP_H__

#include "stdint.h"
#include "usbfsd_core.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define Speaker_GetConfiguration          USB_ProcessNop
//#define Speaker_SetConfiguration          USB_ProcessNop
#define Speaker_GetInterface              USB_ProcessNop
#define Speaker_SetInterface              USB_ProcessNop
#define Speaker_GetStatus                 USB_ProcessNop
#define Speaker_ClearFeature              USB_ProcessNop
#define Speaker_SetEndPointFeature        USB_ProcessNop
#define Speaker_SetDeviceFeature          USB_ProcessNop
//#define Speaker_SetDeviceAddress          USB_ProcessNop


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Speaker_init(void);
void Speaker_Reset(void);
void Speaker_SetConfiguration(void);
void Speaker_SetDeviceAddress (void);
void Speaker_Status_In (void);
void Speaker_Status_Out (void);
USB_Result Speaker_Data_Setup(uint8_t);
USB_Result Speaker_NoData_Setup(uint8_t);
USB_Result Speaker_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Speaker_GetDeviceDescriptor(uint16_t);
uint8_t *Speaker_GetConfigDescriptor(uint16_t);
uint8_t *Speaker_GetStringDescriptor(uint16_t);
uint8_t *Mute_Command(uint16_t Length);

#define GET_CUR                           0x81
#define SET_CUR                           0x01


#endif /* __USBFSD_PROP_H__ */

