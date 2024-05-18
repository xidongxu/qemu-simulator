/*******************************************************************************
  * @file      fault_gcc.s
  * @author    xidongxu
  * @brief     Arm Cortex-M4 Devices for GCC based toolchains. 
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m4
.thumb
.text

.global fd_code_stack_base
.global fd_code_stack_full
.global fault_dump_handler

.global HardFault_Handler
.type HardFault_Handler, % function
HardFault_Handler:
    ldr     r3, =fd_code_stack_base     /* r3 = &fd_code_stack_base */
    ldr     r1, [r3]                    /* r1 = fd_code_stack_base  */
    ldr     r3, =fd_code_stack_full     /* r3 = &fd_code_stack_full */
    ldr     r2, [r3]                    /* r2 = fd_code_stack_full  */

    tst     lr, #4                      /* use exc_return value get sp value */
    ite     eq
    mrseq   r0, msp                     /* lr & 0x04 == 1, r0 = sp = msp */
    mrsne   r0, psp                     /* lr & 0x04 == 0, r0 = sp = psp */

    cmp     r0, r1                      /* compare sp and stack base addr */
    blt     stack_invalid               /* sp < stack_base_addr, sp is invalid */
    cmp     r0, r2                      /* compare sp and stack full addr */
    bgt     stack_invalid               /* sp > stack_base_addr, sp is invalid */

    push    {r4 - r11}                  /* sp value is in stack range, push r4 - r11 to stack */

    tst     lr, #4                      /* update sp value to r0*/
    ite     eq
    mrseq   r0, msp                     /* lr & 0x04 == 1, r0 = sp = msp */
    mrsne   r0, psp                     /* lr & 0x04 == 0, r0 = sp = psp */
stack_invalid:
    mov     r1, lr                      /* now, r0 = sp, r1 = lr */
    ldr     r2, =fault_dump_handler     /* now, r2 = fault_dump_handler */
    bx      r2                          /* jump to fault_dump_handler */                        
.end
