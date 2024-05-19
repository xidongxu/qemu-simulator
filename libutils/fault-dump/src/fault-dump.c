/**
  ******************************************************************************
  * @file    fault-dump.c
  * @author  xidongxu
  * @brief   This file contains all the function prototypes for the fault-dump.c
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
#include "fault-dump.h"

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

/* stach growth direction */
#if FD_STACK_GROWTH_DOWNWARD
/*
 *****************************************************
 *                                                   *
 *                   Stack Start        0x200008F0   *
 *           ┌──────┬───────────┬─────► Stack Full   *
 *           │      │ $$$$,$$$$ │                    *
 *           │      │ $$$$,$$$$ │                    *
 *           │      │ $$$$,$$$$ │       0x200007F0   *
 *           │      ├───────────┼─────► Stack Point  *
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
#define FD_STACK_START                      FD_CODE_STACK_FULL
#define FD_STACK_CHECKIT(point, start)      if (((point) == NULL) || ((point) > (start)))
#define FD_STACK_FOREACH(point, start)      for ((sp) = (point); (((sp) != NULL) && ((sp) <= (start))); (sp)++)
#define FD_STACK_READVAL(point)             (*(unsigned int*)((point)++))
#else
/*
 *****************************************************
 *                                                   *
 *                                      0x200008F0   *
 *           ┌──────┬───────────┬─────► Stack Full   *
 *           │      │           │                    *
 *           │      │           │                    *
 *           │      │     ▲     │                    *
 *           │      │     │     │                    *
 *           │      │     │     │                    *
 *           ▼      │           │                    *
 *       Stack Size │ Grow Dir  │                    *
 *           ▲      │           │       0x200001F0   *
 *           │      ├───────────┼─────► Stack Point  *
 *           │      │ $$$$,$$$$ │                    *
 *           │      │ $$$$,$$$$ │                    *
 *           │      │ $$$$,$$$$ │       0x200000F0   *
 *           └──────┴───────────┴─────► Stack Base   *
 *                   Stack Start                     *
 *                                                   *
 *****************************************************
 */
#define FD_STACK_START                      FD_CODE_STACK_BASE
#define FD_STACK_CHECKIT(point, start)      if (((point) == NULL) || ((point) < (start)))
#define FD_STACK_FOREACH(point, start)      for ((sp) = (point); (((sp) != NULL) && ((sp) >= (start))); (sp)--)
#define FD_STACK_READVAL(point)             (*(unsigned int*)((point)--))
#endif

/* stack segment information */
volatile unsigned int fd_main_stack_base = 0;
volatile unsigned int fd_main_stack_full = 0;

void fault_dump_init(void) {
    fd_main_stack_base = FD_CODE_STACK_BASE;
    fd_main_stack_full = FD_CODE_STACK_FULL;
    printf("Code Stack:[%08X - %08X], size:%d\r\n",
    FD_CODE_STACK_BASE, FD_CODE_STACK_FULL, FD_CODE_STACK_SIZE);
    printf("Code Text :[%08X - %08X], size:%d\r\n",
    FD_CODE_TEXT_BASE,  FD_CODE_TEXT_ENDS,  FD_CODE_TEXT_SIZE );
    printf("Code Stack Growth Downward:%d\r\n", 
    FD_STACK_GROWTH_DOWNWARD);
}

static unsigned int fault_dump_opcode(unsigned int pc) {
    uint16_t value[2] = {0};
    unsigned int opcode = 0;
    for (int i = 0; i < (sizeof(value) / sizeof(uint16_t)); i++) {
        value[i] = *(uint16_t*)(pc + i * sizeof(uint16_t));
    }
    opcode = ((unsigned int)value[1] << 0x10) |
             ((unsigned int)value[0] << 0x00);
    return opcode;
}

static bool opcode_is_bl_or_blx(unsigned int ins) {
#define FD_BL_OPCODE_MASK   (0xF800)
#define FD_BL_OPCODE_BL     (0xF000)
#define FD_BL_OPCODE_BLX    (0xF800)
    uint16_t opcode1 = (((ins >> 0x00) & 0xFFFF) & FD_BL_OPCODE_MASK);
    uint16_t opcode2 = (((ins >> 0x10) & 0xFFFF) & FD_BL_OPCODE_MASK);
    if ((opcode1 == FD_BL_OPCODE_BL) || (opcode1 == FD_BL_OPCODE_BLX)) {
        return true;
    }
    if ((opcode2 == FD_BL_OPCODE_BL) || (opcode2 == FD_BL_OPCODE_BLX)) {
        return true;
    }
    return false;
}

static void dump_exc_return(unsigned int exc_return) {
    printf(" EXE_RETURN: 0x%08X \r\n", exc_return);
#if FD_DUMP_EXC_RETURN_VALUE
    extern void fault_dump_exc_return(unsigned int exc_return);
    fault_dump_exc_return(exc_return);
#endif
}

void fault_dump_handler(unsigned int *stack, unsigned int linker) {
    int count = 0, index = 0;
    unsigned int *point = stack;
    static stack_frame_t frame = {0};
    static unsigned int buffer[FD_STACK_DUMP_DEPTH_MAX] = {0};
    // Record current register information.
    frame.manual.r4  = FD_STACK_READVAL(point);
    frame.manual.r5  = FD_STACK_READVAL(point);
    frame.manual.r6  = FD_STACK_READVAL(point);
    frame.manual.r7  = FD_STACK_READVAL(point);
    frame.manual.r8  = FD_STACK_READVAL(point);
    frame.manual.r9  = FD_STACK_READVAL(point);
    frame.manual.r10 = FD_STACK_READVAL(point);
    frame.manual.r11 = FD_STACK_READVAL(point);
    frame.except.r0  = FD_STACK_READVAL(point);
    frame.except.r1  = FD_STACK_READVAL(point);
    frame.except.r2  = FD_STACK_READVAL(point);
    frame.except.r3  = FD_STACK_READVAL(point);
    frame.except.r12 = FD_STACK_READVAL(point);
    frame.except.lr  = FD_STACK_READVAL(point);
    frame.except.pc  = FD_STACK_READVAL(point);
    frame.except.psr = FD_STACK_READVAL(point);
    // Print current register information.
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
    printf("\r\n");
    dump_exc_return(linker);
    // Get callstack information.
    index = (sizeof(stack_frame_t) / sizeof(unsigned int));
    count = fault_dump_callstack(buffer, FD_STACK_DUMP_DEPTH_MAX, 
                                (unsigned int *)&stack[index], 
                                (unsigned int *)FD_STACK_START);
    // Print stack information.
    printf(" Stack Call: ");
    printf("%08X ", (unsigned int)frame.except.pc);
    for (index = 0; index < count; index++) {
        printf("%08X ", buffer[index]);
    }
    printf("\r\n");
    while (1);
}

int fault_dump_callstack(unsigned int *buffer, size_t size, unsigned int *stack_point, unsigned int *stack_start) {
    int count = 0;
    unsigned int pc = 0, op = 0, *sp = NULL;
    if ((buffer == NULL) || (size <= 0)) {
        return -FD_EEMPTY;
    }
    FD_STACK_CHECKIT(stack_point, stack_start) {
        return -FD_EINVAL;
    }
    FD_STACK_FOREACH(stack_point, stack_start) {
        // Read stack[x] value to pc.
        pc = *(unsigned int *)sp;
        // PC must be in the code segment.
        if ((pc < FD_CODE_TEXT_BASE) || (pc > FD_CODE_TEXT_ENDS)) {
            continue;
        }
        // The thumb instruction must be an odd number.
        if ((pc % 2) == 0) {
            continue;
        }
        // Fix thumb instruction set.
        pc = pc - 1;
        // Calculate the address of the instruction being executed before pushing on the stack.
        pc = pc - sizeof(unsigned int);
        // The thumb instruction is at least 2-byte aligned.
        if ((pc & 0x1) != 0) {
            continue;
        }
        // Read the instruction at the PC address.
        op = fault_dump_opcode(pc);
        // Only BL or BLX opcode need to be recorded.
        if (!opcode_is_bl_or_blx(op)) {
            continue;
        }
        // storage this address.
        buffer[count] = pc;
        count = count + 1;
        if (count >= size) {
            break;
        }
    }
    return count;
}

unsigned int fault_dump_bm_stack_point(void) {
    return __get_MSP();
}

unsigned int fault_dump_bm_stack_start(void) {
    return FD_STACK_START;
}
