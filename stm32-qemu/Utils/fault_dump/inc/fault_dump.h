/**
  ******************************************************************************
  * @file    FaultTrace.h
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

typedef struct fault_stack_frame fault_stack_frame_t;
struct fault_stack_frame {
    /* Generic register */
		uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
};

typedef struct fault_stack_frame_fpu fault_stack_frame_fpu_t;
struct fault_stack_frame_fpu {
    /* Generic register */
		uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
    /* Fpu register */
    uint32_t S0;
    uint32_t S1;
    uint32_t S2;
    uint32_t S3;
    uint32_t S4;
    uint32_t S5;
    uint32_t S6;
    uint32_t S7;
    uint32_t S8;
    uint32_t S9;
    uint32_t S10;
    uint32_t S11;
    uint32_t S12;
    uint32_t S13;
    uint32_t S14;
    uint32_t S15;
    uint32_t FPSCR;
    uint32_t NONE;	
};

void fault_dump_handler(uint32_t *stack, uint32_t link);
void fault_dump_handler_fpu(uint32_t *stack, uint32_t link);

#ifdef __cplusplus
}
#endif

#endif /* __FaultTrace_H__ */

