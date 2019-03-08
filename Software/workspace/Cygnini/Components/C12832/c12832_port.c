/*
 * c12832_port.c
 *
 *  Created on: Mar 8, 2019
 *      Author: emon1
 */

#include "c12832_port.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

#include <stdlib.h>

static SPI_HandleTypeDef *c12832_SpiHandle;
//static GPIO_InitTypeDef c12832_A0_pin_Struct = 			{GPIO_PIN_5,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,};
//static GPIO_InitTypeDef c12832_nSEL_pin_Struct = 		{GPIO_PIN_5,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,};
//static GPIO_InitTypeDef c12832_nRST_pin_Struct = 		{GPIO_PIN_5,GPIO_MODE_IT_FALLING,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,};
//static GPIO_InitTypeDef c12832_backlight_pin_Struct = 	{GPIO_PIN_5,GPIO_MODE_IT_FALLING,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,};




void c12832_assign_SPI(SPI_HandleTypeDef *hspix){
	c12832_SpiHandle = hspix;
}


int hal_spi_write_read (uint8_t *tx_data, uint8_t *rx_data, uint16_t lenght) {

	//if (HAL_SPI_Transmit (&hspi1, tx_data, 1, 200) != HAL_OK)
	//	DEBUG_MESSAGE_AND_EXIT_FAILURE

	HAL_SPI_Transmit (c12832_SpiHandle, tx_data, 1, 200);
	return EXIT_SUCCESS;

}




