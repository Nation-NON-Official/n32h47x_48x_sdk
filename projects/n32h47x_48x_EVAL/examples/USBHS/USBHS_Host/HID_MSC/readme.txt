1. 功能说明
    USB 主机 HID mouse & HID keyboard & MSC

2. 使用环境

    软件开发环境：KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    硬件开发环境：
        N32H482系列：
        基于评估板N32H482ZEL7_STB V1.0开发
        N32H487系列：
        基于评估板N32H487ZEL7_EVB V1.1开发


3. 使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
    1. SystemClock：240MHz
    2. GPIO: KEY2--PA15、VBUS驱动引脚-PE1
    3. 串口配置：
            - 串口为USART1（TX：PA9  RX：PA10）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无
            - 波特率： 115200 

    描述Demo的测试步骤和现象 
    1. 编译后下载程序复位运行；
    2. 打开串口调试助手，设置波特率为115200bps
    3. 连接OTG转接线，再接上鼠标或键盘或者U盘设备，等待枚举完成
    4. 枚举完成后，按下KEY2按键，开始鼠标或键盘或U盘数据通信 
    5. 串口调试助手界面打印相应鼠标坐标或键盘键值信息或U盘读写信息。

4. 注意事项
    无

1. Function description
    USB host HID mouse & HID keyboard & MSC

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
                                      IAR EWARM 8.50.1

    Hardware development environment:
        N32H482 series:
        Developed based on the evaluation board N32H482ZEL7_STB V1.0
        N32H487 series:
        Developed based on the evaluation board N32H487ZEL7_EVB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
    1. SystemClock: 240MHz
    2. GPIO: KEY2--PA15、VBUS driver pin(PE1)
    3. Serial port configuration:
            - Serial port: USART1 (TX: PA9 RX: PA10) :
            - Data bit: 8
            - Stop bit: 1
            - Parity check: None
            - Baud rate: 115200
    
    Describe the testing steps and phenomena of the Demo
    1. Compile the program and download it for reset and execution.
    2. Open the serial port debugging Assistant and set the baud rate to 115200bps.
    3. Connect the OTG adapter cable, then connect the mouse or keyboard or USB flash disk device, and wait for the enumeration to complete
    4. After the enumeration is complete, press KEY2 to start data communication with the mouse or keyboard or USB flash disk
    5. The interface of the serial debugging assistant displays the corresponding mouse coordinates or keyboard key values, or USB flash disk read and write information.    

4. Matters needing attention
    None