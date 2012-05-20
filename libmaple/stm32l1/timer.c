/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
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
 * @file   libmaple/stm32l1/timer.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  STM32L1 timer support.
 */

#include <libmaple/timer.h>
#include "timer_private.h"

/*
 * Devices
 *
 * Defer to the timer_private API.
 */

static DECLARE_GENERAL_TIMER(timer1, 1);
static DECLARE_GENERAL_TIMER(timer2, 2);
static DECLARE_GENERAL_TIMER(timer3, 3);
static DECLARE_GENERAL_TIMER(timer4, 4);

/** Timer 1 device (general-purpose) */
timer_dev *TIMER1 = &timer1;
/** Timer 2 device (general-purpose) */
timer_dev *TIMER2 = &timer2;
/** Timer 3 device (general-purpose) */
timer_dev *TIMER3 = &timer3;
/** Timer 4 device (general-purpose) */
timer_dev *TIMER4 = &timer4;

static DECLARE_BASIC_TIMER(timer6, 6);
static DECLARE_BASIC_TIMER(timer7, 7);
/** Timer 6 device (basic) */
timer_dev *TIMER6 = &timer6;
/** Timer 7 device (basic) */
timer_dev *TIMER7 = &timer7;

/* TIM9 has UIE, CC1IE, CC2IE, TIE bits in DIER. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer9, 9, TIMER_DIER_TIE_BIT);
/* TIM10 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer10, 10, TIMER_DIER_CC1IE_BIT);
/* TIM11 has UIE, CC1IE. */
static DECLARE_RESTRICTED_GENERAL_TIMER(timer11, 11, TIMER_DIER_CC1IE_BIT);

/** Timer 9 device (general-purpose) */
timer_dev *TIMER9 = &timer9;
/** Timer 10 device (general-purpose) */
timer_dev *TIMER10 = &timer10;
/** Timer 11 device (general-purpose) */
timer_dev *TIMER11 = &timer11;

/*
 * Routines
 */

/**
 * @brief Call a function on timer devices.
 * @param fn Function to call on each timer device.
 */
void timer_foreach(void (*fn)(timer_dev*)) {
    fn(TIMER1);
    fn(TIMER2);
    fn(TIMER3);
    fn(TIMER4);
    fn(TIMER6);
    fn(TIMER7);
    fn(TIMER9);
    fn(TIMER10);
    fn(TIMER11);
}

/*
 * IRQ handlers
 *
 * Defer to the timer_private dispatch API.
 *
 */

void __irq_tim2(void) {
    dispatch_general(TIMER2);
}

void __irq_tim3(void) {
    dispatch_general(TIMER3);
}

void __irq_tim4(void) {
    dispatch_general(TIMER4);
}

void __irq_tim6(void) {
    dispatch_basic(TIMER6);
}

void __irq_tim7(void) {
    dispatch_basic(TIMER7);
}

void __irq_tim9(void) {
    dispatch_general(TIMER9);
}

void __irq_tim10(void) {
    dispatch_general(TIMER10);
}

void __irq_tim11(void) {
    dispatch_general(TIMER11);
}

