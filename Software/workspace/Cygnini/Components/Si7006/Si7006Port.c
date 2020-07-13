/*
 * Si7006Port.c
 *
 *  Created on: Jul 12, 2020
 *      Author: hr193
 */


#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

#include "Si7006.h"

extern I2C_HandleTypeDef  hi2c1;
extern Si7006_t Si7006;


Si7006_error_t Si7006_port_i2c_init(void){

}
Si7006_error_t Si7006_port_i2c_transmit(uint8_t *data, unsigned int size){

	HAL_StatusTypeDef ret = HAL_I2C_Master_Transmit(&hi2c1,(0x40<<1) ,data,size, 1000);
	if(ret == HAL_OK) return SI7006_SUCCESS;
	else return SI7006_ERROR;
}
Si7006_error_t Si7006_port_i2c_receive(uint8_t *data, unsigned int size){
	HAL_StatusTypeDef ret = HAL_I2C_Master_Receive(&hi2c1,(0x40<<1) ,data,size, 1000);
	if(ret == HAL_OK) return SI7006_SUCCESS;
	else return SI7006_ERROR;
}
Si7006_error_t Si7006_port_check_hardware(){
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1,(0x40<<1), 1000, 1000);
	if(ret == HAL_OK) return SI7006_SUCCESS;
	else return SI7006_ERROR;
}
Si7006_error_t Si7006_port_delay(unsigned int ms){

	HAL_Delay(ms);
}


Si7006_error_t Si7006_port_init(void){
	Si7006.init = Si7006_port_init;
	Si7006.i2c_init = Si7006_port_i2c_init;
	Si7006.i2c_transmit = Si7006_port_i2c_transmit;
	Si7006.i2c_receive = Si7006_port_i2c_receive;
	Si7006.check_hardware = Si7006_port_check_hardware;
	Si7006.delay = Si7006_port_delay;

	return Si7006_port_check_hardware();

}

