/*
 * application.h
 *
 *  Created on: May 22, 2025
 *      Author: julian
 */

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "DrPushButton.h"
#include "DrSystem.h"
#include "DrTimer.h"
/* Private defines -----------------------------------------------------------*/
/* Typedefs and structs ------------------------------------------------------*/
/* Static variables ----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/



void Appl_checkButtons_watering(void);
void Appl_Processed_to_Idle(void);


#endif /* INC_APPLICATION_H_ */
