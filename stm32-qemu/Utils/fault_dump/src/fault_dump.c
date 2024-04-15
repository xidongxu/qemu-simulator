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

void fault_dump_handler(unsigned long *stack_frame, unsigned int link_reg) 
{
		unsigned long stack_r0  = 0;
		unsigned long stack_r1  = 0;
		unsigned long stack_r2  = 0;
		unsigned long stack_r3  = 0;
		unsigned long stack_r12 = 0;
		unsigned long stack_lr  = 0;
		unsigned long stack_pc  = 0;
		unsigned long stack_psr = 0;
	
		unsigned long cur_fault_cfsr = 0;
		unsigned long bus_fault_addr = 0;
		unsigned long mem_fault_addr = 0;
	
		bus_fault_addr = SCB->BFAR;
		mem_fault_addr = SCB->MMFAR;
		cur_fault_cfsr = SCB->CFSR;

		stack_r0  = (unsigned long)stack_frame[0];
		stack_r1  = (unsigned long)stack_frame[1];
		stack_r2  = (unsigned long)stack_frame[2];
		stack_r3  = (unsigned long)stack_frame[3];
		stack_r12 = (unsigned long)stack_frame[4];
		stack_lr  = (unsigned long)stack_frame[5];
		stack_pc  = (unsigned long)stack_frame[6];
		stack_psr = (unsigned long)stack_frame[7];
	
		printf("===== HardFault =====\r\n");
		printf(" Stack Frame \r\n");
		printf(" R0   = 0x%08X \r\n", (unsigned int)stack_r0);
		printf(" R1   = 0x%08X \r\n", (unsigned int)stack_r1);
		printf(" R2   = 0x%08X \r\n", (unsigned int)stack_r2);
		printf(" R3   = 0x%08X \r\n", (unsigned int)stack_r3);
		printf(" R12  = 0x%08X \r\n", (unsigned int)stack_r12);
		printf(" LR   = 0x%08X \r\n", (unsigned int)stack_lr);
		printf(" PC   = 0x%08X \r\n", (unsigned int)stack_pc);
		printf(" PSR  = 0x%08X \r\n", (unsigned int)stack_psr);
		printf(" FSR/FAR \r\n");
		printf(" CFSR = 0x%08X \r\n", (unsigned int)cur_fault_cfsr);
		printf(" HFSR = 0x%08X \r\n", (unsigned int)SCB->HFSR);
		printf(" DFSR = 0x%08X \r\n", (unsigned int)SCB->DFSR);
		printf(" AFSR = 0x%08X \r\n", (unsigned int)SCB->AFSR);
		if(cur_fault_cfsr & 0x0080) 
		{
				printf(" MMFAR= 0x%08X \r\n", (unsigned int)mem_fault_addr);
		}
		if(cur_fault_cfsr & 0x8000) 
		{
				printf(" BFAR = 0x%08X \r\n", (unsigned int)bus_fault_addr);
		}
		printf(" Misc \r\n");
		printf(" LR/EXE_RETURN = 0x%08X \r\n", link_reg);
		while(1);
}







