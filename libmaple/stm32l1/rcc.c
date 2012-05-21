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
 * @file libmaple/stm32l1/rcc.c
 * @brief STM32L1 RCC routines.
 */

#include <libmaple/rcc.h>
#include <libmaple/libmaple.h>
#include <libmaple/bitband.h>

#include "rcc_private.h"

#define APB1                            RCC_APB1
#define APB2                            RCC_APB2
#define AHB                             RCC_AHB

/* Device descriptor table, maps rcc_clk_id onto bus and enable/reset
 * register bit numbers. */
const struct rcc_dev_info rcc_dev_table[] = {
    [RCC_GPIOA]  = { .clk_domain = AHB,  .line_num = 0 },
    [RCC_GPIOB]  = { .clk_domain = AHB,  .line_num = 1 },
    [RCC_GPIOC]  = { .clk_domain = AHB,  .line_num = 2 },
    [RCC_GPIOD]  = { .clk_domain = AHB,  .line_num = 3 },
    [RCC_GPIOE]  = { .clk_domain = AHB,  .line_num = 4 },
    [RCC_GPIOH]  = { .clk_domain = AHB,  .line_num = 5 },
    [RCC_CRC]    = { .clk_domain = AHB,  .line_num = 12},
    [RCC_FLITF]  = { .clk_domain = AHB,  .line_num = 15},
    [RCC_DMA1]   = { .clk_domain = AHB,  .line_num = 24},

    [RCC_SYSCFG] = { .clk_domain = APB2, .line_num = 0 },
    [RCC_TIMER9] = { .clk_domain = APB2, .line_num = 2 },
    [RCC_TIMER10]= { .clk_domain = APB2, .line_num = 3 },
    [RCC_TIMER11]= { .clk_domain = APB2, .line_num = 4 },
    [RCC_ADC1]   = { .clk_domain = APB2, .line_num = 9 },
    [RCC_SPI1]   = { .clk_domain = APB2, .line_num = 12 },
    [RCC_USART1] = { .clk_domain = APB2, .line_num = 14 },

    [RCC_TIMER2] = { .clk_domain = APB1, .line_num = 0 },
    [RCC_TIMER3] = { .clk_domain = APB1, .line_num = 1 },
    [RCC_TIMER4] = { .clk_domain = APB1, .line_num = 2 },
    [RCC_TIMER6] = { .clk_domain = APB1, .line_num = 4 },
    [RCC_TIMER7] = { .clk_domain = APB1, .line_num = 5 },
    [RCC_LCD]    = { .clk_domain = APB1, .line_num = 9 },
    [RCC_WWDG]   = { .clk_domain = APB1, .line_num = 11 },
    [RCC_SPI2]   = { .clk_domain = APB1, .line_num = 14 },
    [RCC_USART2] = { .clk_domain = APB1, .line_num = 17 },
    [RCC_USART3] = { .clk_domain = APB1, .line_num = 18 },
    [RCC_I2C1]   = { .clk_domain = APB1, .line_num = 21 },
    [RCC_I2C2]   = { .clk_domain = APB1, .line_num = 22 },
    [RCC_USB]    = { .clk_domain = APB1, .line_num = 23},
    [RCC_PWR]    = { .clk_domain = APB1, .line_num = 28 },
    [RCC_DAC]    = { .clk_domain = APB1, .line_num = 29 },
    [RCC_COMP]    = { .clk_domain = APB1, .line_num = 31 }
};

/**
 * @brief Deprecated.
 *
 * Initialize the clock control system. Initializes the system
 * clock source to use the PLL driven by an external oscillator.
 *
 * This function is limited and nonportable. Instead of using it,
 * follow this (portable) procedure:
 *
 * 1. Switch to HSI by calling rcc_switch_sysclk(RCC_CLKSRC_HSI).
 * 2. Turn off HSE by calling rcc_turn_off_clk(RCC_CLK_HSE).
 * 3. Turn off the PLL by calling rcc_turn_off_clk(RCC_CLK_HSE).
 * 4. Reconfigure the PLL using rcc_configure_pll().
 * 5. Turn on RCC_CLK_HSE using rcc_turn_on_clk() and wait for it to
 *    become ready by busy-waiting on rcc_is_clk_ready().
 * 6. Turn on RCC_CLK_PLL using the same methods.
 * 7. Switch to the PLL with rcc_switch_sysclk(RCC_CLKSRC_PLL).
 *
 * @param sysclk_src system clock source, must be PLL
 * @param pll_src pll clock source, must be HSE
 * @param pll_mul pll multiplier
 */
void rcc_clk_init(rcc_sysclk_src sysclk_src,
                  rcc_pllsrc pll_src,
                  rcc_pll_multiplier pll_mul) {
    /* Assume that we're going to clock the chip off the PLL, fed by
     * the HSE */
    ASSERT(sysclk_src == RCC_CLKSRC_PLL &&
           pll_src    == RCC_PLLSRC_HSE);

    RCC_BASE->CFGR = pll_src | pll_mul;

    /* Turn on, and wait for, HSE. */
    rcc_turn_on_clk(RCC_CLK_HSE);
    while (!rcc_is_clk_ready(RCC_CLK_HSE))
        ;

    /* Do the same for the main PLL. */
    rcc_turn_on_clk(RCC_CLK_PLL);
    while(!rcc_is_clk_ready(RCC_CLK_PLL))
        ;

    /* Finally, switch over to the PLL. */
    rcc_switch_sysclk(RCC_CLKSRC_PLL);
}

/**
 * @brief Configure the main PLL.
 *
 * You may only call this function while the PLL is disabled.
 *
 * @param pll_cfg Desired PLL configuration. The data field must point
 *                to a valid struct stm32f1_rcc_pll_data.
 */
void rcc_configure_pll(rcc_pll_cfg *pll_cfg) {
    stm32l1_rcc_pll_data *data = pll_cfg->data;
    rcc_pll_multiplier pll_mul = data->pll_mul;
    rcc_pll_divider pll_div = data->pll_div;
    uint32 cfgr;

    /* Check that the PLL is disabled. */
    ASSERT_FAULT(!rcc_is_clk_on(RCC_CLK_PLL));

    cfgr = RCC_BASE->CFGR;
    cfgr &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL | RCC_CFGR_PLLDIV);
    cfgr |= pll_cfg->pllsrc | pll_mul | pll_div;
    RCC_BASE->CFGR = cfgr;
}

/**
 * @brief Turn on the clock line on a peripheral
 * @param id Clock ID of the peripheral to turn on.
 */
void rcc_clk_enable(rcc_clk_id id) {
    static __io uint32* enable_regs[] = {
        [APB1] = &RCC_BASE->APB1ENR,
        [APB2] = &RCC_BASE->APB2ENR,
        [AHB] = &RCC_BASE->AHBENR,
    };
    rcc_do_clk_enable(enable_regs, id);
}

/**
 * @brief Reset a peripheral.
 *
 * Caution: not all rcc_clk_id values refer to a peripheral which can
 * be reset.
 *
 * @param id Clock ID of the peripheral to reset.
 */
void rcc_reset_dev(rcc_clk_id id) {
    static __io uint32* reset_regs[] = {
        [APB1] = &RCC_BASE->APB1RSTR,
        [APB2] = &RCC_BASE->APB2RSTR,
    };
    rcc_do_reset_dev(reset_regs, id);
}

/**
 * @brief Set the divider on a peripheral prescaler
 * @param prescaler prescaler to set
 * @param divider prescaler divider
 */
void rcc_set_prescaler(rcc_prescaler prescaler, uint32 divider) {
    static const uint32 masks[] = {
        [RCC_PRESCALER_AHB] = RCC_CFGR_HPRE,
        [RCC_PRESCALER_APB1] = RCC_CFGR_PPRE1,
        [RCC_PRESCALER_APB2] = RCC_CFGR_PPRE2,
    };
    rcc_do_set_prescaler(masks, prescaler, divider);
}