/*
 * DrFlowMeter.h
 *
 *  Created on: May 2, 2025
 *      Author: julian
 */

#ifndef INC_DRFLOWMETER_H_
#define INC_DRFLOWMETER_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Private defines -----------------------------------------------------------*/
#define TARGET_CNT_LVL1 500u  /* 10 Liters */
#define TARGET_CNT_LVL2 1000u /* 20 Liters */
#define TARGET_CNT_LIMIT (3*TARGET_CNT_LVL2)

/* Typedefs and structs ------------------------------------------------------*/
typedef enum {
	FlowMeter_Idle, FlowMeter_Measuring, FlowMeter_TargetReached,
} eDrFlowMeter;

typedef struct {
	eDrFlowMeter state;
	uint32_t pulseCount_current;
	uint32_t pulseCount_target;
} sDrFlowMeter;
/* Static variables (file-scope) ---------------------------------------------*/
/* Static vars go in C file, just add extern here if needed */
/* External variables --------------------------------------------------------*/
extern sDrFlowMeter FlowMeter1;
/* Function declarations -----------------------------------------------------*/
void DrFlowMeter_ResetInit(sDrFlowMeter *flowMeter);
void DrFlowMeter_StartMeasure(sDrFlowMeter *flowMeter, uint32_t targetCnt);
void DrFlowMeter_SetTarget(sDrFlowMeter *flowMeter, uint32_t increment);
#endif /* INC_DRFLOWMETER_H_ */
