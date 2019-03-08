/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

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


void SystemClock_Config(void);
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define DISPLAY_A0_Pin GPIO_PIN_0
#define DISPLAY_A0_GPIO_Port GPIOC
#define DISPLAY_BACKLIGHT_Pin GPIO_PIN_1
#define DISPLAY_BACKLIGHT_GPIO_Port GPIOC
#define DISPLAY_nSEL_Pin GPIO_PIN_2
#define DISPLAY_nSEL_GPIO_Port GPIOC
#define DISPLAY_nRESET_Pin GPIO_PIN_3
#define DISPLAY_nRESET_GPIO_Port GPIOC
#define SI4455_nSEL_Pin GPIO_PIN_0
#define SI4455_nSEL_GPIO_Port GPIOA
#define SPI_SCK_Pin GPIO_PIN_5
#define SPI_SCK_GPIO_Port GPIOA
#define SPI_MISO_Pin GPIO_PIN_6
#define SPI_MISO_GPIO_Port GPIOA
#define SPI_MOSI_Pin GPIO_PIN_7
#define SPI_MOSI_GPIO_Port GPIOA
#define SI4455_SND_Pin GPIO_PIN_4
#define SI4455_SND_GPIO_Port GPIOC
#define SI4455_nIRQ_Pin GPIO_PIN_5
#define SI4455_nIRQ_GPIO_Port GPIOC
#define SI133_INT_Pin GPIO_PIN_0
#define SI133_INT_GPIO_Port GPIOB
#define DIP1_Pin GPIO_PIN_1
#define DIP1_GPIO_Port GPIOB
#define DIP2_Pin GPIO_PIN_2
#define DIP2_GPIO_Port GPIOB
#define CODEC_BCLK_Pin GPIO_PIN_10
#define CODEC_BCLK_GPIO_Port GPIOB
#define AK4556_nRESET_Pin GPIO_PIN_11
#define AK4556_nRESET_GPIO_Port GPIOB
#define CODEC_LRCK_Pin GPIO_PIN_12
#define CODEC_LRCK_GPIO_Port GPIOB
#define CODEC_MCLK_Pin GPIO_PIN_14
#define CODEC_MCLK_GPIO_Port GPIOB
#define CODEC_DAC_Pin GPIO_PIN_15
#define CODEC_DAC_GPIO_Port GPIOB
#define SI4455_GPIO0_Pin GPIO_PIN_6
#define SI4455_GPIO0_GPIO_Port GPIOC
#define SI4455_GPIO1_Pin GPIO_PIN_7
#define SI4455_GPIO1_GPIO_Port GPIOC
#define RED_LED_Pin GPIO_PIN_8
#define RED_LED_GPIO_Port GPIOC
#define GREEN_LED_Pin GPIO_PIN_9
#define GREEN_LED_GPIO_Port GPIOC
#define SCL_Pin GPIO_PIN_9
#define SCL_GPIO_Port GPIOA
#define SDA_Pin GPIO_PIN_10
#define SDA_GPIO_Port GPIOA
#define USB_D__Pin GPIO_PIN_11
#define USB_D__GPIO_Port GPIOA
#define USB_D_A12_Pin GPIO_PIN_12
#define USB_D_A12_GPIO_Port GPIOA
#define EXT_1_Pin GPIO_PIN_10
#define EXT_1_GPIO_Port GPIOC
#define EXT_2_Pin GPIO_PIN_11
#define EXT_2_GPIO_Port GPIOC
#define EXT_3_Pin GPIO_PIN_12
#define EXT_3_GPIO_Port GPIOC
#define CODEC_ADC_Pin GPIO_PIN_5
#define CODEC_ADC_GPIO_Port GPIOB
#define USART_TX_Pin GPIO_PIN_6
#define USART_TX_GPIO_Port GPIOB
#define USART_RX_Pin GPIO_PIN_7
#define USART_RX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
