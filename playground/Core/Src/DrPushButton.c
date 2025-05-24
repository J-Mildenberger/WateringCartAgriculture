/*
 * DrPushButton.c
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include "DrPushButton.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_gpio.h"
#include "DrTimer.h"
#include "DrDebug.h"
#include "string.h"
#include "PinDefines.h"
#include "DrFlowMeter.h"
#include "DrSystem.h"
/* Private defines ----------------------------------------------------------*/

/* Static variables ----------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
sButton Buttons[15];

/* Private function prototypes -----------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void DrPushButton_InitResetButtons(void)
{
	memset(&Buttons[0], 0x00, sizeof(Buttons));
	/* Button 1
	 * DIN1_BUTTON_WATERINGLVL_1
	 */
	Buttons[0].buttonNum = DIN1_BUTTON_WATERINGLVL_1;
	Buttons[0].HAL_GPIO.GPIOx = GPIOA;
	Buttons[0].HAL_GPIO.GPIO_Pin = GPIO_PIN_12;

	/* Button 2
	 * DIN2_BUTTON_WATERINGLVL_2
	 */
	Buttons[1].buttonNum = DIN2_BUTTON_WATERINGLVL_2;
	Buttons[1].HAL_GPIO.GPIOx = GPIOA;
	Buttons[1].HAL_GPIO.GPIO_Pin = GPIO_PIN_11;
	/* Button 3
	 * DIN3_BUTTON_CTRL_PUMP_1
	 */
	Buttons[2].buttonNum = DIN3_BUTTON_CTRL_PUMP_1;
	Buttons[2].HAL_GPIO.GPIOx = GPIOB;
	Buttons[2].HAL_GPIO.GPIO_Pin = GPIO_PIN_12;

	/* Button 12
	 * DIN11_BUTTON_EVALUSER
	 */
	Buttons[12].buttonNum = DIN11_BUTTON_EVALUSER;
	Buttons[12].HAL_GPIO.GPIOx = GPIOC;
	Buttons[12].HAL_GPIO.GPIO_Pin = GPIO_PIN_13;

}

eDrPushButton_ButtonState DrPushButton_ButtonGetState(sButton *button)
{
	GPIO_PinState res = HAL_GPIO_ReadPin(button->HAL_GPIO.GPIOx,
			button->HAL_GPIO.GPIO_Pin);
	eDrPushButton_ButtonState ret;
	if (res == GPIO_PIN_RESET)
	{
		ret = ButtonReleased;
	}
	if (res == GPIO_PIN_SET)
	{
		ret = ButtonPushed;
	}
	return ret;
}

void DrPushButton_ButtonReleasedCB(sButton *button)
{
	if (button->ButtonActionState == ButtonActionIdle)
	{
		button->ButtonActionState = ButtonActionEnqueued;
		Appl_notify();
		DBG_PRINT_BUTTON(button);
	}
}

void DrPushButton_ButtonPushedCB(sButton *button)
{
	DBG_PRINT_BUTTON(button);
	switch (button->ButtonApplState_Watering)
	{
	case ButtonIdle:
		// Your code for ButtonIdle
		break;
	case ButtonWaterAuto:
		// Your code for ButtonWaterLvl_1
		break;
	case ButtonWaterManually:
		// Your code for ButtonWaterManually
		break;
	case FlowMeterTarget:

		break;
	case Timeout:

		break;
	default:
		DBG_PRINT("**!!case default reached!!**");
		break;
	}
}
#if (DRPUSHBUTTON_TEST == 1)
extern volatile uint8_t exti12_sw_triggered;
#endif
void DrPushButton_ButtonISR(sButton *button)
{
	/* Ensure once entered, the IRQ is disabled */
	DrTimer_TimDelay(DEBOUNCE_TIME);

	// Get the current button state
	eDrPushButton_ButtonState tempButtonState = DrPushButton_ButtonGetState(
			button);

#if (DRPUSHBUTTON_TEST == 1)
	if (exti12_sw_triggered == 1)
	{
		static uint8_t toggle = 1;
		if (toggle)
		{
			toggle = 0;
			tempButtonState = ButtonPushed;
		}
		else
		{
			toggle = 1;
			tempButtonState = ButtonReleased;
		}
	}
#endif

	//DBG_PRINT("button# %u | StateOld: %u | State %u ", (uint32_t)button->buttonNum, (uint32_t)button->buttonStateOld, (uint32_t)tempButtonState);

	// Check if the button state has changed
	if (tempButtonState != button->buttonStateOld)
	{
		// Must be a valid button event
		button->buttonStateOld = tempButtonState;

		// Handle button release
		if (button->buttonStateOld == ButtonReleased)
		{
			DBG_PRINT("buttonNum: %u RELEASED", (button->buttonNum)+1);
			DrPushButton_ButtonReleasedCB(button);
		}
		// Handle button push
		else if (button->buttonStateOld == ButtonPushed)
		{
			DBG_PRINT("buttonNum: %u PUSHED", (button->buttonNum)+1);
			DrPushButton_ButtonPushedCB(button);
		}
	}
}

