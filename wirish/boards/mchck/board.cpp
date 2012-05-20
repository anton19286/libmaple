/******************************************************************************
 * The MIT License
 *
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
 * @file   wirish/boards/mchck/board.cpp
 * @author Anton Eltchaninov <anton.eltchaninov@gmail.com>
 * @brief  mc hck board file.
 */

#include <board/board.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>
#include <wirish/wirish_types.h>

void boardInit(void) {
//    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
}

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {

    {GPIOA, TIMER9, ADC1,  3, 2,    3}, /* D0/PA3 */
    {GPIOA, TIMER9, ADC1,  2, 1,    2}, /* D1/PA2 */
    {GPIOA,   NULL, ADC1,  0, 0,    0}, /* D2/PA0 */
    {GPIOA, TIMER2, ADC1,  1, 2,    1}, /* D3/PA1 */
    {GPIOB, TIMER3, NULL,  5, 2, ADCx}, /* D4/PB5 */
    {GPIOB, TIMER4, NULL,  6, 1, ADCx}, /* D5/PB6 */
    {GPIOA,   NULL, NULL,  8, 0, ADCx}, /* D6/PA8 */
    {GPIOA,   NULL, NULL,  9, 0, ADCx}, /* D7/PA9 */
    {GPIOA,   NULL, NULL, 10, 0, ADCx}, /* D8/PA10 */
    {GPIOB, TIMER4, NULL,  7, 2, ADCx}, /* D9/PB7  */
    {GPIOA,   NULL, ADC1,  4, 0,    4}, /* D10/PA4 */
    {GPIOA, TIMER3, ADC1,  7, 2,    7}, /* D11/PA7 */
    {GPIOA, TIMER3, ADC1,  6, 1,    6}, /* D12/PA6 */
    {GPIOA,   NULL, ADC1,  5, 0,    5}, /* D13/PA5 */
    {GPIOB, TIMER4, NULL,  8, 3, ADCx}, /* D14/PB8 */
    {GPIOC,   NULL, NULL, 13, 0, ADCx}, /* D15/PC13 (LED) */
    {GPIOC,   NULL, NULL, 14, 0, ADCx}, /* D16/PC14 */
    {GPIOC,   NULL, NULL, 15, 0, ADCx}, /* D17/PC15 */
    {GPIOB, TIMER4, NULL,  9, 4, ADCx}, /* D18/PB9 */
    {GPIOB, TIMER3, ADC1,  0, 3,    8}, /* D19/PB0 */
    {GPIOB, TIMER3, ADC1,  1, 4,    9}, /* D20/PB1 */
    {GPIOB, TIMER2, NULL, 10, 3, ADCx}, /* D21/PB10 */
    {GPIOB, TIMER2, NULL, 11, 4, ADCx}, /* D22/PB11 */
    {GPIOB,TIMER10, ADC1, 12, 1,   18}, /* D23/PB12 */
    {GPIOB, TIMER9, ADC1, 13, 1,   19}, /* D24/PB13 */
    {GPIOB,   NULL, ADC1, 14, 0,   20}, /* D25/PB14 */
    {GPIOB,TIMER11, ADC1, 15, 1,   21}, /* D26/PB15 */
    {GPIOA,   NULL, NULL, 11, 0, ADCx}, /* D27/PA11 */
    {GPIOA,   NULL, NULL, 12, 0, ADCx}, /* D28/PA12 */
    {GPIOA,   NULL, NULL, 15, 0, ADCx}, /* D29/PA15 */
    {GPIOB,   NULL, NULL,  2, 0, ADCx}, /* D30/PB2 */
    {GPIOB,   NULL, NULL,  3, 0, ADCx}, /* D31/PB3 */
    {GPIOB,   NULL, NULL,  4, 0, ADCx}, /* D32/PB4 */
};

extern const uint8 boardPWMPins[] __FLASH__ = {
    0, 1, 3, 4, 5, 9, 11, 12, 14, 18, 19, 20, 21, 22, 23, 24, 26
};

extern const uint8 boardADCPins[] __FLASH__ = {
    0, 1, 2, 3, 10, 11, 12, 13, 19, 20, 23, 24, 25, 26
};

extern const uint8 boardUsedPins[] __FLASH__ = {
    BOARD_LED_PIN
};
