/*
 * Si7006.h
 *
 *  Created on: May 1, 2019
 *      Author: emon1
 */

#ifndef SI7006_SI7006_H_
#define SI7006_SI7006_H_

#include <stdint.h>

typedef enum{
	SI7006_SUCCESS = 0,
	SI7006_ERROR = 1,
}Si7006_error_t;


typedef struct{
	Si7006_error_t (*init)(void);
	Si7006_error_t (*i2c_init)(void);
	Si7006_error_t (*i2c_transmit)(uint8_t *data, unsigned int size);
	Si7006_error_t (*i2c_receive)(uint8_t *data, unsigned int size);
	Si7006_error_t (*check_hardware)();
	Si7006_error_t (*delay)(unsigned int ms);
}Si7006_t;




Si7006_error_t Si7006_init(Si7006_t *unit);
Si7006_error_t Si7006_i2c_init(Si7006_t *unit);
Si7006_error_t Si7006_i2c_transmit(Si7006_t *unit, uint8_t *data, unsigned int size);
Si7006_error_t Si7006_i2c_receive(Si7006_t *unit, uint8_t *data, unsigned int size);
Si7006_error_t Si7006_check_hardware(Si7006_t *unit);
Si7006_error_t Si7006_delay(Si7006_t *unit, unsigned int ms);

float Si7006_temperature(Si7006_t *unit);
float Si7006_relativeHumidity(Si7006_t *unit);
Si7006_error_t Si7006_read_firmware_revision(Si7006_t *unit);


#endif /* SI7006_SI7006_H_ */
