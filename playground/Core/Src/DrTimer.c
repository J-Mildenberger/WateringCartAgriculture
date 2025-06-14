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
#include "DrDebug.h"
#include "Application.h"
/* Static variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
void DrTimer_TimDelay(uint32_t delay_ms) {
	DBG_PRINT("HAL_Delay _%lu_ ...", delay_ms);
	HAL_Delay(delay_ms);
}

void DrTimer_StartTimer(sDrTimer_Timer *timer, uint32_t delayMs) {
	timer->startTime = HAL_GetTick();
	timer->delay_ms = delayMs;
	timer->active = true;
}

uint8_t DrTimer_IsTimerOver(sDrTimer_Timer *timer)
{
	if (timer->active == true)
	{
		if ((HAL_GetTick() - timer->startTime) >= timer->delay_ms)
		    {
		        if (timer->timMode == eTimMode_CYCLIC)
		        {
		            DrTimer_StartTimer(timer, timer->delay_ms);
		        }
		        timer->active = false;
		        return 1;
		    }
	}
    return 0;
}


void DrTimer_StopwatchStart(sDrTimer_Stopwatch *stopwatch) {
	stopwatch->startTime = HAL_GetTick();
}

uint32_t DrTimer_StopwatchElapsed(sDrTimer_Stopwatch *stopwatch) {
	return HAL_GetTick() - stopwatch->startTime;
}


volatile uint8_t overflow_count = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM4)
    {
        overflow_count++;
        if (overflow_count >= WATERING_WDG_TIME)
        {
            overflow_count = 0;
            Appl_WateringWatchdogHit();
        }
    }
}

void Start_TIM4_OneShot(void)
{
    overflow_count = 0;
    __HAL_TIM_SET_COUNTER(&htim4, 0);               // Reset hardware counter
    HAL_TIM_Base_Start_IT(&htim4);                  // Start timer in interrupt mode
}

void Cancel_TIM4_OneShot(void)
{
    HAL_TIM_Base_Stop_IT(&htim4);
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    overflow_count = 0;
}
