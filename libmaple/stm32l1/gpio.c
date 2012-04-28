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
 * @file libmaple/stm32l1/gpio.c
 * @brief GPIO support for STM32L1 line.
 */

#include <libmaple/gpio.h>
#include <libmaple/rcc.h>

/*
 * GPIO devices
 */

gpio_dev gpioa = {
    .regs      = GPIOA_BASE,
    .clk_id    = RCC_GPIOA,
    .exti_port = AFIO_EXTI_PA,
};
/** GPIO port A device. */
gpio_dev* const GPIOA = &gpioa;

gpio_dev gpiob = {
    .regs      = GPIOB_BASE,
    .clk_id    = RCC_GPIOB,
    .exti_port = AFIO_EXTI_PB,
};
/** GPIO port B device. */
gpio_dev* const GPIOB = &gpiob;

gpio_dev gpioc = {
    .regs      = GPIOC_BASE,
    .clk_id    = RCC_GPIOC,
    .exti_port = AFIO_EXTI_PC,
};
/** GPIO port C device. */
gpio_dev* const GPIOC = &gpioc;

gpio_dev gpiod = {
    .regs      = GPIOD_BASE,
    .clk_id    = RCC_GPIOD,
    .exti_port = AFIO_EXTI_PD,
};
/** GPIO port D device. */
gpio_dev* const GPIOD = &gpiod;

gpio_dev gpioe = {
    .regs      = GPIOE_BASE,
    .clk_id    = RCC_GPIOE,
    .exti_port = AFIO_EXTI_PE,
};
/** GPIO port E device. */
gpio_dev* const GPIOE = &gpioe;

/*
gpio_dev gpioh = {
    .regs      = GPIOH_BASE,
    .clk_id    = RCC_GPIOH,
    .exti_port = AFIO_EXTI_PH,
};*/
/** GPIO port H device. */
// gpio_dev* const GPIOH = &gpioh;

/*
 * GPIO routines
 */

/**
 * Initialize and reset all available GPIO devices.
 */
void gpio_init_all(void) {
    gpio_init(GPIOA);
    gpio_init(GPIOB);
    gpio_init(GPIOC);
    gpio_init(GPIOD);
    gpio_init(GPIOE);
//    gpio_init(GPIOH);
}

void set_two_bits(__io uint32 *reg, uint32 val, uint32 shift) {
    uint32 tmp = *reg;

    tmp &= ~(0x3 << shift);
    tmp |= (val & 0x3) << shift;
    *reg = tmp;
}

void set_one_bit(__io uint32 *reg, uint32 val, uint32 shift) {
    uint32 tmp = *reg;
    tmp &= ~(0x1 << shift);
    tmp |= (val & 0x1) << shift;
    *reg = tmp;
}

/**
 * Set the mode of a GPIO pin.
 *
 * @param dev GPIO device.
 * @param pin Pin on the device whose mode to set, 0--15.
 * @param mode General purpose or alternate function mode to set the pin to.
 * @see gpio_pin_mode
 */
void gpio_set_mode(gpio_dev *dev, uint8 pin, gpio_pin_mode mode) {
    gpio_reg_map *regs = dev->regs;

    uint32 shift = (pin & 0xF) * 2;
    
    uint32 portMode= GPIO_MODE_OUTPUT;
    uint32 outputType = GPIO_OTYPE_PP;
    uint32 portSpeed = GPIO_OSPEED_40MHZ;
    uint32 pullUpPullDown = GPIO_PUPD_NO_PUPD;

    switch(mode) {
    case GPIO_OUTPUT_PP:
        break;
    case GPIO_OUTPUT_OD:
        outputType = GPIO_OTYPE_OD;
        break;
    case GPIO_INPUT_FLOATING:
        portMode = GPIO_MODE_INPUT;
        break;
    case GPIO_INPUT_ANALOG:
        portMode = GPIO_MODE_ANALOG;
        break;
    case GPIO_INPUT_PU:
        portMode = GPIO_MODE_INPUT;
        pullUpPullDown = GPIO_PUPD_PU;
        break;
    case GPIO_INPUT_PD:
        portMode = GPIO_MODE_INPUT;
        pullUpPullDown = GPIO_PUPD_PD;
        break;
    case GPIO_AF_OUTPUT_PP:
        portMode = GPIO_MODE_AF;
        break;
    case GPIO_AF_OUTPUT_OD:
        portMode = GPIO_MODE_AF;
        outputType = GPIO_OTYPE_OD;
        break;
    default:
        ASSERT(0);
        return;
    }

    set_two_bits(&regs->MODER, portMode, shift);
    set_two_bits(&regs->OTYPER, outputType, pin);
    set_two_bits(&regs->OSPEEDR, portSpeed, shift);
    set_two_bits(&regs->PUPDR, pullUpPullDown, shift);

    if (mode == GPIO_INPUT_PD) {
        regs->ODR &= ~BIT(pin);
    } else if (mode == GPIO_INPUT_PU) {
        regs->ODR |= BIT(pin);
    }
}

/*
 * AFIO
 */

/**
 * @brief Initialize the AFIO clock, and reset the AFIO registers.
 */
void afio_init(void) {
    rcc_clk_enable(RCC_AFIO);
    rcc_reset_dev(RCC_AFIO);
}

#define AFIO_EXTI_SEL_MASK 0xF

/**
 * @brief Select a source input for an external interrupt.
 *
 * @param exti      External interrupt.
 * @param gpio_port Port which contains pin to use as source input.
 * @see afio_exti_num
 * @see afio_exti_port
 */
void afio_exti_select(afio_exti_num exti, afio_exti_port gpio_port) {
    __io uint32 *exti_cr = &AFIO_BASE->EXTICR1 + exti / 4;
    uint32 shift = 4 * (exti % 4);
    uint32 cr = *exti_cr;

    cr &= ~(AFIO_EXTI_SEL_MASK << shift);
    cr |= gpio_port << shift;
    *exti_cr = cr;
}

/**
 * @brief Perform an alternate function remap.
 * @param remapping Remapping to perform.
 */
void afio_remap(afio_remap_peripheral remapping) {
    if (remapping & AFIO_REMAP_USE_MAPR2) {
        remapping &= ~AFIO_REMAP_USE_MAPR2;
        AFIO_BASE->MAPR2 |= remapping;
    } else {
        AFIO_BASE->MAPR |= remapping;
    }
}
