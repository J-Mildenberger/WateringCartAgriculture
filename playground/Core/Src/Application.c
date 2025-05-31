/*
 * application.c
 *
 *  Created on: May 22, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include <Application.h>
#include "PinDefines.h"
#include "MyQueue.h"
#include "DrFlowMeter.h"
#include "DrDebug.h"
#include "string.h"
/* Private defines -----------------------------------------------------------*/
/* Typedefs and structs ------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern sButton Buttons[15]; /* handled by dedicated Queue */
/* Static variables ----------------------------------------------------------*/
eApplState_watering ApplState_watering;
sApplElements ApplElements[8]; /* handled by dedicated Queue */

/* Queue Handles */
tQueue buttonQueue;
tQueue applQueue;
/* Queue Buffers - determining queue capacity */
sButton buttonQueueBuf[QUEUE_SIZE];
sApplElements applQueueBuf[QUEUE_SIZE];

/* Private function prototypes -----------------------------------------------*/
void ApplHandler_WateringButtons(sButton *pButton);
bool ApplHandler_CheckFlowMeterTargetReached(sDrFlowMeter *pFlowMeter);
/* Function definitions ------------------------------------------------------*/

void Appl_InitApplElements(void)
{
	memset(&ApplElements, 0x00, sizeof(ApplElements));
	/* Application FlowMeter Target Counter	 */
	ApplElements[eApplElement_FlowMeterTarget].ApplElement =
			eApplElement_FlowMeterTarget;
	/* Application watering automatic */
	ApplElements[eApplElement_watering_Auto].ApplElement =
			eApplElement_watering_Auto;
	/* Application watering stop */
	ApplElements[eApplElement_watering_Stop].ApplElement =
			eApplElement_watering_Stop;
}

void Appl_Processed_to_Idle(void)
{
	for (uint8_t i = 0; i < ARRAY_COUNT(Buttons); i++)
	{
		if (Buttons[i].ButtonActionState == ButtonActionProcessed)
		{
			DBG_PRINT_BUTTON(&Buttons[i]);
			Buttons[i].ButtonActionState = ButtonActionIdle;
		}
	}
}

void Appl_ApplHandler_MAIN(tQueue *pQueue)
{
	sButton buttonToProcess;
	if (MyQueue_Dequeue(pQueue, &buttonToProcess))
	{
		if (ButtonMask_Watering & buttonToProcess.ButtonMask)
		{
			ApplHandler_WateringButtons(&buttonToProcess);
		}
		// #TODO think about processed flag here
	}
	else
	{
		DBG_PRINT("Queue __ %s __ is empty, queue.count: %i",pQueue->name, pQueue->count);
		/* #TODO SysFailure Handling */
		// Timeout
		// Force Safe State
		// SystemReset
	}

}

void ApplHandler_WateringButtons(sButton *pButton)
{
	switch (ApplState_watering)
	{
	case ApplState_watering_Idle:
		if (pButton->buttonNum == DIN1_BUTTON_WATERINGLVL_1)
		{
			DrFlowMeter_StartMeasure(&FlowMeter1, TARGET_CNT_LVL1);
		}
		else if (pButton->buttonNum == DIN2_BUTTON_WATERINGLVL_2)
		{
			DrFlowMeter_StartMeasure(&FlowMeter1, TARGET_CNT_LVL2);
		}
		else
		{
			DBG_PRINT(
					"ERR Button to be dequeued - wrong state info as follows:");
			DBG_PRINT_BUTTON(pButton);
			pButton->ButtonActionState = ButtonActionIdle;
			return;
		}

		ApplState_watering = ApplState_watering_Auto;
		MyQueue_Enqueue(&applQueue, &ApplElements[eApplElement_watering_Auto]);
		ApplElements[eApplElement_watering_Auto].ApplActionState =
				ApplActionState_Enqueued;
		MyQueue_Enqueue(&applQueue, &ApplElements[eApplElement_FlowMeterTarget]);
		ApplElements[eApplElement_FlowMeterTarget].ApplActionState =
				ApplActionState_Enqueued;

		DBG_PRINT("Start Measure target_ %lu", FlowMeter1.pulseCount_target);
		pButton->ButtonActionState = ButtonActionProcessed;
		break;

	case ApplState_watering_Auto:
		if (pButton->buttonNum == DIN1_BUTTON_WATERINGLVL_1)
		{
			DrFlowMeter_SetTarget(&FlowMeter1, TARGET_CNT_LVL1);
		}
		else if (pButton->buttonNum == DIN2_BUTTON_WATERINGLVL_2)
		{
			DrFlowMeter_SetTarget(&FlowMeter1, TARGET_CNT_LVL2);
		}
		pButton->ButtonActionState = ButtonActionProcessed;

		break;

	case ApplState_watering_Manually:
		// handle manual watering
		break;

	default:
		// handle unknown or uninitialized state
		break;
	}
}

void ApplHandler_Watering(void)
{

	sApplElements ApplElToProcess;
	MyQueue_Dequeue(&applQueue, &ApplElToProcess);

	if (ApplElToProcess.ApplElement == eApplElement_watering_Auto)
	{
		/* start watering mechanism (1st) open valve -> (2nd) start pump */

	}
	else if (ApplElToProcess.ApplElement == eApplElement_FlowMeterTarget)
	{

		bool reached = ApplHandler_CheckFlowMeterTargetReached(&FlowMeter1);
		if (!reached) /* if not reached - enqueue again */
		{
			MyQueue_Enqueue(&applQueue,
					&ApplElements[eApplElement_FlowMeterTarget]);
			ApplElements[eApplElement_FlowMeterTarget].ApplActionState =
					ApplActionState_Enqueued;
		}
		else if (reached) /* if reached mark as processed and enqueue watering stop mechanism */
		{
			ApplElements[eApplElement_FlowMeterTarget].ApplActionState =
					ApplActionState_Processed;

			MyQueue_Enqueue(&applQueue,
					&ApplElements[eApplElement_watering_Stop]);
			ApplElements[eApplElement_watering_Stop].ApplActionState =
					ApplActionState_Enqueued;
		}
	}
	else if (ApplElToProcess.ApplElement == eApplElement_watering_Stop)
	{

	}
	else if (ApplElToProcess.ApplElement == ApplState_watering_Timeout)
	{

	}
}


bool ApplHandler_CheckFlowMeterTargetReached(sDrFlowMeter *pFlowMeter)
{
	if (pFlowMeter->pulseCount_current >= pFlowMeter->pulseCount_target)
	{
		DBG_PRINT("REACHED FLOWMETER TARGET: %lu __ current: %lu",
				pFlowMeter->pulseCount_target, pFlowMeter->pulseCount_current);
		return true;
	}

	return false;
}
