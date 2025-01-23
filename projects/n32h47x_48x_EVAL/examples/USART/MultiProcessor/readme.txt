1¡¢¹¦ÄÜËµÃ÷

    ¸Ã²âÀıÑİÊ¾ÁËÈçºÎÊ¹ÓÃUSART¶à´¦ÀíÆ÷Ä£Ê½¡
    Ê×ÏÈ£¬·Ö±ğÉèÖÃUSARTyºÍUSARTzµÄµØÖ·Îª0x1ºÍ0x2¡£USARTyÁ¬Ğø¸øUSARTz
·¢ËÍ×Ö·û0x33¡£USARTzÊÕµ½0x33£¬±ã·­×ªLED1µÄÒı½Å¡£
    Ò»µ©KEY1_INT_EXTI_LINEÏß¼ì²âµ½ÉÏÉıÑØ£¬Ôò²úÉúEXTI0ÖĞ¶Ï£¬ÔÚ
EXTI0_IRQHandlerÖĞ¶Ï´¦Àíº¯ÊıÖĞ(the ControlFlag = 0)£¬USARTz½øÈë¾²Ä¬
Ä£Ê½£¬ÔÚ¾²Ä¬Ä£Ê½ÖĞ£¬LEDÒı½ÅÍ£Ö¹·­×ª£¬Ö±µ½KEY1_INT_EXTI_LINEÏß¼ì²âµ½
ÉÏÉıÑØ(the ControlFlag = 1)¡£ÔÚEXTI0_IRQHandlerÖĞ¶Ï´¦Àíº¯ÊıÖĞ£¬USARTy
·¢ËÍµØÖ·0x102»½ĞÑUSARTz¡£LEDÒı½ÅÖØĞÂÆô¶¯·­×ª¡£


2¡¢Ê¹ÓÃ»·¾³

    Èí¼ş¿ª·¢»·¾³£ºKEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    
    Ó²¼ş¿ª·¢»·¾³£º    
        N32H473ÏµÁĞ£º
        »ùÓÚÆÀ¹À°åN32H473VEL7_STB V1.0¿ª·¢
        N32H474ÏµÁĞ£º
        »ùÓÚÆÀ¹À°åN32H474VEL7_STB V1.0¿ª·¢
        N32H475ÏµÁĞ£º
        »ùÓÚÆÀ¹À°åN32H475UEQ7_STB V1.0¿ª·¢
        N32H482ÏµÁĞ£º
        »ùÓÚÆÀ¹À°åN32H482ZEL7_STB V1.0¿ª·¢
        N32H487ÏµÁĞ£º
        »ùÓÚÆÀ¹À°åN32H487ZEL7_EVB V1.0¿ª·¢
        

3¡¢Ê¹ÓÃËµÃ÷
	
	/* ÃèÊöÏà¹ØÄ£¿éÅäÖÃ·½·¨£»ÀıÈç:Ê±ÖÓ£¬I/OµÈ */
    ÏµÍ³Ê±ÖÓÅäÖÃ£º
        N32H475/N32H482/N32H487:
            SystemClock£º240MHz
        N32H474/N32H473:
            SystemClock£º200MHz
    
    USARTyÅäÖÃÈçÏÂ£º
    - ²¨ÌØÂÊ = 115200 baud
    - ×Ö³¤ = 9Êı¾İÎ»
    - 1Í£Ö¹Î»
    - Ğ£Ñé¿ØÖÆ½ûÓÃ
    - Ó²¼şÁ÷¿ØÖÆ½ûÓÃ£¨RTSºÍCTSĞÅºÅ£©
    - ½ÓÊÕÆ÷ºÍ·¢ËÍÆ÷Ê¹ÄÜ  
    
    
    USARTÒı½ÅÁ¬½ÓÈçÏÂ£º    
     - USART3_Tx.PA9 <-------> UART5_Rx.PA3
     - USART3_Rx.PA15 <-------> UART5_Tx.PA2
    
    N32H487ÏµÁĞ£º
        EXIT£ºPC13Îª¸¡¿ÕÊäÈëÄ£Ê½£¬Íâ²¿ÖĞ¶ÏÏß - EXIT_LINE13£¬¿ªÆôÍâ²¿ÖĞ¶Ï
    N32H482/N32H475/N32H474/N32H473ÏµÁĞ:
        EXIT£ºPA4Îª¸¡¿ÕÊäÈëÄ£Ê½£¬Íâ²¿ÖĞ¶ÏÏß - EXIT_LINE4£¬¿ªÆôÍâ²¿ÖĞ¶Ï
        
    LED <-------> PA8

    
    ²âÊÔ²½ÖèÓëÏÖÏó£º
    - DemoÔÚKEIL»·¾³ÏÂ±àÒëºó£¬ÏÂÔØÖÁMCU
    - ¸´Î»ÔËĞĞ£¬¹Û²ìLED1ÊÇ·ñ´¦ÓÚÉÁË¸×´Ì¬
    - °´°´¼üKEY£¬¹Û²ìLED1ÊÇ·ñÍ£Ö¹ÉÁË¸
    - ÔÙ´Î°´°´¼üKEY£¬¹Û²ìLED1ÊÇ·ñ»Ö¸´ÉÁË¸


4¡¢×¢ÒâÊÂÏî
   ĞèÏÈ½«¿ª·¢°åNS-LINKµÄMCU_TXºÍMCU_RXÌøÏßÃ±¶Ï¿ª


1. Function description
    This test example demonstrates how to use the USART multiprocessor mode.
    First, set the addresses of USARTy and USARTz to 0x1 and 0x2, respectively. USARTy continuously gives USARTz send the character
    0x33. USARTz receives 0x33 and flips the pin of LED1.
    Once a rising edge is detected on the KEY1_INT_EXTI_LINE line, an EXTI0 interrupt will be generated.
    In the EXTI0_IRQHandler interrupt handler (the ControlFlag = 0), USARTz goes silent mode, in silent mode, the LED pin stops toggling.
    toggling until the KEY1_INT_EXTI_LINE line detects rising edge (the ControlFlag = 1). In the EXTI0_IRQHandler interrupt handler, 
    USARTysend address 0x102 to wake up USARTz. The LED pin restarts toggling.


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
            SystemClock£º240MHz
        N32H474/N32H473:
            SystemClock£º200MHz
    
    USARTy is configured as follows:
    - Baud rate = 115200 baud
    - Word length = 9 data bits
    - 1 stop bit
    - checksum control disabled
    - Hardware flow control disabled (RTS and CTS signals)
    - Receiver and transmitter enable
    
    
    The USART pins are connected as follows:
     - USART3_Tx.PA9 <-------> UART5_Rx.PA3
     - USART3_Rx.PA15 <-------> UART5_Tx.PA2
    
    N32H487£º               
        EXIT: PC13 is in floating input mode, and external interrupt line -exit_line13 is used to enable external interrupt
    N32H482/N32H475/N32H474/N32H473£º               
        EXIT: PA4 is in floating input mode, and external interrupt line -exit_line4 is used to enable external interrupt
        
    
    LED <-------> PA8

    
    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Reset operation and observe whether LED1 are blinking
    - Press the button KEY and observe whether LED1 stop flashing
    - Press the button KEY again and observe whether LED1 resume to flash


4. Attention
    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first