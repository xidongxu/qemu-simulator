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

#if defined(__CC_ARM)
extern unsigned int STACK$$Base;
extern unsigned int STACK$$Length;
extern unsigned int Image$$ER_IROM1$$Base;
extern unsigned int Image$$ER_IROM1$$Length;
/* stack segment information */
#define FD_CODE_STACK_BASE    (unsigned int)&STACK$$Base
#define FD_CODE_STACK_SIZE    (unsigned int)&STACK$$Length
#define FD_CODE_STACK_FULL    (FD_CODE_STACK_BASE + FD_CODE_STACK_SIZE)
/* text segment information */
#define FD_CODE_TEXT_BASE     (unsigned int)&Image$$ER_IROM1$$Base
#define FD_CODE_TEXT_SIZE     (unsigned int)&Image$$ER_IROM1$$Length
#define FD_CODE_TEXT_ENDS     (FD_CODE_TEXT_BASE + FD_CODE_TEXT_SIZE)
#elif defined(__GNUC__)
extern unsigned int _stext;
extern unsigned int _etext;
extern unsigned int _sstack;
extern unsigned int _estack;
/* stack segment information */
#define FD_CODE_STACK_BASE    (unsigned int)&_sstack
#define FD_CODE_STACK_FULL    (unsigned int)&_estack
#define FD_CODE_STACK_SIZE    (FD_CODE_STACK_FULL - FD_CODE_STACK_BASE)
/* text segment information */
#define FD_CODE_TEXT_BASE     (unsigned int)&_stext
#define FD_CODE_TEXT_ENDS     (unsigned int)&_etext
#define FD_CODE_TEXT_SIZE     (FD_CODE_TEXT_ENDS - FD_CODE_TEXT_BASE)
#else
#error "fault dump does not support current compiler."
#endif

/*
 *****************************************************
 *                                                   *
 *                                      0x200008F0   *
 *           ┌──────┬───────────┬─────► Stack Full   *
 *           │      │ $$$$,$$$$ │                    *
 *           │      │ $$$$,$$$$ │                    *
 *           │      │ $$$$,$$$$ │       0x20000870   *
 *           │      ├───────────┼─────► Stack Used   *
 *           │      │           │                    *
 *           ▼      │ Grow Dir  │                    *
 *       Stack Size │           │                    *
 *           ▲      │     │     │                    *
 *           │      │     │     │                    *
 *           │      │     ▼     │                    *
 *           │      │           │                    *
 *           │      │           │       0x200000F0   *
 *           └──────┴───────────┴─────► Stack Base   *
 *                                                   *
 *****************************************************
 */

void fault_dump_init(void) {
    printf("Code Stack:\r\n");
    printf("base->%08X.\r\n", FD_CODE_STACK_BASE);
    printf("full->%08X.\r\n", FD_CODE_STACK_FULL);
    printf("size->%d.  \r\n", FD_CODE_STACK_SIZE);
    printf("Code Text: \r\n");
    printf("base->%08X.\r\n", FD_CODE_TEXT_BASE);
    printf("ends->%08X.\r\n", FD_CODE_TEXT_ENDS);
    printf("size->%d.  \r\n", FD_CODE_TEXT_SIZE);
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
    printf(" Stack Frame   \r\n");
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
    printf(" Call Stack    \r\n");
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
