;/**************************************************************************//**
; * @file     startup_IOTKit_CM33.s
; * @brief    CMSIS Core Device Startup File for
; *           IOTKit_CM33 Device
; * @version  V1.0.0
; * @date     14. June 2017
; ******************************************************************************/
;/* Copyright (c) 2015 - 2017 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00001000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                    ;      Top of Stack
                DCD     Reset_Handler                   ;      Reset Handler
                DCD     NMI_Handler                     ;      NMI Handler
                DCD     HardFault_Handler               ;      Hard Fault Handler
                DCD     MemManage_Handler               ;      MPU Fault Handler
                DCD     BusFault_Handler                ;      Bus Fault Handler
                DCD     UsageFault_Handler              ;      Usage Fault Handler
                DCD     SecureFault_Handler             ;      Secure Fault Handler
                DCD     0                               ;      Reserved
                DCD     0                               ;      Reserved
                DCD     0                               ;      Reserved
                DCD     SVC_Handler                     ;      SVCall Handler
                DCD     DebugMon_Handler                ;      Debug Monitor Handler
                DCD     0                               ;      Reserved
                DCD     PendSV_Handler                  ;      PendSV Handler
                DCD     SysTick_Handler                 ;      SysTick Handler

                ; Core IoT Interrupts
                DCD      NONSEC_WATCHDOG_RESET_Handler  ;   0  Non-Secure Watchdog Reset Request
                DCD      NONSEC_WATCHDOG_Handler        ;   1  Non-Secure Watchdog Interrupt
                DCD      S32K_TIMER_Handler             ;   2  S32K Timer
                DCD      TIMER0_Handler                 ;   3  Timer 0
                DCD      TIMER1_Handler                 ;   4  Timer 1
                DCD      DUALTIMER_Handler              ;   5  Dual Timer
                DCD      0                              ;   6  Reserved
                DCD      0                              ;   7  Reserved
                DCD      0                              ;   8  Reserved
                DCD      MPC_Handler                    ;   9  MPC Combined (Secure)
                DCD      PPC_Handler                    ;  10  PPC Combined (Secure)
                DCD      MSC_Handler                    ;  11  MSC Combined (Secure)
                DCD      BRIDGE_ERROR_Handler           ;  12  Bridge Error Combined Interrupt (Secure)
                DCD      0                              ;  13  Reserved
                DCD      0                              ;  14  Reserved
                DCD      0                              ;  15  Reserved
                DCD      0                              ;  16  Reserved
                DCD      0                              ;  17  Reserved
                DCD      0                              ;  18  Reserved
                DCD      0                              ;  19  Reserved
                DCD      0                              ;  20  Reserved
                DCD      0                              ;  21  Reserved
                DCD      0                              ;  22  Reserved
                DCD      0                              ;  23  Reserved
                DCD      0                              ;  24  Reserved
                DCD      0                              ;  25  Reserved
                DCD      0                              ;  26  Reserved
                DCD      0                              ;  27  Reserved
                DCD      0                              ;  28  Reserved
                DCD      0                              ;  29  Reserved
                DCD      0                              ;  30  Reserved
                DCD      0                              ;  31  Reserved

                ; External Interrupts
                DCD     UART0RX_Handler                 ;  32  UART 0 Receive Interrupt
                DCD     UART0TX_Handler                 ;  33  UART 0 Transmit Interrupt
                DCD     UART1RX_Handler                 ;  34  UART 1 Receive Interrupt
                DCD     UART1TX_Handler                 ;  35  UART 1 Transmit Interrupt
                DCD     UART2RX_Handler                 ;  36  UART 2 Receive Interrupt
                DCD     UART2TX_Handler                 ;  37  UART 2 Transmit Interrupt
                DCD     UART3RX_Handler                 ;  38  UART 3 Receive Interrupt
                DCD     UART3TX_Handler                 ;  39  UART 3 Transmit Interrupt
                DCD     UART4RX_Handler                 ;  40  UART 4 Receive Interrupt
                DCD     UART4TX_Handler                 ;  41  UART 4 Transmit Interrupt
                DCD     UART0_Handler                   ;  42  UART 0 Combined Interrupt
                DCD     UART1_Handler                   ;  43  UART 1 Combined Interrupt
                DCD     UART2_Handler                   ;  44  UART 2 Combined Interrupt
                DCD     UART3_Handler                   ;  45  UART 3 Combined Interrupt
                DCD     UART4_Handler                   ;  46  UART 4 Combined Interrupt
                DCD     UARTOVF_Handler                 ;  47  UART Overflow (0, 1, 2, 3, 4 & 5) Interrupt
                DCD     ETHERNET_Handler                ;  48  Ethernet
                DCD     I2S0_Handler                    ;  49  FPGA Audio I2S
                DCD     TSC_Handler                     ;  50  Touch Screen
                DCD     USB_Handler                     ;  51  USB
                DCD     SPI0_Handler                    ;  52  SPI ADC
                DCD     SPI1_Handler                    ;  53  SPI (Shield 0)
                DCD     SPI2_Handler                    ;  54  SPI (Shield 1)
                DCD     I2S1_Handler                    ;  55  HDMI Audio I2S
                DCD     DMA0_ERROR_Handler              ;  56  DMA #0 Error Interrupt Request
                DCD     DMA0_TC_Handler                 ;  57  DMA #0 Terminal Count Interrupt Request
                DCD     DMA0_Handler                    ;  58  DMA #0 Combined Interrupt Request
                DCD     DMA1_ERROR_Handler              ;  59  DMA #1 Error Interrupt Request
                DCD     DMA1_TC_Handler                 ;  60  DMA #1 Terminal Count Interrupt Request
                DCD     DMA1_Handler                    ;  61  DMA #1 Combined Interrupt Request
                DCD     DMA2_ERROR_Handler              ;  62  DMA #2 Error Interrupt Request
                DCD     DMA2_TC_Handler                 ;  63  DMA #2 Terminal Count Interrupt Request
                DCD     DMA2_Handler                    ;  64  DMA #2 Combined Interrupt Request
                DCD     DMA3_ERROR_Handler              ;  65  DMA #3 Error Interrupt Request
                DCD     DMA3_TC_Handler                 ;  66  DMA #3 Terminal Count Interrupt Request
                DCD     DMA3_Handler                    ;  67  DMA #3 Combined Interrupt Request
                DCD     GPIO0_Handler                   ;  68  GPIO 0 Combined Interrupt
                DCD     GPIO1_Handler                   ;  69  GPIO 1 Combined Interrupt
                DCD     GPIO2_Handler                   ;  70  GPIO 2 Combined Interrupt
                DCD     GPIO3_Handler                   ;  71  GPIO 3 Combined Interrupt
                DCD     GPIO0_0_Handler                 ;  72  GPIO 0 individual interrupt 0
                DCD     GPIO0_1_Handler                 ;  73  GPIO 0 individual interrupt 1
                DCD     GPIO0_2_Handler                 ;  74  GPIO 0 individual interrupt 2
                DCD     GPIO0_3_Handler                 ;  75  GPIO 0 individual interrupt 3
                DCD     GPIO0_4_Handler                 ;  76  GPIO 0 individual interrupt 4
                DCD     GPIO0_5_Handler                 ;  77  GPIO 0 individual interrupt 5
                DCD     GPIO0_6_Handler                 ;  78  GPIO 0 individual interrupt 6
                DCD     GPIO0_7_Handler                 ;  79  GPIO 0 individual interrupt 7
                DCD     GPIO0_8_Handler                 ;  80  GPIO 0 individual interrupt 8
                DCD     GPIO0_9_Handler                 ;  81  GPIO 0 individual interrupt 9
                DCD     GPIO0_10_Handler                ;  82  GPIO 0 individual interrupt 10
                DCD     GPIO0_11_Handler                ;  83  GPIO 0 individual interrupt 11
                DCD     GPIO0_12_Handler                ;  84  GPIO 0 individual interrupt 12
                DCD     GPIO0_13_Handler                ;  85  GPIO 0 individual interrupt 13
                DCD     GPIO0_14_Handler                ;  86  GPIO 0 individual interrupt 14
                DCD     GPIO0_15_Handler                ;  87  GPIO 0 individual interrupt 15
                DCD     GPIO1_0_Handler                 ;  88  GPIO 1 individual interrupt 0
                DCD     GPIO1_1_Handler                 ;  89  GPIO 1 individual interrupt 1
                DCD     GPIO1_2_Handler                 ;  90  GPIO 1 individual interrupt 2
                DCD     GPIO1_3_Handler                 ;  91  GPIO 1 individual interrupt 3
                DCD     GPIO1_4_Handler                 ;  92  GPIO 1 individual interrupt 4
                DCD     GPIO1_5_Handler                 ;  93  GPIO 1 individual interrupt 5
                DCD     GPIO1_6_Handler                 ;  94  GPIO 1 individual interrupt 6
                DCD     GPIO1_7_Handler                 ;  95  GPIO 1 individual interrupt 7
                DCD     GPIO1_8_Handler                 ;  96  GPIO 1 individual interrupt 8
                DCD     GPIO1_9_Handler                 ;  97  GPIO 1 individual interrupt 9
                DCD     GPIO1_10_Handler                ;  98  GPIO 1 individual interrupt 10
                DCD     GPIO1_11_Handler                ;  99  GPIO 1 individual interrupt 11
                DCD     GPIO1_12_Handler                ; 100  GPIO 1 individual interrupt 12
                DCD     GPIO1_13_Handler                ; 101  GPIO 1 individual interrupt 13
                DCD     GPIO1_14_Handler                ; 102  GPIO 1 individual interrupt 14
                DCD     GPIO1_15_Handler                ; 103  GPIO 1 individual interrupt 15
                DCD     GPIO2_0_Handler                 ; 104  GPIO 2 individual interrupt 0
                DCD     GPIO2_1_Handler                 ; 105  GPIO 2 individual interrupt 1
                DCD     GPIO2_2_Handler                 ; 106  GPIO 2 individual interrupt 2
                DCD     GPIO2_3_Handler                 ; 107  GPIO 2 individual interrupt 3
                DCD     GPIO2_4_Handler                 ; 108  GPIO 2 individual interrupt 4
                DCD     GPIO2_5_Handler                 ; 109  GPIO 2 individual interrupt 5
                DCD     GPIO2_6_Handler                 ; 110  GPIO 2 individual interrupt 6
                DCD     GPIO2_7_Handler                 ; 111  GPIO 2 individual interrupt 7
                DCD     GPIO2_8_Handler                 ; 112  GPIO 2 individual interrupt 8
                DCD     GPIO2_9_Handler                 ; 113  GPIO 2 individual interrupt 9
                DCD     GPIO2_10_Handler                ; 114  GPIO 2 individual interrupt 10
                DCD     GPIO2_11_Handler                ; 115  GPIO 2 individual interrupt 11
                DCD     GPIO2_12_Handler                ; 116  GPIO 2 individual interrupt 12
                DCD     GPIO2_13_Handler                ; 117  GPIO 2 individual interrupt 13
                DCD     GPIO2_14_Handler                ; 118  GPIO 2 individual interrupt 14
                DCD     GPIO2_15_Handler                ; 119  GPIO 2 individual interrupt 15
                DCD     GPIO3_0_Handler                 ; 120  GPIO 3 individual interrupt 0
                DCD     GPIO3_1_Handler                 ; 121  GPIO 3 individual interrupt 1
                DCD     GPIO3_2_Handler                 ; 122  GPIO 3 individual interrupt 2
                DCD     GPIO3_3_Handler                 ; 123  GPIO 3 individual interrupt 3
                DCD     UART5RX_Handler                 ; 124  UART 5 Receive Interrupt
                DCD     UART5TX_Handler                 ; 125  UART 5 Transmit Interrupt
                DCD     UART5_Handler                   ; 126  UART 5 Combined Interrupt
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SecureFault_Handler\
                PROC
                EXPORT  SecureFault_Handler       [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
; Core IoT Interrupts
                EXPORT NONSEC_WATCHDOG_RESET_Handler   [WEAK]
                EXPORT NONSEC_WATCHDOG_Handler         [WEAK]
                EXPORT S32K_TIMER_Handler              [WEAK]
                EXPORT TIMER0_Handler                  [WEAK]
                EXPORT TIMER1_Handler                  [WEAK]
                EXPORT DUALTIMER_Handler               [WEAK]
                EXPORT MPC_Handler                     [WEAK]
                EXPORT PPC_Handler                     [WEAK]
                EXPORT MSC_Handler                     [WEAK]
                EXPORT BRIDGE_ERROR_Handler            [WEAK]

; External Interrupts
                EXPORT UART0RX_Handler                 [WEAK]
                EXPORT UART0TX_Handler                 [WEAK]
                EXPORT UART1RX_Handler                 [WEAK]
                EXPORT UART1TX_Handler                 [WEAK]
                EXPORT UART2RX_Handler                 [WEAK]
                EXPORT UART2TX_Handler                 [WEAK]
                EXPORT UART3RX_Handler                 [WEAK]
                EXPORT UART3TX_Handler                 [WEAK]
                EXPORT UART4RX_Handler                 [WEAK]
                EXPORT UART4TX_Handler                 [WEAK]
                EXPORT UART0_Handler                   [WEAK]
                EXPORT UART1_Handler                   [WEAK]
                EXPORT UART2_Handler                   [WEAK]
                EXPORT UART3_Handler                   [WEAK]
                EXPORT UART4_Handler                   [WEAK]
                EXPORT UARTOVF_Handler                 [WEAK]
                EXPORT ETHERNET_Handler                [WEAK]
                EXPORT I2S0_Handler                    [WEAK]
                EXPORT TSC_Handler                     [WEAK]
                EXPORT USB_Handler                     [WEAK]
                EXPORT SPI0_Handler                    [WEAK]
                EXPORT SPI1_Handler                    [WEAK]
                EXPORT SPI2_Handler                    [WEAK]
                EXPORT I2S1_Handler                    [WEAK]
                EXPORT DMA0_ERROR_Handler              [WEAK]
                EXPORT DMA0_TC_Handler                 [WEAK]
                EXPORT DMA0_Handler                    [WEAK]
                EXPORT DMA1_ERROR_Handler              [WEAK]
                EXPORT DMA1_TC_Handler                 [WEAK]
                EXPORT DMA1_Handler                    [WEAK]
                EXPORT DMA2_ERROR_Handler              [WEAK]
                EXPORT DMA2_TC_Handler                 [WEAK]
                EXPORT DMA2_Handler                    [WEAK]
                EXPORT DMA3_ERROR_Handler              [WEAK]
                EXPORT DMA3_TC_Handler                 [WEAK]
                EXPORT DMA3_Handler                    [WEAK]
                EXPORT GPIO0_Handler                   [WEAK]
                EXPORT GPIO1_Handler                   [WEAK]
                EXPORT GPIO2_Handler                   [WEAK]
                EXPORT GPIO3_Handler                   [WEAK]
                EXPORT GPIO0_0_Handler                 [WEAK]
                EXPORT GPIO0_1_Handler                 [WEAK]
                EXPORT GPIO0_2_Handler                 [WEAK]
                EXPORT GPIO0_3_Handler                 [WEAK]
                EXPORT GPIO0_4_Handler                 [WEAK]
                EXPORT GPIO0_5_Handler                 [WEAK]
                EXPORT GPIO0_6_Handler                 [WEAK]
                EXPORT GPIO0_7_Handler                 [WEAK]
                EXPORT GPIO0_8_Handler                 [WEAK]
                EXPORT GPIO0_9_Handler                 [WEAK]
                EXPORT GPIO0_10_Handler                [WEAK]
                EXPORT GPIO0_11_Handler                [WEAK]
                EXPORT GPIO0_12_Handler                [WEAK]
                EXPORT GPIO0_13_Handler                [WEAK]
                EXPORT GPIO0_14_Handler                [WEAK]
                EXPORT GPIO0_15_Handler                [WEAK]
                EXPORT GPIO1_0_Handler                 [WEAK]
                EXPORT GPIO1_1_Handler                 [WEAK]
                EXPORT GPIO1_2_Handler                 [WEAK]
                EXPORT GPIO1_3_Handler                 [WEAK]
                EXPORT GPIO1_4_Handler                 [WEAK]
                EXPORT GPIO1_5_Handler                 [WEAK]
                EXPORT GPIO1_6_Handler                 [WEAK]
                EXPORT GPIO1_7_Handler                 [WEAK]
                EXPORT GPIO1_8_Handler                 [WEAK]
                EXPORT GPIO1_9_Handler                 [WEAK]
                EXPORT GPIO1_10_Handler                [WEAK]
                EXPORT GPIO1_11_Handler                [WEAK]
                EXPORT GPIO1_12_Handler                [WEAK]
                EXPORT GPIO1_13_Handler                [WEAK]
                EXPORT GPIO1_14_Handler                [WEAK]
                EXPORT GPIO1_15_Handler                [WEAK]
                EXPORT GPIO2_0_Handler                 [WEAK]
                EXPORT GPIO2_1_Handler                 [WEAK]
                EXPORT GPIO2_2_Handler                 [WEAK]
                EXPORT GPIO2_3_Handler                 [WEAK]
                EXPORT GPIO2_4_Handler                 [WEAK]
                EXPORT GPIO2_5_Handler                 [WEAK]
                EXPORT GPIO2_6_Handler                 [WEAK]
                EXPORT GPIO2_7_Handler                 [WEAK]
                EXPORT GPIO2_8_Handler                 [WEAK]
                EXPORT GPIO2_9_Handler                 [WEAK]
                EXPORT GPIO2_10_Handler                [WEAK]
                EXPORT GPIO2_11_Handler                [WEAK]
                EXPORT GPIO2_12_Handler                [WEAK]
                EXPORT GPIO2_13_Handler                [WEAK]
                EXPORT GPIO2_14_Handler                [WEAK]
                EXPORT GPIO2_15_Handler                [WEAK]
                EXPORT GPIO3_0_Handler                 [WEAK]
                EXPORT GPIO3_1_Handler                 [WEAK]
                EXPORT GPIO3_2_Handler                 [WEAK]
                EXPORT GPIO3_3_Handler                 [WEAK]
                EXPORT UART5RX_Handler                 [WEAK]
                EXPORT UART5TX_Handler                 [WEAK]
                EXPORT UART5_Handler                   [WEAK]

NONSEC_WATCHDOG_RESET_Handler
NONSEC_WATCHDOG_Handler
S32K_TIMER_Handler
TIMER0_Handler
TIMER1_Handler
DUALTIMER_Handler
MPC_Handler
PPC_Handler
MSC_Handler
BRIDGE_ERROR_Handler
UART0RX_Handler
UART0TX_Handler
UART1RX_Handler
UART1TX_Handler
UART2RX_Handler
UART2TX_Handler
UART3RX_Handler
UART3TX_Handler
UART4RX_Handler
UART4TX_Handler
UART0_Handler
UART1_Handler
UART2_Handler
UART3_Handler
UART4_Handler
UARTOVF_Handler
ETHERNET_Handler
I2S0_Handler
TSC_Handler
USB_Handler
SPI0_Handler
SPI1_Handler
SPI2_Handler
I2S1_Handler
DMA0_ERROR_Handler
DMA0_TC_Handler
DMA0_Handler
DMA1_ERROR_Handler
DMA1_TC_Handler
DMA1_Handler
DMA2_ERROR_Handler
DMA2_TC_Handler
DMA2_Handler
DMA3_ERROR_Handler
DMA3_TC_Handler
DMA3_Handler
GPIO0_Handler
GPIO1_Handler
GPIO2_Handler
GPIO3_Handler
GPIO0_0_Handler
GPIO0_1_Handler
GPIO0_2_Handler
GPIO0_3_Handler
GPIO0_4_Handler
GPIO0_5_Handler
GPIO0_6_Handler
GPIO0_7_Handler
GPIO0_8_Handler
GPIO0_9_Handler
GPIO0_10_Handler
GPIO0_11_Handler
GPIO0_12_Handler
GPIO0_13_Handler
GPIO0_14_Handler
GPIO0_15_Handler
GPIO1_0_Handler
GPIO1_1_Handler
GPIO1_2_Handler
GPIO1_3_Handler
GPIO1_4_Handler
GPIO1_5_Handler
GPIO1_6_Handler
GPIO1_7_Handler
GPIO1_8_Handler
GPIO1_9_Handler
GPIO1_10_Handler
GPIO1_11_Handler
GPIO1_12_Handler
GPIO1_13_Handler
GPIO1_14_Handler
GPIO1_15_Handler
GPIO2_0_Handler
GPIO2_1_Handler
GPIO2_2_Handler
GPIO2_3_Handler
GPIO2_4_Handler
GPIO2_5_Handler
GPIO2_6_Handler
GPIO2_7_Handler
GPIO2_8_Handler
GPIO2_9_Handler
GPIO2_10_Handler
GPIO2_11_Handler
GPIO2_12_Handler
GPIO2_13_Handler
GPIO2_14_Handler
GPIO2_15_Handler
GPIO3_0_Handler
GPIO3_1_Handler
GPIO3_2_Handler
GPIO3_3_Handler
UART5RX_Handler
UART5TX_Handler
UART5_Handler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
