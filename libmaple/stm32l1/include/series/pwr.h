/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2012 LeafLabs, LLC.
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
 * @file stm32l1/pwr.h
  * @brief STM32L1 Power control (PWR) support.
 */

#ifndef _LIBMAPLE_STM32L1_PWR_H_
#define _LIBMAPLE_STM32L1_PWR_H_

/** Power register map type */
// typedef struct pwr_reg_map {
//    __io uint32 CR;             /**< Control register */
//    __io uint32 CSR;            /**< Control/status register */
// } pwr_reg_map;

/*
 * Register bit definitions
 */
/* Control register */

#define PWR_CR_LPRUN_BIT			14
#define PWR_CR_FWU_BIT				10
#define PWR_CR_ULP_BIT				9
#define PWR_CR_DBP_BIT				8
#define PWR_CR_PVDE_BIT				4
#define PWR_CR_CSBF_BIT				3
#define PWR_CR_CWUF_BIT				2
#define PWR_CR_PDDS_BIT				1
#define PWR_CR_LPSDSR_BIT			0

#define PWR_CR_VOS					(0x3 << 12)
#define PWR_CR_PLS					(0x7 << 5)

/* Voltage scaling range selection */
#define PWR_CR_VOS_1_2V (0x3 << 12)
#define PWR_CR_VOS_1_5V (0x2 << 12)
#define PWR_CR_VOS_1_8V (0x1 << 12)

/* PVD level selection */
#define PWR_CR_PLS_1_9V                 (0x0 << 5)
#define PWR_CR_PLS_2_1V                 (0x1 << 5)
#define PWR_CR_PLS_2_3V                 (0x2 << 5)
#define PWR_CR_PLS_2_5V                 (0x3 << 5)
#define PWR_CR_PLS_2_7V                 (0x4 << 5)
#define PWR_CR_PLS_2_9V                 (0x5 << 5)
#define PWR_CR_PLS_3_1V                 (0x6 << 5)
#define PWR_CR_PLS_PVD_IN               (0x7 << 5)

/* Control/status register */

#define PWR_CSR_EWUP3_BIT			26
#define PWR_CSR_EWUP2_BIT			25
#define PWR_CSR_EWUP1_BIT			24
#define PWR_CSR_REGLPF_BIT			5
#define PWR_CSR_VOSF_BIT			4
#define PWR_CSR_VREFINTRDYF_BIT			3
#define PWR_CSR_PVDO_BIT			2
#define PWR_CSR_SBF_BIT				1
#define PWR_CSR_WUF_BIT				0

#define PWR_CSR_VOSF				BIT(PWR_CSR_VOSF_BIT)


#endif
