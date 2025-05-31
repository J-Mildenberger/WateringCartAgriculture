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
#define DEBOUNCE_TIME 75 /* Time in ms */

#define DRPUSHBUTTON_TEST 0
#if (DRPUSHBUTTON_TEST == 1)
#warning "DRPUSHBUTTON_TEST IS MANIPULATING THE BUTTONS"
#endif


/* Typedefs and structs ------------------------------------------------------*/
typedef enum {
	ButtonReleased,
	ButtonPushed,
} eDrPushButton_ButtonState;
typedef enum {
	ButtonActionIdle,
	ButtonActionEnqueued,
	ButtonActionProcessed,
} eButtonActionState;
typedef enum {
	ButtonMask_Watering = 0x01,
	ButtonMask_MotorCtrl = 0x02,
	ButtonMask_WaterTank = 0x04,
} eButtonMask;
typedef struct {
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
} sHAL_GPIO;
typedef struct {
	uint8_t buttonNum;
	sHAL_GPIO HAL_GPIO;
	eButtonMask ButtonMask;
	eButtonActionState ButtonActionState;
	eDrPushButton_ButtonState buttonStateOld;
} sButton;

/* External variables --------------------------------------------------------*/
extern sButton Buttons[15];

/* Function declarations -----------------------------------------------------*/
void DrPushButton_ButtonISR(sButton *button);
eDrPushButton_ButtonState DrPushButton_ButtonGetState(sButton *button);
void DrPushButton_InitButtons(void);


#endif /* INC_DRPUSHBUTTON_H_ */
