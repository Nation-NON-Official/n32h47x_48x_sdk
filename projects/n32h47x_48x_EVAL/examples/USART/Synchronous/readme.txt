1、功能说明

    该测例演示了USARTy（同步模式）与SPIy间通过查询检测标识实现的基础通信。
    首先，通过TXC检测标志，USARTy发送TxBuffer1数据至SPIy，而SPIy接收数据，
则查询RNE检测标志，接收的数据存至RxBuffer1。
    随后，SPIy通过查询TE检测标志，发送TxBuffer2数据至USARTy。USARTy则利用
RXDNE检测标志接收数据，将其存入RxBuffer2。
    最后，分别比较两组收、发数据，比较结果存入TransferStatus1变量
和TransferStatus2变量。


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

3、使用说明

    系统时钟配置：
        N32H475/N32H482/N32H487:
            SystemClock：240MHz
        N32H474/N32H473:
            SystemClock：200MHz
    
    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - 时钟使能
    - 时钟极性：不对外发送时保持低电平
    - 时钟相位：在第二个时钟边沿采样第一个数据
    - 最后一位时钟脉冲：最后一位数据的时钟脉冲从CK输出
    
    SPI配置如下：
    - 方向 = “双线双向”模式
    - 模式 = 从模式
    - 数据大小 = 8位数据帧
    - CPOL = 空闲状态时，时钟保持低电平
    - CPHA = 数据采样从第二个时钟边沿开始
    - NSS = 启用软件从设备管理
    - 第1位 = 第1位为LSB
    
    
    USART引脚连接如下：    
    - USART1_Tx.PA9 <-------> SPI1_MOSI.PA7
    - USART1_Rx.PA10 <-------> SPI1_MISO.PA6
    - USART1_Clk.PA8 <-------> SPI1_SCK.PA5
    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 将串口打印跳帽拔除
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常


4、注意事项

    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开


1. Function description

    This test example demonstrates basic communication between USARTy (synchronous mode) and SPIy by querying the detection flag.
    USARTy and SPIy can be USART1 and SPI1, USART3 and SPI1, or USART2 and SPI2.
    First, through the TXC detection flag, USARTy sends TxBuffer1 data to SPIy, and SPIy receives data,then query the RNE detection flag, 
    and store the received data in RxBuffer1.Then, SPIy sends TxBuffer2 data to USARTy by querying the TE detection flag. USARTy uses
    the RXDNE detection flag receives data and stores it in RxBuffer2.
    Finally, compare the two groups of receiving and sending data respectively, and store the comparison results in the TransferStatus1 variable
    and the TransferStatus2 variable.

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
        

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
    System Clock Configuration:
        N32H475/N32H482/N32H487:
            SystemClock：240MHz
        N32H474/N32H473:
            SystemClock：200MHz
    
    USART is configured as follows:
    - Baud rate = 115200 baud
    - Word length = 8 data bits
    - 1 stop bit
    - checksum control disabled
    - Hardware flow control disabled (RTS and CTS signals)
    - Receiver and transmitter enable
    - Clock enable
    - Clock polarity: keep low when not sending out
    - Clock Phase: The first data is sampled on the second clock edge
    - Last bit clock pulse: The clock pulse of the last bit of data is output from CK
    
    The SPI configuration is as follows:
    - Direction = "Two-Line Bidirectional" mode
    - mode = slave mode
    - data size = 8-bit data frame
    - CPOL = when idle, the clock remains low
    - CPHA = data sampling starts on second clock edge
    - NSS = Enable Software Slave Device Management
    - 1st bit = 1st bit is LSB
    
    
    The USART pins are connected as follows:
    - USART1_Tx.PA9 <-------> SPI1_MOSI.PA7
    - USART1_Rx.PA10 <-------> SPI1_MISO.PA6
    - USART1_Clk.PA8 <-------> SPI1_SCK.PA5
    
    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Remove the serial print jump cap
    - Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, where,
      PASSED is the test passed, FAILED is the test abnormal


4. Attention
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first