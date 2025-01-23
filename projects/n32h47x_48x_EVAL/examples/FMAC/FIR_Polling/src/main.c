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

#define fir_coeffb_size          21
#define fir_d0                   107
#define fir_d1                   108
#define fir_gain                 0
#define input_array_size         100

/*
Array of filter (FIR) coefficients B (feed-forward taps) in Q1.15 format
FIR filter order is 20 order, the output data is multiply by 32767
the sampling frequency is 16KHz and the cut-off frequency is 800Hz
*/
static int16_t fir_coeffb[fir_coeffb_size] = 
{
    0, 43, 152, 385, 779, 1334, 2004, 2700, 3312, 3732,
    3882, 3732, 3312, 2700, 2004, 1334, 779, 385, 152, 43,
    0
};
/*
Array of input values in -32767~32768
the data is calculated by using 'x[i]=25000*(sin(2*pi*500/16000*i)+0.2*sin(2*pi*5*500/16000*i));' i goes from 1 to 100
The useful signal frequency is 500Hz, and the noise signal frequency is 2500Hz
*/
static int16_t input_data[input_array_size] = 
{
    9035, 14186, 14865, 14142, 15883, 21184, 27297, 30000, 27297, 21184,
    15883, 14142, 14865, 14186, 9035, 0, -9035, -14186, -14865, -14142,
    -15883, -21184, -27297, -30000, -27297, -21184, -15883, -14142, -14865, -14186,
    -9035, 0, 9035, 14186, 14865, 14142, 15883, 21184, 27297, 30000,
    27297, 21184, 15883, 14142, 14865, 14186, 9035, 0, -9035, -14186,
    -14865, -14142, -15883, -21184, -27297, -30000, -27297, -21184, -15883, -14142,
    -14865, -14186, -9035, 0, 9035, 14186, 14865, 14142, 15883, 21184,
    27297, 30000, 27297, 21184, 15883, 14142, 14865, 14186, 9035, 0,
    -9035, -14186, -14865, -14142, -15883, -21184, -27297, -30000, -27297, -21184,
    -15883, -14142, -14865, -14186, -9035, 0, 9035, 14186, 14865, 14142,
};
/* Array of calculated filtered data by computer */
int16_t reference_data[input_array_size - fir_coeffb_size + 1] = 
{
    17055, 14502, 11381, 7827, 3984, 0, -3984, -7827, -11381, -14502,
    -17055, -18938, -20089, -20475, -20089, -18938, -17055, -14502, -11381, -7827,
    -3984, 0, 3984, 7827, 11381, 14502, 17055, 18938, 20089, 20475,
    20089, 18938, 17055, 14502, 11381, 7827, 3984, 0, -3984, -7827,
    -11381, -14502, -17055, -18938, -20089, -20475, -20089, -18938, -17055, -14502,
    -11381, -7827, -3984, 0, 3984, 7827, 11381, 14502, 17055, 18938,
    20089, 20475, 20089, 18938, 17055, 14502, 11381, 7827, 3984, 0,
    -3984, -7827, -11381, -14502, -17055, -18938, -20089, -20475, -20089, -18938,
};
/* Array of calculated filtered data by MCU */
int16_t calculated_data[input_array_size - fir_coeffb_size + 1] = {0};
/* error between reference_data and calculated_data */
volatile int16_t error[input_array_size - fir_coeffb_size + 1];

void FAMC_Init(void);

/**
*\*\name main.
*\*\fun Main program.
*\*\return none
**/
int main(void)
{
    uint16_t i;
    /* FAMC_Init all configured peripherals */
    FAMC_Init();
    
        /* get calculation result */
    for(i = 0; i < input_array_size - fir_coeffb_size + 1; i++) 
    {
        while(FMAC_GetFlagStatus(FMAC_FLAG_YBUFEF) != RESET);
        
        calculated_data[i] = FMAC_ReadData();
        error[i] = calculated_data[i] - reference_data[i];
    }
    /* finish calculation */
    FMAC_FinishCalculate();

    while(1) 
    {
    }
}

/**
*\*\name    FAMC_Init.
*\*\fun     FMAC Initialization.
*\*\param   none
*\*\return  none
**/
void FAMC_Init(void)
{
    FMAC_InitType FMAC_InitStruct;
    FMAC_PreLoadType  FMAC_PreLoadStruct;
    /* reset the FMAC */
    FMAC_DeInit();
    
    RCC_EnableAHBPeriphClk( RCC_AHB_PERIPHEN_FMAC, ENABLE);
    /* initialize the FMAC filter parameter struct */
    FMAC_StructInit(&FMAC_InitStruct);
    FMAC_PreLoadStructInit(&FMAC_PreLoadStruct);

    /* Configure Coefficient buffer,X2 buffer */
    FMAC_InitStruct.CoeffBufBaseAddress = 0;
    FMAC_InitStruct.CoeffBufSize        = fir_coeffb_size;

    /* Configure input buffer, X1 buffer */
    FMAC_InitStruct.InputBufBaseAddress = fir_coeffb_size;
    FMAC_InitStruct.InputBufSize        = fir_coeffb_size + fir_d0;;
    FMAC_InitStruct.InputBufThreshold   = FMAC_THRESHOLD1;

    /* Configure input buffer, Y buffer */
    FMAC_InitStruct.OutBufBaseAddress   = fir_coeffb_size + fir_coeffb_size + fir_d0;
    FMAC_InitStruct.OutBufSize          = fir_d1;
    FMAC_InitStruct.OutBufThreshold     = FMAC_THRESHOLD1;
    FMAC_InitStruct.Limit               = FMAC_LIMIT_DISABLE;
    FMAC_Init(&FMAC_InitStruct);

    FMAC_PreLoadStruct.pCoeffA          = NULL;
    FMAC_PreLoadStruct.CoeffASize       = 0;

    FMAC_PreLoadStruct.pCoeffB          = fir_coeffb;
    FMAC_PreLoadStruct.CoeffBSize       = fir_coeffb_size;
    FMAC_PreLoadStruct.pInputData       = input_data;
    FMAC_PreLoadStruct.InputDataSize    = input_array_size;
    FMAC_PreLoadStruct.pOutputData      = NULL;
    FMAC_PreLoadStruct.OutputDataSize   = 0;
    FMAC_PreloadBufferData(&FMAC_PreLoadStruct);

    FMAC_InitStruct.Func    = FMAC_FUNC_CONVO_FIR;
    FMAC_InitStruct.P       = fir_coeffb_size;
    FMAC_InitStruct.Q       = 0;
    FMAC_InitStruct.R       = fir_gain;
    FMAC_ConfigParam(&FMAC_InitStruct);
    
    /* Enable FMAC */
    FMAC_Enable(ENABLE);

}
