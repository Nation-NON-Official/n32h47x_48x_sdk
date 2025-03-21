1、功能说明

    该测例演示了USARTy与USARTz间实现串行IrDA低功耗模式红外解码功能的基础通信。
    首先，USARTy发送TxBuffer1数据至USARTz，USARTz通过中断接收数据存至RxBuffer1。
    随后，比较接收数据与发送数据，比较结果存入TransferStatus变量。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    
    硬件开发环境：    
        N32H473系列：
        基于评估板N32H473VEL7_STB V1.0开发
        N32H474系列：
        基于评估板N32H474VEL7_STB V1.0开发
        N32H475系列：
        基于评估板N32H475UEQ7_STB V1.0开发
        N32H482系列：
        基于评估板N32H482ZEL7_STB V1.0开发
        N32H487系列：
        基于评估板N32H487ZEL7_EVB V1.0开发

    IrDA发送器及接收器


3、使用说明

    系统时钟配置如下：
    - 时钟源 = HSE
    - 系统时钟 = 60MHz
    
    USART配置如下：
    - 波特率 = 1200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - IrDA模式使能
    
    USART引脚连接如下：
    N32H475/N32H474/N32H473/N32H482:
    - USART3_Tx.PA9    <------->   IrDA Transmitter
    - UART5_Rx.PA3    <------->   IrDA Receiver   
    - GPIO.PD2         <------->   38kHz carrier
    
    N32H487:
    - USART3_Tx.PG6    <------->   IrDA Transmitter
    - UART5_Rx.PH3    <------->   IrDA Receiver   
    - GPIO.PA8         <------->   38kHz carrier

    
    测试步骤与现象：
    - 复位运行MCU，查看变量TransferStatus，其中，PASSED为测试通过，FAILED为测试异常


4、注意事项

1. Function description

    This test example demonstrates the basic communication between USARTy and USARTz to realize the infrared 
    decoding function of serial IrDA low power consumption mode.
    First, USARTy sends TxBuffer1 data to USARTz, and USARTz receives data through interrupt and stores it in RxBuffer1.
    Subsequently, compare the received data with the sent data, and the result of the comparison is stored in the 
    TransferStatus variable.


2. Use environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
        N32H473 series:
        Developed based on the evaluation board N32H473VEL7_STB V1.0
        N32H474 series:
        Developed based on the evaluation board N32H474VEL7_STB V1.0
        N32H475 series:
        Developed based on the evaluation board N32H475UEQ7_STB V1.0
        N32H482 series:
        Developed based on the evaluation board N32H482ZEL7_STB V1.0
        N32H487 series:
        Developed based on the evaluation board N32H487ZEL7_EVB V1.0
    IrDA transmitter and receiver


3. Instructions for use

    The system clock configuration is as follows:
    -Clock source = HSE
    -System clock = 60MHz
    
    The USART configuration is as follows:
    -Baud rate = 1200 baud
    -Word length = 8 data bits
    -1 stop bit
    -Verification control disabled
    -Hardware flow control disabled (RTS and CTS signals)
    -Receiver and transmitter enable
    -IrDA mode enable
    
    The USART pin connections are as follows:
    - USART3_Tx.PA9    <------->   IrDA Transmitter
    - UART5_Rx.PA3    <------->   IrDA Receiver
    
    - GPIO.PD2         <------->   38kHz carrier

    
    Test steps and phenomena:
-Reset and run the MCU, check the variable TransferStatus, where PASSED means the test passed and FAILED means the test is abnormal


4. Matters needing attention