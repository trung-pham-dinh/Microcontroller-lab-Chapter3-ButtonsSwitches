/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "input_processing.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

// timer parameter


// led7 parameter


// button parameter


// traffic parameter



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
//void scanLed7(void);

//void setBufferLed7(uint8_t firstPair, uint8_t secondPair);

//void blinkTraffic(ModeState state);
//void increase(ModeState state, uint8_t* buffer);
//void decrease(ModeState state, uint8_t* buffer);
//void copyArray(uint8_t* from, uint8_t* to, int n);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);

  init_fsm_input_processing(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  switch(trafficMode) {
//	  case NORMAL:
//		  if(getPressFlag(BUTTON_MODE)) {
//			  resetPressFlag(BUTTON_MODE);
//			  trafficMode = CHANGE_RED;
//			  clearTraffic();
//			  resetPressAllFlag();
//
//			  controlSecTimer(TRAFFIC_VER_TIMER, STOP_TIMER);
//			  controlSecTimer(TRAFFIC_HOR_TIMER, STOP_TIMER);
//			  break;
//		  }
//		  traffic_display();
//		  setBufferLed7(getSecCounter(TRAFFIC_VER_TIMER), getSecCounter(TRAFFIC_HOR_TIMER));
//		  break;
//	  case CHANGE_RED:
//	  case CHANGE_YELLOW:
//	  case CHANGE_GREEN:
//		  if(getPressFlag(BUTTON_MODE)) {
//			  resetPressFlag(BUTTON_MODE);
//			  trafficMode = (trafficMode == CHANGE_GREEN)? NORMAL : trafficMode+1;
//			  clearTraffic();
//
//			  if(updateFlag == 0) {
//				  copyArray(traffic_time, traffic_time_update, 6); // update buffer -> current buffer
//			  }
//
//			  if(trafficMode == CHANGE_GREEN) {
//				  controlSecTimer(TRAFFIC_VER_TIMER, START_TIMER);
//				  controlSecTimer(TRAFFIC_HOR_TIMER, START_TIMER);
//			  }
//			  break;
//		  }
//		  if(getPressFlag(BUTTON_INCREASE)) {
//			  resetPressFlag(BUTTON_INCREASE) ;
//			  increase(trafficMode, traffic_time_update);
//		  }
//		  if(getPressFlag(BUTTON_DECREASE)) {
//			  resetPressFlag(BUTTON_DECREASE) ;
//			  decrease(trafficMode, traffic_time_update);
//		  }
//		  if(getPressFlag(BUTTON_SET)) {
//			  resetPressFlag(BUTTON_SET);
//			  updateFlag = 1;
//		  }
//		  if(trafficMode == CHANGE_RED) setBufferLed7(traffic_time_update[VER_RED], trafficMode);
//		  else if(trafficMode == CHANGE_YELLOW) setBufferLed7(traffic_time_update[VER_YELLOW], trafficMode);
//		  else if(trafficMode == CHANGE_GREEN) setBufferLed7(traffic_time_update[VER_GREEN], trafficMode);
//	  }
	  fsm_for_input_processing();
	  fsm_for_traffic_control();

//	  scanLed7();
//	  blinkTraffic(trafficMode);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 799;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 99;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DEBUG_Pin|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : DEBUG_Pin PA4 PA5 PA6
                           PA7 PA8 PA9 */
  GPIO_InitStruct.Pin = DEBUG_Pin|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB3 PB4 PB5 PB6
                           PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA10 PA11 PA12 PA13 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//void scanLed7() {
//	static uint8_t index = 0;
//
//	if(getMilFlag(SCAN_TIMER)) {
//		setMilTimer(SCAN_TIMER, scanTime);
//		display_7SEG(index++);
//		if(index == 4) index = 0;
//	}
//}
//void setBufferLed7(uint8_t firstPair, uint8_t secondPair) {
//	buffer_led7[0] = firstPair / 10;
//	buffer_led7[1] = firstPair % 10;
//	buffer_led7[2] = secondPair / 10;
//	buffer_led7[3] = secondPair % 10;
//}

//void blinkTraffic(ModeState state) {
//	if(state == NORMAL) return;
//	if(getMilFlag(BLINK_TIMER)) {
//		setMilTimer(BLINK_TIMER, blinkTime);
//		HAL_GPIO_TogglePin(TRAFFIC_PORT, (RED_VER << (state-1)) | (RED_HOR << (state-1)));
//	}
//}
//			RV          GV    YV
//	|-----------------|------|---|
//	|------------|----|----------|
//        GH       YH      RH
//void increase(ModeState state, uint8_t* buffer) {
//	switch(state) {
//	case CHANGE_RED:
//		if(buffer[VER_GREEN]-1 > 0 && buffer[HOR_RED]-1 > 1) {
//			buffer[VER_RED]++;
//			buffer[VER_GREEN]--;
//
//			buffer[HOR_RED]--;
//			buffer[HOR_GREEN]++;
//		}
//		break;
//	case CHANGE_GREEN:
//		if(buffer[VER_RED]-1 > 1 && buffer[HOR_GREEN]-1 > 0) {
//			buffer[VER_GREEN]++;
//			buffer[VER_RED]--;
//
//			buffer[HOR_GREEN]--;
//			buffer[HOR_RED]++;
//		}
//		break;
//	case CHANGE_YELLOW:
//		if(buffer[VER_GREEN]-1 > 0) {
//			buffer[VER_YELLOW]++;
//			buffer[VER_GREEN]--;
//		}
//		break;
//	default:
//		break;
//	}
//}
//			RV          GV    YV
//	|-----------------|------|---|
//	|------------|----|----------|
//        GH       YH      RH
//void decrease(ModeState state, uint8_t* buffer) {
//	switch(state) {
//	case CHANGE_RED:
//		if(buffer[VER_RED]-1 > 1 && buffer[VER_GREEN]-1 > 0) {
//			buffer[VER_RED]--;
//			buffer[VER_GREEN]++;
//
//			buffer[HOR_RED]++;
//			buffer[HOR_GREEN]--;
//		}
//		break;
//	case CHANGE_GREEN:
//		if(buffer[VER_GREEN]-1 > 0 && buffer[HOR_RED]-1 > 1) {
//			buffer[VER_GREEN]--;
//			buffer[VER_RED]++;
//
//			buffer[HOR_GREEN]++;
//			buffer[HOR_RED]--;
//		}
//		break;
//	case CHANGE_YELLOW:
//		if(buffer[VER_YELLOW]-1 > 0) {
//			buffer[VER_YELLOW]--;
//			buffer[VER_GREEN]++;
//		}
//		break;
//	default:
//		break;
//	}
//}
//void copyArray(uint8_t* from, uint8_t* to, int n) {
//	for(int i = 0; i < n; i++) {
//		to[i] = from[i];
//	}
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
