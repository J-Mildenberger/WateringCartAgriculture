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
/* Static variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
eButtonState DrPushButton_ButtonGetState(sButton *button) {
	GPIO_PinState res = HAL_GPIO_ReadPin(button->HAL_GPIO.GPIOx,
			button->HAL_GPIO.GPIO_Pin);
	eButtonState ret;
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
	TimerDelay_synch(DEBOUNCE_TIME);
	eButtonState tempButtonState = DrPushButton_ButtonGetState(button);
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
