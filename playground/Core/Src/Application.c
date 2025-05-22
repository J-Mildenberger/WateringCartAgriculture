/*
 * application.c
 *
 *  Created on: May 22, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include <Application.h>
#include "PinDefines.h"
#include "DrFlowMeter.h"
#include "DrDebug.h"
/* Private defines -----------------------------------------------------------*/
/* Typedefs and structs ------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern sButton Buttons[15];
/* Static variables ----------------------------------------------------------*/
uint8_t Buttons_watering_idxs[4] =
{ DIN1_BUTTON_WATERINGLVL_1-1, DIN2_BUTTON_WATERINGLVL_2-1, DIN3_BUTTON_CTRL_PUMP_1-1,
		DIN10_FLOWMETER_DETECT-1 }; //#TODO fix this tomorrow

/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/

void Appl_checkButtons_watering(void)
{
	for (uint8_t i = 0; i < ARRAY_COUNT(Buttons_watering_idxs); i++)
	{
		_CRITICAL_SECTION_ENTER();
		sButton ButtonTemp = Buttons[Buttons_watering_idxs[i]];
		if (ButtonTemp.ButtonActionState
				== ButtonActionEnqueued)
		{
			switch (ButtonTemp.ButtonApplState_Watering)
			{
			case ButtonIdle:
				if (ButtonTemp.buttonNum == DIN1_BUTTON_WATERINGLVL_1)
				{
					ButtonTemp.ButtonApplState_Watering = ButtonWaterAuto;
					DrFlowMeter_StartMeasure(&FlowMeter1, TARGET_CNT_LVL1);
				}
				else if (ButtonTemp.buttonNum == DIN2_BUTTON_WATERINGLVL_2)
				{
					ButtonTemp.ButtonApplState_Watering = ButtonWaterAuto;
					DrFlowMeter_StartMeasure(&FlowMeter1, TARGET_CNT_LVL2);
				}
				ButtonTemp.ButtonActionState = ButtonActionProcessed;
				break;

			case ButtonWaterAuto:
				if (ButtonTemp.buttonNum == DIN1_BUTTON_WATERINGLVL_1)
				{
					DrFlowMeter_SetTarget(&FlowMeter1, TARGET_CNT_LVL1);
				}
				else if (ButtonTemp.buttonNum == DIN2_BUTTON_WATERINGLVL_2)
				{
					DrFlowMeter_SetTarget(&FlowMeter1, TARGET_CNT_LVL2);
				}
				Buttons[Buttons_watering_idxs[i]].ButtonActionState = ButtonActionProcessed;

				break;

			case ButtonWaterManually:
				// handle manual watering
				break;

			case FlowMeterTarget:
				// handle flow meter target logic
				break;

			case Timeout:
				// handle timeout
				break;

			default:
				// handle unknown or uninitialized state
				break;
			}

		}
		_CRITICAL_SECTION_EXIT();
	}

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
