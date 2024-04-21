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
    unsigned int r0;
    unsigned int r1;
    unsigned int r2;
    unsigned int r3;
    unsigned int r12;
    unsigned int lr;
    unsigned int pc;
    unsigned int psr;
};

typedef struct stack_frame_manual stack_frame_manual_t;
struct stack_frame_manual {
    unsigned int r4;
    unsigned int r5;
    unsigned int r6;
    unsigned int r7;
    unsigned int r8;
    unsigned int r9;
    unsigned int r10;
    unsigned int r11;
};

typedef struct stack_frame stack_frame_t;
struct stack_frame {
    stack_frame_manual_t manual;
    stack_frame_except_t except;
};

void fault_dump_init(void);
void fault_dump_handler(unsigned int *stack, unsigned int linker);
void fault_dump_register(void);

#ifdef __cplusplus
}
#endif

#endif /* __FaultTrace_H__ */

