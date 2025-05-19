/*
 * DrTimer.c
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include "DrTimer.h"
#include "stm32f4xx_hal.h"

/* Static variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
void DrTimer_TimDelay(uint32_t delay_ms) {
	HAL_Delay(delay_ms);
}

void DrTimer_StartTimer(sDrTimer_Timer *timer, uint32_t delayMs) {
	timer->startTime = HAL_GetTick();
	timer->delay_ms = delayMs;
}

uint8_t DrTimer_IsTimerOver(sDrTimer_Timer *timer)
{
    if ((HAL_GetTick() - timer->startTime) >= timer->delay_ms)
    {
        if (timer->timMode == eTimMode_CYCLIC)
        {
            DrTimer_StartTimer(timer, timer->delay_ms);
        }
        return 1;
    }
    return 0;
}


void DrTimer_StopwatchStart(sDrTimer_Stopwatch *stopwatch) {
	stopwatch->startTime = HAL_GetTick();
}

uint32_t DrTimer_StopwatchElapsed(sDrTimer_Stopwatch *stopwatch) {
	return HAL_GetTick() - stopwatch->startTime;
}
