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
void DrTimer_TimDelay(uint32_t delay_ms) {
	HAL_Delay(delay_ms);
}

void DrTimer_StartTimer(sDrTimer_Timer *timer, uint32_t delayMs) {
	timer->startTime = HAL_GetTick();
	timer->delay = delayMs;
}

uint8_t DrTimer_IsTimerOver(sDrTimer_Timer *timer) {
	return (HAL_GetTick() - timer->startTime) >= timer->delay;
}

void DrTimer_StopwatchStart(sDrTimer_Stopwatch *stopwatch) {
	stopwatch->startTime = HAL_GetTick();
}

uint32_t DrTimer_StopwatchElapsed(sDrTimer_Stopwatch *stopwatch) {
	return HAL_GetTick() - stopwatch->startTime;
}
