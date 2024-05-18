;*******************************************************************************
;* @file      fault_gcc.s
;* @author    xidongxu
;* @brief     Arm Cortex-M4 Devices for MDK based toolchains. 
;*******************************************************************************
;* @attention
;*
;*
;*
;*******************************************************************************


    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    IMPORT fd_code_stack_base
    IMPORT fd_code_stack_full
    IMPORT fault_dump_handler
HardFault_Handler    PROC
    EXPORT  HardFault_Handler
    LDR     R3, =fd_code_stack_base     ; r3 = &fd_code_stack_base
    LDR     R1, [R3]                    ; r1 = fd_code_stack_base
    LDR     R3, =fd_code_stack_full     ; r3 = &fd_code_stack_full
    LDR     R2, [R3]                    ; r2 = fd_code_stack_full

    TST     LR, #4                      ; use exc_return value get sp value
    ITE     EQ
    MRSEQ   R0, MSP                     ; lr & 0x04 == 1, r0 = sp = msp
    MRSNE   R0, PSP                     ; lr & 0x04 == 0, r0 = sp = psp

    CMP     R0, R1                      ; compare sp and stack base addr
    BLT     stack_invalid               ; sp < stack_base_addr, sp is invalid
    CMP     R0, R2                      ; compare sp and stack full addr
    BGT     stack_invalid               ; sp > stack_base_addr, sp is invalid

    PUSH    {R4 - R11}                  ; sp value is in stack range, push r4 - r11 to stack

    TST     LR, #4                      ; update sp value to r0
    ITE     EQ
    MRSEQ   R0, MSP                     ; lr & 0x04 == 1, r0 = sp = msp
    MRSNE   R0, PSP                     ; lr & 0x04 == 0, r0 = sp = psp
stack_invalid
    MOV     R1, LR                      ; now, r0 = sp, r1 = lr
    BL     fault_dump_handler           ; jump to fault_dump_handler
    ENDP
    END
