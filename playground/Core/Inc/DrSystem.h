/*
 * DrSystem.h
 *
 *  Created on: May 22, 2025
 *      Author: julian
 */

#ifndef INC_DRSYSTEM_H_
#define INC_DRSYSTEM_H_

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stm32f4xx_hal.h"
/* Private defines -----------------------------------------------------------*/

#define APPL_NVIC_PRIO_HIGH 0
#define NVIC_ENTRIES_PRIO_LOW 56

#define _CRITICAL_SECTION_ENTER()  __disable_irq()
#define _CRITICAL_SECTION_EXIT()   __enable_irq()

#define ARRAY_COUNT(array_) (sizeof(array_)/sizeof((array_)[0]))
/* Typedefs and structs ------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/* Function declarations -----------------------------------------------------*/

void Reenable_Previously_Enabled_Low_Priority_IRQs(void);
void Disable_And_Record_Enabled_Low_Priority_IRQs(void);

void Disable_Low_Priority_IRQs(void);
void Clear_Low_Priority_Pending_IRQs(void);
void Reenable_Low_Priority_IRQs(void);

#endif /* INC_DRSYSTEM_H_ */
