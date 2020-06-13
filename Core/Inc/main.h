/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define PD5_LALT_13_Pin GPIO_PIN_13
#define PD5_LALT_13_GPIO_Port GPIOC
#define PD7_LAMI_14_Pin GPIO_PIN_14
#define PD7_LAMI_14_GPIO_Port GPIOC
#define PA0_Y14_15_Pin GPIO_PIN_0
#define PA0_Y14_15_GPIO_Port GPIOA
#define PA1_Y13_16_Pin GPIO_PIN_1
#define PA1_Y13_16_GPIO_Port GPIOA
#define PA2_Y12_17_Pin GPIO_PIN_2
#define PA2_Y12_17_GPIO_Port GPIOA
#define PA3_Y11_18_Pin GPIO_PIN_3
#define PA3_Y11_18_GPIO_Port GPIOA
#define PA4_Y10_19_Pin GPIO_PIN_4
#define PA4_Y10_19_GPIO_Port GPIOA
#define PA5_Y9_20_Pin GPIO_PIN_5
#define PA5_Y9_20_GPIO_Port GPIOA
#define PA6_Y8_21_Pin GPIO_PIN_6
#define PA6_Y8_21_GPIO_Port GPIOA
#define PA7_Y7_22_Pin GPIO_PIN_7
#define PA7_Y7_22_GPIO_Port GPIOA
#define PC6_Y0_29_Pin GPIO_PIN_0
#define PC6_Y0_29_GPIO_Port GPIOB
#define PD0_RSHF_6_Pin GPIO_PIN_1
#define PD0_RSHF_6_GPIO_Port GPIOB
#define PB2_X2_7_Pin GPIO_PIN_2
#define PB2_X2_7_GPIO_Port GPIOB
#define PD3_CTRL_11_Pin GPIO_PIN_10
#define PD3_CTRL_11_GPIO_Port GPIOB
#define PD4_LSHIFT_12_Pin GPIO_PIN_11
#define PD4_LSHIFT_12_GPIO_Port GPIOB
#define KB_DATA_Pin GPIO_PIN_12
#define KB_DATA_GPIO_Port GPIOB
#define KB_CLK_Pin GPIO_PIN_13
#define KB_CLK_GPIO_Port GPIOB
#define KB_RESET_Pin GPIO_PIN_14
#define KB_RESET_GPIO_Port GPIOB
#define PC7_CAPS_LED_31_Pin GPIO_PIN_15
#define PC7_CAPS_LED_31_GPIO_Port GPIOB
#define PA8_Y6_23_Pin GPIO_PIN_8
#define PA8_Y6_23_GPIO_Port GPIOA
#define PC1_Y5_24_Pin GPIO_PIN_9
#define PC1_Y5_24_GPIO_Port GPIOA
#define PC2_Y4_25_Pin GPIO_PIN_10
#define PC2_Y4_25_GPIO_Port GPIOA
#define PC3_Y3_26_Pin GPIO_PIN_11
#define PC3_Y3_26_GPIO_Port GPIOA
#define PC4_Y2_27_Pin GPIO_PIN_12
#define PC4_Y2_27_GPIO_Port GPIOA
#define PC5_Y1_28_Pin GPIO_PIN_15
#define PC5_Y1_28_GPIO_Port GPIOA
#define PB3_X3_5_Pin GPIO_PIN_3
#define PB3_X3_5_GPIO_Port GPIOB
#define PB4_X4_1_Pin GPIO_PIN_4
#define PB4_X4_1_GPIO_Port GPIOB
#define PB5_X5_2_Pin GPIO_PIN_5
#define PB5_X5_2_GPIO_Port GPIOB
#define PB6_X6_3_Pin GPIO_PIN_6
#define PB6_X6_3_GPIO_Port GPIOB
#define PB7_X7_4_Pin GPIO_PIN_7
#define PB7_X7_4_GPIO_Port GPIOB
#define PD1_RALT_8_Pin GPIO_PIN_8
#define PD1_RALT_8_GPIO_Port GPIOB
#define PD2_RAMI_10_Pin GPIO_PIN_9
#define PD2_RAMI_10_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
