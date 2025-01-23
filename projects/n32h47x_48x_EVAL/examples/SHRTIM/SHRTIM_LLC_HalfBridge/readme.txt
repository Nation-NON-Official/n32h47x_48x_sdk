1、功能说明
    此示例显示如何配置 HRTIM 来控制半桥 LLC具有同步整流的转换器，使用定时器单元 A 和 B 以及TA1/TA2/TB1/TB2 输出。
2、使用环境
    软件开发环境：KEIL MDK-ARM 5.34
                 IAR EWARM 8.50.1
    硬件环境：N32H474VEL7-STB V1.0    

3、使用说明
    系统配置：
        1、 时钟源：
            HSE=8M,PLL=200M,AHB=200M, 
            SHRTIM clock(SHRTPLL) = 250M，High-resolution clock = 1.6GHz。
            ADC sampling clock = 200MHz/3 = 66.7MHz。
        2、 ADC配置为8个转换周期，在以下时间点采样：
            - ADC1： 间断扫描模式、注入通道、HRTIM触发，序列长度为4、HRTIM_TRG2触发、PA0采样
            - ADC1： 间断扫描模式、注入通道、HRTIM触发，序列长度为4、HRTIM_TRG4触发、PA6采样
            - SRT1开启前的250ns， SR1开启后的250ns. SR1关闭前的250ns，SR1关闭后的250ns
            - SR2的采样时间同理
        3、TA1 和 TA2 输出（分别为 PA8、PA9）是互补 PWM 输出，用于控制初级侧半桥开关。
           TB1 和 TB2 输出（分别为 PA10、PA11）是独立的 PWM 信号，用于控制次级侧的同步整流 FET。
           PA12 上启用 FAULT1 输入（高电平激活）以演示 PWM 关闭，适用于所有输出。
           故障触发时（PA12输入高电平） TA1、TA2、TB1、TB2信号被关闭。 按下用户按钮即可重新装备系统。
           电路还通过比较器2在PA1输入上进行延迟空闲保护模式，以防止初级侧过电流。

    使用方法： 
          演示在RUN模式下启动，且LLC开关频率在Master IRQ处理程序中缓慢调整（50KHz~200KHz），
          以模拟控制环在实时调整操作点，并显示所有事件都与初级侧（SR FETs和ADC采样点）同步。
4、注意事项
    无
    
    
1. Function description
    This example shows how to configure the HRTIM to control a half-bridge LLC 
    converter with synchronous rectification, using timer units A and B and 
    TA1/TA2/TB1/TB2 outputs.

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34
                                      IAR EWARM 8.50.1
    Hardware environment: N32H474VEL7-STB V1.0  

3. Instructions for use
    System Configuration:
        1. clock source
            HSE=8M,PLL=200M,AHB=200M, 
            SHRTIM clock(SHRTPLL) = 250M，High-resolution clock = 1.6GHz。
            ADC sampling clock = 200MHz/3 = 66.7MHz。
        2.  The ADC is configured to do 8 conversions per switching cycle, at the 
            following time:
            - 250ns before SR1 turn-on, 250ns after SR1 turn-on, 250ns before SR1 turn-off
              and 250ns after SR1 turn-off
            - same applies for SR2 also
        3.  The TA1 and TA2 outputs (resp. PA8, PA9)are complementary PWM outputs for
            controlling the primary side half-bridge switches.
            The TB1 and TB2 outputs (resp. PA10, PA11) are independent PWM signals for
            controlling the synchronous rectification FETs on the secondary side.
            The FAULT1 input is enabled on PA12 (high level active) to demonstrate PWM shut down 
            for all outputs.
            When the fault is triggered (PA12 input connected to GND) TA1, TA2, TB1, TB2
            signals are shut-down. The system can be re-armed by pressing the user button.
            The circuit is also protected from over-current on the primary side with the 
            comparator 2, on PA7 input, in delayed idle protection mode.
    Instructions:
            The demo starts in RUN mode, and the LLC switching frequency is slowly(50KHz~200KHz) 
            adjusted in the Master IRQ handler to simulate a control loop adjusting the
            operating point in real-time and show that all events are synchronized with 
            the primary side (SR FETs and ADC sampling points).
        
4. Matters needing attention
     None