/*
 * DrTimer.c
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */


/* Includes ------------------------------------------------------------------*/
#include "DrTimer.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

/* Static variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
void TimerDelay_synch(uint32_t delay_ms) {
	HAL_Delay(delay_ms);
}
