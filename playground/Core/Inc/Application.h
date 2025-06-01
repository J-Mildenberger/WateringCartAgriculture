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

#define DOUT_RELAIS_ACTIVE 0u
#define PUMP1_VALVE1_DELAY 650u
/* Typedefs and structs ------------------------------------------------------*/

/* high-layer state-machine for watering */
typedef enum {
    ApplState_watering_Idle,
    ApplState_watering_Auto,
    ApplState_watering_Manually,
    ApplState_watering_FlowMeterTarget,
    ApplState_watering_Timeout
} eApplState_watering;
/* watering application elements for enqueue */
typedef enum {
	eApplElement_FlowMeterTarget = 0,
	eApplElement_watering_Auto = 1,
	eApplElement_watering_Stop = 2,
	eApplElement_watering_Timeout = 3,
	eApplElement_watering_Manually = 4,
} eApplElement;
/* status info of the application elements */
typedef enum {
	ApplActionState_Idle,
	ApplActionState_Enqueued,
	ApplActionState_Processed,
} eApplActionState;
/* struct: application elements */
typedef struct {
	eApplActionState ApplActionState;
	eApplElement	ApplElement;
} sApplElement;
/* Static variables ----------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern eApplState_watering ApplState_watering;
extern sButton buttonQueueBuf[QUEUE_SIZE];
extern tQueue buttonQueue;
extern sApplElement applQueueBuf[QUEUE_SIZE];
extern tQueue applQueue;
/* Function declarations -----------------------------------------------------*/
void ApplHandler_SetWateringState(eApplState_watering state);
void Appl_InitApplElements(void);
bool ApplHandler_CheckFlowMeterTargetReached(sDrFlowMeter *pFlowMeter);
void ApplHandler_WateringButtons(sButton *pButton);
void ApplHandler_Watering(void);
void Appl_Processed_to_Idle(void);
void Appl_notify(void);
void ApplHandler_MAIN(tQueue *q);
void ApplHandler_ProcessedApplEls(void);
void ApplHandler_ProcessedButtons(void);
#endif /* INC_APPLICATION_H_ */
