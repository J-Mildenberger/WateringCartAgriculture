/*
 * DrTimer.h
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

#ifndef INC_DRTIMER_H_
#define INC_DRTIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
/* Private defines -----------------------------------------------------------*/
/* Typedefs and structs ------------------------------------------------------*/
/* Static variables (file-scope) ---------------------------------------------*/
/* Static vars go in C file, just add extern here if needed */
/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
void TimerDelay_synch(uint32_t delay_ms);
void Test(TIM_HandleTypeDef a);
//TIM_HandleTypeDef
#endif /* INC_DRTIMER_H_ */
