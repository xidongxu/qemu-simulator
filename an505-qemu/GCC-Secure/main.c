#include <stdint.h>

#include "uart.h"
#include "printf.h"
#include "ARMCM33_DSP_FP.h"

void __aeabi_unwind_cpp_pr0(void) {

}

void HardFault_Handler(void) {
    printf("%s\n", __func__);
}

void Default_Handler(void) {
    printf("%s\n", __func__);
}

int main(void) {
    int count = 0;
    uart_init();

    printf("Start\n");

    while (1) {
        __NOP();
        printf("hello world - %d.\n", count++);
    }
    return 0;
}
