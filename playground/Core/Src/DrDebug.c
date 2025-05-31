/*
 * DrDebug.c
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include "DrDebug.h"
#include "Application.h"
/* Static variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
const char* ApplicationStateWateringToString(void)
{
	switch (ApplState_watering)
	{
	case ApplState_watering_Idle:
		return "Idle";
	case ApplState_watering_Auto:
		return "WaterAuto";
	case ApplState_watering_Manually:
		return "WaterManually";
	case ApplState_watering_FlowMeterTarget:
		return "FlowMeterTarget";
	case ApplState_watering_Timeout:
		return "Timeout";

	default:
		return "UnknownState";
	}
}

const char* ButtonActionStateToString(eButtonActionState state)
{
	switch (state)
	{
	case ButtonActionIdle:
		return "Idle";
	case ButtonActionEnqueued:
		return "Enqueued";
	case ButtonActionProcessed:
		return "Processed";

	default:
		return "UnknownState";
	}
}
