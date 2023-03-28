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
#include "stm32f4xx_hal.h"

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

#define GREEN_BUTTON	GPIO_PIN_8
#define ORANGE_BUTTON	GPIO_PIN_9
#define RED_BUTTON		GPIO_PIN_6
#define BLUE_BUTTON		GPIO_PIN_11

#define GREEN_LED		GPIO_PIN_12
#define ORANGE_LED 		GPIO_PIN_13
#define RED_LED 		GPIO_PIN_14
#define BLUE_LED		GPIO_PIN_15

#define MAX12BIT 				(float)(4096)
#define Vdd_mV					(float)(3300.0)
#define HighVoltage_mV			(float)(3000.0)

#define INP_mV(ADC_VAL)			(float)((ADC_VAL * Vdd_mV) / (MAX12BIT))
#define AVG_SLP_EXT 			(float)(-20.0)
#define V_t0_EXT_mV 			(float)(2020)
#define Tcurr_EXT_deg(ADC_VAL)	((INP_mV(ADC_VAL) - V_t0_EXT_mV)  / AVG_SLP_EXT)

/*---------------------------------------------*/
// INP_MV(ADC_VAL) - 	gives voltage in millivolts read by ADC given 12bit converted value
// AVG_SLP_x       - 	mV/C ratio constants for respective temperature sensors
// ZERO_DEG_x	   -	gives voltage in millivolts output by respective temperature sensors at 0 degrees Celsius

// for V_t0 is voltage at temperature t0 = 0, V_sens is voltage output by sensor, K_max - max value of adc output
// given 12bit converted value from adc K_adc to find current temperature measured by sensor we'll use the following formula:
// T_curr = (V_t0 - V_sens)/AVG_SLP = (V_t0 - (K_adc * V_max)/K_max)/AVG_SLP
/*---------------------------------------------*/

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
