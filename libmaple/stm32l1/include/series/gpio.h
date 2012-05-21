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
 *         (SYSCFG) prototypes, defines, and inlined access functions.
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

/**
 * @brief External interrupt line port selector.
 *
 * Used to determine which GPIO port to map an external interrupt line
 * onto. */
/* (See SYSCFG sections, below) */
typedef enum syscfg_exti_port {
    AFIO_EXTI_PA,               /**< Use port A (PAx) pin. */
    AFIO_EXTI_PB,               /**< Use port B (PBx) pin. */
    AFIO_EXTI_PC,               /**< Use port C (PCx) pin. */
    AFIO_EXTI_PD,               /**< Use port D (PDx) pin. */
    AFIO_EXTI_PE,               /**< Use port E (PEx) pin. */
    AFIO_EXTI_PH,               /**< Use port H (PHx) pin. */
} syscfg_exti_port;

/** GPIO device type */
typedef struct gpio_dev {
    gpio_reg_map *regs;       /**< Register map */
    rcc_clk_id clk_id;        /**< RCC clock information */
    syscfg_exti_port exti_port; /**< SYSCFG external interrupt port value */
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

/**
 * @brief Get a GPIO port's corresponding syscfg_exti_port.
 * @param dev GPIO device whose syscfg_exti_port to return.
 */
static inline syscfg_exti_port gpio_exti_port(gpio_dev *dev) {
    return dev->exti_port;
}

/*
 * SYSCFG register map
 */

/** SYSCFG register map */
typedef struct syscfg_reg_map {
    __io uint32 SYSCFG_MEMRMP;        /**< Memory remap register.  */
    __io uint32 SYSCFG_PMC;        /**< Peripheral mode configuration 
	                            register. (USB D+ pullup)*/
    __io uint32 EXTICR1;     /**< External interrupt configuration
                                register 1. */
    __io uint32 EXTICR2;     /**< External interrupt configuration
                                register 2. */
    __io uint32 EXTICR3;     /**< External interrupt configuration
                                register 3. */
    __io uint32 EXTICR4;     /**< External interrupt configuration
                                register 4. */
} syscfg_reg_map;

/** SYSCFG register map base pointer. */
#define SYSCFG_BASE                       ((struct syscfg_reg_map *)0x40010000)

/*
 * SYSCFG register bit definitions
 */

/* External interrupt configuration register 1 */

#define SYSCFG_EXTICR1_EXTI3              (0xF << 12)
#define SYSCFG_EXTICR1_EXTI3_PA           (0x0 << 12)
#define SYSCFG_EXTICR1_EXTI3_PB           (0x1 << 12)
#define SYSCFG_EXTICR1_EXTI3_PC           (0x2 << 12)
#define SYSCFG_EXTICR1_EXTI3_PD           (0x3 << 12)
#define SYSCFG_EXTICR1_EXTI3_PE           (0x4 << 12)
#define SYSCFG_EXTICR1_EXTI3_PH           (0x5 << 12)
#define SYSCFG_EXTICR1_EXTI2              (0xF << 8)
#define SYSCFG_EXTICR1_EXTI2_PA           (0x0 << 8)
#define SYSCFG_EXTICR1_EXTI2_PB           (0x1 << 8)
#define SYSCFG_EXTICR1_EXTI2_PC           (0x2 << 8)
#define SYSCFG_EXTICR1_EXTI2_PD           (0x3 << 8)
#define SYSCFG_EXTICR1_EXTI2_PE           (0x4 << 8)
#define SYSCFG_EXTICR1_EXTI2_PH           (0x5 << 8)
#define SYSCFG_EXTICR1_EXTI1              (0xF << 4)
#define SYSCFG_EXTICR1_EXTI1_PA           (0x0 << 4)
#define SYSCFG_EXTICR1_EXTI1_PB           (0x1 << 4)
#define SYSCFG_EXTICR1_EXTI1_PC           (0x2 << 4)
#define SYSCFG_EXTICR1_EXTI1_PD           (0x3 << 4)
#define SYSCFG_EXTICR1_EXTI1_PE           (0x4 << 4)
#define SYSCFG_EXTICR1_EXTI1_PH           (0x5 << 4)
#define SYSCFG_EXTICR1_EXTI0              0xF
#define SYSCFG_EXTICR1_EXTI0_PA           0x0
#define SYSCFG_EXTICR1_EXTI0_PB           0x1
#define SYSCFG_EXTICR1_EXTI0_PC           0x2
#define SYSCFG_EXTICR1_EXTI0_PD           0x3
#define SYSCFG_EXTICR1_EXTI0_PE           0x4
#define SYSCFG_EXTICR1_EXTI0_PH           0x5


/* External interrupt configuration register 2 */

#define SYSCFG_EXTICR2_EXTI7              (0xF << 12)
#define SYSCFG_EXTICR2_EXTI7_PA           (0x0 << 12)
#define SYSCFG_EXTICR2_EXTI7_PB           (0x1 << 12)
#define SYSCFG_EXTICR2_EXTI7_PC           (0x2 << 12)
#define SYSCFG_EXTICR2_EXTI7_PD           (0x3 << 12)
#define SYSCFG_EXTICR2_EXTI7_PE           (0x4 << 12)
#define SYSCFG_EXTICR2_EXTI7_PH           (0x5 << 12)
#define SYSCFG_EXTICR2_EXTI6              (0xF << 8)
#define SYSCFG_EXTICR2_EXTI6_PA           (0x0 << 8)
#define SYSCFG_EXTICR2_EXTI6_PB           (0x1 << 8)
#define SYSCFG_EXTICR2_EXTI6_PC           (0x2 << 8)
#define SYSCFG_EXTICR2_EXTI6_PD           (0x3 << 8)
#define SYSCFG_EXTICR2_EXTI6_PE           (0x4 << 8)
#define SYSCFG_EXTICR2_EXTI6_PH           (0x5 << 8)
#define SYSCFG_EXTICR2_EXTI5              (0xF << 4)
#define SYSCFG_EXTICR2_EXTI5_PA           (0x0 << 4)
#define SYSCFG_EXTICR2_EXTI5_PB           (0x1 << 4)
#define SYSCFG_EXTICR2_EXTI5_PC           (0x2 << 4)
#define SYSCFG_EXTICR2_EXTI5_PD           (0x3 << 4)
#define SYSCFG_EXTICR2_EXTI5_PE           (0x4 << 4)
#define SYSCFG_EXTICR2_EXTI5_PH           (0x5 << 4)
#define SYSCFG_EXTICR2_EXTI4              0xF
#define SYSCFG_EXTICR2_EXTI4_PA           0x0
#define SYSCFG_EXTICR2_EXTI4_PB           0x1
#define SYSCFG_EXTICR2_EXTI4_PC           0x2
#define SYSCFG_EXTICR2_EXTI4_PD           0x3
#define SYSCFG_EXTICR2_EXTI4_PE           0x4
#define SYSCFG_EXTICR2_EXTI4_PH           0x5

/*
 * SYSCFG convenience routines
 */

void syscfg_init(void);

/**
 * External interrupt line numbers.
 */
typedef enum syscfg_exti_num {
    SYSCFG_EXTI_0,                /**< External interrupt line 0. */
    SYSCFG_EXTI_1,                /**< External interrupt line 1. */
    SYSCFG_EXTI_2,                /**< External interrupt line 2. */
    SYSCFG_EXTI_3,                /**< External interrupt line 3. */
    SYSCFG_EXTI_4,                /**< External interrupt line 4. */
    SYSCFG_EXTI_5,                /**< External interrupt line 5. */
    SYSCFG_EXTI_6,                /**< External interrupt line 6. */
    SYSCFG_EXTI_7,                /**< External interrupt line 7. */
    SYSCFG_EXTI_8,                /**< External interrupt line 8. */
    SYSCFG_EXTI_9,                /**< External interrupt line 9. */
    SYSCFG_EXTI_10,               /**< External interrupt line 10. */
    SYSCFG_EXTI_11,               /**< External interrupt line 11. */
    SYSCFG_EXTI_12,               /**< External interrupt line 12. */
    SYSCFG_EXTI_13,               /**< External interrupt line 13. */
    SYSCFG_EXTI_14,               /**< External interrupt line 14. */
    SYSCFG_EXTI_15,               /**< External interrupt line 15. */
} syscfg_exti_num;

void syscfg_exti_select(syscfg_exti_num exti, syscfg_exti_port gpio_port);
#ifdef __cplusplus
}
#endif

#endif
