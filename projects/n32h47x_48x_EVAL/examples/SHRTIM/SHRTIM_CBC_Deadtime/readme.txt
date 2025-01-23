1、功能说明
    此示例展示了如何实现带死区时间互补的Cycle by cycle(CBC)电流控制。

2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                 IAR EWARM 8.50.1
    硬件环境：N32H474VEL7-STB V1.0    

3、使用说明
    系统配置：
        1、 时钟源：
            HSE=8M,PLL=200M,AHB=200M, 
            SHRTIM clock(SHRTPLL) = 250M，High-resolution clock = 8GHz。

    使用方法： 
        在TD1和TD2输出上（PB14和PB15）生成两个互补的PWM波形。
        过流条件将关闭两个互补输入，过流条件不满足时则自动恢复两个互补输出。
        过电流数字信号必须连接到PB8和PB9输入的EXEV5和EXEV8外部事件线。
        PWM频率和死区时间持续时间可以分别以kHz和ns为单位输入，使用以下用户常量：
            - TIMER_PWM_FREQ
            - DEADTIME_IN_NS
    测试方法：
        开启ENTRY_TEST宏，程序执行测试函数。
        TA1（PA8）产生过流信号，TA1连接到EXEV5和EXEV8（PB8和PB9）。
        默认是电平CBC，过流信号高电平时关闭两个互补输出，过流信号低电平时恢复
        两个互补输出。
        若要测试边沿CBC，即上下沿时关闭两个互补输出，其他时间恢复两个互补输出，
        则可以通过在调试界面将SHRTIM_EXEVCTRL1寄存器的EXEV5SRC位段改成0b'001,
        即EXEV5的源由GPIO切到模拟比较器输出，也就是断开接入EXEV5的源。
        因为EXEV5是电平有效，所以断开后是EXEV8起作用，EXEV8是边沿有效，
        那么就能实现边沿CBC。
        用户也可以断开TA1和EXEV5的硬件连接来实现边沿CBC。

4、注意事项
    无
    
    
1. Function description
    This example describes outputting a PWM waveform via SHRTIM

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Hardware environment: N32H474VEL7-STB V1.0  

3. Instructions for use
    System Configuration:
        1. clock source
            HSE=8M,PLL=200M,AHB=200M, 
            SHRTIM clock(SHRTPLL) = 250M，High-resolution clock = 8GHz。
    Instructions:
        An over-current condition will turn-off the two complementary outputs, without re-arming the complementary output.
        Two complementary PWM waveforms are generated on the TD1 and TD2 outputs (PB14 and PB15).
        The over-current digital signal must be connected to both EEV5 and EEV8 external event lines on PB8 and PB9 inputs.
    Test method:
        Enabling the ENTRY_TEST macro triggers the execution of the test function in the program. 
        TA1 (PA8) generates an over-current signal and is connected to EXEV5 and EXEV8 (PB8 and PB9). 
        By default, this is set to level-controlled CBC, where a high level over-current signal turns off both complementary outputs, and a low level over-current signal restores them. 
        To test edge-controlled CBC, which involves turning off both complementary outputs at both rising and falling edges and restoring them at all other times, one can switch the source of EXEV5 from GPIO to the output of an analog comparator by changing the EXEV5SRC bit field of the SHRTIM_EXEVCTRL1 register to 0b'001. This effectively disconnects the source connected to EXEV5. Because EXEV5 operates on a level-sensitive basis, disconnecting it allows EXEV8 to take over, which operates on an edge-sensitive basis. This enables edge-controlled CBC. Alternatively, users can disconnect the hardware connection between TA1 and EXEV5 to achieve edge-controlled CBC.
        
4. Matters needing attention
     None