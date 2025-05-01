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

/* Private defines -----------------------------------------------------------*/
#define DEBOUNCE_TIME 45 /* Time in ms */
/* Typedefs and structs ------------------------------------------------------*/
typedef enum
{
	ButtonReleased = 0,
	ButtonPushed = 1
}eDrPushButton_buttonState;

typedef struct
{
	uint8_t buttonNum;
	eDrPushButton_buttonState buttonState;

}sButtonHandle;

/* External variables --------------------------------------------------------*/
extern sButtonHandle ButtonHandle1;
extern sButtonHandle ButtonHandle2;
extern sButtonHandle ButtonHandle3;


/* Function declarations -----------------------------------------------------*/
void DrPushButton_ButtonISR(uint8_t buttonNum);


#endif /* INC_DRPUSHBUTTON_H_ */
