1、功能说明
    此示例展示了如何配置SHRTIM来控制一个多相降压转换器。它在A、B、C和D定时器单元上处理5个相位，并输出TA2、TB1、TC2、TD1、TD2。

2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                 IAR EWARM 8.50.1
    硬件环境：N32H474VEL7-STB V1.0    

3、使用说明
    系统配置：
        1、 时钟源：
            HSE=8M,PLL=200M,AHB=200M, 
            SHRTIM clock(SHRTPLL) = 250M，High-resolution clock = 8GHz。
            ADC sampling clock = 200MHz/3 = 66.7MHz。
    使用方法： 
        在PA12（高电平激活）上启用FAULT1输入，以演示PWM关闭，适用于所有输出。当故障被触发（PA12输入高电平）时，TA2、TB1、TC2、TD1、TD2（分别对应PA9、PA10、PB13、PB14和PB15）信号将被关闭。
        系统可以通过按下用户按钮重新启动。
        ADC配置为在每个5相位的转换器开启时间的中间触发转换，在PA0输入上。
        对于此示例（通常是5个输入上的5次转换序列，演示以5相模式开始。
        如果按下按钮，演示模式将改变，以便扫描所有相位削减选项：从5相到1相，最后是突发模式。
        每一相都有不同的LED指示，可参考代码。
4、注意事项
    无
    
    
1. Function description
    This example shows how to configure the SHRTIM to control a multiphase buck converter. It handles here 5-phases on timer unit A, B C and D and outputs TA2, TB1, TC2, TD1, TD2.

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Hardware environment: N32H474VEL7-STB V1.0  

3. Instructions for use
    System Configuration:
        1. clock source
            HSE=8M,PLL=200M,AHB=200M, 
            SHRTIM clock(SHRTPLL) = 250M，High-resolution clock = 8GHz。
            ADC sampling clock = 200MHz/3 = 66.7MHz。
    Instructions:
        The FAULT1 input is enabled on PA12 (active high) to demonstrate PWM shut down, for all outputs.
        When the fault is triggered (PA12 input high lever), TA2, TB1, TC2, TD1, TD2 (resp. PA9, PA10, PB13, PB14 and PB15) signals are shut-down. The system can be re-armed by pressing the user button.
        The ADC is configured to have conversions triggered in the middle of the converter ON time of each of 5 phases, on PA0 input.
        For this example(usually a sequence of 5 conversion on 5 inputs), the demo starts in 5-phase mode.
        If the push-button is pressed, the demo mode changes so that all phase shedding options are scanned: from 5 to 1-phase, and finally burst mode.
        
4. Matters needing attention
     None