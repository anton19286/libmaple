/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010, 2011 LeafLabs, LLC.
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
 * @file libmaple/stm32l1/stm32.h
 * @brief STM32L1 chip- and series-specific definitions.
 */

#ifndef _LIBMAPLE_STM32L1_H_
#define _LIBMAPLE_STM32L1_H_

#ifdef __cplusplus
extern "C" {
#endif

#define STM32_MCU_SERIES                STM32_SERIES_L1
#define STM32_MEDIUM_DENSITY


/*
 * MCU-specific values.
 *
 * You can use this section to override any of the below settings on a
 * per-MCU basis. For example, if your MCU has different STM32_PCLK1
 * or STM32_PCLK2 values, you can set them here and the values for
 * STM32F103 microcontrollers set below won't take effect.
 */

#if defined(MCU_STM32L152RB) || defined(MCU_STM32L151CB)
#   define STM32_NR_GPIO_PORTS          6
#   define STM32_DELAY_US_MULT          8 //???
#   define STM32_SRAM_END              ((void*)0x20004000)
#   define NR_GPIO_PORTS               STM32_NR_GPIO_PORTS
#   define DELAY_US_MULT               STM32_DELAY_US_MULT
#   define STM32_HAVE_FSMC              0
#else
#error "Unrecognized STM32L1 MCU, or no MCU specified. Add something like " \
       "-DMCU_STM32F151RB to your compiler arguments."
#endif

/*
 * Derived values.
 */

#    define STM32_HAVE_USB             1
#    define STM32_NR_INTERRUPTS       45

/*
 * Clock configuration.
 *
 * We've currently got values for F103 MCUs operating at the fastest
 * possible speeds.
 *
 * You can patch these for your line, MCU, clock configuration,
 * etc. here or by setting cflags when compiling libmaple.
 */
#    ifndef STM32_PCLK1
#    define STM32_PCLK1                     32000000U
#    endif
#    ifndef STM32_PCLK2
#    define STM32_PCLK2                     32000000U
#    endif


#ifdef __cplusplus
}
#endif

#endif
