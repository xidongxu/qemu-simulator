/**
  ******************************************************************************
  * @file    Fault_Dump.h
  * @brief   This file contains all the function prototypes for
  *          the FaultTrace.c file
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
#ifndef __FaultTrace_H__
#define __FaultTrace_H__

#include "stm32f4xx.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct stack_frame_except stack_frame_except_t;
struct stack_frame_except {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
};

typedef struct stack_frame_manual stack_frame_manual_t;
struct stack_frame_manual {
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
};

typedef struct stack_frame stack_frame_t;
struct stack_frame {
  stack_frame_manual_t manual;
  stack_frame_except_t except;
  uint32_t callback[16];
};

void fault_dump_init(void);
void fault_dump_handler(uint32_t *stack, uint32_t link);
void fault_dump_register(void);

#ifdef __cplusplus
}
#endif

#endif /* __FaultTrace_H__ */

