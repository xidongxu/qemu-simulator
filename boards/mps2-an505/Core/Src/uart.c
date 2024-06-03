#include "uart.h"

/* Base address of the UART0 See application note AN505 */
#define UART0_BASE_NONSECURE    (0x40200000)
#define UART0_BASE_SECURE       (0x50200000)

#ifdef C_SECURE_CODE
#define UART0                   UART0_BASE_SECURE
#else
#define UART0                   UART0_BASE_NONSECURE
#endif

#define UART_DATA(base)         (*((volatile uint32_t *)(base + 0x00)))
#define UART_RSR(base)          (*((volatile uint32_t *)(base + 0x04)))
#define UART_CTRL(base)         (*((volatile uint32_t *)(base + 0x08)))
#define UART_FLAG(base)         (*((volatile uint32_t *)(base + 0x18)))
#define UART_LPR(base)          (*((volatile uint32_t *)(base + 0x20)))
#define UART_IBRD(base)         (*((volatile uint32_t *)(base + 0x24)))
#define UART_FBRD(base)         (*((volatile uint32_t *)(base + 0x28)))
#define UART_LCRH(base)         (*((volatile uint32_t *)(base + 0x2C)))
#define UART_CR(base)           (*((volatile uint32_t *)(base + 0x30)))
#define UART_IFLS(base)         (*((volatile uint32_t *)(base + 0x34)))
#define UART_MSC(base)          (*((volatile uint32_t *)(base + 0x38)))
#define UART_RIS(base)          (*((volatile uint32_t *)(base + 0x3C)))
#define UART_MIS(base)          (*((volatile uint32_t *)(base + 0x40)))
#define UART_ICR(base)          (*((volatile uint32_t *)(base + 0x44)))
#define UART_DMACR(base)        (*((volatile uint32_t *)(base + 0x48)))

int put_char(int ch) {
    while (UART_FLAG(UART0) & 0x20);
    UART_DATA(UART0) = ch;
    return ch;
}

int get_char(void) {
    while ((UART_FLAG(UART0) & 0x40) == 0);
    return UART_DATA(UART0);
}

int puts(const char* string) {
    int index = 0;
    while (string[index] != '\0') {
        put_char(string[index]);
        index++;
    }
    put_char('\n');
    return index;
}

void uart_init(void) {
    UART_IBRD(UART0) = 40;
    UART_FBRD(UART0) = 11;
    UART_LCRH(UART0) = 0x60;
    UART_CR(UART0)   = 0x301;
    UART_RSR(UART0)  = 0x0A;
    UART_CTRL(UART0) = 0x01;
}

void uart_send(const char* string) {
    puts(string);
}

size_t uart_recv(uint8_t* buffer, size_t size) {
    uint8_t ch = 0;
    size_t it = 0;
    while (1) {
        ch = getchar();
        if(ch == '\n' || it >= size) {
            break;
        }
        buffer[it] = ch;
        it = it + 1;
    }
    return (it + 1);
}
