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
.cpu cortex-m33
.fpu softvfp
.thumb

.type HardFault_Handler, % function
.global fault_dump_handler
.global HardFault_Handler
HardFault_Handler:
    tst     lr, #4
    ite     eq
    mrseq   r0, msp
    mrsne   r0, psp
    stmfd   r0!, {r4 - r11}
    mov     r1, lr
    ldr     r2, =fault_dump_handler
    bx      r2
.end
