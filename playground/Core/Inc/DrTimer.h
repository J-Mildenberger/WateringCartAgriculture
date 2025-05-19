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
/* Private defines -----------------------------------------------------------*/

/* Typedefs and structs ------------------------------------------------------*/
typedef enum
{
	eTimMode_ONESHOT,
	eTimMode_CYCLIC,
} eTimMode;

typedef struct {
	eTimMode timMode;
	uint32_t startTime;
	uint32_t delay_ms;
} sDrTimer_Timer;

typedef struct {
	uint32_t startTime;
} sDrTimer_Stopwatch;
/* Static variables (file-scope) ---------------------------------------------*/
/* Static vars go in C file, just add extern here if needed */
/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
void DrTimer_TimDelay(uint32_t delay_ms);
void DrTimer_StartTimer(sDrTimer_Timer *timer, uint32_t delayMs);
uint8_t DrTimer_IsTimerOver(sDrTimer_Timer *timer);
void DrTimer_StopwatchStart(sDrTimer_Stopwatch *stopwatch);
uint32_t DrTimer_StopwatchElapsed(sDrTimer_Stopwatch *stopwatch);

//TIM_HandleTypeDef
#endif /* INC_DRTIMER_H_ */
