/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "keyboard.h"
#include "amiga.h"
#include "dwt_delay.h"
#include <string.h>

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

/* USER CODE BEGIN PV */
    keyboard_t keyboard;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */
  DWT_Init();


  amikb_startup();
  keyboard_t keyboard;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //clear
	  memset(&keyboard,0,sizeof(keyboard));

	  //As there is amiga code for 0x00 other value is requried to mark entry as empty.
	  memset(&keyboard.keyboard_codes,0xFF,sizeof(keyboard.keyboard_codes));
	  //
	  memset(&keyboard.special_keys,0xFF,sizeof(keyboard.special_keys));
	  ProcessKeyboard(&keyboard);
	  amikb_process(&keyboard);
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PB2_X2_7_GPIO_Port, PB2_X2_7_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, KBD_DATA_Pin|KBD_CLOCK_Pin|KBD_RESET_Pin|PC7_CAPS_LED_31_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PB3_X3_5_Pin|PB4_X4_1_Pin|PB5_X5_2_Pin|PB6_X6_3_Pin 
                          |PB7_X7_4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PD5_LALT_13_Pin */
  GPIO_InitStruct.Pin = PD5_LALT_13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PD5_LALT_13_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PD7_LAMI_14_Pin */
  GPIO_InitStruct.Pin = PD7_LAMI_14_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(PD7_LAMI_14_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB2_X2_7_Pin */
  GPIO_InitStruct.Pin = PB2_X2_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PB2_X2_7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0_Y14_15_Pin PA1_Y13_16_Pin PA2_Y12_17_Pin PA3_Y11_18_Pin 
                           PA4_Y10_19_Pin PA5_Y9_20_Pin PA6_Y8_21_Pin PA7_Y7_22_Pin 
                           PA8_Y6_23_Pin PC1_Y5_24_Pin PC2_Y4_25_Pin PC3_Y3_26_Pin 
                           PC4_Y2_27_Pin PC5_Y1_28_Pin */
  GPIO_InitStruct.Pin = PA0_Y14_15_Pin|PA1_Y13_16_Pin|PA2_Y12_17_Pin|PA3_Y11_18_Pin 
                          |PA4_Y10_19_Pin|PA5_Y9_20_Pin|PA6_Y8_21_Pin|PA7_Y7_22_Pin 
                          |PA8_Y6_23_Pin|PC1_Y5_24_Pin|PC2_Y4_25_Pin|PC3_Y3_26_Pin 
                          |PC4_Y2_27_Pin|PC5_Y1_28_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6_Y0_29_Pin PD0_RSHF_6_Pin PD3_CTRL_11_Pin PD4_LSHIFT_12_Pin 
                           PD1_RALT_8_Pin PD2_RAMI_10_Pin */
  GPIO_InitStruct.Pin = PC6_Y0_29_Pin|PD0_RSHF_6_Pin|PD3_CTRL_11_Pin|PD4_LSHIFT_12_Pin 
                          |PD1_RALT_8_Pin|PD2_RAMI_10_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : KBD_DATA_Pin KBD_CLOCK_Pin KBD_RESET_Pin */
  GPIO_InitStruct.Pin = KBD_DATA_Pin|KBD_CLOCK_Pin|KBD_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7_CAPS_LED_31_Pin */
  GPIO_InitStruct.Pin = PC7_CAPS_LED_31_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PC7_CAPS_LED_31_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3_X3_5_Pin PB5_X5_2_Pin PB6_X6_3_Pin PB7_X7_4_Pin */
  GPIO_InitStruct.Pin = PB3_X3_5_Pin|PB5_X5_2_Pin|PB6_X6_3_Pin|PB7_X7_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB4_X4_1_Pin */
  GPIO_InitStruct.Pin = PB4_X4_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PB4_X4_1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
