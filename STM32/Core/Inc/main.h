/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define LCD_TP_Pin GPIO_PIN_2
#define LCD_TP_GPIO_Port GPIOE
#define LCD_TPE3_Pin GPIO_PIN_3
#define LCD_TPE3_GPIO_Port GPIOE
#define LCD_TP_EXT14_Pin GPIO_PIN_4
#define LCD_TP_EXT14_GPIO_Port GPIOE
#define LCD_TP_EXT14_EXTI_IRQn EXTI4_IRQn
#define dir1_Pin GPIO_PIN_6
#define dir1_GPIO_Port GPIOE
#define key2_Pin GPIO_PIN_13
#define key2_GPIO_Port GPIOC
#define step1_Pin GPIO_PIN_4
#define step1_GPIO_Port GPIOC
#define onboard_led_Pin GPIO_PIN_0
#define onboard_led_GPIO_Port GPIOB
#define onboard_ledB1_Pin GPIO_PIN_1
#define onboard_ledB1_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_12
#define LCD_BL_GPIO_Port GPIOD
#define LCD_TPD13_Pin GPIO_PIN_13
#define LCD_TPD13_GPIO_Port GPIOD
#define onboard_ledB5_Pin GPIO_PIN_5
#define onboard_ledB5_GPIO_Port GPIOB
#define LCD_TPE0_Pin GPIO_PIN_0
#define LCD_TPE0_GPIO_Port GPIOE
#define LCD_RST_Pin GPIO_PIN_1
#define LCD_RST_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
