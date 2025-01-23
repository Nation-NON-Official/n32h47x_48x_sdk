1. ����˵��
    USB MSC + CDC ����豸

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
         2. ���ڣ�USART1 TX -- PA9  RX -- PA10 �����ʣ�115200
         3. SPI1���ã�NSS--PA4��SCK--PA5��MISO--PA6��MOSI--PA7 (����W25Q128)


    ����Demo�Ĳ��Բ�������� 
         1. ��������س���λ���У�
         2. ͨ�� USB ������ J62 USB �ڣ�����ʶ������⴮���豸��U ���豸
         3. �� USART1 �ӵ����ڹ����ϣ�Ȼ����PC�ϴ� USB ���⴮�ڣ�USB ���⴮�ڷ������ݣ�
            �ô��ڹ��߽������ݣ�Ȼ���ô��ڹ��߷������ݣ� USB ���⴮�ڽ�������


4. ע������
    �״ι��� U ����Ҫ��ʽ������ʽ����ɺ󼴿ɵ��� U ��ʹ�á���N32H487ZEL7_EVB V1.1�������ϣ�J29��J31������ñ���ӣ�
    ��ͨ���޸ĺ궨�� USE_USB_HS_IN_FS �� USE_USB_HS_IN_HS �л��豸Ϊȫ��ģʽ���߸���ģʽ��
    ʹ�ø���ģʽʱ����Ҫʹ��16MHz�ⲿ���塣

1. Function description
    USB MSC + CDC composite device

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
        3. SPI1 configuration: NSS--PA4, SCK--PA5, MISO--PA6, MOSI--PA7 (connected to W25Q128)

    Describe the testing steps and phenomena of the Demo
    1. After compiling, the downloaded program is reset and run;
    2. Connect a USB cable to the J62 USB port. The computer identifies the virtual serial port device and U disk device
    3. Connect USART1 to the serial port tool, then open the USB virtual serial port on the PC, and send data through the USB virtual serial port.
       Use the serial port tool to receive data, and then use the serial port tool to send data, USB virtual serial port to receive data
    
        
4. Matters needing attention
     The first mount U disk needs to be formatted, and it can be used as a U disk after formatting. On N32H487ZEL7_EVB V1.1 board, J29 and J31 Connected with jumper cap;
     The device can be switched to Full-Speed mode or High-Speed mode by modify the macro definition USE_USB_HS_IN_FS or USE_USB_HS_IN_HS;
     When using the High-Speed mode, a 16MHz external cycstal is required.