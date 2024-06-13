/**
  ******************************************************************************
  * @file      fault_gcc.s
  * @author    xidongxu
  * @brief     Arm Cortex-M33 Devices for GCC based toolchains. 
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m33
.thumb
.text

.global fd_main_stack_base
.global fd_main_stack_full
.global fault_dump_handler

.global HardFault_Handler
.type HardFault_Handler, % function
HardFault_Handler:
    cpsid   i                           /* disable interrupts */
    ldr     r3, =fd_main_stack_base     /* r3 = &fd_main_stack_base */
    ldr     r1, [r3]                    /* r1 = fd_main_stack_base  */
    ldr     r3, =fd_main_stack_full     /* r3 = &fd_main_stack_full */
    ldr     r2, [r3]                    /* r2 = fd_main_stack_full  */

    tst     lr, #4                      /* use exc_return value get sp value */
    bne     stack_use_psp               /* if (sp != msp), jump to stack_use_psp */

    mrs     r0, msp                     /* else (sp == msp), r0 = sp = msp */
    cmp     r0, r1                      /* compare msp and stack base addr */
    blt     stack_invalid               /* msp < stack_base_addr, msp is invalid */
    cmp     r0, r2                      /* compare msp and stack full addr */
    bgt     stack_invalid               /* msp > stack_base_addr, msp is invalid */

    push    {r4 - r11}                  /* stack value is normal, push {r4 - r11} to stack */
    mrs     r0, msp                     /* refresh r0 = sp = msp */
    b       stack_checked
stack_use_psp:
    mrs     r0, psp                     /* lr & 0x04 == 0, r0 = sp = psp */
    stmdb   r0!, {r4 - r11}             /* sp using psp, use stmdb push {r4 - r11} to stack */
    
stack_invalid:
    nop                                 /* stack value is invalid, not to process temporary */
stack_checked:
    mov     r1, lr                      /* now, r0 = sp, r1 = lr */
    ldr     r2, =fault_dump_handler     /* now, r2 = fault_dump_handler */
    dsb                                 /* wait for memory access to complete */
    cpsie   i                           /* enable interrupts */
    bx      r2                          /* jump to fault_dump_handler */
.end
