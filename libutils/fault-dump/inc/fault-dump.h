/**
  ******************************************************************************
  * @file    fault-dump.h
  * @author  xidongxu
  * @brief   This file contains all the function prototypes for the fault-dump.c
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
#ifndef __FaultDump_H__
#define __FaultDump_H__

#include <stdio.h>
#include <stdbool.h>
#include "fault-cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FD_STACK_GROWTH_DOWNWARD
#define FD_STACK_GROWTH_DOWNWARD        (1)
#endif
#ifndef FD_STACK_DUMP_DEPTH_MAX
#define FD_STACK_DUMP_DEPTH_MAX         (64)
#endif
#ifndef FD_DUMP_EXC_RETURN_VALUE
#define FD_DUMP_EXC_RETURN_VALUE        (0)
#endif
#define FD_CHECK_BIT(var, pos)          ((var) & (1 << (pos)))

#define FD_EOK                          (0)
#define FD_ERROR                        (1)
#define FD_EEMPTY                       (2)
#define FD_EINVAL                       (3)

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

typedef int (*stack_parser_t)(unsigned int*, size_t, unsigned int*, unsigned int*);

void fault_dump_init(void);
void fault_dump_handler(unsigned int *stack, unsigned int linker);
int  fault_dump_callstack(unsigned int *buffer, size_t size, unsigned int *stack_point, unsigned int *stack_start);
/* bare metal code stack information. */
unsigned int fault_dump_bm_stack_point(void);
unsigned int fault_dump_bm_stack_start(void);
/* stack frame parser object interface */
int fault_dump_psp_stack_parser(stack_parser_t parser);

#ifdef __cplusplus
}
#endif

#endif /* __FaultDump_H__ */

