/*
 * DrDebug.c
 *
 *  Created on: May 1, 2025
 *      Author: julian
 */


/* Includes ------------------------------------------------------------------*/
#include "DrDebug.h"


/* Static variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Function definitions ------------------------------------------------------*/
const char* ButtonApplicationStateToString(eButtonApplicationState state) {
    switch (state) {
        case ButtonIdle:           return "ButtonIdle";
        case ButtonWaterLvl_1:     return "ButtonWaterLvl_1";
        case ButtonWaterLvl_2:     return "ButtonWaterLvl_2";
        case ButtonWaterLvl_3:     return "ButtonWaterLvl_3";
        case ButtonWaterManually:  return "ButtonWaterManually";
        default:                   return "UnknownState";
    }
}
