1. 功能说明
    USB Audio 设备

2. 使用环境

    软件开发环境：KEIL MDK-ARM V5.34
                  IAR EWARM 8.50.1
      
    硬件开发环境：
        N32H482系列：
        基于评估板N32H482ZEL7_STB V1.0开发
        N32H487系列：
        基于评估板N32H487ZEL7_STB V1.1开发


3. 使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：HSE_PLL 240MHz
         2. I2SClock:    SHRTPLL 245.76MHz(I2S 音频频率48KHz)
         3. WM8978: I2C SCL -- PB6
                        SDL -- PB7
                    I2S CK  -- PC7
                    I2S WS  -- PC6
                    I2S SD  -- PC2
                    I2S MCK -- PA8

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J62 USB 口，电脑识别出Audio设备，用耳机接入J21口
         3. 电脑播放音乐，耳机可以听到声音

4. 注意事项
    可通过修改宏定义 USE_USB_HS_IN_FS 或 USE_USB_HS_IN_HS 切换设备为全速模式或者高速模式；
    使用高速模式时，需要使用16MHz外部晶体。

1. Function description
    USB Audio device

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
        1. SystemClock：HSE_PLL 240MHz
        2. I2SClock: SHRTPLL 245.76MHz(for I2S audio clock 48KHz)
        3. WM8978: I2C SCL -- PB6
                       SDL -- PB7
                   I2S CK  -- PC7
                   I2S WS  -- PC6
                   I2S SD  -- PC2
                   I2S MCK -- PA8
    
    Describe the testing steps and phenomena of the Demo

        1. Download the program after compiling and reset it to run;
        2. Connect the J62 USB port via a USB cable, and the computer recognizes the Audio device, and connects to the J21 port with the headphone; 
        3. The computer plays music, and the headphones can hear the sound

4. Matters needing attention
    The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
    When using the High-Speed mode, a 16MHz external cycstal is required.