#include <stdint.h>

#include "uart.h"
#include "printf.h"
#include "ARMCM33_DSP_FP.h"
#include "tx_api.h"

void HardFault_Handler_Legency(void) {
    printf("%s\n", __func__);
}

void Default_Handler(void) {
    printf("%s\n", __func__);
}

void test0(void) {
    printf("this is %s.\r\n", __func__);
}

void test1(void) {
    printf("this is %s.\r\n", __func__);
    test0();
}

void test2(void) {
    printf("this is %s.\r\n", __func__);
    test1();
}

void test3(void) {
    printf("this is %s.\r\n", __func__);
    test2();
}

void test4(void) {
    printf("this is %s.\r\n", __func__);
    test3();
}

void test5(void) {
    printf("this is %s.\r\n", __func__);
    test4();
}

static void tx_task_entry(ULONG thread_input) {
    int counter = 0;
    while(1) {
        printf("hello threadx %d\r\n", counter++);
        tx_thread_sleep(1000);
    }
}

void tx_application_define(void *first_unused_memory) {
    CHAR *tx_stack = TX_NULL;
    static TX_THREAD tx_task;
    static TX_BYTE_POOL tx_pool;
    static UCHAR tx_memory[4096];

    tx_byte_pool_create(&tx_pool, "tx_pool", tx_memory, sizeof(tx_memory));
    tx_byte_allocate(&tx_pool, (VOID **) &tx_stack, 1024, TX_NO_WAIT);
    tx_thread_create(&tx_task, "tx_task", tx_task_entry, 0, tx_stack, 1024, 1, 1, 10, TX_AUTO_START);
    tx_block_release(tx_stack);
}

int main(void) {
    int count = 0;
    uart_init();

    printf("Start\r\n");
    tx_kernel_enter();

    while (1) {
        __NOP();
        printf("hello world - %d.\r\n", count++);
    }
    return 0;
}
