#include "logPrint.h"
#include "uart.h"
#include "ARMCM33_DSP_FP_TZ.h"
#include <stdint.h>

void __aeabi_unwind_cpp_pr0(void) {

}

int main(void) {
    int count = 0;
    SystemInit();
    uart_init();
    uart_send("Start\n");

    while (1) {
        __NOP();
        uart_send("hello world.\n");
    }
    return 0;
}
