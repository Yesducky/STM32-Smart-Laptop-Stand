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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

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
#define dir1_Pin GPIO_PIN_5
#define dir1_GPIO_Port GPIOE
#define dir2_Pin GPIO_PIN_6
#define dir2_GPIO_Port GPIOE
#define key2_Pin GPIO_PIN_13
#define key2_GPIO_Port GPIOC
#define key2_EXTI_IRQn EXTI15_10_IRQn
#define key1_Pin GPIO_PIN_0
#define key1_GPIO_Port GPIOA
#define key1_EXTI_IRQn EXTI0_IRQn
#define step1_Pin GPIO_PIN_6
#define step1_GPIO_Port GPIOA
#define step2_Pin GPIO_PIN_7
#define step2_GPIO_Port GPIOA
#define onboard_led_Pin GPIO_PIN_0
#define onboard_led_GPIO_Port GPIOB
#define onboard_ledB1_Pin GPIO_PIN_1
#define onboard_ledB1_GPIO_Port GPIOB
#define LCD_BL_Pin GPIO_PIN_12
#define LCD_BL_GPIO_Port GPIOD
#define LCD_TPD13_Pin GPIO_PIN_13
#define LCD_TPD13_GPIO_Port GPIOD
#define btn_Pin GPIO_PIN_8
#define btn_GPIO_Port GPIOC
#define btn_EXTI_IRQn EXTI9_5_IRQn
#define fan_state_Pin GPIO_PIN_9
#define fan_state_GPIO_Port GPIOC
#define fan_stateC10_Pin GPIO_PIN_10
#define fan_stateC10_GPIO_Port GPIOC
#define fan_stateC11_Pin GPIO_PIN_11
#define fan_stateC11_GPIO_Port GPIOC
#define onboard_ledB5_Pin GPIO_PIN_5
#define onboard_ledB5_GPIO_Port GPIOB
#define FAN_Pin GPIO_PIN_6
#define FAN_GPIO_Port GPIOB
#define LCD_TPE0_Pin GPIO_PIN_0
#define LCD_TPE0_GPIO_Port GPIOE
#define LCD_RST_Pin GPIO_PIN_1
#define LCD_RST_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
void stepper_up(void);
void stepper_stop(void);
void fan(void);
int take_photo();
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
