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
    printf("[%-8lu ms] " fmt "\r\n", HAL_GetTick(), ##__VA_ARGS__)

#define DBG_PRINT_BUTTON(buttonPtr) \
    do { \
        printf("[%-8lu ms] %s | Line %d | buttonNum: %u | State: %s\r\n", \
               HAL_GetTick(), \
               __func__, \
               __LINE__, \
               (buttonPtr)->buttonNum, \
               ButtonApplicationStateToString((buttonPtr)->ButtonApplState)); \
    } while (0)


/* Typedefs and structs ------------------------------------------------------*/
/* Static variables (file-scope) ---------------------------------------------*/
/* Static vars go in C file, just add extern here if needed */
/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/
const char* ButtonApplicationStateToString(eButtonApplicationState state);


#endif /* SRC_DRDEBUG_H_ */
