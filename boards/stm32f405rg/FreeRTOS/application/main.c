/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  *
  *
  ******************************************************************************
  */

#include "usart.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fault-dump.h"

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>

uint8_t ucHeap[configTOTAL_HEAP_SIZE];
void SystemClock_Config(void);

#ifdef __GNUC__
int __io_putchar(int ch) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
#elif __CC_ARM
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
#elif __ICCARM__
#include <LowLevelIOInterface.h>
size_t __write(int handle, const unsigned char * buffer, size_t size) {
    if(HAL_UART_Transmit(&huart1, (uint8_t *)buffer, size, 0xFFFF) == HAL_OK) {
        return size;
    } else {
        return _LLIO_ERROR;
    }
}
#else
#error "io port does not support current compiler."
#endif

void fault_div_zero_trigger(void) {
    int a = 0, b = 0, c = 0;

    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
    c = (a + (b / c));
    printf("c = %d\r\n", c);
}

void fault_unalign_trigger(void) {
    volatile int *addr = NULL;
    volatile int value = 0;
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;

    addr = (int*)0x00;
    value = *addr;
    printf("addr:0x%02X-value:0x%08X\r\n", (int)addr, value);
    addr = (int*)0x04;
    value = *addr;
    printf("addr:0x%02X-value:0x%08X\r\n", (int)addr, value);
    addr = (int*)0x03;
    value = *addr;
    printf("addr:0x%02X-value:0x%08X\r\n", (int)addr, value);
}

void test0(void) {
    printf("this is %s.\r\n", __func__);
    // trigger a fault.
    //float a = 0.0, b = 1.1;
    //printf("this is %f.\r\n", (a + b));
    fault_unalign_trigger();
}

void test1(void) {
    printf("this is %s.\r\n", __func__);
    test0();
}

void test2(void) {
    printf("this is %s.\r\n", __func__);
    test1();
}

void test3(void) {
    printf("this is %s.\r\n", __func__);
    test2();
}

void test4(void) {
    printf("this is %s.\r\n", __func__);
    test3();
}

void test5(void) {
    printf("this is %s.\r\n", __func__);
    test4();
}

static void main_task_entry(void *parameters) {
    int counter = 0;
    while(1) {
        vTaskDelay(1000);
        printf("hello this is FreeRTOS.\r\n");
        if (counter >= 3) {
            test5();
        } else {
            counter++;
        }
    }
}

static void main_task_init(void) {
    static TaskHandle_t main_task = NULL;
    BaseType_t xReturn = pdPASS;
    xReturn = xTaskCreate(main_task_entry, "main_task", 2048, NULL, 1U, &main_task);
    if (xReturn == pdPASS) {
        vTaskStartScheduler();
    } else {
        printf("main task create failed(%d).\r\n", (int)(xReturn));
    }
}

int main(void) {
    HAL_Init();
    // SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    fault_dump_init();
    main_task_init();

    while (1) {
        printf("hello qemu.\r\n");
        HAL_Delay(1000);
    }
    return 0;
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
}
