;*******************************************************************************
;* File Name          : fault_mdk.s
;* Author             : xdx
;* Description        : STM32F405xx devices vector table for MDK-ARM toolchain. 
;*******************************************************************************
;* @attention
;*
;*
;*
;*******************************************************************************
    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
	IMPORT fault_dump_handler
HardFault_Handler_Proc	PROC
	EXPORT  HardFault_Handler_Proc
	TST		LR, #4
	ITE		EQ
	MRSEQ	R0, MSP
	MRSNE	R0, PSP
	MOV		R1, LR
	BL		fault_dump_handler
	ENDP
	END
