/*
* NRF24L01pPort.h
*
*  Created on: Apr 23, 2019
*      Author: emon1
*/

#ifndef NRF24L01P_PORT_NRF24L01PPORT_H_
#define NRF24L01P_PORT_NRF24L01PPORT_H_

#include <stdint.h>
#include <stdbool.h>



typedef struct{
	void (*initialize)(void);
	void (*deinitialize)(void);
	void (*Pin_CE_Initialize)();
	void (*Pin_CSN_Initialize)();
	void (*Pin_IRQ_Initialize)();
	bool (*read_Pin_CE)();
	bool (*read_Pin_CSN)();
	void (*write_Pin_CE)(bool val);
	void (*write_Pin_CSN)(bool val);
	void (*SPI_Initialize)(void);
	void (*SPI_Transcieve)(uint8_t *dataOut, uint8_t *dataIn, unsigned int size);
	void (*delayMS)(unsigned int ms);
	void (*delayUS)(unsigned int us);
	unsigned int (*ClockMs)();
	unsigned int (*ClockUs)();
	void (*debug)(const char *format, ...);
	void (*debug_if)(bool condition, const char *format, ...);
}NRF24L01pPort_t;





/**
 * initializes the low level drivers of the platform
 */
void NRF24L01p_port_Initialize();
/**
 * deinitializes the low level drivers of the platform
 */
void NRF24L01p_port_DeInitialize();

 /**
 * initialization of the CE pin configuration
 */
void NRF24L01p_port_Pin_CE_Initialize();
/**
 * initialization of the CSN pin configuration
 */
void NRF24L01p_port_Pin_CSN_Initialize();
/**
 * initialization of the IRQ pin configuration
 */
void NRF24L01p_port_Pin_IRQ_Initialize();

/**
 * reads the logical value on the CE pin
 * return the logical value on CE pin
 */
bool NRF24L01p_port_read_Pin_CE();
/**
 * reads the logical value on the CSN pin
 * return the logical value on CSN pin
 */
bool NRF24L01p_port_read_Pin_CSN();

/**
 * sets the logical value on the CE pin
 * @param val the logical value to be set on the CE pin
 */
void NRF24L01p_port_write_Pin_CE(bool val);
/**
 * sets the logical value on the CSN pin
 * @param val the logical value to be set on the CSN pin
 */
void NRF24L01p_port_write_Pin_CSN(bool val);


/**
 * initializes the SPI configuration for the platform
 */
void NRF24L01p_port_SPI_initialize();
/**
 * exchange data on the SPI bus
 * @param dataOut pointer to the data buffer to read from the SPI
 * @param dataIn pointer the the data buffer to send data over SPI
 * @param size the number of bytes to be exchanged
 * @return returns the error status. 0 for success and -1 for fail
 */
int NRF24L01p_port_SPI_Transcieve(uint8_t *dataOut, uint8_t *dataIn, unsigned int size);


int NRF24L01p_port_SPI_Transmit(uint8_t *data, unsigned int size);
int NRF24L01p_port_SPI_Receive(uint8_t *data, unsigned int size);


/**
 * Millisecond delay function supported by the platform
 * @param ms time value in milliseconds
 */
void NRF24L01p_port_DelayMs(unsigned int ms);
/**
 * Microsecond delay function supported by the platform
 * @param us time value in microseconds
 */
void NRF24L01p_port_DelayUs(unsigned int us);

 /**
 * the global clock time elapsed in milliseconds
 * @return the global clock time elapsed since start in milliseconds
 */
unsigned int NRF24L01p_port_ClockMs();
 /**
 * the global clock time elapsed in milliseconds
 * @return the global clock time elapsed since start in microseconds
 */
unsigned int NRF24L01p_port_ClockUs();

/**
 *
 * @param format
 * @param ...
 */
void NRF24L01p_debug(const char *format, ...);

/**
 *
 * @param condition
 * @param format
 * @param ...
 */
void NRF24L01p_debug_if(bool condition, const char *format, ...);




#endif /* NRF24L01P_PORT_NRF24L01PPORT_H_ */
