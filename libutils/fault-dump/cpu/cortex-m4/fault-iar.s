/**
  ******************************************************************************
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

    SECTION     .text:CODE(2)
    THUMB
    REQUIRE8
    PRESERVE8

    IMPORT fd_main_stack_base
    IMPORT fd_main_stack_full
    IMPORT fault_dump_handler

    EXPORT HardFault_Handler
HardFault_Handler:
    cpsid   i                           /* disable interrupts */
    ldr     r3, =fd_main_stack_base     /* r3 = &fd_main_stack_base */
    ldr     r1, [r3]                    /* r1 = fd_main_stack_base  */
    ldr     r3, =fd_main_stack_full     /* r3 = &fd_main_stack_full */
    ldr     r2, [r3]                    /* r2 = fd_main_stack_full  */

    tst     lr, #4                      /* use exc_return value get sp value */
    bne     stack_checked               /* if (sp != msp), jump to stack_checked */

    mrs     r0, msp                     /* else (sp == msp), r0 = sp = msp */
    cmp     r0, r1                      /* compare msp and stack base addr */
    blt     stack_invalid               /* msp < stack_base_addr, msp is invalid */
    cmp     r0, r2                      /* compare msp and stack full addr */
    bgt     stack_invalid               /* msp > stack_base_addr, msp is invalid */
    
stack_checked:
    push    {r4 - r11}                  /* sp value is in stack range, push r4 - r11 to stack */

    tst     lr, #4                      /* update sp value to r0 */
    ite     eq
    mrseq   r0, msp                     /* lr & 0x04 == 1, r0 = sp = msp */
    mrsne   r0, psp                     /* lr & 0x04 == 0, r0 = sp = psp */
stack_invalid:
    mov     r1, lr                      /* now, r0 = sp, r1 = lr */
    ldr     r2, =fault_dump_handler     /* now, r2 = fault_dump_handler */
    dsb                                 /* wait for memory access to complete */
    cpsie   i                           /* enable interrupts */
    bx      r2                          /* jump to fault_dump_handler */

    END