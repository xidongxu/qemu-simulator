;*******************************************************************************
;* @file      fault_gcc.s
;* @author    xidongxu
;* @brief     Arm Cortex-M33 Devices for MDK based toolchains. 
;*******************************************************************************
;* @attention
;*
;*
;*
;*******************************************************************************


    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    IMPORT fd_main_stack_base
    IMPORT fd_main_stack_full
    IMPORT fault_dump_handler
HardFault_Handler    PROC
    EXPORT  HardFault_Handler
    CPSID   i                           ; disable interrupts
    LDR     R3, =fd_main_stack_base     ; r3 = &fd_main_stack_base
    LDR     R1, [R3]                    ; r1 = fd_main_stack_base
    LDR     R3, =fd_main_stack_full     ; r3 = &fd_main_stack_full
    LDR     R2, [R3]                    ; r2 = fd_main_stack_full

    TST     LR, #4                      ; use exc_return value get sp value
    BNE     stack_use_psp               ; if (sp != msp), jump to stack_use_psp
    
    MRS     R0, MSP                     ; else (sp == msp), r0 = sp = msp
    CMP     R0, R1                      ; compare msp and stack base addr
    BLT     stack_invalid               ; msp < stack_base_addr, msp is invalid
    CMP     R0, R2                      ; compare msp and stack full addr
    BGT     stack_invalid               ; msp > stack_base_addr, msp is invalid

    PUSH    {R4 - R11}                  ; stack value is normal, push {r4 - r11} to stack
    MRS     R0, MSP                     ; refresh r0 = sp = msp
    B       stack_checked

stack_use_psp
    MRS     R0, PSP                     ; lr & 0x04 == 0, r0 = sp = psp
    MRS     R1, PSPLIM                  ; r1 = psplim
    CMP     R0, R1                      ; compare psp and psplim
    BLT     stack_invalid               ; psp < psplim, psp is invalid

    STMDB   R0!, {R4 - R11}             ; sp using psp, use stmdb push {r4 - r11} to stack
    B       stack_checked

stack_invalid
    NOP                                 ; stack value is invalid, not to process temporary
stack_checked
    MOV     R1, LR                      ; now, r0 = sp, r1 = lr
    DSB                                 ; wait for memory access to complete 
    CPSIE   i                           ; enable interrupts 
    BL     fault_dump_handler           ; jump to fault_dump_handler
    ENDP
    END
