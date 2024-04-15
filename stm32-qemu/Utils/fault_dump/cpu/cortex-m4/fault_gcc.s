/*******************************************************************************
  * @file      fault_gcc.s
  * @author    MCD Application Team
  * @brief     STM32F405xx Devices vector table for GCC based toolchains. 
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.type HardFault_Handler_Proc, % function
.global fault_dump_handler
.global HardFault_Handler_Proc
HardFault_Handler_Proc:
    tst     lr, #4
    ite     eq
    mrseq   r0, msp
    mrsne   r0, psp
    mov     r1, lr
    ldr     r2, =fault_dump_handler
    bx      r2
.end
