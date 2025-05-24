/*
 * DrDebug.h
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */

#ifndef SRC_DRDEBUG_H_
#define SRC_DRDEBUG_H_

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "DrPushButton.h"
/* Private defines -----------------------------------------------------------*/
#define DBG_PRINT(fmt, ...) \
    printf("[%-6lu] " fmt "\r\n", HAL_GetTick(), ##__VA_ARGS__)

#define DBG_PRINT_BUTTON(buttonPtr) \
    do { \
        printf("[%-6lu] button#: %u | ApplWater: %s | Action: %s \r\n", \
               HAL_GetTick(), \
               ((buttonPtr)->buttonNum+1), \
               ButtonApplicationStateWateringToString((buttonPtr)->ButtonApplState_Watering), \
               ButtonActionStateToString((buttonPtr)->ButtonActionState) );\
    } while (0)
//	Line %s %d 		   __func__, \
//               __LINE__ ); \
/* Typedefs and structs ------------------------------------------------------*/
/* Static variables (file-scope) ---------------------------------------------*/
/* Static vars go in C file, just add extern here if needed */
/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
const char* ButtonApplicationStateWateringToString(
		eButtonApplState_Watering state);
const char* ButtonActionStateToString(eButtonActionState state);
#endif /* SRC_DRDEBUG_H_ */
