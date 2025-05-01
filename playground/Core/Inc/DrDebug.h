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
/* Private defines -----------------------------------------------------------*/
#define DBG_PRINT(fmt, ...) \
    printf("[%-8lu ms] " fmt "\r\n", HAL_GetTick(), ##__VA_ARGS__)

/* Typedefs and structs ------------------------------------------------------*/
/* Static variables (file-scope) ---------------------------------------------*/
/* Static vars go in C file, just add extern here if needed */
/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/


#endif /* SRC_DRDEBUG_H_ */
