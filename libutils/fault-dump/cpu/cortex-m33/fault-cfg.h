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

#if defined (ARMCM33)
#include "ARMCM33.h"
#elif defined (ARMCM33_TZ)
#include "ARMCM33_TZ.h"
#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
#include "partition_ARMCM33.h"
#endif
#elif defined (ARMCM33_DSP_FP)
#include "ARMCM33_DSP_FP.h"
#elif defined (ARMCM33_DSP_FP_TZ)
#include "ARMCM33_DSP_FP_TZ.h"
#if defined (__ARM_FEATURE_CMSE) &&  (__ARM_FEATURE_CMSE == 3U)
#include "partition_ARMCM33.h"
#endif
#else
#error device not specified!
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define FD_STACK_GROWTH_DOWNWARD        (1)
#define FD_STACK_DUMP_DEPTH_MAX         (64)
#define FD_DUMP_EXC_RETURN_VALUE        (1)

#ifdef __cplusplus
}
#endif

#endif /* __FAULT_CFG_H__ */

