1、功能说明
    此示例展示了如何配置SHRTIM来控制 transition mode PFC。

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
        通过TD1输出（PB14）完成的。TD1控制信号具有恒定的Ton时间和可变频率。
        为了完全演示该示例，需要模拟反馈信号：
            - 过电流信号（“OC”，在EXEV3/PB7上）
            - 零交叉检测信号（“ZCD”，在EXEV4/PB6上）
        OC是由TD1上升沿触发的单次短脉冲（通常为200ns）。它必须被延迟以缩短Ton（Ton < Ton max）==> 从TD1到OC上升沿的延迟OC周期应该小于Ton max。如果从TD1到OC上升沿的延迟小于Ton min，则忽略OC信号。

        ZCD信号是一个周期性信号，脉冲长度约为200 ns。必须改变周期以验证三个操作范围：
            1. 如果没有ZCD信号，转换器将以Ton + Toffmax的周期运行（转换器自由运行）
            2. 当其周期为：Ton + Toffmin < ZCD周期 < Tonmax + Toff max时，ZCD信号将作为外部同步（转换器被锁定）
            3. 当ZCD < Ton + Toff min时，TD1将失去与ZCD的同步，但TD1周期将保持 >= Ton + Toff min（转换器在其高频限制下操作）。
        在上述等式中，Ton min < Ton < Ton max
        
        在PA12（高电平有效）上启用了FAULT1输入，以演示PWM关闭（高电平敏感）。当故障触发时（PA12输入高电平），只有TD1信号停止。系统可以通过按下用户按钮重新启动。
        
        LED指示以下内容：
            LED1：在触发故障时闪烁
            LED2: 正常操作期间闪烁
    测试方法：
        开启ENTRY_TEST宏，程序执行测试函数。
        TA1（PA8）产生过流信号，TA1连接到EXEV3（PB7），TB1（PA10）产生ZCD信号，TB1连接到EXEV4（PB6）。示波器观察TD1、TA1、TB1的波形，
        1. 无OC和ZCD信号的测试
        断点打在TestEntry函数中的第一个OCBlankingZCDConfig处。示波器观察TD1高电平1.44us,周期5.76us。
        2. OC消隐和ZCD生效的测试
        断点打在TestEntry函数的第一个systick_delay_ms函数处。
        示波器观察消隐窗口内的OC信号被消隐，ZCD信号将TD1低电平缩短一点点，周期变成5.75us。
        3. OC过流测试
        断点打在TestEntry函数的第二个systick_delay_ms函数处。
        示波器观察消隐窗口外的OC信号将TD1高电平时间缩短
        4. ZCD latch测试
        断点打在TestEntry函数的第四个systick_delay_ms函数处。
        示波器观察消隐窗口内的ZCD信号被Lactch到消隐窗口外生效
4、注意事项
    无
    
    
1. Function description
     This example shows how to configure the SHRTIM to control a transition mode PFC.

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
        This is done with the TD1 output (PB14).
        The TD1 control signal has a constant Ton time and variable frequency.
  
        To exercice fully the demo, it is necessary to simulate the feedback signals:
            - Over-current signal ("OC", on EXEV3/PB7)
            - Zero-crossing detection signal ("ZCD", on EXEV4/PB6)
  
        OC is a single-shot short pulse ( typically 200ns ) triggered by TD1 rising edge. 
        It has to be delayed to shorten Ton (Ton< Ton max) ==> the delay from TD1 to OC rising edge OC period should be less than Ton max.
        If the delay from TD1 to OC rising edge is lower than Ton min, the OC signal is ignored.

        ZCD signal is a periodic signal with a pulse length ~ 200 ns.  The period must be varied to verify
        the 3 operating ranges:
            1. If ZCD signal is not present, the converter will run with a period equal to Ton + Toffmax (converter is free-running)
            2. The ZCD signal will serve as external synchronization when its period is: Ton + Toffmin < ZCD period < Tonmax + Toff max (converter is locked)
            3. When the ZCD is < Ton + Toff min, the TD1 will lost synchronization with ZCD, but TD1 period will remain >= Ton + Toff min (converter operates at its high frequency limit)
         In the above equation,  Ton min < Ton < Ton max
 
        The FAULT1 input is enabled on PA12 (active high) to demonstrate PWM shut down (high level sensitive).
        When the fault is triggered (PA12 input high level, TD1 signal only is stopped. The system can be re-armed by pressing the user button.

        LEDs are indicating the following:
            - LED1: blinks during normal operation
            - LED2: blinks when FAULT is triggered
    Testing Method:
        Enable the ENTRY_TEST macro to execute the test function.
        TA1 (PA8) generates an overcurrent signal, connected to EXEV3 (PB7). TB1 (PA10) generates a ZCD (Zero Cross Detection) signal, connected to EXEV4 (PB6). Use an oscilloscope to observe the waveforms of TD1, TA1, and TB1.

        Test without OC (Overcurrent) and ZCD signals
        Set a breakpoint at the first OCBlankingZCDConfig in the TestEntry function. Observe on the oscilloscope that TD1 is high for 1.44us, with a period of 5.76us.
        Test with OC blanking and ZCD effective
        Set a breakpoint at the first systick_delay_ms function in the TestEntry function.
        The oscilloscope shows that the OC signal within the blanking window is blanked, and the ZCD signal slightly shortens the low level of TD1, changing the period to 5.75us.
        OC Overcurrent Test
        Set a breakpoint at the second systick_delay_ms function in the TestEntry function.
        The oscilloscope shows that the OC signal outside the blanking window shortens the high level duration of TD1.
        ZCD Latch Test
        Set a breakpoint at the fourth systick_delay_ms function in the TestEntry function.
        The oscilloscope observes that the ZCD signal within the blanking window is latched to take effect outside the blanking window.
4. Matters needing attention
     None