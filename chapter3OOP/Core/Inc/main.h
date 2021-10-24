/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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
#define DEBUG_Pin GPIO_PIN_3
#define DEBUG_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define TRAFFIC_PORT 	GPIOA
#define RED_VER 		GPIO_PIN_4
#define YELLOW_VER 		GPIO_PIN_5
#define GREEN_VER 		GPIO_PIN_6
#define RED_HOR 		GPIO_PIN_7
#define YELLOW_HOR 		GPIO_PIN_8
#define GREEN_HOR		GPIO_PIN_9


#define BUTTON_PORT					GPIOA
#define BUTTON_MODE_PORT			GPIO_PIN_10
#define BUTTON_FUNC_PORT		GPIO_PIN_11
#define BUTTON_SET_PORT				GPIO_PIN_12
#define BUTTON_DECREASE_PORT		GPIO_PIN_13


#define SEG_PORT		GPIOB
#define EN_PORT		GPIOB
#define SEG_0		GPIO_PIN_0
#define SEG_1		GPIO_PIN_1
#define SEG_2		GPIO_PIN_2
#define SEG_3		GPIO_PIN_3
#define SEG_4		GPIO_PIN_4
#define SEG_5		GPIO_PIN_5
#define SEG_6		GPIO_PIN_6

#define EN_SEG_0	GPIO_PIN_7
#define EN_SEG_1	GPIO_PIN_8
#define EN_SEG_2	GPIO_PIN_9
#define EN_SEG_3	GPIO_PIN_10
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
