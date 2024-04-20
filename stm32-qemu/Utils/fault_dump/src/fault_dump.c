/**
  ******************************************************************************
  * @file    Fault_Dump.c
  * @brief   This file provides code for the FaultTrace.
  *
  ******************************************************************************
	*
	*
	*
  ******************************************************************************
  */
#include "fault_dump.h"

static volatile unsigned int code_stack_start  = 0;
static volatile unsigned int code_stack_length = 0;
static volatile unsigned int code_text_start   = 0;
static volatile unsigned int code_text_length  = 0;

#if defined(__CC_ARM)
extern unsigned int STACK$$Base;
extern unsigned int STACK$$Length;
extern unsigned int Image$$ER_IROM1$$Base;
extern unsigned int Image$$ER_IROM1$$Length;
#define FD_CODE_STACK_START  (unsigned int)&STACK$$Base
#define FD_CODE_STACK_LENGTH (unsigned int)&STACK$$Length
#define FD_CODE_TEXT_START   (unsigned int)&Image$$ER_IROM1$$Base
#define FD_CODE_TEXT_LENGTH  (unsigned int)&Image$$ER_IROM1$$Length
#elif defined(__GNUC__)
extern unsigned int _sstack;
extern unsigned int _estack;
extern unsigned int _stext;
extern unsigned int _etext;
#define FD_CODE_STACK_START  (unsigned int)&_sstack
#define FD_CODE_STACK_LENGTH (unsigned int)&_estack - (unsigned int)&_sstack
#define FD_CODE_TEXT_START   (unsigned int)&_stext
#define FD_CODE_TEXT_LENGTH  (unsigned int)&_etext - (unsigned int)&_stext
#else
#error "fault dump does not support current compiler."
#endif

void fault_dump_init(void) {
    code_stack_start  = FD_CODE_STACK_START;
    code_stack_length = FD_CODE_STACK_LENGTH;
    code_text_start   = FD_CODE_TEXT_START;
    code_text_length  = FD_CODE_TEXT_LENGTH;
    printf("Code Stack Start  = 0x%08X.\r\n", code_stack_start);
    printf("Code Stack Length = %d.\r\n",     code_stack_length);
    printf("Code Text  Start  = 0x%08X.\r\n", code_text_start);
    printf("Code Text  Length = %d.\r\n",     code_text_length);
}

void fault_dump_handler(uint32_t *stack, uint32_t link) {
    static stack_frame_t frame = { 0 };
    frame.manual.r4  = stack[ 0];
    frame.manual.r5  = stack[ 1];
    frame.manual.r6  = stack[ 2];
    frame.manual.r7  = stack[ 3];
    frame.manual.r8  = stack[ 4];
    frame.manual.r9  = stack[ 5];
    frame.manual.r10 = stack[ 6];
    frame.manual.r11 = stack[ 7];
    frame.except.r0  = stack[ 8];
    frame.except.r1  = stack[ 9];
    frame.except.r2  = stack[10];
    frame.except.r3  = stack[11];
    frame.except.r12 = stack[12];
    frame.except.lr  = stack[13];
    frame.except.pc  = stack[14];
    frame.except.psr = stack[15];
    for (int iter = 0; iter < 16; iter++) {
        frame.callback[iter] = stack[iter + 16];
    }
    
    printf("\r\n");
    printf(" HardFault Information Dump \r\n");
    printf(" Stack Frame \r\n");
    printf(" R0   = 0x%08X \r\n", (unsigned int)frame.except.r0);
    printf(" R1   = 0x%08X \r\n", (unsigned int)frame.except.r1);
    printf(" R2   = 0x%08X \r\n", (unsigned int)frame.except.r2);
    printf(" R3   = 0x%08X \r\n", (unsigned int)frame.except.r3);
    printf(" R4   = 0x%08X \r\n", (unsigned int)frame.manual.r4);
    printf(" R5   = 0x%08X \r\n", (unsigned int)frame.manual.r5);
    printf(" R6   = 0x%08X \r\n", (unsigned int)frame.manual.r6);
    printf(" R7   = 0x%08X \r\n", (unsigned int)frame.manual.r7);
    printf(" R8   = 0x%08X \r\n", (unsigned int)frame.manual.r8);
    printf(" R9   = 0x%08X \r\n", (unsigned int)frame.manual.r9);
    printf(" R10  = 0x%08X \r\n", (unsigned int)frame.manual.r10);
    printf(" R11  = 0x%08X \r\n", (unsigned int)frame.manual.r11);
    printf(" R12  = 0x%08X \r\n", (unsigned int)frame.except.r12);
    printf(" LR   = 0x%08X \r\n", (unsigned int)frame.except.lr);
    printf(" PC   = 0x%08X \r\n", (unsigned int)frame.except.pc);
    printf(" PSR  = 0x%08X \r\n", (unsigned int)frame.except.psr);
    printf(" EXE_RETURN = 0x%08X \r\n", (unsigned int)link);
    printf(" Call Stack \r\n");
    for (int iter = 0; iter < (sizeof(frame.callback) / sizeof(uint32_t)); iter++) {
        printf("%08X ", (unsigned int)(frame.callback[iter]));
    }
    printf("\r\n");
    while(1);
}

static uint32_t fault_dump_sp(void) {
    uint32_t control_reg;
    control_reg = __get_CONTROL();
    return (control_reg & CONTROL_SPSEL_Msk) ? __get_PSP() : __get_MSP();
}

void fault_dump_register(void) {
    uint32_t sp = fault_dump_sp();
    printf("current sp: 0x%08X.\r\n", (unsigned int)sp);
}
