/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   NRF24L01pPort.h
 * Author: emon1
 *
 * Created on January 29, 2017, 8:03 AM
 */


#include "NRF24L01pPort.h"
#include <stdint.h>
#include <stdbool.h>


#include <stm32l4xx_hal.h>


/* Kernel */
#include "cmsis_os.h"

#define NRF24L01P_SPI				SPI3
#define NRF24L01P_CE_PORT			GPIOC
#define NRF24L01P_CE_PIN			GPIO_PIN_8
#define NRF24L01P_CSN_PORT			GPIOC
#define NRF24L01P_CSN_PIN			GPIO_PIN_9
#define NRF24L01P_IRQ_PORT			GPIOC
#define NRF24L01P_IRQ_PIN			GPIO_PIN_7

/* Definition for SPIx clock resources */
#define NRF24L01P_SPIx                             SPI3
#define NRF24L01P_SPIx_CLK_ENABLE()                __HAL_RCC_SPI3_CLK_ENABLE()
#define NRF24L01P_SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define NRF24L01P_SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define NRF24L01P_SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()

#define NRF24L01P_SPIx_FORCE_RESET()               __HAL_RCC_SPI3_FORCE_RESET()
#define NRF24L01P_SPIx_RELEASE_RESET()             __HAL_RCC_SPI3_RELEASE_RESET()

/* Definition for SPIx Pins */
#define NRF24L01P_SPIx_SCK_PIN                     GPIO_PIN_10
#define NRF24L01P_SPIx_SCK_GPIO_PORT               GPIOC
#define NRF24L01P_SPIx_SCK_AF                      GPIO_AF6_SPI3
#define NRF24L01P_SPIx_MISO_PIN                    GPIO_PIN_11
#define NRF24L01P_SPIx_MISO_GPIO_PORT              GPIOC
#define NRF24L01P_SPIx_MISO_AF                     GPIO_AF6_SPI3
#define NRF24L01P_SPIx_MOSI_PIN                    GPIO_PIN_12
#define NRF24L01P_SPIx_MOSI_GPIO_PORT              GPIOC
#define NRF24L01P_SPIx_MOSI_AF                     GPIO_AF6_SPI3




static SPI_HandleTypeDef nrf24l01p_SpiHandle;
static GPIO_InitTypeDef nrf24l01p_CE_pin_Struct = {NRF24L01P_CE_PIN,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,};
static GPIO_InitTypeDef nrf24l01p_CSN_pin_Struct = {NRF24L01P_CSN_PIN,GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,};
static GPIO_InitTypeDef nrf24l01p_IRQ_pin_Struct = {NRF24L01P_IRQ_PIN,GPIO_MODE_IT_FALLING,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,};



void NRF24L01p_port_Initialize(){
	NRF24L01p_port_SPI_initialize();

	/* Enable GPIOA clock */
	//__HAL_RCC_GPIOA_CLK_ENABLE();
	//__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();


	HAL_SPI_Init(&nrf24l01p_SpiHandle);

	NRF24L01p_port_Pin_CE_Initialize();
	NRF24L01p_port_Pin_CSN_Initialize();
	NRF24L01p_port_Pin_IRQ_Initialize();
}
void NRF24L01p_port_DeInitialize(){
	HAL_GPIO_Init(NRF24L01P_CE_PORT, &nrf24l01p_CE_pin_Struct);
}
void NRF24L01p_port_Pin_CE_Initialize(){
	HAL_GPIO_Init(NRF24L01P_CE_PORT, &nrf24l01p_CE_pin_Struct);
}
void NRF24L01p_port_Pin_CSN_Initialize(){
	HAL_GPIO_Init(NRF24L01P_CSN_PORT, &nrf24l01p_CSN_pin_Struct);
}
void NRF24L01p_port_Pin_IRQ_Initialize(){
	HAL_GPIO_Init(NRF24L01P_IRQ_PORT, &nrf24l01p_IRQ_pin_Struct);

	//HAL_NVIC_SetPriority(EXTI9_5_IRQn, 10, 0);//------------------------------------------------
	//HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);//---------------------------------------------------------
}
bool NRF24L01p_port_read_Pin_CE(){
	return HAL_GPIO_ReadPin(NRF24L01P_CE_PORT, NRF24L01P_CE_PIN);
}
bool NRF24L01p_port_read_Pin_CSN(){
	return HAL_GPIO_ReadPin(NRF24L01P_CSN_PORT, NRF24L01P_CSN_PIN);
}
void NRF24L01p_port_write_Pin_CE(bool val){
	HAL_GPIO_WritePin(NRF24L01P_CE_PORT, NRF24L01P_CE_PIN, (GPIO_PinState)val);
}
void NRF24L01p_port_write_Pin_CSN(bool val){
	HAL_GPIO_WritePin(NRF24L01P_CSN_PORT, NRF24L01P_CSN_PIN, (GPIO_PinState)val);
}
void NRF24L01p_port_SPI_initialize(){
	// TODO Auto-generated destructor stub
	/*##-1- Configure the SPI peripheral #######################################*/
	/* Set the SPI parameters */
	nrf24l01p_SpiHandle.Instance               = NRF24L01P_SPIx;
	nrf24l01p_SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	nrf24l01p_SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
	nrf24l01p_SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
	nrf24l01p_SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
	nrf24l01p_SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
	nrf24l01p_SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	nrf24l01p_SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
	nrf24l01p_SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	nrf24l01p_SpiHandle.Init.CRCPolynomial     = 7;
	//nrf24l01p_SpiHandle.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
	nrf24l01p_SpiHandle.Init.NSS               = SPI_NSS_SOFT;
	//nrf24l01p_SpiHandle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;

	nrf24l01p_SpiHandle.Init.Mode = SPI_MODE_MASTER;

	GPIO_InitTypeDef  GPIO_InitStruct;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	NRF24L01P_SPIx_SCK_GPIO_CLK_ENABLE();
	NRF24L01P_SPIx_MISO_GPIO_CLK_ENABLE();
	NRF24L01P_SPIx_MOSI_GPIO_CLK_ENABLE();
	/* Enable SPI clock */
	NRF24L01P_SPIx_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* SPI SCK GPIO pin configuration  */
	GPIO_InitStruct.Pin       = NRF24L01P_SPIx_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = NRF24L01P_SPIx_SCK_AF;
	HAL_GPIO_Init(NRF24L01P_SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

	/* SPI MISO GPIO pin configuration  */
	GPIO_InitStruct.Pin = NRF24L01P_SPIx_MISO_PIN;
	GPIO_InitStruct.Alternate = NRF24L01P_SPIx_MISO_AF;
	HAL_GPIO_Init(NRF24L01P_SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

	/* SPI MOSI GPIO pin configuration  */
	GPIO_InitStruct.Pin = NRF24L01P_SPIx_MOSI_PIN;
	GPIO_InitStruct.Alternate = NRF24L01P_SPIx_MOSI_AF;
	HAL_GPIO_Init(NRF24L01P_SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);
}
int NRF24L01p_port_SPI_Transcieve(uint8_t *dataOut, uint8_t *dataIn, unsigned int size){
	return HAL_SPI_TransmitReceive(&nrf24l01p_SpiHandle, dataOut, dataIn, size,1000);
}

int NRF24L01p_port_SPI_Transmit(uint8_t *data, unsigned int size){
	HAL_SPI_Transmit(&nrf24l01p_SpiHandle, data, size, 1000);
}

int NRF24L01p_port_SPI_Receive(uint8_t *data, unsigned int size){
	HAL_SPI_Receive(&nrf24l01p_SpiHandle, data, size, 1000);
}


void NRF24L01p_port_DelayMs(unsigned int ms){
	HAL_Delay(ms);
	//vTaskDelay ((ms / portTICK_PERIOD_MS));

}
void NRF24L01p_port_DelayUs(unsigned int us){
	unsigned int ms = us/1000;
	HAL_Delay(ms + 1);
	//vTaskDelay (( ms / portTICK_PERIOD_MS));
}
unsigned int NRF24L01p_port_ClockMs(){
	return HAL_GetTick();
}
unsigned int NRF24L01p_port_ClockUs(){
	return HAL_GetTick()*1000;
}
void NRF24L01p_debug(const char *format, ...){

}
void NRF24L01p_debug_if(bool condition, const char *format, ...){

}












