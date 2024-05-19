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
    printf(" Bit0 Except Security State: ");
    if (FD_CHECK_BIT(exc_return, 0)) {
        printf("[Use Security State    ].\r\n");
    } else {
        printf("[Use Not Security State].\r\n");
    }
    printf(" Bit2 Stack Point Select:    ");
    if (FD_CHECK_BIT(exc_return, 2)) {
        printf("[Use PSP               ].\r\n");
    } else {
        printf("[Use MSP               ].\r\n");
    }
    printf(" Bit3 Proc Mode Before IRQ:  ");
    if (FD_CHECK_BIT(exc_return, 3)) {
        printf("[Use Thread Mode       ].\r\n");
    } else {
        printf("[Use Process Mode      ].\r\n");
    }
    printf(" Bit4 Stack Frame Type:      ");
    if (FD_CHECK_BIT(exc_return, 4)) {
        printf("[Use Standard Frame    ].\r\n");
    } else {
        printf("[Use Extended Frame    ].\r\n");
    }
    printf(" Bit5 Default Call Rule:     ");
    if (FD_CHECK_BIT(exc_return, 5)) {
        printf("[Use Default Rule      ].\r\n");
    } else {
        printf("[Use Not Default Rule  ].\r\n");
    }
    printf(" Bit6 Security Stack:        ");
    if (FD_CHECK_BIT(exc_return, 6)) {
        printf("[Use Security Stack    ].\r\n");
    } else {
        printf("[Use Not Security Stack].\r\n");
    }
    printf(" \r\n");
}
