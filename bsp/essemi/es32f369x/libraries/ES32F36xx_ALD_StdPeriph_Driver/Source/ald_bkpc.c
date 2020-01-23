/**
  *********************************************************************************
  *
  * @file    ald_bkpc.c
  * @brief   BKPC module driver.
  *
  * @version V1.0
  * @date    15 Dec 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_bkpc.h"
#include "ald_rtc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup BKPC BKPC
  * @brief BKPC module driver
  * @{
  */
#ifdef ALD_BKPC

/** @defgroup BKPC_Public_Functions BKPC Public Functions
  * @{
  */

/** @addtogroup BKPC_Public_Functions_Group1 Peripheral Control functions
  * @brief Peripheral Control functions
  *
  * @verbatim
  ==============================================================================
              ##### Peripheral Control functions #####
  ==============================================================================
  [..]  This section provides functions allowing to:
    (+) ald_bkpc_ldo_config() API can configure LDO in backup field.
    (+) ald_bkpc_bor_config() API can configure BOR in backup field.

    @endverbatim
  * @{
  */

/**
  * @brief  Configure standby wakeup in backup field
  * @param  port: Wakeup port
  * @param  level: HIGH/LOW.
  * @retval None
  */
void ald_bkpc_standby_wakeup_config(bkpc_wakeup_port_t port, bkpc_wakeup_level_t level)
{
	assert_param(IS_BKPC_WAKEUP_PORT(port));
	assert_param(IS_BKPC_WAKEUP_LEVEL(level));

	BKPC_UNLOCK();
	SET_BIT(BKPC->CR, BKPC_CR_WKPEN_MSK);
	MODIFY_REG(BKPC->CR, BKPC_CR_WKPS_MSK, port << BKPC_CR_WKPS_POSS);
	MODIFY_REG(BKPC->CR, BKPC_CR_WKPOL_MSK, level << BKPC_CR_WKPOL_POS);
	BKPC_LOCK();

	return;
}

/**
  * @brief  Configure rtc clock in backup field
  * @param  clock: Clock
  * @retval None
  */
void ald_bkpc_rtc_clock_config(bkpc_preh_clk_t clock)
{
	assert_param(IS_BKPC_PREH_CLOCK(clock));

	BKPC_UNLOCK();
	MODIFY_REG(BKPC->PCCR, BKPC_PCCR_RTCCS_MSK, clock << BKPC_PCCR_RTCCS_POSS);
	BKPC_LOCK();

	return;
}

/**
  * @brief  Configure tsense clock in backup field
  * @param  clock: Clock
  * @retval None
  */
void ald_bkpc_tsense_clock_config(bkpc_preh_clk_t clock)
{
	assert_param(IS_BKPC_PREH_CLOCK(clock));

	BKPC_UNLOCK();
	MODIFY_REG(BKPC->PCCR, BKPC_PCCR_TSENSECS_MSK, clock << BKPC_PCCR_TSENSECS_POSS);
	BKPC_LOCK();

	return;
}
/**
  * @}
  */

/** @addtogroup BKPC_Public_Functions_Group2 IO operation functions
  * @brief IO operation functions
  *
  * @verbatim
  ==============================================================================
              ##### IO operation functions #####
  ==============================================================================
  [..]  This section provides functions allowing to:
    (+) ald_bkpc_write_ram() API can write data in backup ram.
    (+) ald_bkpc_read_ram() API can read data from backup ram.

    @endverbatim
  * @{
  */

/**
  * @brief  Write data into backup ram.
  * @param  idx: Index of backup word.
  * @param  value: Value which will be written to backup ram.
  * @retval None
  */
void ald_bkpc_write_ram(uint8_t idx, uint32_t value)
{
	assert_param(IS_BKPC_RAM_IDX(idx));

	RTC_UNLOCK();
	WRITE_REG(RTC->BKPR[idx], value);
	RTC_LOCK();

	return;
}

/**
  * @brief  Read data from backup ram.
  * @param  idx: Index of backup word.
  * @retval The data.
  */
uint32_t ald_bkpc_read_ram(uint8_t idx)
{
	assert_param(IS_BKPC_RAM_IDX(idx));

	return READ_REG(RTC->BKPR[idx]);
}
/**
  * @}
  */

/**
  * @}
  */
#endif /* ALD_BKPC */
/**
  * @}
  */

/**
  * @}
  */
