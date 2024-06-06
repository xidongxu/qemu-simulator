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

int freertos_stack_parser(unsigned int *buffer, size_t size, unsigned int *stack_point, unsigned int *stack_start) {
    int count = fault_dump_callstack(buffer, size, stack_point, stack_point);
    return count;
}
