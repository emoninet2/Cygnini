/*
 * C12832Port.c
 *
 *  Created on: Apr 30, 2019
 *      Author: emon1
 */


#include "C12832Port.h"

SPI_HandleTypeDef hspi2;


void c12832_hal_spi_init(){

	GPIO_InitTypeDef GPIO_InitStruct = {0};


    /* USER CODE END SPI2_MspInit 0 */
	/* Peripheral clock enable */
	__HAL_RCC_SPI2_CLK_ENABLE();

	__HAL_RCC_GPIOB_CLK_ENABLE();
	/**SPI2 GPIO Configuration
	PB13     ------> SPI2_SCK
	PB14     ------> SPI2_MISO
	PB15     ------> SPI2_MOSI
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USER CODE BEGIN SPI2_MspInit 1 */

    /* USER CODE END SPI2_MspInit 1 */


	  hspi2.Instance = SPI2;
	  hspi2.Init.Mode = SPI_MODE_MASTER;
	  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	  hspi2.Init.NSS = SPI_NSS_SOFT;
	  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	  hspi2.Init.CRCPolynomial = 7;
	  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	  if (HAL_SPI_Init(&hspi2) != HAL_OK)
	  {
	    Error_Handler();
	  }

}


void c12832_hal_gpio_init(){
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();


	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, DISPLAY_NRESET_Pin|DISPLAY_A0_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(DISPLAY_NSEL_GPIO_Port, DISPLAY_NSEL_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(DISPLAY_BACKLIGHT_GPIO_Port, DISPLAY_BACKLIGHT_Pin, GPIO_PIN_RESET);


	  /*Configure GPIO pins : DISPLAY_NRESET_Pin DISPLAY_A0_Pin */
	  GPIO_InitStruct.Pin = DISPLAY_NRESET_Pin|DISPLAY_A0_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pin : DISPLAY_NSEL_Pin */
	  GPIO_InitStruct.Pin = DISPLAY_NSEL_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(DISPLAY_NSEL_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : DISPLAY_BACKLIGHT_Pin */
	  GPIO_InitStruct.Pin = DISPLAY_BACKLIGHT_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(DISPLAY_BACKLIGHT_GPIO_Port, &GPIO_InitStruct);



}


int c12832_hal_spi_write_read (uint8_t *tx_data, uint8_t *rx_data, uint16_t lenght) {

	HAL_SPI_Transmit (&hspi2, tx_data, 1, 200);
		//DEBUG_MESSAGE_AND_EXIT_FAILURE

	return EXIT_SUCCESS;

}
