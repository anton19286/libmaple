/**
 *  @brief General STM32 specific definitions
 */

#ifndef _STM32_H_
#define _STM32_H_

#ifdef(BOARD_discovery)
	#define PCLK1   12000000U
	#define PCLK2   24000000U
#else
	#define PCLK1   36000000U
	#define PCLK2   72000000U
#endif

#ifdef STM32_MEDIUM_DENSITY
    #define NR_INTERRUPTS 43
#else
#ifdef STM32_HIGH_DENSITY
    #define NR_INTERRUPTS 60
#else
#error "No STM32 board type defined!"
#endif
#endif

#endif

