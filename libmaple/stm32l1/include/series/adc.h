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
 * @file stm32l1/include/series/adc.h
 * @author jbaker0428
 * @brief STM32L1 ADC header.
 */

#ifndef _LIBMAPLE_STM32L1_ADC_H_
#define _LIBMAPLE_STM32L1_ADC_H_

#include <libmaple/rcc.h>       /* For the prescalers */

#ifdef __cplusplus
extern "C"{
#endif

extern const adc_dev *ADC1;

/*
 * Register map base pointers
 */

/** ADC1 register map base pointer. */
#define ADC1_BASE                       ((struct adc_reg_map*)0x40012400)

/*
 * Register bit definitions
 */

/* Control register 2 */
#define ADC_CR2_ADON_BIT                0
#define ADC_CR2_CONT_BIT                1
#define ADC_CR2_DMA_BIT                 8
#define ADC_CR2_DDS_BIT                 9
#define ADC_CR2_EOCS_BIT                10
#define ADC_CR2_ALIGN_BIT               11
#define ADC_CR2_JSWSTART_BIT            22
#define ADC_CR2_SWSTART_BIT             30

#define ADC_CR2_ADON                    BIT(ADC_CR2_ADON_BIT)
#define ADC_CR2_CONT                    BIT(ADC_CR2_CONT_BIT)
#define ADC_CR2_DELS					(0x7 << 4)
#define ADC_CR2_DMA                     BIT(ADC_CR2_DMA_BIT)
#define ADC_CR2_DDS                     BIT(ADC_CR2_DDS_BIT)
#define ADC_CR2_EOCS                    BIT(ADC_CR2_EOCS_BIT)
#define ADC_CR2_ALIGN                   BIT(ADC_CR2_ALIGN_BIT)
#define ADC_CR2_JEXTSEL                 (0xF << 16)
#define ADC_CR2_JEXTEN                  (0x3 << 20)
#define ADC_CR2_JSWSTART                BIT(ADC_CR2_JSWSTART_BIT)
#define ADC_CR2_EXTSEL                  (0xF << 24)
#define ADC_CR2_EXTEN                   (0x3 << 28)
#define ADC_CR2_SWSTART                 BIT(ADC_CR2_SWSTART_BIT)

/* Sample time register 1 */

#define ADC_SMPR1_SMP25                 (0x7 << 15)
#define ADC_SMPR1_SMP24                 (0x7 << 12)
#define ADC_SMPR1_SMP23                 (0x7 << 9)
#define ADC_SMPR1_SMP22                 (0x7 << 6)
#define ADC_SMPR1_SMP21                 (0x7 << 3)
#define ADC_SMPR1_SMP20                 0x7

/* Sample time register 2 */

#define ADC_SMPR2_SMP19                  (0x7 << 27)
#define ADC_SMPR2_SMP18                  (0x7 << 24)
#define ADC_SMPR2_SMP17                  (0x7 << 21)
#define ADC_SMPR2_SMP16                  (0x7 << 18)
#define ADC_SMPR2_SMP15                  (0x7 << 15)
#define ADC_SMPR2_SMP14                  (0x7 << 12)
#define ADC_SMPR2_SMP13                  (0x7 << 9)
#define ADC_SMPR2_SMP12                  (0x7 << 6)
#define ADC_SMPR2_SMP11                  (0x7 << 3)
#define ADC_SMPR2_SMP10                  0x7

/* Sample time register 3 */

#define ADC_SMPR3_SMP9                  (0x7 << 27)
#define ADC_SMPR3_SMP8                  (0x7 << 24)
#define ADC_SMPR3_SMP7                  (0x7 << 21)
#define ADC_SMPR3_SMP6                  (0x7 << 18)
#define ADC_SMPR3_SMP5                  (0x7 << 15)
#define ADC_SMPR3_SMP4                  (0x7 << 12)
#define ADC_SMPR3_SMP3                  (0x7 << 9)
#define ADC_SMPR3_SMP2                  (0x7 << 6)
#define ADC_SMPR3_SMP1                  (0x7 << 3)
#define ADC_SMPR3_SMP0                  0x7

/* Regular sequence register 1 */

#define ADC_SQR1_L                      (0x1F << 20)
#define ADC_SQR1_SQ27                   (0x1F << 10)
#define ADC_SQR1_SQ26                   (0x1F << 5)
#define ADC_SQR1_SQ25                   0x1F

/* Regular sequence register 2 */

#define ADC_SQR2_SQ24                   (0x1F << 25)
#define ADC_SQR2_SQ23                   (0x1F << 20)
#define ADC_SQR2_SQ22                   (0x1F << 16)
#define ADC_SQR2_SQ21                   (0x1F << 10)
#define ADC_SQR2_SQ20                   (0x1F << 5)
#define ADC_SQR2_SQ19                   0x1F

/* Regular sequence register 3 */

#define ADC_SQR3_SQ18                   (0x1F << 25)
#define ADC_SQR3_SQ17                   (0x1F << 20)
#define ADC_SQR3_SQ16                   (0x1F << 16)
#define ADC_SQR3_SQ15                   (0x1F << 10)
#define ADC_SQR3_SQ14                   (0x1F << 5)
#define ADC_SQR3_SQ13                    0x1F

/* Regular sequence register 4 */

#define ADC_SQR4_SQ12                   (0x1F << 25)
#define ADC_SQR4_SQ11                   (0x1F << 20)
#define ADC_SQR4_SQ10                   (0x1F << 16)
#define ADC_SQR4_SQ9                    (0x1F << 10)
#define ADC_SQR4_SQ8                    (0x1F << 5)
#define ADC_SQR4_SQ7                    0x1F

/* Regular sequence register 5 */

#define ADC_SQR5_SQ6                    (0x1F << 25)
#define ADC_SQR5_SQ5                    (0x1F << 20)
#define ADC_SQR5_SQ4                    (0x1F << 16)
#define ADC_SQR5_SQ3                    (0x1F << 10)
#define ADC_SQR5_SQ2                    (0x1F << 5)
#define ADC_SQR5_SQ1                    0x1F

/* Common status register */

#define ADC_CSR_AWD1_BIT                0
#define ADC_CSR_EOC1_BIT                1
#define ADC_CSR_JEOC1_BIT               2
#define ADC_CSR_JSTRT1_BIT              3
#define ADC_CSR_STRT1_BIT               4
#define ADC_CSR_OVR1_BIT                5
#define ADC_CSR_ADONS1_BIT              6

#define ADC_CSR_AWD1                    BIT(ADC_CSR_AWD1_BIT)
#define ADC_CSR_EOC1                    BIT(ADC_CSR_EOC1_BIT)
#define ADC_CSR_JEOC1                   BIT(ADC_CSR_JEOC1_BIT)
#define ADC_CSR_JSTRT1                  BIT(ADC_CSR_JSTRT1_BIT)
#define ADC_CSR_STRT1                   BIT(ADC_CSR_STRT1_BIT)
#define ADC_CSR_OVR1                    BIT(ADC_CSR_OVR1_BIT)
#define ADC_CSR_ADONS1                  BIT(ADC_CSR_ADONS1_BIT)

/* Common control register */
#define ADC_CCR_TSVREFE_BIT             23

// Do not shift 0x3 into the prescaler field, it is a reserved value
#define ADC_CCR_ADCPRE_DIV1             (0x0 << 16)
#define ADC_CCR_ADCPRE_DIV2             (0x1 << 16)
#define ADC_CCR_ADCPRE_DIV4             (0x2 << 16)
#define ADC_CCR_TSVREFE                 BIT(ADC_CCR_TSVREFE_BIT)

void adc_init(const adc_dev *dev);

/**
 * @brief External event selector for regular group conversion.
 * @see adc_set_extsel
 */
typedef enum adc_extsel_event {
    ADC_ADC12_TIM9_CC2  = (0 << 24), /**< ADC: Timer 9 CC2 event */
    ADC_ADC12_TIM9_TRGO = (1 << 24), /**< ADC: Timer 9 TRGO event */
    ADC_ADC12_TIM2_CC3  = (2 << 24), /**< ADC: Timer 2 CC3 event */
    ADC_ADC12_TIM2_CC2  = (3 << 24), /**< ADC: Timer 2 CC2 event */
    ADC_ADC12_TIM4_CC4  = (4 << 24), /**< ADC: Timer 4 CC4 event */
    ADC_ADC12_TIM2_TRGO = (5 << 24), /**< ADC: Timer 2 TRGO event */
    ADC_ADC12_TIM3_CC1  = (6 << 24), /**< ADC: Timer 3 CC1 event */
    ADC_ADC12_TIM3_CC3  = (7 << 24), /**< ADC: Timer 3 CC3 event */
    ADC_ADC12_TIM4_TRGO = (8 << 24), /**< ADC: Timer 4 TRGO event */
    ADC_ADC12_TIM6_TRGO = (9 << 24), /**< ADC: Timer 6 TRGO event */
    ADC_ADC12_EXTI11    = (0xF << 24), /**< ADC: EXTI 11 event */
} adc_extsel_event;

void adc_set_extsel(const adc_dev *dev, adc_extsel_event event);
void adc_foreach(void (*fn)(const adc_dev*));

/**
 * @brief ADC sample times, in ADC clock cycles
 *
 * These control the amount of time spent sampling the input voltage.
 */
typedef enum {
    ADC_SMPR_1_5,               /**< 1.5 ADC cycles */
    ADC_SMPR_7_5,               /**< 7.5 ADC cycles */
    ADC_SMPR_13_5,              /**< 13.5 ADC cycles */
    ADC_SMPR_28_5,              /**< 28.5 ADC cycles */
    ADC_SMPR_41_5,              /**< 41.5 ADC cycles */
    ADC_SMPR_55_5,              /**< 55.5 ADC cycles */
    ADC_SMPR_71_5,              /**< 71.5 ADC cycles */
    ADC_SMPR_239_5              /**< 239.5 ADC cycles */
} adc_smp_rate;

/**
 * @brief STM32F1 ADC prescalers, as divisors of PCLK2.
 */
typedef enum adc_prescaler {
    ADC_PRE_PCLK2_DIV_2 = RCC_ADCPRE_PCLK_DIV_2, /** PCLK2 divided by 2 */
    ADC_PRE_PCLK2_DIV_4 = RCC_ADCPRE_PCLK_DIV_4, /** PCLK2 divided by 4 */
    ADC_PRE_PCLK2_DIV_6 = RCC_ADCPRE_PCLK_DIV_6, /** PCLK2 divided by 6 */
    ADC_PRE_PCLK2_DIV_8 = RCC_ADCPRE_PCLK_DIV_8, /** PCLK2 divided by 8 */
} adc_prescaler;


void adc_set_sample_rate(const adc_dev *dev, adc_smp_rate smp_rate);
void adc_calibrate(const adc_dev *dev);
uint16 adc_read(const adc_dev *dev, uint8 channel);

/**
 * @brief Set external trigger conversion mode event for regular channels
 * @param dev    ADC device
 * @param enable If 1, conversion on external events is enabled; if 0,
 *               disabled.
 */
static inline void adc_set_exttrig(const adc_dev *dev, uint8 enable) {
//???    *bb_perip(&dev->regs->CR2, ADC_CR2_EXTTRIG_BIT) = !!enable;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif
