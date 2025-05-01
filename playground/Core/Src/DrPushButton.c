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

void DrPushButton_ButtonISR(uint8_t buttonNum)
{
	// #todo add disable_button_interrupt();
	TimerDelay_synch(DEBOUNCE_TIME);
//	if (Button_getState(me->itsButton) != me->oldState) {
//		/* must be a valid button event */
//		me->oldState = me->itsButton->deviceState;
//		if ((me->oldState == 0)) {
//			/* must be a button release, so update toggle value */
//			if (me->toggleOn) {
//				me->toggleOn = 0; /* toggle it off */
//				Button_backlight(me->itsButton, 0);
//				MicrowaveEmitter_stopEmitting(me->itsMicrowaveEmitter);
//			} else {
//				me->toggleOn = 1; /* toggle it on */
//				Button_backlight(me->itsButton, 1);
//				MicrowaveEmitter_startEmitting(me->itsMicrowaveEmitter);
//			}
//		}
//		/* if it’s not a button release, then it must
//		 be a button push, which we ignore.
//		 */
//	}
	// #todo add enable_button_interrupt();
}
