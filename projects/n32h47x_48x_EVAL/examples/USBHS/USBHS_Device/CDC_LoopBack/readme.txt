1. ����˵��
    USB CDC �豸�ػ�����

2. ʹ�û���

    �������������KEIL MDK-ARM 5.34
                  IAR EWARM 8.50.1

    Ӳ������������
        N32H482ϵ�У�
        ����������N32H482ZEL7_STB V1.0����
        N32H487ϵ�У�
        ����������N32H487ZEL7_STB V1.1����


3. ʹ��˵��
    �������ģ�����÷���������:ʱ�ӣ�I/O�� 
         1. SystemClock��240MHz

    ����Demo�Ĳ��Բ�������� 
         1. ��������س���λ���У�
         2. ͨ�� USB ������ J62 USB �ڣ�����ʶ������⴮���豸
         3. ��PC�ϴ� USB ���⴮�ڣ�USB ���⴮�ڷ������ݣ����ڹ��߻������յ��ոշ��͵����ݡ�


4. ע������
    ��ͨ���޸ĺ궨�� USE_USB_HS_IN_FS �� USE_USB_HS_IN_HS �л��豸Ϊȫ��ģʽ���߸���ģʽ��
    ʹ�ø���ģʽʱ����Ҫʹ��16MHz�ⲿ���塣

1. Function description
    USB CDC device loopback test

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
    3. Open the USB virtual serial port on the PC, and send data through the USB virtual serial port, the serial port tool will immediately receive the data just sent.
      
        
4. Matters needing attention
    The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
    When using the High-Speed mode, a 16MHz external cycstal is required.