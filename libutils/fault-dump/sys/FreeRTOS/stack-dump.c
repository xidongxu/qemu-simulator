/**
  ******************************************************************************
  * @file    stack-dump.c
  * @author  xidongxu
  * @brief   This file contains all the function prototypes for the stack-dump.c
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
#include "fault-dump.h"
#include "FreeRTOSConfig.h"

int freestos_return_parser(unsigned int stack_point) {
    unsigned int pc = 0, *sp = NULL, reg_cnt = 10, fpu_cnt = 0;
    sp = (unsigned int*)(stack_point + sizeof(unsigned int));
    pc = *sp;
    if ((pc != 0xFFFFFFE1) && (pc != 0xFFFFFFF1) && \
        (pc != 0xFFFFFFE9) && (pc != 0xFFFFFFF9) && \
        (pc != 0xFFFFFFED) && (pc != 0xFFFFFFFD)) {
        return 0;
    }
    // is using mpu?
    if (configENABLE_MPU) {
        reg_cnt = 11;
    }
    // is using fpu? 0: using, 1: not using.
    if (!(pc & 0x10)) {
        fpu_cnt = 16;
    }
    // 6 is: r0 - r3, r12, lr.
    sp = (unsigned int*)(stack_point + ((reg_cnt + fpu_cnt + 6) * sizeof(unsigned int)));
    pc = 0;
    // *sp = return adress.
    if ((*sp >= fault_dump_text_base()) && (*sp <= fault_dump_text_ends())) {
        pc = *sp;
    }
    return pc;
}

int freertos_stack_parser(unsigned int *buffer, size_t size, unsigned int *stack_point, unsigned int *stack_start) {
    int count = fault_dump_callstack(buffer, size, stack_point, stack_point);
    return count;
}