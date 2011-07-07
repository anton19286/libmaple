/**
 *  @brief General STM32 specific definitions
 */

#ifndef _STM32_H_
#define _STM32_H_
#include "rcc.h"

#define HSO_FREQ_HZ 8000000UL

#ifdef MCU_STM32F100RB
#define RCC_PLLMUL RCC_PLLMUL_3
#define RCC_PLLMUL_VALUE 3
#define DELAY_US_MULTIPLIER 8
#else
#define RCC_PLLMUL RCC_PLLMUL_9
#define RCC_PLLMUL_VALUE 9
#define DELAY_US_MULTIPLIER 12
#endif

#define CLOCK_SPEED_HZ (HSO_FREQ_HZ * RCC_PLLMUL_VALUE)
#define CLOCK_SPEED_MHZ (CLOCK_SPEED_HZ / 1000000UL)

#define RCC_AHB_SYSCLK_DIV RCC_AHB_SYSCLK_DIV_1
#define RCC_APB1_HCLK_DIV RCC_APB1_HCLK_DIV_2
#define RCC_APB2_HCLK_DIV RCC_APB2_HCLK_DIV_1

#define CYCLES_PER_MICROSECOND  CLOCK_SPEED_MHZ
#define SYSTICK_RELOAD_VAL     (CLOCK_SPEED_HZ / 1000 - 1) /* takes a cycle to reload */

#define PCLK1   (CLOCK_SPEED_HZ / 2)
#define PCLK2   (CLOCK_SPEED_HZ)


#ifdef STM32_MEDIUM_DENSITY
    #define NR_INTERRUPTS 43
#else
#ifdef STM32_HIGH_DENSITY
    #define NR_INTERRUPTS 60
#else
#error "No STM32 board type defined!"
#endif
#endif

#endif

