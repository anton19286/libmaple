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
 *  @file libmaple/stm32l1/gpio.h
 *  @brief General purpose I/O (GPIO) and Alternate Function I/O
 *         (AFIO) prototypes, defines, and inlined access functions.
 */

#ifndef _LIBMAPLE_STM32L1_GPIO_H_
#define _LIBMAPLE_STM32L1_GPIO_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple.h>
#include <libmaple/rcc.h>

/*
 * GPIO register maps and devices
 */

/** GPIO register map type */
typedef struct gpio_reg_map {
    __io uint32 MODER;          /**< Mode register */
    __io uint32 OTYPER;         /**< Output type register */
    __io uint32 OSPEEDR;        /**< Output speed register */
    __io uint32 PUPDR;          /**< Pull-up/pull-down register */
    __io uint32 IDR;            /**< Input data register */
    __io uint32 ODR;            /**< Output data register */
    __io uint32 BSRR;           /**< Bit set/reset register */
    __io uint32 LCKR;           /**< Configuration lock register */
    __io uint32 AFRL;           /**< Alternate function low register */
    __io uint32 AFRH;           /**< Alternate function high register */
} gpio_reg_map;

/** GPIO port A register map base pointer */
#define GPIOA_BASE                      ((struct gpio_reg_map*)0x40020000)
/** GPIO port B register map base pointer */
#define GPIOB_BASE                      ((struct gpio_reg_map*)0x40020400)
/** GPIO port C register map base pointer */
#define GPIOC_BASE                      ((struct gpio_reg_map*)0x40020800)
/** GPIO port D register map base pointer */
#define GPIOD_BASE                      ((struct gpio_reg_map*)0x40020C00)
/** GPIO port E register map base pointer */
#define GPIOE_BASE                      ((struct gpio_reg_map*)0x40021000)
/** GPIO port H register map base pointer */
#define GPIOH_BASE                      ((struct gpio_reg_map*)0x40021400)

/** GPIO device type */
typedef struct gpio_dev {
    gpio_reg_map *regs;       /**< Register map */
    rcc_clk_id clk_id;        /**< RCC clock information */
} gpio_dev;

extern gpio_dev gpioa;
extern gpio_dev* const GPIOA;
extern gpio_dev gpiob;
extern gpio_dev* const GPIOB;
extern gpio_dev gpioc;
extern gpio_dev* const GPIOC;
extern gpio_dev gpiod;
extern gpio_dev* const GPIOD;
extern gpio_dev gpioe;
extern gpio_dev* const GPIOE;
extern gpio_dev gpioh;
extern gpio_dev* const GPIOH;

/*
 * GPIO register bit definitions
 */

/* Control registers */

/* Mode register */
#define GPIO_MODE_INPUT                 0x0
#define GPIO_MODE_OUTPUT                0x1
#define GPIO_MODE_AF                    0x2
#define GPIO_MODE_ANALOG                0x3

/* Output type register */

#define GPIO_OTYPE_PP                   0x0
#define GPIO_OTYPE_OD                   0x1

/* Output speed register */

#define GPIO_OSPEED_400KHZ              0x0
#define GPIO_OSPEED_2MHZ                0x1
#define GPIO_OSPEED_10MHZ               0x2
#define GPIO_OSPEED_40MHZ               0x3

/* Pull-up/pull-down register */

#define GPIO_PUPD_NO_PUPD               0x0
#define GPIO_PUPD_PU                    0x1
#define GPIO_PUPD_PD                    0x2

/* Alternate function register low */

#define GPIO_AFRL_AF0                   (0xFU << 0)
#define GPIO_AFRL_AF1                   (0xFU << 4)
#define GPIO_AFRL_AF2                   (0xFU << 8)
#define GPIO_AFRL_AF3                   (0xFU << 12)
#define GPIO_AFRL_AF4                   (0xFU << 16)
#define GPIO_AFRL_AF5                   (0xFU << 20)
#define GPIO_AFRL_AF6                   (0xFU << 24)
#define GPIO_AFRL_AF7                   (0xFU << 28)

/* Alternate function register high */

#define GPIO_AFRH_AF8                   (0xFU << 0)
#define GPIO_AFRH_AF9                   (0xFU << 4)
#define GPIO_AFRH_AF10                  (0xFU << 8)
#define GPIO_AFRH_AF11                  (0xFU << 12)
#define GPIO_AFRH_AF12                  (0xFU << 16)
#define GPIO_AFRH_AF13                  (0xFU << 20)
#define GPIO_AFRH_AF14                  (0xFU << 24)
#define GPIO_AFRH_AF15                  (0xFU << 28)
/**
 * @brief GPIO Pin modes.
 *
 * These only allow for 40MHZ max output speeds; if you want slower,
 * use direct register access.
 */
typedef enum gpio_pin_mode {
    GPIO_OUTPUT_PP, /**< Output push-pull. */
    GPIO_OUTPUT_OD, /**< Output open-drain. */
    GPIO_AF_OUTPUT_PP, /**< Alternate function output push-pull. */
    GPIO_AF_OUTPUT_OD, /**< Alternate function output open drain. */
    GPIO_INPUT_ANALOG, /**< Analog input. */
    GPIO_INPUT_FLOATING, /**< Input floating. */
    GPIO_INPUT_PD, /**< Input pull-down. */
    GPIO_INPUT_PU /**< Input pull-up. */
} gpio_pin_mode;


/**
 * @brief GPIO alternate functions.
 * Use these to select an alternate function for a pin.
 * @see gpio_set_af()
 */
typedef enum gpio_af {
    GPIO_AF_SYS                  = 0, /**< System. */
    GPIO_AF_TIM_2                = 1, /**< Timer 2. */
    GPIO_AF_TIM_3_4              = 2, /**< Timers 3 and 4. */
    GPIO_AF_TIM_9_10_11          = 3, /**< Timers 9 through 11. */
    GPIO_AF_I2C                  = 4, /**< I2C 1 and 2. */
    GPIO_AF_SPI_1_2              = 5, /**< SPI1, SPI2. */
    GPIO_AF_6                    = 6, /**< Not used?. */
    GPIO_AF_USART_1_2_3          = 7, /**< USART 1, 2, and 3. */
    GPIO_AF_8                    = 8, /**< Not used?. */
	GPIO_AF_9                    = 9, /**< Not used?. */
    GPIO_AF_USB                  = 10, /**< USB. */
    GPIO_AF_LCD                  = 11, /**< LCD. */
	GPIO_AF_12                   = 12, /**< Not used?. */
	GPIO_AF_13                   = 13, /**< Not used?. */
	GPIO_AF_RI                   = 13, /**< RI. */
    GPIO_AF_EVENTOUT             = 15, /**< EVENTOUT. */
} gpio_af;


#ifdef __cplusplus
}
#endif

#endif
