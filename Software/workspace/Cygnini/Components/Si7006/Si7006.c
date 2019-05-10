/*
 * Si7006.c
 *
 *  Created on: May 1, 2019
 *      Author: emon1
 */

#include "Si7006.h"

#include <stdio.h>



Si7006_error_t Si7006_init(Si7006_t *unit){
	unit->init();
}
Si7006_error_t Si7006_i2c_init(Si7006_t *unit){
	unit->i2c_init();
}
Si7006_error_t Si7006_i2c_transmit(Si7006_t *unit, uint8_t *data, unsigned int size){
	unit->i2c_transmit(data,size);
}
Si7006_error_t Si7006_i2c_receive(Si7006_t *unit, uint8_t *data, unsigned int size){
	unit->i2c_receive(data,size);
}
Si7006_error_t Si7006_check_hardware(Si7006_t *unit){
	unit->check_hardware();
}
Si7006_error_t Si7006_delay(Si7006_t *unit, unsigned int ms){
	unit->delay(ms);
}

/////////////////////////////////////////////////////////////////////////////////////

float Si7006_temperature(Si7006_t *unit){
	uint8_t data[3] = {0xF3, 0, 0};
	unit->i2c_transmit(data, 1);
	unit->delay(500);
	unit->i2c_receive(data,2);

	uint16_t Temp_Code = data[0]<<8 | data[1];
	//printf("the data received is %d, %d\r\n", data[1], data[0]);
	//printf("temp code is is %d\r\n", tempCode );

	return ((175.72* (float)Temp_Code)/65536) - 46.85;
}

float Si7006_relativeHumidity(Si7006_t *unit){
	uint8_t data[2] = {0xF5, 0};
	unit->i2c_transmit(data, 1);
	unit->delay(500);
	unit->i2c_receive(data,2);

	uint16_t RH_Code = data[0]<<8 | data[1];
	//printf("the data received is %d, %d\r\n", data[1], data[0]);
	printf("RH code is is %d\r\n", RH_Code );

	//float step1 = ((float) RH_Code * 125.0 );
	//float step2 = (((float) RH_Code * 125.0 ) / 65536 ) - 6.0;

	float relativeHumidity = (((float) RH_Code * 125.0 ) / 65536 ) - 6.0;
	return relativeHumidity;
}


Si7006_error_t Si7006_read_firmware_revision(Si7006_t *unit){

	printf("gonna read firmware revision now\r\n");











}


