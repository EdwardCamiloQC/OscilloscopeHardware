#ifndef _UART_H_
    #define _UART_H_

    void uart0_init(int baudRate);
    void uart0_putChar(char character);
    char uart0_getChar(void);
#endif
