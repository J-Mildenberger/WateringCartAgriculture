/*
 * DrFlowMeter.c
 *
 *  Created on: May 2, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include "DrFlowMeter.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "DrDebug.h"
/* Static variables ----------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
sDrFlowMeter FlowMeter1;
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
void DrFlowMeter_ReInit(sDrFlowMeter *flowMeter)
{
	flowMeter->pulseCount_current = 0;
	flowMeter->state = FlowMeter_Idle;
}

/* @brief Valve Application calls this Function
 *
 */
void DrFlowMeter_StartMeasure(sDrFlowMeter *flowMeter, uint32_t targetCnt)
{
	flowMeter->pulseCount_current = 0;
	flowMeter->pulseCount_target = targetCnt;
	flowMeter->state = FlowMeter_Measuring;
	DBG_PRINT("Start Measure target_ %lu", flowMeter->pulseCount_target);
}

/* @brief Call this Function by FlowMeter Pulse Interrupt Routine.
 *
 * @param incr gives possibility to buffer calls of this function
 */
void DrFlowMeter_PulseCounterCB(sDrFlowMeter *flowMeter)
{
#if (FLOWMETER_DEBUG == 1)
	static uint32_t delta = 0;
	delta++;
	if (delta >= DEBUG_FLOWPULSES_NUM)
	{
		DBG_PRINT("Flowmeter current sum of pulses _ %lu _ ",
				flowMeter->pulseCount_current);
		delta = 0;
	}
#endif
	flowMeter->pulseCount_current += 1;
	if (flowMeter->pulseCount_current >= flowMeter->pulseCount_target)
	{
		flowMeter->state = FlowMeter_TargetReached;		/* Appl. polls for FlowMeter_TargetReached */
	}
}

void DrFlowMeter_SetTarget(sDrFlowMeter *flowMeter, uint32_t increment)
{
	if (flowMeter->state == FlowMeter_TargetReached)
	{
		DBG_PRINT("ERR CANNOT SET FLOWMETER TARGET WHILE REACHED: %lu",
				flowMeter->pulseCount_target);
		return;
	}
	if (((flowMeter->pulseCount_target) + increment) <= TARGET_CNT_LIMIT)
	{
		flowMeter->pulseCount_target += increment;
		DBG_PRINT("SET FLOWMETER TARGET: %lu __ current: %lu",
				flowMeter->pulseCount_target, flowMeter->pulseCount_current);
	}
	else
	{
		DBG_PRINT(
				"ERR CANNOT SET FLOWMETER TARGET: %lu __ current: %lu __ incr: %lu",
				flowMeter->pulseCount_target, flowMeter->pulseCount_current,
				increment);
	}
	return;
}
