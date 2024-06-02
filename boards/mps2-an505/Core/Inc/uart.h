#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdint.h>

void uart_init(void);
void uart_send(const char* string);
size_t uart_recv(uint8_t* buffer, size_t size);

#endif
