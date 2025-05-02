/*
 * DrPushButton.h
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

#ifndef INC_DRPUSHBUTTON_H_
#define INC_DRPUSHBUTTON_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

/* Private defines -----------------------------------------------------------*/
#define DEBOUNCE_TIME 45 /* Time in ms */
/* Typedefs and structs ------------------------------------------------------*/
typedef enum {
	ButtonReleased, ButtonPushed
} eDrPushButton_ButtonState;
typedef enum {
	ButtonIdle,
	ButtonWaterLvl_1,
	ButtonWaterLvl_2,
	ButtonWaterLvl_3,
	ButtonWaterManually,
} eButtonApplicationState;
typedef struct {
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
} sHAL_GPIO;
typedef struct {
	uint8_t buttonNum;
	eDrPushButton_ButtonState buttonStateOld;
	sHAL_GPIO HAL_GPIO;
	eButtonApplicationState ButtonApplState;
} sButton;

/* External variables --------------------------------------------------------*/
extern sButton button_1;
extern sButton button_2;
extern sButton button_3;

/* Function declarations -----------------------------------------------------*/
void DrPushButton_ButtonISR(sButton *button);
eDrPushButton_ButtonState DrPushButton_ButtonGetState(sButton *button);

#endif /* INC_DRPUSHBUTTON_H_ */
