/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DOUT2_PUMP1_WATER_Pin LL_GPIO_PIN_2
#define DOUT2_PUMP1_WATER_GPIO_Port GPIOC
#define LD2_Pin LL_GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define DIN5_BUTTON_EXTEND_WATERINGARM_HORIZ_Pin LL_GPIO_PIN_1
#define DIN5_BUTTON_EXTEND_WATERINGARM_HORIZ_GPIO_Port GPIOB
#define DIN5_BUTTON_EXTEND_WATERINGARM_HORIZ_EXTI_IRQn EXTI1_IRQn
#define DIN4_BUTTON_RETRACT_WATERINGARM_VERT_FULL_Pin LL_GPIO_PIN_2
#define DIN4_BUTTON_RETRACT_WATERINGARM_VERT_FULL_GPIO_Port GPIOB
#define DIN4_BUTTON_RETRACT_WATERINGARM_VERT_FULL_EXTI_IRQn EXTI2_IRQn
#define DIN15_WATERLEVEL_SENS_2_Pin LL_GPIO_PIN_10
#define DIN15_WATERLEVEL_SENS_2_GPIO_Port GPIOB
#define DIN15_WATERLEVEL_SENS_2_EXTI_IRQn EXTI15_10_IRQn
#define DIN10_FLOWMETER_DETECT_Pin LL_GPIO_PIN_13
#define DIN10_FLOWMETER_DETECT_GPIO_Port GPIOB
#define DIN10_FLOWMETER_DETECT_EXTI_IRQn EXTI15_10_IRQn
#define DIN7_BUTTON_RETRACT_WATERINGARM_VERT_Pin LL_GPIO_PIN_14
#define DIN7_BUTTON_RETRACT_WATERINGARM_VERT_GPIO_Port GPIOB
#define DIN7_BUTTON_RETRACT_WATERINGARM_VERT_EXTI_IRQn EXTI15_10_IRQn
#define DIN6_BUTTON_EXTEND_WATERINGARM_VERT_Pin LL_GPIO_PIN_15
#define DIN6_BUTTON_EXTEND_WATERINGARM_VERT_GPIO_Port GPIOB
#define DIN6_BUTTON_EXTEND_WATERINGARM_VERT_EXTI_IRQn EXTI15_10_IRQn
#define DIN8_BUTTON_RETRACT_WATERINGARM_HORIZ_Pin LL_GPIO_PIN_6
#define DIN8_BUTTON_RETRACT_WATERINGARM_HORIZ_GPIO_Port GPIOC
#define DIN8_BUTTON_RETRACT_WATERINGARM_HORIZ_EXTI_IRQn EXTI9_5_IRQn
#define DIN12_ENDSWITCH_1_Pin LL_GPIO_PIN_7
#define DIN12_ENDSWITCH_1_GPIO_Port GPIOC
#define DIN12_ENDSWITCH_1_EXTI_IRQn EXTI9_5_IRQn
#define DIN14_WATERLEVEL_SENS_1_Pin LL_GPIO_PIN_8
#define DIN14_WATERLEVEL_SENS_1_GPIO_Port GPIOA
#define DIN14_WATERLEVEL_SENS_1_EXTI_IRQn EXTI9_5_IRQn
#define DIN13_ENDSWITCH_2_Pin LL_GPIO_PIN_9
#define DIN13_ENDSWITCH_2_GPIO_Port GPIOA
#define DIN13_ENDSWITCH_2_EXTI_IRQn EXTI9_5_IRQn
#define DIN2_BUTTON_WATERING_LVL2_Pin LL_GPIO_PIN_11
#define DIN2_BUTTON_WATERING_LVL2_GPIO_Port GPIOA
#define DIN2_BUTTON_WATERING_LVL2_EXTI_IRQn EXTI15_10_IRQn
#define DIN1_BUTTON_WATERING_LVL1_Pin LL_GPIO_PIN_12
#define DIN1_BUTTON_WATERING_LVL1_GPIO_Port GPIOA
#define DIN1_BUTTON_WATERING_LVL1_EXTI_IRQn EXTI15_10_IRQn
#define TMS_Pin LL_GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin LL_GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin LL_GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
