/**
  ******************************************************************************
  * @file    fault-hal.c
  * @author  xidongxu
  * @brief   This file contains all the function prototypes for the fault-hal.c
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
#include "fault-dump.h"

void fault_dump_exc_return(unsigned int exc_return) {
    printf(" \r\n");
    printf(" Bit2 Return Stack Select..:");
    if (FD_CHECK_BIT(exc_return, 2)) {
        printf("[Use PSP...............].\r\n");
    } else {
        printf("[Use MSP...............].\r\n");
    }
    printf(" Bit3 Return Mode Select...:");
    if (FD_CHECK_BIT(exc_return, 3)) {
        printf("[Use Thread Mode.......].\r\n");
    } else {
        printf("[Use Process Mode......].\r\n");
    }
    printf(" Bit4 Stack Frame Type.....:");
    if (FD_CHECK_BIT(exc_return, 4)) {
        printf("[Use 8 World Frame.....].\r\n");
    } else {
        printf("[Use 26 World Frame....].\r\n");
    }
    printf(" \r\n");
}

bool fault_dump_using_msp(unsigned int exc_return) {
    if (FD_CHECK_BIT(exc_return, 2)) {
        return false;
    } else {
        return true;
    }
}

void fault_dump_div_zero(void) {
    int a = 0, b = 0, c = 0;

    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
    c = (a + (b / c));
    printf("zero = %d\r\n", c);
}

void fault_dump_unalign(void) {
    volatile int *addr = NULL;
    volatile int value = 0;
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
    addr = (int*)0x00;
    value = *addr;
    printf("addr:0x%02X-value:0x%08X\r\n", (int)addr, value);
    addr = (int*)0x04;
    value = *addr;
    printf("addr:0x%02X-value:0x%08X\r\n", (int)addr, value);
    addr = (int*)0x03;
    value = *addr;
    printf("addr:0x%02X-value:0x%08X\r\n", (int)addr, value);
}
