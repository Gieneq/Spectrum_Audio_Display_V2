/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include <arm_math.h>
#include <arm_const_structs.h>
#include "pixeltypes.h"
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
#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define ADS983_SPI1_FS_Pin GPIO_PIN_15
#define ADS983_SPI1_FS_GPIO_Port GPIOC
#define BATCH_DONE_Pin GPIO_PIN_0
#define BATCH_DONE_GPIO_Port GPIOC
#define SWIPE_NEXT_Pin GPIO_PIN_0
#define SWIPE_NEXT_GPIO_Port GPIOB
#define RELAY_SIG0_Pin GPIO_PIN_12
#define RELAY_SIG0_GPIO_Port GPIOB
#define RELAY_SIG1_Pin GPIO_PIN_13
#define RELAY_SIG1_GPIO_Port GPIOB
#define RELAY_SIG2_Pin GPIO_PIN_14
#define RELAY_SIG2_GPIO_Port GPIOB
#define BAR_LED7_Pin GPIO_PIN_15
#define BAR_LED7_GPIO_Port GPIOB
#define BAR_LED6_Pin GPIO_PIN_6
#define BAR_LED6_GPIO_Port GPIOC
#define BAR_LED5_Pin GPIO_PIN_7
#define BAR_LED5_GPIO_Port GPIOC
#define BAR_LED4_Pin GPIO_PIN_8
#define BAR_LED4_GPIO_Port GPIOC
#define BAR_LED3_Pin GPIO_PIN_9
#define BAR_LED3_GPIO_Port GPIOC
#define BAR_LED2_Pin GPIO_PIN_8
#define BAR_LED2_GPIO_Port GPIOA
#define BAR_LED1_Pin GPIO_PIN_11
#define BAR_LED1_GPIO_Port GPIOA
#define BAR_LED0_Pin GPIO_PIN_12
#define BAR_LED0_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
