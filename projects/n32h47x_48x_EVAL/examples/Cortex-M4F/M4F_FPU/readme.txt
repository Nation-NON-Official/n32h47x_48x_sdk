1¡¢¹¦ÄÜËµÃ÷

    /* ¼òµ¥ÃèÊö¹¤³Ì¹¦ÄÜ */
        Õâ¸öÀı³ÌÅäÖÃ²¢ÑİÊ¾ÁËFPUµÄ¸¡µãÔËËãµ¥Ôª


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
        »ùÓÚÆÀ¹À°åN32H487ZEL7_EVB V1.0¿ª·¢¢


3¡¢Ê¹ÓÃËµÃ÷

    /* ÃèÊöÏà¹ØÄ£¿éÅäÖÃ·½·¨£»ÀıÈç:Ê±ÖÓ£¬I/OµÈ */
    N32H475/N32H482/N32H487:
        SystemClock£º240MHz
        USART£ºTX - PA9£¬²¨ÌØÂÊ115200
    N32H474/N32H473:
        SystemClock£º200MHz
        USART£ºTX - PA9£¬²¨ÌØÂÊ115200

    /* ÃèÊöDemoµÄ²âÊÔ²½ÖèºÍÏÖÏó */
        1.±àÒëºóÏÂÔØ³ÌĞò¸´Î»ÔËĞĞ£»
        2.Ê¹ÓÃJuliaÌ××°²âÊÔFPU£¬²é¿´´òÓ¡µÄĞÅÏ¢£¬²¢±È½Ï´ò¿ª»ò¹Ø±ÕFPUµ¥ÔªµÄ¼ÆËãÊ±¼ä¡£


4¡¢×¢ÒâÊÂÏî
    ÎŞ



1. Function description
    /* A brief description of the engineering function */
    This routine configures and demonstrates the FPU floating point arithmetic unit

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
    /* Describe the related module configuration method; For example: clock, I/O, etc. */
    N32H475/N32H482/N32H487:
        SystemClock: 240MHZ
        USART: TX-PA9, baud rate 115200
    N32H474/N32H473:
        SystemClock: 200MHZ
        USART: TX-PA9, baud rate 115200
    /* Describes the test steps and symptoms of Demo */
    1. Reset and run the downloaded program after compilation;
    2. Use the Julia set to test the FPU, view the printed information, and compare the calculation time of opening or closing the FPU unit.

4. Precautions
    None