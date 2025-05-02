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

/* Static variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
void DrFlowMeter_ReInit(sDrFlowMeter *flowMeter) {
	flowMeter->pulseCount_current = 0;
	flowMeter->state = FlowMeter_Idle;
}

/* @brief Valve Application calls this Function
 *
 */
void DrFlowMeter_StartMeasure(sDrFlowMeter *flowMeter, uint32_t targetCnt) {
	flowMeter->pulseCount_current = 0;
	flowMeter->pulseCount_target = targetCnt;
	flowMeter->state = FlowMeter_Measuring;
}

/* @brief Call this Function by FlowMeter Pulse Interrupt Routine.
 *
 * @param incr gives possibility to buffer calls of this function
 */
void DrFlowMeter_PulseCounterCB(sDrFlowMeter *flowMeter, uint16_t incr) {
	if (flowMeter->state == FlowMeter_Measuring) {
		flowMeter->pulseCount_current += incr;
		if (flowMeter->pulseCount_current >= flowMeter->pulseCount_target) {
			flowMeter->state = FlowMeter_TargetReached;
			/* To reduce complexity and multiple application modes,
			 Valve appl. polls for FlowMeter_TargetReached */
		}
	}
}
