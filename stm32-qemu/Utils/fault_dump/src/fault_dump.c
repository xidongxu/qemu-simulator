/**
  ******************************************************************************
  * @file    Fault.c
  * @brief   This file provides code for the FaultTrace.
  *
  ******************************************************************************
	*
	*
	*
  *
  ******************************************************************************
  */
#include "fault_dump.h"

void fault_dump_handler(uint32_t *stack, uint32_t link) 
{
		fault_stack_frame_t frame = { 0 };
		uint32_t currents_cfsr = 0;
		uint32_t busfault_addr = 0;
		uint32_t memfault_addr = 0;
	
		busfault_addr = SCB->BFAR;
		memfault_addr = SCB->MMFAR;
		currents_cfsr = SCB->CFSR;

		frame.r0  = stack[0];
		frame.r1  = stack[1];
		frame.r2  = stack[2];
		frame.r3  = stack[3];
		frame.r12 = stack[4];
		frame.lr  = stack[5];
		frame.pc  = stack[6];
		frame.psr = stack[7];
	
		printf("\r\n===== HardFault =====\r\n");
		printf(" Stack Frame \r\n");
		printf(" R0   = 0x%08X \r\n", frame.r0);
		printf(" R1   = 0x%08X \r\n", frame.r1);
		printf(" R2   = 0x%08X \r\n", frame.r2);
		printf(" R3   = 0x%08X \r\n", frame.r3);
		printf(" R12  = 0x%08X \r\n", frame.r12);
		printf(" LR   = 0x%08X \r\n", frame.lr);
		printf(" PC   = 0x%08X \r\n", frame.pc);
		printf(" PSR  = 0x%08X \r\n", frame.psr);
		printf(" FSR/FAR \r\n");
		printf(" CFSR = 0x%08X \r\n", currents_cfsr);
		printf(" HFSR = 0x%08X \r\n", SCB->HFSR);
		printf(" DFSR = 0x%08X \r\n", SCB->DFSR);
		printf(" AFSR = 0x%08X \r\n", SCB->AFSR);
		if(currents_cfsr & 0x0080) 
		{
				printf(" MMFAR= 0x%08X \r\n", memfault_addr);
		}
		if(currents_cfsr & 0x8000) 
		{
				printf(" BFAR = 0x%08X \r\n", busfault_addr);
		}
		printf(" Misc \r\n");
		printf(" LR/EXE_RETURN = 0x%08X \r\n", link);
		printf(" STACK \r\n");
		int position = (sizeof(fault_stack_frame_t) / sizeof(uint32_t));
		for (int iter = position; iter < (32 + position); iter++) {
				printf("%08X ", (uint32_t)(stack[iter]));
		}
		printf("\r\n");
		while(1);
}

void fault_dump_handler_fpu(uint32_t *stack, uint32_t link) 
{
		fault_stack_frame_fpu_t frame = { 0 };
		uint32_t currents_cfsr = 0;
		uint32_t busfault_addr = 0;
		uint32_t memfault_addr = 0;
	
		busfault_addr = SCB->BFAR;
		memfault_addr = SCB->MMFAR;
		currents_cfsr = SCB->CFSR;

		frame.r0    = stack[ 0];
		frame.r1    = stack[ 1];
		frame.r2    = stack[ 2];
		frame.r3    = stack[ 3];
		frame.r12   = stack[ 4];
		frame.lr    = stack[ 5];
		frame.pc    = stack[ 6];
		frame.psr   = stack[ 7];
		frame.S0    = stack[ 8];
		frame.S1    = stack[ 9];
		frame.S2    = stack[10];
		frame.S3    = stack[11];
		frame.S4    = stack[12];
		frame.S5    = stack[13];
		frame.S6    = stack[14];
		frame.S7    = stack[15];
		frame.S8    = stack[16];
		frame.S9    = stack[17];
		frame.S10   = stack[18];
		frame.S11   = stack[19];
		frame.S12   = stack[20];
		frame.S13   = stack[21];
		frame.S14   = stack[22];
		frame.S15   = stack[23];
		frame.FPSCR = stack[24];
		frame.NONE  = stack[25];
		
		printf("\r\n===== HardFault =====\r\n");
		printf(" Stack Frame \r\n");
		printf(" R0   = 0x%08X \r\n", frame.r0);
		printf(" R1   = 0x%08X \r\n", frame.r1);
		printf(" R2   = 0x%08X \r\n", frame.r2);
		printf(" R3   = 0x%08X \r\n", frame.r3);
		printf(" R12  = 0x%08X \r\n", frame.r12);
		printf(" LR   = 0x%08X \r\n", frame.lr);
		printf(" PC   = 0x%08X \r\n", frame.pc);
		printf(" PSR  = 0x%08X \r\n", frame.psr);
		printf(" FSR/FAR \r\n");
		printf(" CFSR = 0x%08X \r\n", currents_cfsr);
		printf(" HFSR = 0x%08X \r\n", SCB->HFSR);
		printf(" DFSR = 0x%08X \r\n", SCB->DFSR);
		printf(" AFSR = 0x%08X \r\n", SCB->AFSR);
		if(currents_cfsr & 0x0080) 
		{
				printf(" MMFAR= 0x%08X \r\n", memfault_addr);
		}
		if(currents_cfsr & 0x8000) 
		{
				printf(" BFAR = 0x%08X \r\n", busfault_addr);
		}
		printf(" Misc \r\n");
		printf(" LR/EXE_RETURN = 0x%08X \r\n", link);
		printf(" STACK \r\n");
		int position = (sizeof(fault_stack_frame_fpu_t) / sizeof(uint32_t));
		for (int iter = position; iter < (32 + position); iter++) {
				printf("%08X ", (uint32_t)(stack[iter]));
		}
		printf("\r\n");
		while(1);
}
