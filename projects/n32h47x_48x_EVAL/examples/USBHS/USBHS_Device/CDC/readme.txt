1. 功能说明
    USB CDC 设备

2. 使用环境

    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        N32H482系列：
        基于评估板N32H482ZEL7_STB V1.0开发
        N32H487系列：
        基于评估板N32H487ZEL7_STB V1.1开发


3. 使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：240MHz
         2. 串口：USART1 TX -- PA9  RX -- PA10 波特率：115200

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J62 USB 口，电脑识别出虚拟串口设备
         3. 将 USART1 接到串口工具上，然后在PC上打开 USB 虚拟串口，USB 虚拟串口发送数据，
            用串口工具接收数据，然后用串口工具发送数据， USB 虚拟串口接收数据


4. 注意事项
    可通过修改宏定义 USE_USB_HS_IN_FS 或 USE_USB_HS_IN_HS 切换设备为全速模式或者高速模式；
    使用高速模式时，需要使用16MHz外部晶体。

1. Function description
    USB CDC device

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        N32H482 series:
        Developed based on the evaluation board N32H482ZEL7_STB V1.0
        N32H487 series:
        Developed based on the evaluation board N32H487ZEL7_STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 240MHz
        2. Serial port: USART1 TX -- PA9 RX -- PA10 Baud rate: 115200

    Describe the testing steps and phenomena of the Demo
    1. After compiling, the downloaded program is reset and run;
    2. Connect a USB cable to the J62 USB port. The computer identifies the virtual serial port device
    3. Connect USART1 to the serial port tool, then open the USB virtual serial port on the PC, and send data through the USB virtual serial port.
       Use the serial port tool to receive data, and then use the serial port tool to send data, USB virtual serial port to receive data
        
4. Matters needing attention
    The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
    When using the High-Speed mode, a 16MHz external cycstal is required.