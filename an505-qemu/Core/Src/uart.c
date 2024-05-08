#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

/* Base address of the UART0 See application note AN505 */
#define UART0_BASE_NONSECURE    (0x40200000)
#define UART0_BASE_SECURE       (0x50200000)

#ifdef C_SECURE_CODE
#define UART0_BASE              UART0_BASE_SECURE
#else
#define UART0_BASE              UART0_BASE_NONSECURE
#endif

#define UART_DR(base)           (*((volatile uint32_t *)(base + 0x00)))
#define UART_CTRL(base)         (*((volatile uint32_t *)(base + 0x08)))

void uart_init(void) {
    // uart send enable register.
    UART_CTRL(UART0_BASE) = 1;
}

int __io_putchar(int ch) {
    // uart send data register.
    UART_DR(UART0_BASE) = ch;
    return ch;
}

void uart_send(const char* string) {
    while (*string != '\0') {
        __io_putchar(*string);
        string++;
    }
}

void logPrint(const char* format, ...) {
    char buffer[256] = {'\0'};
    int bufferPos = 0;

    unsigned int hex;

    va_list arg;
    va_start(arg, format);

    for(const char* nextChar = format; *nextChar != '\0'; nextChar++) {
        while ((*nextChar != '%') && (*nextChar != '\0')) {
            sprintf(buffer + bufferPos, "%c", *nextChar);
            bufferPos++;
            nextChar++;
        }

        if (*nextChar == '\0') {
            break;
        }

        nextChar++;

        switch (*nextChar) 
        {
        case 'x':
            hex = va_arg(arg, unsigned int);
            int written = 0;
            written = sprintf(buffer + bufferPos, "%x", hex);
            bufferPos = bufferPos + written;
            break;
        default:
            break;
        }
    }

    buffer[bufferPos] = '\0';
    va_end(arg);
    uart_send(buffer);
}
