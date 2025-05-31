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
sApplElement ApplElements[8]; /* handled by dedicated Queue */

/* Queue Handles */
tQueue buttonQueue;
tQueue applQueue;
/* Queue Buffers - determining queue capacity */
sButton buttonQueueBuf[QUEUE_SIZE];
sApplElement applQueueBuf[QUEUE_SIZE];

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



void ApplHandler_MAIN(tQueue *pQueue)
{
#if (QUEUE_DEBUG == 1)
	   static uint32_t lastPrintTick = 0;
	    uint32_t now = HAL_GetTick();

	    // Only process logic if 5 seconds have passed
	    if ((now - lastPrintTick) >= 5000)
	    {
	        lastPrintTick = now;

	        if (MyQueue_IsEmpty(pQueue))
	        {
	            DBG_PRINT("Queue __ %s __ is empty, queue.count: %i", pQueue->name, pQueue->count);
	        }
	        else
	        {
	            DBG_PRINT("Queue __ %s __ has %i elements:", pQueue->name, pQueue->count);

	            for (uint32_t i = 0; i < pQueue->count; ++i)
	            {
	                uint32_t index = (pQueue->tail + i) % pQueue->capacity;
	                uint8_t *src = pQueue->buffer + (index * pQueue->elementSize);

	                // Assuming sButton is the only thing in the queue
	                sButton *btn = (sButton *)src;
	                DBG_PRINT("  [%lu] ButtonMask=0x%X", i, btn->ButtonMask);
	            }
	        }
	    }
#endif
	    // Now handle actual dequeuing and processing
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
	        // Optional: Add other non-print error handling here
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
		MyQueue_Enqueue(&applQueue,
				&ApplElements[eApplElement_FlowMeterTarget]);
		ApplElements[eApplElement_FlowMeterTarget].ApplActionState =
				ApplActionState_Enqueued;

		DBG_PRINT("Start Measure target_ %lu", FlowMeter1.pulseCount_target);

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
	static uint32_t lastPrintTick = 0;
	sApplElement ApplElToProcess;
	uint32_t now = HAL_GetTick();

	// Print contents of the queue every 5 seconds
	if ((now - lastPrintTick) >= 5000)
	{
		lastPrintTick = now;

		if (MyQueue_IsEmpty(&applQueue))
		{
			DBG_PRINT("Queue __ %s __ is empty, queue.count: %i", applQueue.name, applQueue.count);
		}
		else
		{
			DBG_PRINT("Queue __ %s __ has %i elements:", applQueue.name, applQueue.count);

			for (uint32_t i = 0; i < applQueue.count; ++i)
			{
				uint32_t index = (applQueue.tail + i) % applQueue.capacity;
				uint8_t *src = applQueue.buffer + (index * applQueue.elementSize);

				sApplElement *el = (sApplElement *)src;
				DBG_PRINT("  [%lu] ApplElement=%d, ActionState=%d",
				          i,
				          el->ApplElement,
				          el->ApplActionState);
			}
		}
	}

	// Process one queue element
	if (MyQueue_Dequeue(&applQueue, &ApplElToProcess))
	{
		switch (ApplElToProcess.ApplElement)
		{
			case eApplElement_watering_Auto:
				// Start watering mechanism: open valve -> start pump
				break;

			case eApplElement_FlowMeterTarget:
			{
				bool reached = ApplHandler_CheckFlowMeterTargetReached(&FlowMeter1);
				if (!reached)
				{
					MyQueue_Enqueue(&applQueue, &ApplElements[eApplElement_FlowMeterTarget]);
					ApplElements[eApplElement_FlowMeterTarget].ApplActionState = ApplActionState_Enqueued;
				}
				else
				{
					ApplElements[eApplElement_FlowMeterTarget].ApplActionState = ApplActionState_Processed;

					MyQueue_Enqueue(&applQueue, &ApplElements[eApplElement_watering_Stop]);
					ApplElements[eApplElement_watering_Stop].ApplActionState = ApplActionState_Enqueued;
				}
				break;
			}

			case eApplElement_watering_Stop:
				// Stop watering mechanism
				break;

			case eApplElement_watering_Timeout:
				// Handle timeout
				break;

			default:
				DBG_PRINT("Unhandled ApplElement: %d", ApplElToProcess.ApplElement);
				break;
		}
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

void ApplHandler_ProcessedApplEls(void)
{
	uint8_t foundIdx = ARRAY_COUNT(ApplElements); // Invalid index sentinel
	// Find the first processed element
	for (uint8_t idx = 0; idx < ARRAY_COUNT(ApplElements); idx++)
	{
		if (ApplElements[idx].ApplActionState == ApplActionState_Processed)
		{
			foundIdx = idx;
			break;
		}
	}

	// Handle the found index, if any
	if (foundIdx < ARRAY_COUNT(ApplElements))
	{
		switch(ApplElements[foundIdx].ApplElement)
		{
		case eApplElement_FlowMeterTarget:
			Buttons[DIN1_BUTTON_WATERINGLVL_1].ButtonActionState = ButtonActionIdle;
			Buttons[DIN2_BUTTON_WATERINGLVL_2].ButtonActionState = ButtonActionIdle;
			ApplState_watering = ApplState_watering_Idle;
			break;
		case eApplElement_watering_Auto:
			break;
		case eApplElement_watering_Stop:
			break;
		case eApplElement_watering_Timeout:
			break;
		}
		ApplElements[foundIdx].ApplActionState = ApplActionState_Idle;
	}
}
void ApplHandler_ProcessedButtons(void)
{

}
