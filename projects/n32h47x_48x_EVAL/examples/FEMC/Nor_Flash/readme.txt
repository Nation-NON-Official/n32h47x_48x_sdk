﻿1、功能说明
    1、读写擦Nor Flash S29GL01GS11TFI020

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34
	              IAR EWARM 8.50.1

    硬件开发环境：
        N32H473系列：
        基于评估板N32H473VEL7_STB V1.0开发
        N32H474系列：
        基于评估板N32H474VEL7_STB V1.0开发
        N32H482系列：
        基于评估板N32H482ZEL7_STB V1.0开发
        N32H487系列：
        基于评估板N32H487ZEL7_STB V1.1开发

3、使用说明
    
    系统配置:
        1、FEMC时钟源：AHB
        2、串口配置：
                    - 串口为USART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 
                    
        3、GPIO配置：
                D0:PD14     D1:PD15     D2:PD0      D3:PD1
                D4:PE7      D5:PE8      D6:PE9      D7:PE10
                D8:PE11     D9:PE12     D10:PE13    D11:PE14
                D12:PE15    D13:PD8     D14:PD9     D15:PD10
                
                A0:PF0      A1:PF1      A2:PF2      A3:PF3
                A4:PF4      A5:PF5      A6:PF12     A7:PF13
                A8:PF14     A9:PF15     A10:PG0     A11:PG1
                A12:PG2     A13:PG3     A14:PG4     A15:PG5
                A16:PD11    A17:PD12    A18:PD13    A19:PE3
                A20:PE4     A21:PE5     A22:PE6     A23:PE2
                A24:PF8     A25:PF9
                
                NOE:PD4     NWE:PD5     NE:PB9      NWAIT:PD6
                
    使用方法：
        编译后烧录到评估板，上电，串口打印Nor Flash 读写擦结果

4、注意事项
    开发板上没有NorFlash，需要外接
    

1. Function description
    Read, write and erase NOR Flash S29GL01GS11TFI020

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1	

    Hardware development environment:
        N32H473 series:
        Developed based on the evaluation board N32H473VEL7_STB V1.0
        N32H474 series:
        Developed based on the evaluation board N32H474VEL7_STB V1.0
        N32H482 series:
        Developed based on the evaluation board N32H482ZEL7_STB V1.0
        N32H487 series:
        Developed based on the evaluation board N32H487ZEL7_STB V1.1

3. Instructions for use

    System configuration:
        1. FEMC clock source: AHB
        2. Serial port configuration:

                            - Serial port: USART1 (TX: PA9 RX: PA10) :
                            - Data bit: 8
                            - Stop bit: 1
                            - Parity check: None
                            - Baud rate: 115200
        3. GPIO configuration：
                D0:PD14     D1:PD15     D2:PD0      D3:PD1
                D4:PE7      D5:PE8      D6:PE9      D7:PE10
                D8:PE11     D9:PE12     D10:PE13    D11:PE14
                D12:PE15    D13:PD8     D14:PD9     D15:PD10
                
                A0:PF0      A1:PF1      A2:PF2      A3:PF3
                A4:PF4      A5:PF5      A6:PF12     A7:PF13
                A8:PF14     A9:PF15     A10:PG0     A11:PG1
                A12:PG2     A13:PG3     A14:PG4     A15:PG5
                A16:PD11    A17:PD12    A18:PD13    A19:PE3
                A20:PE4     A21:PE5     A22:PE6     A23:PE2
                A24:PF8     A25:PF9
                
                NOE:PD4     NWE:PD5     NE:PB9      NWAIT:PD6

    Instructions:
        After compiling, burn it to the evaluation board, power it on, and print the Nor Flash read-write-erase results through the serial port

4. Matters needing attention
    There is no NorFlash on the development board, it needs to be connected externally

