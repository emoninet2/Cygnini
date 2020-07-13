/*
 * C12832Port.h
 *
 *  Created on: Apr 30, 2019
 *      Author: emon1
 */

#ifndef C12832_C12832PORT_H_
#define C12832_C12832PORT_H_

#include <stdlib.h>
#include <stdint.h>
#include "stm32l4xx_hal.h"


void c12832_hal_spi_init();
void c12832_hal_gpio_init();
int c12832_hal_spi_write_read (uint8_t *tx_data, uint8_t *rx_data, uint16_t lenght);

#define DISPLAY_NSEL_GPIO_Port 			GPIOB
#define DISPLAY_NSEL_Pin 				GPIO_PIN_12

#define DISPLAY_A0_GPIO_Port			GPIOC
#define DISPLAY_A0_Pin					GPIO_PIN_6

#define DISPLAY_NRESET_GPIO_Port 		GPIOC
#define DISPLAY_NRESET_Pin				GPIO_PIN_5

#define DISPLAY_BACKLIGHT_GPIO_Port		GPIOA
#define DISPLAY_BACKLIGHT_Pin			GPIO_PIN_8


#define DISPLAY_CHIP_SELECT_LOW      			HAL_GPIO_WritePin (DISPLAY_NSEL_GPIO_Port, DISPLAY_NSEL_Pin, GPIO_PIN_RESET)
#define DISPLAY_CHIP_SELECT_HIGH				HAL_GPIO_WritePin (DISPLAY_NSEL_GPIO_Port, DISPLAY_NSEL_Pin, GPIO_PIN_SET)

#define DISPLAY_A0_LOW      					HAL_GPIO_WritePin (DISPLAY_A0_GPIO_Port, DISPLAY_A0_Pin, GPIO_PIN_RESET)
#define DISPLAY_A0_HIGH							HAL_GPIO_WritePin (DISPLAY_A0_GPIO_Port, DISPLAY_A0_Pin, GPIO_PIN_SET)

#define DISPLAY_RESET_LOW      					HAL_GPIO_WritePin (DISPLAY_NRESET_GPIO_Port, DISPLAY_NRESET_Pin, GPIO_PIN_RESET)
#define DISPLAY_RESET_HIGH						HAL_GPIO_WritePin (DISPLAY_NRESET_GPIO_Port, DISPLAY_NRESET_Pin, GPIO_PIN_SET)

#define DISPLAY_BACKLIGHT_OFF  					HAL_GPIO_WritePin (DISPLAY_BACKLIGHT_GPIO_Port, DISPLAY_BACKLIGHT_Pin, GPIO_PIN_RESET)
#define DISPLAY_BACKLIGHT_ON					HAL_GPIO_WritePin (DISPLAY_BACKLIGHT_GPIO_Port, DISPLAY_BACKLIGHT_Pin, GPIO_PIN_SET)


#endif /* C12832_C12832PORT_H_ */
