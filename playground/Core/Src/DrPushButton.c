/*
 * DrPushButton.c
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

/* Includes ------------------------------------------------------------------*/
#include "DrPushButton.h"

#include "stm32f4xx_hal.h"
#include "DrTimer.h"
#include "DrDebug.h"
/* Static variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
eDrPushButton_ButtonState DrPushButton_ButtonGetState(sButton *button) {
	GPIO_PinState res = HAL_GPIO_ReadPin(button->HAL_GPIO.GPIOx,
			button->HAL_GPIO.GPIO_Pin);
	eDrPushButton_ButtonState ret;
	if (res == GPIO_PIN_RESET) {
		ret = ButtonReleased;
	}
	if (res == GPIO_PIN_SET) {
		ret = ButtonPushed;
	}
	return ret;
}

void DrPushButton_ButtonPushedCB(sButton *button) {
	switch (button->ButtonApplState) {
	case (ButtonIdle): {

	}
		break;
	case (ButtonWaterLvl_1): {

	}
		break;
	case (ButtonWaterLvl_2): {

	}
		break;
	case (ButtonWaterLvl_3): {

	}
		break;
	case (ButtonWaterManually): {

	}
		break;
	default:

	}
}

void DrPushButton_ButtonISR(sButton *button) {
	// #todo add disable_button_interrupt();
	DrTimer_TimDelay(DEBOUNCE_TIME);
	eDrPushButton_ButtonState tempButtonState = DrPushButton_ButtonGetState(
			button);
	DBG_PRINT("buttonStateOld %u", button->buttonStateOld);
	DBG_PRINT("buttonState %u", tempButtonState);
	if (tempButtonState != button->buttonStateOld) {
		/* must be a valid button event */
		button->buttonStateOld = tempButtonState;
		if (button->buttonStateOld == ButtonReleased) {
			/* must be a button release, so update toggle value */
			DrPushButton_ButtonPushedCB(button);
		}
		/* if it’s not a button release, then it must
		 be a button push, which we ignore.
		 */
	}
//	 #todo add enable_button_interrupt();
}
