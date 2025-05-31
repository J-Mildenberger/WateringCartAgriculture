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
#include "MyQueue.h"
#include "DrFlowMeter.h"
/* Private defines -----------------------------------------------------------*/
/* Typedefs and structs ------------------------------------------------------*/
typedef enum {
    ApplState_watering_Idle,
    ApplState_watering_Auto,
    ApplState_watering_Manually,
    ApplState_watering_FlowMeterTarget,
    ApplState_watering_Timeout
} eApplState_watering;
typedef enum {
	ApplActionState_Idle,
	ApplActionState_Enqueued,
	ApplActionState_Processed,
} eApplActionState;
typedef enum {
	eApplElement_FlowMeterTarget = 0,
	eApplElement_watering_Auto = 1,
	eApplElement_watering_Stop = 2,
} eApplElement;
typedef struct {
	eApplActionState ApplActionState;
	eApplElement	ApplElement;
} sApplElements;
/* Static variables ----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern eApplState_watering ApplState_watering;
extern sButton buttonQueueBuf[QUEUE_SIZE];
extern tQueue buttonQueue;
extern sApplElements applQueueBuf[QUEUE_SIZE];
extern tQueue applQueue;
/* Function declarations -----------------------------------------------------*/


bool ApplHandler_CheckFlowMeterTargetReached(sDrFlowMeter *pFlowMeter);
void ApplHandler_WateringButtons(sButton *pButton);
void ApplHandler_Watering(void);
void Appl_Processed_to_Idle(void);
void Appl_notify(void);
void Appl_ApplHandler_MAIN(tQueue *q);
#endif /* INC_APPLICATION_H_ */
