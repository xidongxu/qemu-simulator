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

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE {
    UART_DR(UART0_BASE) = ch;
    return ch;
}

void uart_init(void) {
    UART_CTRL(UART0_BASE) = 1;
}

void uart_send(const char* string) {
    while (*string != '\0') {
        putchar(*string);
        string++;
    }
}
