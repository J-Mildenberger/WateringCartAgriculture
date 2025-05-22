/*
 * DrDebug.c
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include "DrDebug.h"

/* Static variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
const char* ButtonApplicationStateWateringToString(eButtonApplState_Watering state)
{
	switch (state)
	{
	case ButtonIdle:
		return "Idle";
	case ButtonWaterAuto:
		return "WaterAuto";
	case ButtonWaterManually:
		return "WaterManually";
	case FlowMeterTarget:
		return "FlowMeterTarget";
	case Timeout:
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
