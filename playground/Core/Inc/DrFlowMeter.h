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
#define TARGET_CNT_10L 30
#define TARGET_CNT_20L 60
#define TARGET_CNT_30L 90

/* Typedefs and structs ------------------------------------------------------*/
typedef enum
{
	FlowMeter_Idle,
	FlowMeter_Measuring,
	FlowMeter_TargetReached,
}eDrFlowMeter;

typedef struct
{
	eDrFlowMeter state;
	uint32_t pulseCount_current;
	uint32_t pulseCount_target;
}sDrFlowMeter;
/* Static variables (file-scope) ---------------------------------------------*/
/* Static vars go in C file, just add extern here if needed */
/* External variables --------------------------------------------------------*/

/* Function declarations -----------------------------------------------------*/
void DrFlowMeter_ReInit(sDrFlowMeter *flowMeter);
void DrFlowMeter_StartMeasure(sDrFlowMeter *flowMeter,  uint32_t targetCnt);


#endif /* INC_DRFLOWMETER_H_ */
