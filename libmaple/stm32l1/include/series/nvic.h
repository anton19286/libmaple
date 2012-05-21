/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/stm32l1/include/series/nvic.h
 * @brief STM32L1 Nested Vectored Interrupt Controller (NVIC) support.
 */

#ifndef _LIBMAPLE_STM32L1_NVIC_H_
#define _LIBMAPLE_STM32L1_NVIC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>

/**
 * @brief Interrupt vector table interrupt numbers.
 * @see <libmaple/scb.h>
 */
typedef enum nvic_irq_num {
    NVIC_NMI            = -14,  /**< Non-maskable interrupt */
    NVIC_HARDFAULT      = -13,  /**< Hard fault (all class of fault) */
    NVIC_MEM_MANAGE     = -12,  /**< Memory management */
    NVIC_BUS_FAULT      = -11,  /**< Bus fault: prefetch fault, memory
                                     access fault. */
    NVIC_USAGE_FAULT    = -10,  /**< Usage fault: Undefined instruction or
                                     illegal state. */
    NVIC_SVC            = -5,   /**< System service call via SWI insruction */
    NVIC_DEBUG_MON      = -4,   /**< Debug monitor */
    NVIC_PEND_SVC       = -2,   /**< Pendable request for system service */
    NVIC_SYSTICK        = -1,   /**< System tick timer */
    NVIC_WWDG           = 0,    /**< Window watchdog interrupt */
    NVIC_PVD            = 1,    /**< PVD through EXTI line detection */
    NVIC_TAMPER         = 2,    /**< Tamper */
    NVIC_RTC            = 3,    /**< Real-time clock */
    NVIC_FLASH          = 4,    /**< Flash */
    NVIC_RCC            = 5,    /**< Reset and clock control */
    NVIC_EXTI0          = 6,    /**< EXTI line 0 */
    NVIC_EXTI1          = 7,    /**< EXTI line 1 */
    NVIC_EXTI2          = 8,    /**< EXTI line 2 */
    NVIC_EXTI3          = 9,    /**< EXTI line 3 */
    NVIC_EXTI4          = 10,   /**< EXTI line 4 */
    NVIC_DMA_CH1        = 11,   /**< DMA1 channel 1 */
    NVIC_DMA_CH2        = 12,   /**< DMA1 channel 2 */
    NVIC_DMA_CH3        = 13,   /**< DMA1 channel 3 */
    NVIC_DMA_CH4        = 14,   /**< DMA1 channel 4 */
    NVIC_DMA_CH5        = 15,   /**< DMA1 channel 5 */
    NVIC_DMA_CH6        = 16,   /**< DMA1 channel 6 */
    NVIC_DMA_CH7        = 17,   /**< DMA1 channel 7 */
    NVIC_ADC_1          = 18,   /**< ADC1 */
    NVIC_USB_HP         = 19,   /**< USB high priority */
    NVIC_USB_LP_CAN_RX0 = 20,   /**< USB low priority */
    NVIC_DAC            = 21,   /**< DAC */
    NVIC_COMP           = 22,   /**< COMP */
    NVIC_EXTI_9_5       = 23,   /**< EXTI line [9:5] */
    NVIC_LCD            = 24, /**< LCD */
    NVIC_TIMER9         = 25, /**< Timer 9 */
    NVIC_TIMER10        = 26, /**< Timer 10 */
    NVIC_TIMER11        = 27,   /**< Timer 11 */
    NVIC_TIMER2         = 28,   /**< Timer 2 */
    NVIC_TIMER3         = 29,   /**< Timer 3 */
    NVIC_TIMER4         = 30,   /**< Timer 4 */
    NVIC_I2C1_EV        = 31,   /**< I2C1 event */
    NVIC_I2C1_ER        = 32,   /**< I2C1 error */
    NVIC_I2C2_EV        = 33,   /**< I2C2 event */
    NVIC_I2C2_ER        = 34,   /**< I2C2 error */
    NVIC_SPI1           = 35,   /**< SPI1 */
    NVIC_SPI2           = 36,   /**< SPI2 */
    NVIC_USART1         = 37,   /**< USART1 */
    NVIC_USART2         = 38,   /**< USART2 */
    NVIC_USART3         = 39,   /**< USART3 */
    NVIC_EXTI_15_10     = 40,   /**< EXTI line [15:10] */
    NVIC_RTCALARM       = 41,   /**< RTC alarm through EXTI line */
    NVIC_USBWAKEUP      = 42,   /**< USB wakeup from suspend through
                                     EXTI line */
    NVIC_TIMER6         = 43,   /**< Timer 6 */
    NVIC_TIMER7         = 44,   /**< Timer 7 */


    NVIC_TIMER1_UP_TIMER10 = 45,
    NVIC_TIMER8_UP_TIMER13 = 46,
    NVIC_TIMER1_CC      = 47,
    NVIC_TIMER8_CC      = 48,
    NVIC_TIMER1_TRG_COM_TIMER11 = 49,
    NVIC_TIMER8_TRG_COM_TIMER14 = 50,
    NVIC_TIMER1_BRK_TIMER9 = 51,
    NVIC_TIMER8_BRK_TIMER12 = 52,
    NVIC_TIMER5         = 53
} nvic_irq_num;

static inline void nvic_irq_disable_all(void) {
    /* Note: This only works up to XL density.  The fix for
     * connectivity line is:
     *
     *     NVIC_BASE->ICER[2] = 0xF;
     *
     * We don't support connectivity line devices (yet), so leave it
     * alone for now.
     */
    NVIC_BASE->ICER[0] = 0xFFFFFFFF;
    NVIC_BASE->ICER[1] = 0xFFFFFFFF;
}

#ifdef __cplusplus
}
#endif

#endif
