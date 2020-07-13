/*
 * Si7006Port.h
 *
 *  Created on: Jul 12, 2020
 *      Author: hr193
 */

#ifndef SI7006_SI7006PORT_H_
#define SI7006_SI7006PORT_H_





Si7006_error_t Si7006_port_i2c_init(void);
Si7006_error_t Si7006_port_i2c_transmit(uint8_t *data, unsigned int size);
Si7006_error_t Si7006_port_i2c_receive(uint8_t *data, unsigned int size);
Si7006_error_t Si7006_port_check_hardware();
Si7006_error_t Si7006_port_delay(unsigned int ms);


#endif /* SI7006_SI7006PORT_H_ */
