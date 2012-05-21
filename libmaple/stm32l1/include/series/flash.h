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
 * @file libmaple/stm32l1/flash.h
 * @brief STM32L1 Flash header.
 *
 * Provides register map, base pointer, and register bit definitions
 * for the Flash controller on the STM32F1 line, along with
 * series-specific configuration values.
 */

#ifndef _LIBMAPLE_STM32L1_FLASH_H_
#define _LIBMAPLE_STM32L1_FLASH_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple.h>

/*
 * Register map
 */

/** Flash register map type */
typedef struct flash_reg_map {
    __io uint32 ACR;             /**< Access control register */
    __io uint32 PECR;            /**< Program/erase control register */
    __io uint32 PDKEYR;          /**< Power down key register */
    __io uint32 PEKEYR;          /**< SProgram/erase key register */
    __io uint32 PRGKEYR;         /**< Program memory key register */
    __io uint32 OPTKEYR;         /**< Option byte key register */
    __io uint32 SR;              /**< Status register */
    __io uint32 OBR;             /**< Option byte register */
    __io uint32 WRPR1;           /**< Write protection register 1 */
	const uint32 RESERVED[0x5C];
    __io uint32 WRPR2;           /**< Write protection register 2 */
    __io uint32 WRPR3;           /**< Write protection register 3 */
} flash_reg_map;

/** Flash register map base pointer */
#define FLASH_BASE                      ((struct flash_reg_map*)0x40023C00)

/*
 * Register bit definitions
 */

/* Access control register */

#define FLASH_ACR_RUN_PD_BIT            4
#define FLASH_ACR_SLEEP_PD_BIT          3
#define FLASH_ACR_ACC64_BIT             2
#define FLASH_ACR_PRFTEN_BIT            1
#define FLASH_ACR_LATENCY_BIT           0

#define FLASH_ACR_RUN_PD                BIT(FLASH_ACR_RUN_PD_BIT)
#define FLASH_ACR_SLEEP_PD              BIT(FLASH_ACR_SLEEP_PD_BIT)
#define FLASH_ACR_ACC64                 BIT(FLASH_ACR_ACC64_BIT)
#define FLASH_ACR_PRFTEN                BIT(FLASH_ACR_PRFTEN_BIT)
#define FLASH_ACR_LATENCY               BIT(FLASH_ACR_LATENCY_BIT)

/* Status register */

#define FLASH_SR_OPTVERRUSR_BIT         12
#define FLASH_SR_OPTVERR_BIT            11
#define FLASH_SR_SIZEERR_BIT            10
#define FLASH_SR_PGAERR_BIT             9
#define FLASH_SR_WRPERR_BIT             8
#define FLASH_SR_READY_BIT              3
#define FLASH_SR_ENDHV_BIT              2
#define FLASH_SR_EOP_BIT                1
#define FLASH_SR_BSY_BIT                0

#define FLASH_SR_OPTVERRUSR         	BIT(FLASH_SR_OPTVERRUSR_BIT)
#define FLASH_SR_OPTVERR            	BIT(FLASH_SR_OPTVERR_BIT)
#define FLASH_SR_SIZEERR            	BIT(FLASH_SR_SIZEERR_BIT)
#define FLASH_SR_PGAERR                 BIT(FLASH_SR_PGARR_BIT)
#define FLASH_SR_WRPERR                 BIT(FLASH_SR_WRPERR_BIT)
#define FLASH_SR_READY              	BIT(FLASH_SR_READY_BIT)
#define FLASH_SR_ENDHV              	BIT(FLASH_SR_ENDHV_BIT)
#define FLASH_SR_EOP                    BIT(FLASH_SR_EOP_BIT)
#define FLASH_SR_BSY                    BIT(FLASH_SR_BSY_BIT)

/* Control register */

#define FLASH_PECR_OBL_LAUNCH_BIT         18
#define FLASH_PECR_ERRIE_BIT              17
#define FLASH_PECR_EOPIE_BIT              16
#define FLASH_PECR_PARALLELBANK_BIT       15
#define FLASH_PECR_FPRG_BIT		  10
#define FLASH_PECR_ERASE_BIT       	  9
#define FLASH_PECR_FTDW_BIT               8
#define FLASH_PECR_DATA_BIT               4
#define FLASH_PECR_PROG_BIT            	  3
#define FLASH_PECR_OPTLOCK_BIT            2
#define FLASH_PECR_PRGLOCK_BIT            1
#define FLASH_PECR_PELOCK_BIT             0

#define FLASH_PECR_OBL_LAUNCH         	  BIT(FLASH_PECR_OBL_LAUNCH_BIT)
#define FLASH_PECR_ERRIE                  BIT(FLASH_PECR_ERRIE_BIT)
#define FLASH_PECR_EOPIE                  BIT(FLASH_PECR_EOPIE_BIT)
#define FLASH_PECR_PARALLELBANK    	  BIT(FLASH_PECR_PARALLELBANK_BIT)
#define FLASH_PECR_FPRG		    	  BIT(FLASH_PECR_FPRG_BIT)
#define FLASH_PECR_ERASE       		  BIT(FLASH_PECR_ERASE_BIT)
#define FLASH_PECR_FTDW          	  BIT(FLASH_PECR_FTDW_BIT)
#define FLASH_PECR_DATA           	  BIT(FLASH_PECR_DATA_BIT)
#define FLASH_PECR_PROG	            	  BIT(FLASH_PECR_PROG_BIT)

#define FLASH_PECR_OPTLOCK                BIT(FLASH_PECR_OPTLOCK_BIT)
#define FLASH_PECR_PRGLOCK                BIT(FLASH_PECR_PRGLOCK_BIT)
#define FLASH_PECR_PELOCK                 BIT(FLASH_PECR_PELOCK_BIT)

/* Option byte register */

#define FLASH_OBR_BFB2_BIT              23
#define FLASH_OBR_nRST_STDBY_BIT        22
#define FLASH_OBR_nRST_STOP_BIT         21
#define FLASH_OBR_IWDG_SW_BIT           20

#define FLASH_OBR_BOR_LEV               (0xF << 16)
#define FLASH_OBR_RDPRT                 0xFF
#define FLASH_OBR_BFB2                  BIT(FLASH_OBR_BFB2_BIT)
#define FLASH_OBR_nRST_STDBY            BIT(FLASH_OBR_nRST_STDBY_BIT)
#define FLASH_OBR_nRST_STOP             BIT(FLASH_OBR_nRST_STOP_BIT)
#define FLASH_OBR_IWDG_SW               BIT(FLASH_OBR_WDG_SW_BIT)

/*
 * Series-specific configuration values.
 */

#define FLASH_SAFE_WAIT_STATES          FLASH_WAIT_STATE_1

/* Flash memory features available via ACR */
enum {
    FLASH_PREFETCH   = FLASH_ACR_PRFTEN,
    FLASH_ACC64      = FLASH_ACR_ACC64,
    FLASH_HALF_CYCLE = 0x0,	    /* Not available on STM32L1 */
    FLASH_ICACHE     = 0x0,     /* Not available on STM32L1 */
    FLASH_DCACHE     = 0x0,     /* Not available on STM32L1 */
};

#ifdef __cplusplus
}
#endif

#endif
