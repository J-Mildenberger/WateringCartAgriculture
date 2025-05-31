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
#include "MyQueue.h"
#include "Application.h"
/* Private defines ----------------------------------------------------------*/

/* Static variables ----------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
sButton Buttons[15];

/* Private function prototypes -----------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void DrPushButton_InitButtons(void)
{
	memset(&Buttons, 0x00, sizeof(Buttons));
	/* Button 1
	 * DIN1_BUTTON_WATERINGLVL_1
	 */
	Buttons[DIN1_BUTTON_WATERINGLVL_1].buttonNum = DIN1_BUTTON_WATERINGLVL_1;
	Buttons[DIN1_BUTTON_WATERINGLVL_1].HAL_GPIO.GPIOx = GPIOA;
	Buttons[DIN1_BUTTON_WATERINGLVL_1].HAL_GPIO.GPIO_Pin = GPIO_PIN_12;
	Buttons[DIN1_BUTTON_WATERINGLVL_1].ButtonMask = ButtonMask_Watering;
	/* Button 2
	 * DIN2_BUTTON_WATERINGLVL_2
	 */
	Buttons[DIN2_BUTTON_WATERINGLVL_2].buttonNum = DIN2_BUTTON_WATERINGLVL_2;
	Buttons[DIN2_BUTTON_WATERINGLVL_2].HAL_GPIO.GPIOx = GPIOA;
	Buttons[DIN2_BUTTON_WATERINGLVL_2].HAL_GPIO.GPIO_Pin = GPIO_PIN_11;
	Buttons[DIN2_BUTTON_WATERINGLVL_2].ButtonMask = ButtonMask_Watering;
	/* Button 3
	 * DIN3_BUTTON_CTRL_PUMP_1
	 */
	Buttons[DIN3_BUTTON_CTRL_PUMP_1].buttonNum = DIN3_BUTTON_CTRL_PUMP_1;
	Buttons[DIN3_BUTTON_CTRL_PUMP_1].HAL_GPIO.GPIOx = GPIOB;
	Buttons[DIN3_BUTTON_CTRL_PUMP_1].HAL_GPIO.GPIO_Pin = GPIO_PIN_12;
	Buttons[DIN3_BUTTON_CTRL_PUMP_1].ButtonMask = ButtonMask_Watering;

	/* Button 12
	 * DIN11_BUTTON_EVALUSER
	 */
	Buttons[DIN11_BUTTON_EVALUSER].buttonNum = DIN11_BUTTON_EVALUSER;
	Buttons[DIN11_BUTTON_EVALUSER].HAL_GPIO.GPIOx = GPIOC;
	Buttons[DIN11_BUTTON_EVALUSER].HAL_GPIO.GPIO_Pin = GPIO_PIN_13;

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
		MyQueue_Enqueue(&buttonQueue,button);
		DBG_PRINT_BUTTON(button);
	}
}

void DrPushButton_ButtonPushedCB(sButton *button)
{
	DBG_PRINT_BUTTON(button);
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
	// Check if the button state has changed
	if (tempButtonState != button->buttonStateOld)
	{
		// Must be a valid button event
		button->buttonStateOld = tempButtonState;

		// Handle button release
		if (button->buttonStateOld == ButtonReleased)
		{
			DBG_PRINT("buttonNum: %lu RELEASED", (button->buttonNum)+1);
			DrPushButton_ButtonReleasedCB(button);
		}
		// Handle button push
		else if (button->buttonStateOld == ButtonPushed)
		{
			DBG_PRINT("buttonNum: %lu PUSHED", (button->buttonNum)+1);
			DrPushButton_ButtonPushedCB(button);
		}
	}
}

