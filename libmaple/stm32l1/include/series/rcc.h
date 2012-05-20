/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file libmaple/stm32f1/rcc.h
 * @brief STM32L1 reset and clock control (RCC) header.
 */

#ifndef _LIBMAPLE_STM32F1_RCC_H_
#define _LIBMAPLE_STM32F1_RCC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple.h>

/*
 * Register map
 */

/** RCC register map type */
typedef struct rcc_reg_map {
    __io uint32 CR;             /**< Clock control register */
    __io uint32 ICSCR;          /**( Internal clock sources calibration register */
    __io uint32 CFGR;           /**< Clock configuration register */
    __io uint32 CIR;            /**< Clock interrupt register */
    __io uint32 AHBRSTR;        /**< AHB peripheral reset register */
    __io uint32 APB2RSTR;       /**< APB2 peripheral reset register */
    __io uint32 APB1RSTR;       /**< APB1 peripheral reset register */
    __io uint32 AHBENR;         /**< AHB peripheral clock enable register */
    __io uint32 APB2ENR;        /**< APB2 peripheral clock enable register */
    __io uint32 APB1ENR;        /**< APB1 peripheral clock enable register */
    __io uint32 AHBLPENR;         /**< AHB peripheral clock enable in low power mode register */
    __io uint32 APB2LPENR;        /**< APB2 peripheral clock enable in low power mode register */
    __io uint32 APB1LPENR;        /**< APB1 peripheral clock enable in low power mode register */
    __io uint32 CSR;            /**< Control/status register */
} rcc_reg_map;

/** RCC register map base pointer */
#define RCC_BASE                        ((struct rcc_reg_map*)0x40023800)

/*
 * Register bit definitions
 */

/* Clock control register */

#define RCC_CR_RTCPRE1_BIT              30
#define RCC_CR_RTCPRE0_BIT              29
#define RCC_CR_CSSON_BIT                28
#define RCC_CR_PLLRDY_BIT               25
#define RCC_CR_PLLON_BIT                24
#define RCC_CR_HSEBYP_BIT               18
#define RCC_CR_HSERDY_BIT               17
#define RCC_CR_HSEON_BIT                16
#define RCC_CR_MSIRDY_BIT               9
#define RCC_CR_MSION_BIT                8
#define RCC_CR_HSIRDY_BIT               1
#define RCC_CR_HSION_BIT                0

#define RCC_CR_PLLRDY                   BIT(RCC_CR_PLLRDY_BIT)
#define RCC_CR_PLLON                    BIT(RCC_CR_PLLON_BIT)
#define RCC_CR_CSSON                    BIT(RCC_CR_CSSON_BIT)
#define RCC_CR_HSEBYP                   BIT(RCC_CR_HSEBYP_BIT)
#define RCC_CR_HSERDY                   BIT(RCC_CR_HSERDY_BIT)
#define RCC_CR_HSEON                    BIT(RCC_CR_HSEON_BIT)
#define RCC_CR_MSIRDY                   BIT(RCC_CR_MSIRDY_BIT)
#define RCC_CR_MSION                    BIT(RCC_CR_MSION_BIT)
#define RCC_CR_HSIRDY                   BIT(RCC_CR_HSIRDY_BIT)
#define RCC_CR_HSION                    BIT(RCC_CR_HSION_BIT)

/* Internal clock sources calibration register */

#define RCC_ICSCR_HSICAL                   (0xFF)
#define RCC_ICSCR_HSITRIM                  (0x1F << 8)
#define RCC_ICSCR_MSIRANGE                 (0x7 << 13)
#define RCC_ICSCR_MSICAL                   (0xFF << 16)
#define RCC_ICSCR_MSITRIM                  (0xFF << 24)

/* Clock configuration register */

#define RCC_CFGR_PLLSRC_BIT             16

#define RCC_CFGR_MCOPRE                 (0x7 << 28)
#define RCC_CFGR_MCOSEL                 (0x7 << 24)
#define RCC_CFGR_PLLDIV                 (0x3 << 22)
#define RCC_CFGR_PLLMUL                 (0xF << 18)
#define RCC_CFGR_PLLSRC                 BIT(RCC_CFGR_PLLSRC_BIT)
#define RCC_CFGR_PPRE2                  (0x7 << 11)
#define RCC_CFGR_PPRE1                  (0x7 << 8)
#define RCC_CFGR_HPRE                   (0xF << 4)
#define RCC_CFGR_SWS                    (0x3 << 2)
#define RCC_CFGR_SW                     0x3

#define RCC_CFGR_MCOPRE_DIV_1           (0x0 << 28)
#define RCC_CFGR_MCOPRE_DIV_2           (0x1 << 28)
#define RCC_CFGR_MCOPRE_DIV_4           (0x2 << 28)
#define RCC_CFGR_MCOPRE_DIV_8           (0x3 << 28)
#define RCC_CFGR_MCOPRE_DIV_16          (0x4 << 28)

#define RCC_CFGR_MCOSEL_DISABLED        (0x0 << 24)
#define RCC_CFGR_MCOSEL_SYSCLK          (0x1 << 24)
#define RCC_CFGR_MCOSEL_HSI             (0x2 << 24)
#define RCC_CFGR_MCOSEL_MSI             (0x3 << 24)
#define RCC_CFGR_MCOSEL_HSE             (0x4 << 24)
#define RCC_CFGR_MCOSEL_PLL             (0x5 << 24)
#define RCC_CFGR_MCOSEL_LSI             (0x6 << 24)
#define RCC_CFGR_MCOSEL_LSE             (0x7 << 24)

#define RCC_CFGR_PLLDIV_DIV_2           (0x1 << 22)
#define RCC_CFGR_PLLDIV_DIV_3           (0x2 << 22)
#define RCC_CFGR_PLLDIV_DIV_4           (0x3 << 22)

#define RCC_CFGR_PLLMUL_MUL_3           (0x0 << 18)
#define RCC_CFGR_PLLMUL_MUL_4           (0x1 << 18)
#define RCC_CFGR_PLLMUL_MUL_6           (0x2 << 18)
#define RCC_CFGR_PLLMUL_MUL_8           (0x3 << 18)
#define RCC_CFGR_PLLMUL_MUL_12          (0x4 << 18)
#define RCC_CFGR_PLLMUL_MUL_16          (0x5 << 18)
#define RCC_CFGR_PLLMUL_MUL_24          (0x6 << 18)
#define RCC_CFGR_PLLMUL_MUL_32          (0x7 << 18)
#define RCC_CFGR_PLLMUL_MUL_48          (0x8 << 18)

#define RCC_CFGR_PLLSRC_HSI             0x0
#define RCC_CFGR_PLLSRC_HSE             RCC_CFGR_PLLSRC

/* Skipped: all the 0b0xx values meaning "not divided" */
#define RCC_CFGR_PPRE2_AHB_DIV_2        (0x4 << 13)
#define RCC_CFGR_PPRE2_AHB_DIV_4        (0x5 << 13)
#define RCC_CFGR_PPRE2_AHB_DIV_8        (0x6 << 13)
#define RCC_CFGR_PPRE2_AHB_DIV_16       (0x7 << 13)

/* Skipped: all the 0b0xx values meaning "not divided" */
#define RCC_CFGR_PPRE1_AHB_DIV_2        (0x4 << 10)
#define RCC_CFGR_PPRE1_AHB_DIV_4        (0x5 << 10)
#define RCC_CFGR_PPRE1_AHB_DIV_8        (0x6 << 10)
#define RCC_CFGR_PPRE1_AHB_DIV_16       (0x7 << 10)

/* Skipped: all the 0b0xxx values meaning "not divided" */
#define RCC_CFGR_HPRE_SYSCLK_DIV_2      (0x8 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV_4      (0x9 << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV_8      (0xA << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV_16     (0xB << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV_64     (0xC << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV_128    (0xD << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV_256    (0xE << 4)
#define RCC_CFGR_HPRE_SYSCLK_DIV_512    (0xF << 4)

#define RCC_CFGR_SWS_PLL                (0x3 << 2)
#define RCC_CFGR_SWS_HSE                (0x2 << 2)
#define RCC_CFGR_SWS_HSI                (0x1 << 2)
#define RCC_CFGR_SWS_MSI                (0x0 << 2)

#define RCC_CFGR_SW_PLL                 0x3
#define RCC_CFGR_SW_HSE                 0x2
#define RCC_CFGR_SW_HSI                 0x1
#define RCC_CFGR_SW_MSI                 0x0

/* Clock interrupt register */

#define RCC_CIR_CSSC_BIT                23
#define RCC_CIR_MSIRDYC_BIT             21
#define RCC_CIR_PLLRDYC_BIT             20
#define RCC_CIR_HSERDYC_BIT             19
#define RCC_CIR_HSIRDYC_BIT             18
#define RCC_CIR_LSERDYC_BIT             17
#define RCC_CIR_LSIRDYC_BIT             16
#define RCC_CIR_MSIRDYIE_BIT            13
#define RCC_CIR_PLLRDYIE_BIT            12
#define RCC_CIR_HSERDYIE_BIT            11
#define RCC_CIR_HSIRDYIE_BIT            10
#define RCC_CIR_LSERDYIE_BIT            9
#define RCC_CIR_LSIRDYIE_BIT            8
#define RCC_CIR_CSSF_BIT                7
#define RCC_CIR_MSERDYF_BIT             5
#define RCC_CIR_PLLRDYF_BIT             4
#define RCC_CIR_HSERDYF_BIT             3
#define RCC_CIR_HSIRDYF_BIT             2
#define RCC_CIR_LSERDYF_BIT             1
#define RCC_CIR_LSIRDYF_BIT             0

#define RCC_CIR_CSSC                    BIT(RCC_CIR_CSSC_BIT)
#define RCC_CIR_MSERDYC                 BIT(RCC_CIR_MSERDYC_BIT)
#define RCC_CIR_PLLRDYC                 BIT(RCC_CIR_PLLRDYC_BIT)
#define RCC_CIR_HSERDYC                 BIT(RCC_CIR_HSERDYC_BIT)
#define RCC_CIR_HSIRDYC                 BIT(RCC_CIR_HSIRDYC_BIT)
#define RCC_CIR_LSERDYC                 BIT(RCC_CIR_LSERDYC_BIT)
#define RCC_CIR_LSIRDYC                 BIT(RCC_CIR_LSIRDYC_BIT)
#define RCC_CIR_MSIRDYIE                BIT(RCC_CIR_MSIRDYIE_BIT)
#define RCC_CIR_PLLRDYIE                BIT(RCC_CIR_PLLRDYIE_BIT)
#define RCC_CIR_HSERDYIE                BIT(RCC_CIR_HSERDYIE_BIT)
#define RCC_CIR_HSIRDYIE                BIT(RCC_CIR_HSIRDYIE_BIT)
#define RCC_CIR_LSERDYIE                BIT(RCC_CIR_LSERDYIE_BIT)
#define RCC_CIR_LSIRDYIE                BIT(RCC_CIR_LSIRDYIE_BIT)
#define RCC_CIR_CSSF                    BIT(RCC_CIR_CSSF_BIT)
#define RCC_CIR_MSIRDYF                 BIT(RCC_CIR_MSIRDYF_BIT)
#define RCC_CIR_PLLRDYF                 BIT(RCC_CIR_PLLRDYF_BIT)
#define RCC_CIR_HSERDYF                 BIT(RCC_CIR_HSERDYF_BIT)
#define RCC_CIR_HSIRDYF                 BIT(RCC_CIR_HSIRDYF_BIT)
#define RCC_CIR_LSERDYF                 BIT(RCC_CIR_LSERDYF_BIT)
#define RCC_CIR_LSIRDYF                 BIT(RCC_CIR_LSIRDYF_BIT)

/* AHB peripheral reset register */

#define RCC_AHBRSTR_DMA1RST_BIT         24
#define RCC_AHBRSTR_FLITFRST_BIT        15
#define RCC_AHBRSTR_CRCRST_BIT          12
#define RCC_AHBRSTR_GPIOHRST_BIT         5
#define RCC_AHBRSTR_GPIOERST_BIT         4
#define RCC_AHBRSTR_GPIODRST_BIT         3
#define RCC_AHBRSTR_GPIOCRST_BIT         2
#define RCC_AHBRSTR_GPIOBRST_BIT         1
#define RCC_AHBRSTR_GPIOARST_BIT         0

#define RCC_AHBRSTR_DMA1RST             BIT(RCC_AHBRSTR_DMA1RST_BIT)
#define RCC_AHBRSTR_FLITFRST            BIT(RCC_AHBRSTR_FLITFRST_BIT)
#define RCC_AHBRSTR_CRCRST              BIT(RCC_AHBRSTR_CRCRST_BIT)
#define RCC_AHBRSTR_GPIOHRST            BIT(RCC_AHBRSTR_GPIOHRST_BIT)
#define RCC_AHBRSTR_GPIOERST            BIT(RCC_AHBRSTR_GPIOERST_BIT)
#define RCC_AHBRSTR_GPIODRST            BIT(RCC_AHBRSTR_GPIODRST_BIT)
#define RCC_AHBRSTR_GPIOCRST            BIT(RCC_AHBRSTR_GPIOCRST_BIT)
#define RCC_AHBRSTR_GPIOBRST            BIT(RCC_AHBRSTR_GPIOBRST_BIT)
#define RCC_AHBRSTR_GPIOARST            BIT(RCC_AHBRSTR_GPIOARST_BIT)

/* APB2 peripheral reset register */

#define RCC_APB2RSTR_USART1RST_BIT      14
#define RCC_APB2RSTR_SPI1RST_BIT        12
#define RCC_APB2RSTR_ADC1RST_BIT        9
#define RCC_APB2RSTR_TIM11RST_BIT       4
#define RCC_APB2RSTR_TIM10RST_BIT       3
#define RCC_APB2RSTR_TIM9RST_BIT        2
#define RCC_APB2RSTR_SYSCRGRST_BIT      0

#define RCC_APB2RSTR_USART1RST          BIT(RCC_APB2RSTR_USART1RST_BIT)
#define RCC_APB2RSTR_SPI1RST            BIT(RCC_APB2RSTR_SPI1RST_BIT)
#define RCC_APB2RSTR_ADC1RST            BIT(RCC_APB2RSTR_ADC1RST_BIT)
#define RCC_APB2RSTR_TIM11RST           BIT(RCC_APB2RSTR_TIM11RST_BIT)
#define RCC_APB2RSTR_TIM10RST           BIT(RCC_APB2RSTR_TIM10RST_BIT)
#define RCC_APB2RSTR_TIM9RST            BIT(RCC_APB2RSTR_TIM9RST_BIT)
#define RCC_APB2RSTR_SYSCRGRST          BIT(RCC_APB2RSTR_SYSCRGRST_BIT)

/* APB1 peripheral reset register */

#define RCC_APB1RSTR_COMPRST_BIT        31
#define RCC_APB1RSTR_DACRST_BIT         29
#define RCC_APB1RSTR_PWRRST_BIT         28
#define RCC_APB1RSTR_USBRST_BIT         23
#define RCC_APB1RSTR_I2C2RST_BIT        22
#define RCC_APB1RSTR_I2C1RST_BIT        21
#define RCC_APB1RSTR_USART3RST_BIT      18
#define RCC_APB1RSTR_USART2RST_BIT      17
#define RCC_APB1RSTR_SPI2RST_BIT        14
#define RCC_APB1RSTR_WWDRST_BIT         11
#define RCC_APB1RSTR_LCDRST_BIT         9
#define RCC_APB1RSTR_TIM7RST_BIT        5
#define RCC_APB1RSTR_TIM6RST_BIT        4
#define RCC_APB1RSTR_TIM4RST_BIT        2
#define RCC_APB1RSTR_TIM3RST_BIT        1
#define RCC_APB1RSTR_TIM2RST_BIT        0

#define RCC_APB1RSTR_COMPRST            BIT(RCC_APB1RSTR_COMPRST_BIT)
#define RCC_APB1RSTR_DACRST             BIT(RCC_APB1RSTR_DACRST_BIT)
#define RCC_APB1RSTR_PWRRST             BIT(RCC_APB1RSTR_PWRRST_BIT)
#define RCC_APB1RSTR_USBRST             BIT(RCC_APB1RSTR_USBRST_BIT)
#define RCC_APB1RSTR_I2C2RST            BIT(RCC_APB1RSTR_I2C2RST_BIT)
#define RCC_APB1RSTR_I2C1RST            BIT(RCC_APB1RSTR_I2C1RST_BIT)
#define RCC_APB1RSTR_USART3RST          BIT(RCC_APB1RSTR_USART3RST_BIT)
#define RCC_APB1RSTR_USART2RST          BIT(RCC_APB1RSTR_USART2RST_BIT)
#define RCC_APB1RSTR_SPI2RST            BIT(RCC_APB1RSTR_SPI2RST_BIT)
#define RCC_APB1RSTR_WWDRST             BIT(RCC_APB1RSTR_WWDRST_BIT)
#define RCC_APB1RSTR_LCDRST             BIT(RCC_APB1RSTR_LCDRST_BIT)
#define RCC_APB1RSTR_TIM7RST            BIT(RCC_APB1RSTR_TIM7RST_BIT)
#define RCC_APB1RSTR_TIM6RST            BIT(RCC_APB1RSTR_TIM6RST_BIT)
#define RCC_APB1RSTR_TIM4RST            BIT(RCC_APB1RSTR_TIM4RST_BIT)
#define RCC_APB1RSTR_TIM3RST            BIT(RCC_APB1RSTR_TIM3RST_BIT)
#define RCC_APB1RSTR_TIM2RST            BIT(RCC_APB1RSTR_TIM2RST_BIT)


/* AHB peripheral clock enable register */

#define RCC_AHBENR_DMA1EN_BIT          24
#define RCC_AHBENR_FLITFEN_BIT         15
#define RCC_AHBENR_CRCEN_BIT           12
#define RCC_AHBENR_GPIOHEN_BIT          5
#define RCC_AHBENR_GPIOEEN_BIT          4
#define RCC_AHBENR_GPIODEN_BIT          3
#define RCC_AHBENR_GPIOCEN_BIT          2
#define RCC_AHBENR_GPIOBEN_BIT          1
#define RCC_AHBENR_GPIOAEN_BIT          0

#define RCC_AHBENR_DMA1EN              BIT(RCC_AHBENR_DMA1EN_BIT)
#define RCC_AHBENR_FLITFEN             BIT(RCC_AHBENR_FLITFEN_BIT)
#define RCC_AHBENR_CRCEN               BIT(RCC_AHBENR_CRCEN_BIT)
#define RCC_AHBENR_GPIOHEN             BIT(RCC_AHBENR_GPIOHEN_BIT)
#define RCC_AHBENR_GPIOEEN             BIT(RCC_AHBENR_GPIOEEN_BIT)
#define RCC_AHBENR_GPIODEN             BIT(RCC_AHBENR_GPIODEN_BIT)
#define RCC_AHBENR_GPIOCEN             BIT(RCC_AHBENR_GPIOCEN_BIT)
#define RCC_AHBENR_GPIOBEN             BIT(RCC_AHBENR_GPIOBEN_BIT)
#define RCC_AHBENR_GPIOAEN             BIT(RCC_AHBENR_GPIOAEN_BIT)

/* APB2 peripheral clock enable register */

#define RCC_APB2ENR_USART1EN_BIT       14
#define RCC_APB2ENR_SPI1EN_BIT         12
#define RCC_APB2ENR_ADC1EN_BIT         9
#define RCC_APB2ENR_TIM11EN_BIT        4
#define RCC_APB2ENR_TIM10EN_BIT        3
#define RCC_APB2ENR_TIM9EN_BIT         2
#define RCC_APB2ENR_SYSCRGEN_BIT       0

#define RCC_APB2ENR_USART1EN           BIT(RCC_APB2ENR_USART1EN_BIT)
#define RCC_APB2ENR_SPI1EN             BIT(RCC_APB2ENR_SPI1EN_BIT)
#define RCC_APB2ENR_ADC1EN             BIT(RCC_APB2ENR_ADC1EN_BIT)
#define RCC_APB2ENR_TIM11EN            BIT(RCC_APB2ENR_TIM11EN_BIT)
#define RCC_APB2ENR_TIM10EN            BIT(RCC_APB2ENR_TIM10EN_BIT)
#define RCC_APB2ENR_TIM9EN             BIT(RCC_APB2ENR_TIM9EN_BIT)
#define RCC_APB2ENR_SYSCRGEN           BIT(RCC_APB2ENR_SYSCRGEN_BIT)

/* APB1 peripheral clock enable register */

#define RCC_APB1ENR_COMPEN_BIT         31
#define RCC_APB1ENR_DACEN_BIT          29
#define RCC_APB1ENR_PWREN_BIT          28
#define RCC_APB1ENR_USBEN_BIT          23
#define RCC_APB1ENR_I2C2EN_BIT         22
#define RCC_APB1ENR_I2C1EN_BIT         21
#define RCC_APB1ENR_USART3EN_BIT       18
#define RCC_APB1ENR_USART2EN_BIT       17
#define RCC_APB1ENR_SPI2EN_BIT         14
#define RCC_APB1ENR_WWDEN_BIT          11
#define RCC_APB1ENR_LCDEN_BIT          9
#define RCC_APB1ENR_TIM7EN_BIT         5
#define RCC_APB1ENR_TIM6EN_BIT         4
#define RCC_APB1ENR_TIM4EN_BIT         2
#define RCC_APB1ENR_TIM3EN_BIT         1
#define RCC_APB1ENR_TIM2EN_BIT         0

#define RCC_APB1ENR_COMPEN             BIT(RCC_APB1ENR_COMPEN_BIT)
#define RCC_APB1ENR_DACEN              BIT(RCC_APB1ENR_DACEN_BIT)
#define RCC_APB1ENR_PWREN              BIT(RCC_APB1ENR_PWREN_BIT)
#define RCC_APB1ENR_USBEN              BIT(RCC_APB1ENR_USBEN_BIT)
#define RCC_APB1ENR_I2C2EN             BIT(RCC_APB1ENR_I2C2EN_BIT)
#define RCC_APB1ENR_I2C1EN             BIT(RCC_APB1ENR_I2C1EN_BIT)
#define RCC_APB1ENR_USART3EN           BIT(RCC_APB1ENR_USART3EN_BIT)
#define RCC_APB1ENR_USART2EN           BIT(RCC_APB1ENR_USART2EN_BIT)
#define RCC_APB1ENR_SPI2EN             BIT(RCC_APB1ENR_SPI2EN_BIT)
#define RCC_APB1ENR_WWDEN              BIT(RCC_APB1ENR_WWDEN_BIT)
#define RCC_APB1ENR_LCDEN              BIT(RCC_APB1ENR_LCDEN_BIT)
#define RCC_APB1ENR_TIM7EN             BIT(RCC_APB1ENR_TIM7EN_BIT)
#define RCC_APB1ENR_TIM6EN             BIT(RCC_APB1ENR_TIM6EN_BIT)
#define RCC_APB1ENR_TIM4EN             BIT(RCC_APB1ENR_TIM4EN_BIT)
#define RCC_APB1ENR_TIM3EN             BIT(RCC_APB1ENR_TIM3EN_BIT)
#define RCC_APB1ENR_TIM2EN             BIT(RCC_APB1ENR_TIM2EN_BIT)

/* AHB peripheral clock enable in lower power mode register */

#define RCC_AHBLPENR_DMA1LPEN_BIT          24
#define RCC_AHBLPENR_FLITFLPEN_BIT         15
#define RCC_AHBLPENR_CRCLPEN_BIT           12
#define RCC_AHBLPENR_GPIOHLPEN_BIT          5
#define RCC_AHBLPENR_GPIOELPEN_BIT          4
#define RCC_AHBLPENR_GPIODLPEN_BIT          3
#define RCC_AHBLPENR_GPIOCLPEN_BIT          2
#define RCC_AHBLPENR_GPIOBLPEN_BIT          1
#define RCC_AHBLPENR_GPIOALPEN_BIT          0

#define RCC_AHBLPENR_DMA1LPEN              BIT(RCC_AHBLPENR_DMA1LPEN_BIT)
#define RCC_AHBLPENR_FLITFLPEN             BIT(RCC_AHBLPENR_FLITFLPEN_BIT)
#define RCC_AHBLPENR_CRCLPEN               BIT(RCC_AHBLPENR_CRCLPEN_BIT)
#define RCC_AHBLPENR_GPIOHLPEN             BIT(RCC_AHBLPENR_GPIOHLPEN_BIT)
#define RCC_AHBLPENR_GPIOELPEN             BIT(RCC_AHBLPENR_GPIOELPEN_BIT)
#define RCC_AHBLPENR_GPIODLPEN             BIT(RCC_AHBLPENR_GPIODLPEN_BIT)
#define RCC_AHBLPENR_GPIOCLPEN             BIT(RCC_AHBLPENR_GPIOCLPEN_BIT)
#define RCC_AHBLPENR_GPIOBLPEN             BIT(RCC_AHBLPENR_GPIOBLPEN_BIT)
#define RCC_AHBLPENR_GPIOALPEN             BIT(RCC_AHBLPENR_GPIOALPEN_BIT)

/* APB2 peripheral clock enable in lower power mode register */

#define RCC_APB2LPENR_USART1LPEN_BIT       14
#define RCC_APB2LPENR_SPI1LPEN_BIT         12
#define RCC_APB2LPENR_ADC1LPEN_BIT         9
#define RCC_APB2LPENR_TIM11LPEN_BIT        4
#define RCC_APB2LPENR_TIM10LPEN_BIT        3
#define RCC_APB2LPENR_TIM9LPEN_BIT         2
#define RCC_APB2LPENR_SYSCRGLPEN_BIT       0

#define RCC_APB2LPENR_USART1LPEN           BIT(RCC_APB2LPENR_USART1LPEN_BIT)
#define RCC_APB2LPENR_SPI1LPEN             BIT(RCC_APB2LPENR_SPI1LPEN_BIT)
#define RCC_APB2LPENR_ADC1LPEN             BIT(RCC_APB2LPENR_ADC1LPEN_BIT)
#define RCC_APB2LPENR_TIM11LPEN            BIT(RCC_APB2LPENR_TIM11LPEN_BIT)
#define RCC_APB2LPENR_TIM10LPEN            BIT(RCC_APB2LPENR_TIM10LPEN_BIT)
#define RCC_APB2LPENR_TIM9LPEN             BIT(RCC_APB2LPENR_TIM9LPEN_BIT)
#define RCC_APB2LPENR_SYSCRGLPEN           BIT(RCC_APB2LPENR_SYSCRGLPEN_BIT)

/* APB1 peripheral clock enable in lower power mode register */

#define RCC_APB1LPENR_COMPLPEN_BIT         31
#define RCC_APB1LPENR_DACLPEN_BIT          29
#define RCC_APB1LPENR_PWRLPEN_BIT          28
#define RCC_APB1LPENR_USBLPEN_BIT          23
#define RCC_APB1LPENR_I2C2LPEN_BIT         22
#define RCC_APB1LPENR_I2C1LPEN_BIT         21
#define RCC_APB1LPENR_USART3LPEN_BIT       18
#define RCC_APB1LPENR_USART2LPEN_BIT       17
#define RCC_APB1LPENR_SPI2LPEN_BIT         14
#define RCC_APB1LPENR_WWDLPEN_BIT          11
#define RCC_APB1LPENR_LCDLPEN_BIT          9
#define RCC_APB1LPENR_TIM7LPEN_BIT         5
#define RCC_APB1LPENR_TIM6LPEN_BIT         4
#define RCC_APB1LPENR_TIM4LPEN_BIT         2
#define RCC_APB1LPENR_TIM3LPEN_BIT         1
#define RCC_APB1LPENR_TIM2LPEN_BIT         0

#define RCC_APB1LPENR_COMPLPEN             BIT(RCC_APB1LPENR_COMPLPEN_BIT)
#define RCC_APB1LPENR_DACLPEN              BIT(RCC_APB1LPENR_DACLPEN_BIT)
#define RCC_APB1LPENR_PWRLPEN              BIT(RCC_APB1LPENR_PWRLPEN_BIT)
#define RCC_APB1LPENR_USBLPEN              BIT(RCC_APB1LPENR_USBLPEN_BIT)
#define RCC_APB1LPENR_I2C2LPEN             BIT(RCC_APB1LPENR_I2C2LPEN_BIT)
#define RCC_APB1LPENR_I2C1LPEN             BIT(RCC_APB1LPENR_I2C1LPEN_BIT)
#define RCC_APB1LPENR_USART3LPEN           BIT(RCC_APB1LPENR_USART3LPEN_BIT)
#define RCC_APB1LPENR_USART2LPEN           BIT(RCC_APB1LPENR_USART2LPEN_BIT)
#define RCC_APB1LPENR_SPI2LPEN             BIT(RCC_APB1LPENR_SPI2LPEN_BIT)
#define RCC_APB1LPENR_WWDLPEN              BIT(RCC_APB1LPENR_WWDLPEN_BIT)
#define RCC_APB1LPENR_LCDLPEN              BIT(RCC_APB1LPENR_LCDLPEN_BIT)
#define RCC_APB1LPENR_TIM7LPEN             BIT(RCC_APB1LPENR_TIM7LPEN_BIT)
#define RCC_APB1LPENR_TIM6LPEN             BIT(RCC_APB1LPENR_TIM6LPEN_BIT)
#define RCC_APB1LPENR_TIM4LPEN             BIT(RCC_APB1LPENR_TIM4LPEN_BIT)
#define RCC_APB1LPENR_TIM3LPEN             BIT(RCC_APB1LPENR_TIM3LPEN_BIT)
#define RCC_APB1LPENR_TIM2LPEN             BIT(RCC_APB1LPENR_TIM2LPEN_BIT)
                                     
/* Control/status register */

#define RCC_CSR_LPWRRSTF_BIT            31
#define RCC_CSR_WWDGRSTF_BIT            30
#define RCC_CSR_IWDGRSTF_BIT            29
#define RCC_CSR_SFTRSTF_BIT             28
#define RCC_CSR_PORRSTF_BIT             27
#define RCC_CSR_PINRSTF_BIT             26
#define RCC_CSR_OBLRSTF_BIT             25
#define RCC_CSR_RMVF_BIT                24
#define RCC_CSR_RTCRST_BIT              23
#define RCC_CSR_RTCEN_BIT               22
#define RCC_CSR_LSEBYP_BIT              10
#define RCC_CSR_LSERDY_BIT              9
#define RCC_CSR_LSEON_BIT               8
#define RCC_CSR_LSIRDY_BIT              1
#define RCC_CSR_LSION_BIT               0

#define RCC_CSR_LPWRRSTF                BIT(RCC_CSR_LPWRRSTF_BIT)
#define RCC_CSR_WWDGRSTF                BIT(RCC_CSR_WWDGRSTF_BIT)
#define RCC_CSR_IWDGRSTF                BIT(RCC_CSR_IWDGRSTF_BIT)
#define RCC_CSR_SFTRSTF                 BIT(RCC_CSR_SFTRSTF_BIT)
#define RCC_CSR_PORRSTF                 BIT(RCC_CSR_PORRSTF_BIT)
#define RCC_CSR_PINRSTF                 BIT(RCC_CSR_PINRSTF_BIT)
#define RCC_CSR_OBLRSTF                 BIT(RCC_CSR_OBLRSTF_BIT)
#define RCC_CSR_RMVF                    BIT(RCC_CSR_RMVF_BIT)
#define RCC_CSR_RTCRST                  BIT(RCC_CSR_RTCRST_BIT)
#define RCC_CSR_RTCEN                   BIT(RCC_CSR_RTCEN_BIT)
#define RCC_CSR_RTCSEL                  (0x3 << 16)
#define RCC_CSR_RTCSEL_NONE             (0x0 << 8)
#define RCC_CSR_RTCSEL_LSE              (0x1 << 8)
#define RCC_CSR_RTCSEL_LSI              (0x2 << 8)
#define RCC_CSR_RTCSEL_HSE              (0x3 << 8)
#define RCC_CSR_LSEBYP                  BIT(RCC_CSR_LSEBYP_BIT)
#define RCC_CSR_LSERDY                  BIT(RCC_CSR_LSERDY_BIT)
#define RCC_CSR_LSEON                   BIT(RCC_CSR_LSEON_BIT)
#define RCC_CSR_LSIRDY                  BIT(RCC_CSR_LSIRDY_BIT)
#define RCC_CSR_LSION                   BIT(RCC_CSR_LSION_BIT)

/*
 * libmaple-mandated enumeration types.
 */

/**
 * @brief SYSCLK sources
 * @see rcc_switch_sysclk()
 */
typedef enum rcc_sysclk_src {
    RCC_CLKSRC_MSI = RCC_CFGR_SW_MSI,
    RCC_CLKSRC_HSI = RCC_CFGR_SW_HSI,
    RCC_CLKSRC_HSE = RCC_CFGR_SW_HSE,
    RCC_CLKSRC_PLL = RCC_CFGR_SW_PLL,
} rcc_sysclk_src;


/**
 * @brief Identifies bus and clock line for a peripheral.
 *
 * Also generally useful as a unique identifier for that peripheral
 * (or its corresponding device struct).
 */
typedef enum rcc_clk_id {
    RCC_GPIOA,
    RCC_GPIOB,
    RCC_GPIOC,
    RCC_GPIOD,
    RCC_AFIO,
    RCC_ADC1,
    RCC_USART1,
    RCC_USART2,
    RCC_USART3,
    RCC_TIMER1,
    RCC_TIMER2,
    RCC_TIMER3,
    RCC_TIMER4,
    RCC_SPI1,
    RCC_SPI2,
    RCC_DMA1,
    RCC_PWR,
    RCC_BKP,
    RCC_I2C1,
    RCC_I2C2,
    RCC_CRC,
    RCC_FLITF,
    RCC_SRAM,
    RCC_USB,
    RCC_GPIOE,
    RCC_TIMER5,
    RCC_GPIOH,
    RCC_TIMER6,
    RCC_TIMER7,
    RCC_FSMC,
    RCC_DAC,
    RCC_SDIO,
    RCC_TIMER9,
    RCC_TIMER10,
    RCC_TIMER11,
    RCC_TIMER12,
    RCC_TIMER13,
    RCC_TIMER14,
    RCC_SYSCFG,
    RCC_LCD,
    RCC_WWDG,
    RCC_COMP

} rcc_clk_id;

/**
 * @brief Deprecated PLL multipliers, for rcc_clk_init().
 */
typedef enum rcc_pll_multiplier {
    RCC_PLLMUL_3 = RCC_CFGR_PLLMUL_MUL_3,
    RCC_PLLMUL_4 = RCC_CFGR_PLLMUL_MUL_4,
    RCC_PLLMUL_6 = RCC_CFGR_PLLMUL_MUL_6,
    RCC_PLLMUL_8 = RCC_CFGR_PLLMUL_MUL_8,
    RCC_PLLMUL_12 = RCC_CFGR_PLLMUL_MUL_12,
    RCC_PLLMUL_16 = RCC_CFGR_PLLMUL_MUL_16,
    RCC_PLLMUL_24 = RCC_CFGR_PLLMUL_MUL_24,
    RCC_PLLMUL_32 = RCC_CFGR_PLLMUL_MUL_32,
    RCC_PLLMUL_48 = RCC_CFGR_PLLMUL_MUL_48
} rcc_pll_multiplier;

typedef enum rcc_pll_divider {
    RCC_PLLDIV_2 = RCC_CFGR_PLLDIV_DIV_2,
    RCC_PLLDIV_3 = RCC_CFGR_PLLDIV_DIV_3,
    RCC_PLLDIV_4 = RCC_CFGR_PLLDIV_DIV_4
} rcc_pll_divider;

/**
 * @brief PLL clock sources.
 * @see rcc_configure_pll()
 */
typedef enum rcc_pllsrc {
    RCC_PLLSRC_HSE = RCC_CFGR_PLLSRC,
    RCC_PLLSRC_HSI = (0x0 << RCC_CFGR_PLLSRC_BIT)
} rcc_pllsrc;

typedef enum rcc_clk_domain {
    RCC_APB1,
    RCC_APB2,
    RCC_AHB
} rcc_clk_domain;

typedef enum rcc_prescaler {
    RCC_PRESCALER_MCO,
    RCC_PRESCALER_APB2,
    RCC_PRESCALER_APB1,
    RCC_PRESCALER_AHB
} rcc_prescaler;


/**
 * APB1 prescaler dividers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_apb1_divider {
    RCC_APB1_HCLK_DIV_1 = 0x0 << 10,
    RCC_APB1_HCLK_DIV_2 = RCC_CFGR_PPRE1_AHB_DIV_2,
    RCC_APB1_HCLK_DIV_4 = RCC_CFGR_PPRE1_AHB_DIV_4,
    RCC_APB1_HCLK_DIV_8 = RCC_CFGR_PPRE1_AHB_DIV_8,
    RCC_APB1_HCLK_DIV_16 = RCC_CFGR_PPRE1_AHB_DIV_16,
} rcc_apb1_divider;

/**
 * APB2 prescaler dividers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_apb2_divider {
    RCC_APB2_HCLK_DIV_1 = 0x0 << 13,
    RCC_APB2_HCLK_DIV_2 = RCC_CFGR_PPRE2_AHB_DIV_2,
    RCC_APB2_HCLK_DIV_4 = RCC_CFGR_PPRE2_AHB_DIV_4,
    RCC_APB2_HCLK_DIV_8 = RCC_CFGR_PPRE2_AHB_DIV_8,
    RCC_APB2_HCLK_DIV_16 = RCC_CFGR_PPRE2_AHB_DIV_16,
} rcc_apb2_divider;

/**
 * AHB prescaler dividers
 * @see rcc_set_prescaler()
 */
typedef enum rcc_ahb_divider {
    RCC_AHB_SYSCLK_DIV_1 = 0x0 << 4,
    RCC_AHB_SYSCLK_DIV_2 = RCC_CFGR_HPRE_SYSCLK_DIV_2,
    RCC_AHB_SYSCLK_DIV_4 = RCC_CFGR_HPRE_SYSCLK_DIV_4,
    RCC_AHB_SYSCLK_DIV_8 = RCC_CFGR_HPRE_SYSCLK_DIV_8,
    RCC_AHB_SYSCLK_DIV_16 = RCC_CFGR_HPRE_SYSCLK_DIV_16,
    RCC_AHB_SYSCLK_DIV_64 = RCC_CFGR_HPRE_SYSCLK_DIV_64,
    RCC_AHB_SYSCLK_DIV_128 = RCC_CFGR_HPRE_SYSCLK_DIV_128,
    RCC_AHB_SYSCLK_DIV_256 = RCC_CFGR_HPRE_SYSCLK_DIV_256,
    RCC_AHB_SYSCLK_DIV_512 = RCC_CFGR_HPRE_SYSCLK_DIV_512,
} rcc_ahb_divider;


/**
 * @brief Available clock sources.
 */
typedef enum rcc_clk {
    RCC_CLK_PLL    = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_PLLON_BIT), /**< Main PLL, clocked by
                                                    HSI or HSE. */
    RCC_CLK_HSE    = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_HSEON_BIT), /**< High speed external. */
    RCC_CLK_HSI    = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_HSION_BIT), /**< High speed internal. */
    RCC_CLK_MSI    = (uint16)((offsetof(struct rcc_reg_map, CR) << 8) |
                              RCC_CR_MSION_BIT), /**< Medium-speed internal */
} rcc_clk;

/*
 * Series-specific functionality.
 */

__deprecated
void rcc_clk_init(rcc_sysclk_src sysclk_src,
                  rcc_pllsrc pll_src,
                  rcc_pll_multiplier pll_mul);

/**
 * @brief STM32F1-specific PLL configuration values.
 *
 * Use this as the "data" field in a struct rcc_pll_cfg.
 *
 * @see struct rcc_pll_cfg.
 */
typedef struct stm32l1_rcc_pll_data {
     rcc_pll_multiplier pll_mul; /**< PLL multiplication factor. */
     rcc_pll_divider pll_div; /**< PLL divide factor. */
} stm32l1_rcc_pll_data;

#ifdef __cplusplus
}
#endif

#endif
