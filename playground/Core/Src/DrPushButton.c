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
#include "string.h"
#include "PinDefines.h"
/* Static variables ----------------------------------------------------------*/
sButton Buttons[13];

/* Private function prototypes -----------------------------------------------*/

/* Function definitions ------------------------------------------------------*/
void DrPushButton_InitResetButtons(void) {
	memset(&Buttons[0], 0x00, sizeof(Buttons));
	/* Button 1
	 * DIN1_BUTTON_WATERINGLVL_1
	 */
	Buttons[0].buttonNum = DIN1_BUTTON_WATERINGLVL_1;
	Buttons[0].HAL_GPIO.GPIOx = GPIOA;
	Buttons[0].HAL_GPIO.GPIO_Pin = 12;
	/* Button 2
	 * DIN2_BUTTON_WATERINGLVL_2
	 */
	Buttons[1].buttonNum = DIN2_BUTTON_WATERINGLVL_2;
	Buttons[1].HAL_GPIO.GPIOx = GPIOA;
	Buttons[1].HAL_GPIO.GPIO_Pin = 11;

	/* Button 12
	 * DIN11_BUTTON_EVALUSER
	 */
	Buttons[12].buttonNum = DIN11_BUTTON_EVALUSER;
	Buttons[12].HAL_GPIO.GPIOx = GPIOC;
	Buttons[12].HAL_GPIO.GPIO_Pin = 13;

}

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

void DrPushButton_ButtonReleasedCB(sButton *button) {

	if ((button->buttonNum == DIN1_BUTTON_WATERINGLVL_1)
			|| (button->buttonNum == DIN2_BUTTON_WATERINGLVL_2)) {
		switch (button->ButtonApplState) {
//		DBG_PRINT_BUTTON(button);
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
		default:
			DBG_PRINT("**!!case default reached!!**");
		}

		if (button->buttonNum == DIN3_BUTTON_CTRL_PUMP_1) {

		}
	}
}

void DrPushButton_ButtonPushedCB(sButton *button) {
	switch (button->ButtonApplState) {
	case ButtonIdle:
		// Your code for ButtonIdle
		break;
	case ButtonWaterLvl_1:
		// Your code for ButtonWaterLvl_1
		break;
	case ButtonWaterLvl_2:
		// Your code for ButtonWaterLvl_2
		break;
	case ButtonWaterLvl_3:
		// Your code for ButtonWaterLvl_3
		break;
	case ButtonWaterManually:
		// Your code for ButtonWaterManually
		break;
	default:
		break;
	}
}

void DrPushButton_ButtonISR(sButton *button) {
	/* Ensure once entered, the IRQ is disabled */
	DrTimer_TimDelay(DEBOUNCE_TIME);

	// Get the current button state
	eDrPushButton_ButtonState tempButtonState = DrPushButton_ButtonGetState(
			button);

	// Debug prints
	DBG_PRINT("buttonNum: %u", button->buttonNum);
	DBG_PRINT("buttonStateOld: %u", button->buttonStateOld);
	DBG_PRINT("buttonState: %u", tempButtonState);

	// Check if the button state has changed
	if (tempButtonState != button->buttonStateOld) {
		// Must be a valid button event
		button->buttonStateOld = tempButtonState;

		// Handle button release
		if (button->buttonStateOld == ButtonReleased) {
			DBG_PRINT("buttonNum: %u RELEASED", button->buttonNum);
			DrPushButton_ButtonReleasedCB(button);
		}
		// Handle button push
		else if (button->buttonStateOld == ButtonPushed) {
			DBG_PRINT("buttonNum: %u PUSHED", button->buttonNum);
			DrPushButton_ButtonPushedCB(button);
		}
	}
}

