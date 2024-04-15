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

void ft_hardfault(unsigned long *stack_frame, unsigned int link_reg);

#ifdef __cplusplus
}
#endif

#endif /* __FaultTrace_H__ */

