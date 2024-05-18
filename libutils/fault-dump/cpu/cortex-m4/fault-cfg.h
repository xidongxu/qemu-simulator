/**
  ******************************************************************************
  * @file    fault-cfg.h
  * @author  xidongxu
  * @brief   This file contains all the function prototypes for the fault-dump.c
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
#ifndef __FAULT_CFG_H__
#define __FAULT_CFG_H__

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FD_STACK_GROWTH_DOWNWARD        (1)
#define FD_STACK_DUMP_DEPTH_MAX         (64)

#ifdef __cplusplus
}
#endif

#endif /* __FAULT_CFG_H__ */

