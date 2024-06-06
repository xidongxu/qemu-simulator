/**
  ******************************************************************************
  * @file    fault-hal.c
  * @author  xidongxu
  * @brief   This file contains all the function prototypes for the fault-hal.c
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */
#include "fault-dump.h"

void fault_dump_exc_return(unsigned int exc_return) {
    printf(" \r\n");
    printf(" Bit2 Return Stack Select: ");
    if (FD_CHECK_BIT(exc_return, 2)) {
        printf("[Use PSP               ].\r\n");
    } else {
        printf("[Use MSP               ].\r\n");
    }
    printf(" Bit3 Return Mode Select:  ");
    if (FD_CHECK_BIT(exc_return, 3)) {
        printf("[Use Thread Mode       ].\r\n");
    } else {
        printf("[Use Process Mode      ].\r\n");
    }
    printf(" Bit4 Stack Frame Type:    ");
    if (FD_CHECK_BIT(exc_return, 4)) {
        printf("[Use 8 World Frame     ].\r\n");
    } else {
        printf("[Use 26 World Frame    ].\r\n");
    }
    printf(" \r\n");
}

bool fault_dump_using_msp(unsigned int exc_return) {
    if (FD_CHECK_BIT(exc_return, 2)) {
        return false;
    } else {
        return true;
    }
}
