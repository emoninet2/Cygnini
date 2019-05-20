/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.2.0   2019-03-07

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/

#include <string.h>

#include "main.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "NRF24L01p.h"
#include "C12832Port.h"
#include "graphic_lcd.h"
#include "Si7006.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TX_NODE 1
#define RX_NODE 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart1;

TaskHandle_t xRadioHandle = NULL;
TaskHandle_t xGLCDHandle = NULL;
TaskHandle_t xNotificationHandle = NULL;
TaskHandle_t xPCHandle = NULL;
TaskHandle_t xButtonsHandle = NULL;

TaskHandle_t xRxNodeHandle = NULL;
TaskHandle_t xTxNodeHandle = NULL;

Si7006_t Si7006;

NRF24L01p_Payload_t Rxpayload;
NRF24L01p_Payload_t TxPayload;
uint8_t RxData[32];
uint8_t TxData[32];
uint8_t radioRxData[32];
NRF24L01p_RadioConfig_t NRF24L01p_RadioConfig;
NRF24L01p_RxPipeConfig_t RxPipeConfig[6];
char cmdMsg[50];


uint8_t Si7006DevAddr = 0x40<<1;
uint8_t Si1133DevAddr = 0x55<<1;

/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART1_UART_Init(void);
void SystemClock_Config(void);


void xRadio( void *pvParameters );
void xNotification( void *pvParameters );
void xPC( void *pvParameters );
void xGLCD( void *pvParameters );
void xButtons (void *pvParameters);
void xRxNode( void *pvParameters );
void xTxNode( void *pvParameters );





Si7006_error_t Si7006_port_init(void);
Si7006_error_t Si7006_port_i2c_init(void);
Si7006_error_t Si7006_port_i2c_transmit(uint8_t *data, unsigned int size);
Si7006_error_t Si7006_port_i2c_receive(uint8_t *data, unsigned int size);
Si7006_error_t Si7006_port_check_hardware();
Si7006_error_t Si7006_port_delay(unsigned int ms);

void LED_Control(uint8_t id, uint8_t val);
void RadioReset();


static void pc_putc(char c);
static char pc_getc();
static void custom_print(char *str);
void Error_Handler(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */




/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

	HAL_Init();
	SystemClock_Config();

	__HAL_RCC_GPIOC_CLK_ENABLE();
	//__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	c12832_hal_spi_init();
	c12832_hal_gpio_init();


	MX_GPIO_Init();
	MX_DMA_Init();
	MX_I2C1_Init();
	MX_SPI2_Init();
	MX_SPI3_Init();
	MX_USART1_UART_Init();


	//initLEDs();
	//initButtons();


	//testLedAndButtones();


	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);


	HAL_GPIO_WritePin(DISPLAY_BACKLIGHT_GPIO_Port, DISPLAY_BACKLIGHT_Pin, GPIO_PIN_RESET);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DISPLAY_BACKLIGHT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DISPLAY_BACKLIGHT_GPIO_Port, &GPIO_InitStruct);

	DISPLAY_BACKLIGHT_OFF;

	//HAL_Delay(2000);

	graphic_lcd_initialize ();
	graphic_lcd_clear_screen ();
	DISPLAY_BACKLIGHT_ON;

	//HAL_Delay(1000);




	Si7006_port_init();






	if(Si7006.check_hardware() == SI7006_ERROR){
		graphic_lcd_write(0, 0, "Si7006 NOT READY");
	}else{
		graphic_lcd_write(0, 0, "Si7006 READY");
	}


	int x = HAL_I2C_IsDeviceReady(&hi2c1,Si1133DevAddr, 1000, 1000);
	if(x == HAL_OK) graphic_lcd_write(1, 0, "Si1133 READY");
	else graphic_lcd_write(1, 0, "Si1133 NOT READY");



	HAL_Delay(3000);
	graphic_lcd_clear_screen ();



#if(TX_NODE == 1)

	//testLedAndButtones();
	//xTaskCreate(xRadio,(signed portCHAR *) "t1", 500, NULL, tskIDLE_PRIORITY, &xRadioHandle );
	xTaskCreate(xGLCD,(signed portCHAR *) "t3", 500, NULL, tskIDLE_PRIORITY, &xGLCDHandle );
	xTaskCreate(xNotification,(signed portCHAR *) "t4", 200, NULL, tskIDLE_PRIORITY, &xNotificationHandle );
	xTaskCreate(xPC,(signed portCHAR *) "t5", 1000, NULL, tskIDLE_PRIORITY, &xPCHandle );
	xTaskCreate(xButtons,(signed portCHAR *) "t6", 500, NULL, tskIDLE_PRIORITY, &xButtonsHandle );
	//xTaskCreate(xTxNode,(signed portCHAR *) "t7", 1000, NULL, tskIDLE_PRIORITY, &xTxNodeHandle );

	vTaskStartScheduler();

	return 0;
#endif

#if(RX_NODE == 1)

	//testLedAndButtones();
	//xTaskCreate(xRadio,(signed portCHAR *) "t1", 500, NULL, tskIDLE_PRIORITY, &xRadioHandle );
	//xTaskCreate(xGLCD,(signed portCHAR *) "t3", 500, NULL, tskIDLE_PRIORITY, &xGLCDHandle );
	xTaskCreate(xNotification,(signed portCHAR *) "t4", 200, NULL, tskIDLE_PRIORITY, &xNotificationHandle );
	//xTaskCreate(xPC,(signed portCHAR *) "t5", 1000, NULL, tskIDLE_PRIORITY, &xPCHandle );
	xTaskCreate(xButtons,(signed portCHAR *) "t6", 500, NULL, tskIDLE_PRIORITY, &xButtonsHandle );
	xTaskCreate(xRxNode,(signed portCHAR *) "t7", 1000, NULL, tskIDLE_PRIORITY, &xRxNodeHandle );
	vTaskStartScheduler();

	return 0;
#endif

	/* Infinite loop */
	while (1)
	{

	}



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



/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/




void RadioReset(){

	NRF24L01p_RadioConfig.DataReadyInterruptEnabled = 0;
	NRF24L01p_RadioConfig.DataSentInterruptFlagEnabled = 0;
	NRF24L01p_RadioConfig.MaxRetryInterruptFlagEnabled = 0;
	NRF24L01p_RadioConfig.Crc = CONFIG_CRC_16BIT;
	NRF24L01p_RadioConfig.AutoReTransmissionCount = 15;
	NRF24L01p_RadioConfig.AutoReTransmitDelayX250us = 15;
	NRF24L01p_RadioConfig.frequencyOffset = 2;
	NRF24L01p_RadioConfig.datarate = RF_SETUP_RF_DR_2MBPS;
	NRF24L01p_RadioConfig.RfPower = RF_SETUP_RF_PWR_0DBM;
	NRF24L01p_RadioConfig.PllLock = 0;
	NRF24L01p_RadioConfig.ContWaveEnabled = 0;
	NRF24L01p_RadioConfig.FeatureDynamicPayloadEnabled = 1;
	NRF24L01p_RadioConfig.FeaturePayloadWithAckEnabled = 1;
	NRF24L01p_RadioConfig.FeatureDynamicPayloadWithNoAckEnabled = 1;

    RxPipeConfig[0].address = 0x11223344EE;
    RxPipeConfig[1].address = 0x9A4524CE01;
    RxPipeConfig[2].address = 0x9A4524CE02;
    RxPipeConfig[3].address = 0x9A4524CE03;
    RxPipeConfig[4].address = 0x9A4524CE04;
    RxPipeConfig[5].address = 0x9A4524CE05;


	int i;
	for(i=0;i<6;i++){
		RxPipeConfig[i].PipeEnabled = 1;
		RxPipeConfig[i].autoAckEnabled = 1;
		RxPipeConfig[i].dynamicPayloadEnabled = 1;
	}


	NRF24L01p_ResetConfigValues(&NRF24L01p_RadioConfig, RxPipeConfig);
}





void xRadio( void *pvParameters ){
	RadioReset();

	char myMesg[32];

	Rxpayload.UseAck = 1;


	Rxpayload.address = 0x11223344EE;
	Rxpayload.data = (uint8_t*)myMesg;
	Rxpayload.length = strlen(myMesg);
	Rxpayload.retransmitCount = 15;


	int count = 0;
	int success = 0;
	int fail = 0;



	while(1){


		sprintf(TxData, "message %d", count++);
		//TxPayload.data = tempString;
		TxPayload.data = TxData;
		TxPayload.UseAck = 1;
		TxPayload.length = strlen(TxData);
		//TxPayload.length = strlen(tempString);
		TxPayload.address = 0x11223344EE;

		NRF24L01p_writePayload(&TxPayload);

		NRF24L01p_ErrorStatus_t ret = NRF24L01p_TransmitPayload(&TxPayload);

		if(ret == NRF24L01P_SUCCESS){
			success ++;
		}
		else{
			fail++;
		}


		char msg [30];
		sprintf(msg, "success %d", success);
		graphic_lcd_write(1, 0, msg);
		sprintf(msg, "fail %d", fail);
		graphic_lcd_write(2, 0, msg);

		NRF24L01p_flush_tx();
		NRF24L01p_flush_rx();

		HAL_Delay(200);

		if(NRF24L01p_readable()){
			xTaskNotify ( xNotificationHandle, (1<<0), eSetBits);
			xTaskNotify ( xGLCDHandle, (1<<0), eSetBits);

		}
	}
}

void xNotification( void *pvParameters ){
	uint32_t ulNotifiedValue;
	while(1){

		if(xTaskNotifyWait (0 , 0xFFFFFFFF, &ulNotifiedValue, portMAX_DELAY) == pdTRUE){
						//DigitalPin_ClearValue(&led1);
			HAL_GPIO_WritePin (GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
						vTaskDelay(200);
			HAL_GPIO_WritePin (GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);

						//DigitalPin_SetValue(&led1);
		}

		vTaskDelay(100);

	}
}




void xPC( void *pvParameters ){
	char cmd[50];
	int CmdSize = 32;
	custom_print("initialization\r\n");

	RadioReset();

	char myMesg[32];

	Rxpayload.UseAck = 1;


	Rxpayload.address = 0x11223344EE;
	Rxpayload.data = (uint8_t*)myMesg;
	Rxpayload.length = strlen(myMesg);
	Rxpayload.retransmitCount = 15;


	//////
	/////
	custom_print ("\e[1;32mWlecome Everyone.\r\n\e[0m");
	custom_print ("\e[1;34mCygning Demo\r\n\e[0m");
    custom_print ("\e[1;35mFYS4260\r\n\e[0m");

    char command[50];
    char commandPtr = 0;

	while(1){

		//custom_print("hello world\b\b\b\r\n");
		//custom_print ("\e[1;30mThis is a gray text.\r\n\e[0m");
		//custom_print ("\e[1;31mThis is a red text.\r\n\e[0m");
		custom_print("\r\n\e[1;32mCygnini>>\e[0m");
	    //custom_print ("\e[1;36mThis is a cyan text.\r\n\e[0m");
	    //custom_print ("\e[1;37mThis is a white text.\r\n\e[0m");


	    int i = 0;
		char c;
		while(1){
			//c = pc_getc();
			HAL_StatusTypeDef rxerr = HAL_UART_Receive(&huart1, &c, 1, 0);

			if(rxerr == HAL_OK){
				//printf("%#2x",c);
				if(c == '\r'){
				   cmd[i] = 0;
				   if(i>0) break;

				   command[commandPtr] = 0;


				}
				//else if(c == 0x08 || c==0x7f){//backspace || del
				//	i--;
				//	cmd[i] = 0;
				//	pc_putc(0x7f);
				//}
				else{
					if(i<CmdSize){
						pc_putc(c);
						cmd[i] = c;
						i++;

						command[commandPtr] = c;
						commandPtr++;

					}

				}
			}




			if(NRF24L01p_readable()){
				xTaskNotify ( xNotificationHandle, (1<<0), eSetBits);
				//custom_print("message received\r\n");

				Rxpayload.data = RxData;

				NRF24L01p_clear_data_ready_flag();
				NRF24L01p_readPayload(&Rxpayload);
				Rxpayload.data[Rxpayload.length] = '\0';

				graphic_lcd_write(1, 0, "RECEIVED DATA");
				graphic_lcd_write(2, 0, Rxpayload.data);

				custom_print("\r\n\r\n");
				custom_print(Rxpayload.data);
				custom_print("\r\n\r\n");

				//xTaskNotify ( xGLCDHandle, (1<<0), eSetBits);
				NRF24L01p_flush_rx();


				custom_print("\r\n\e[1;32mCygnini>>\e[0m");


				for(int m=0;m<commandPtr;m++){
					pc_putc(command[m]);
				}


			}



		}

		commandPtr = 0;


		for(int j=0;j<=i;j++){
			cmdMsg[j] = cmd[j];
		}


		//custom_print(cmdMsg);
		//custom_print("\r\n");


		sprintf(TxData, cmdMsg);
		//TxPayload.data = tempString;
		TxPayload.data = TxData;
		TxPayload.UseAck = 1;
		TxPayload.length = strlen(cmdMsg);
		//TxPayload.length = strlen(tempString);
		TxPayload.address = 0x11223344EE;

		NRF24L01p_writePayload(&TxPayload);

		NRF24L01p_ErrorStatus_t ret = NRF24L01p_TransmitPayload(&TxPayload);

		if(ret == NRF24L01P_SUCCESS){

		}
		else{
			custom_print("\t\t\r\n\e[1;31mTransmission Failed\e[0m");
		}



		NRF24L01p_flush_tx();
		//NRF24L01p_flush_rx();

		HAL_Delay(200);




		//xTaskNotify ( xGLCDHandle, (1<<0), eSetBits);
		vTaskDelay(100);
	}
}




void xGLCD( void *pvParameters ){
	uint32_t ulNotifiedValue;

	int dataCount = 0;
	char msg[30];
	while(1){

		if(xTaskNotifyWait (0 , 0xFFFFFFFF, &ulNotifiedValue, portMAX_DELAY) == pdTRUE){
			dataCount++;
			sprintf(msg, "total messages: %d", dataCount);
			graphic_lcd_clear_screen ();
			graphic_lcd_write(1, 0, msg);
			graphic_lcd_write(3, 0, cmdMsg);
						//DigitalPin_SetValue(&led1);
		}

		vTaskDelay(100);

	}
}

void xButtons (void *pvParameters) {

	printf("this is button loop\r\n");
	while(1){
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0){
			custom_print("you pressed button D\r\n");

		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0){
			custom_print("you pressed button C\r\n");

		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 0){
			custom_print("you pressed button B\r\n");

		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 0){
			custom_print("you pressed button A\r\n");

		}

		vTaskDelay(200);

	}
}


void LED_Control(uint8_t id, uint8_t val){
	switch(id){

	case '0': {
		if(val == '0') HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		break;}
	case '1': {
		if(val == '0') HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		break;}
	case '2': {
		if(val == '0') HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		break;}
	case '3': {
		if(val == '0') HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		else HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		break;}

	default: break;
	}
}


void xRxNode( void *pvParameters ){

	graphic_lcd_write(0, 0, "RX NODE");
	vTaskDelay(1000);
	graphic_lcd_clear_screen();

	RadioReset();

	char myMesg[32];

	Rxpayload.UseAck = 1;


	Rxpayload.address = 0x11223344EE;
	Rxpayload.data = (uint8_t*)myMesg;
	Rxpayload.length = strlen(myMesg);
	Rxpayload.retransmitCount = 15;


	Si7006_t sensor;
	sensor.init = Si7006_port_init;
	sensor.i2c_init = Si7006_port_i2c_init;
	sensor.i2c_transmit = Si7006_port_i2c_transmit;
	sensor.i2c_receive = Si7006_port_i2c_receive;
	sensor.check_hardware = Si7006_port_check_hardware;
	sensor.delay = Si7006_port_delay;


	graphic_lcd_write(0, 0, "PRESS ANY BUTTON");
	graphic_lcd_write(3, 0, "A     B     C     D");


	while(1){

		int xCount = 0;

		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 0){

			float temperature = Si7006_temperature(&sensor);

			int tempInteger = (int)temperature;
			int tempDecimel = ((float)temperature - (int)temperature)*100;

			char tempString[30];
			char tempString2[30];
			sprintf(tempString, "Temp: %d.%d deg C", tempInteger,tempDecimel );
			sprintf(tempString2, "%d.%d deg C", tempInteger,tempDecimel );
			graphic_lcd_clear_screen();
			graphic_lcd_write(0, 0, "temperature:");
			graphic_lcd_write(1, 0,tempString2);


			sprintf(TxData, tempString);
			//TxPayload.data = tempString;
			TxPayload.data = TxData;
			TxPayload.UseAck = 1;
			TxPayload.length = strlen(tempString);
			//TxPayload.length = strlen(tempString);
			TxPayload.address = 0x11223344EE;

			NRF24L01p_writePayload(&TxPayload);
			NRF24L01p_ErrorStatus_t ret = NRF24L01p_TransmitPayload(&TxPayload);

			if(ret == NRF24L01P_ERROR){
				graphic_lcd_write(3, 0, "Transmission Error");
			}




		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 0){

			float relativeHumidity = Si7006_relativeHumidity(&sensor);
			int tempInteger = (int)relativeHumidity;
			int tempDecimel = ((float)relativeHumidity - (int)relativeHumidity)*100;

			char tempString[30];
			char tempString2[30];
			sprintf(tempString, "Humidity: %d.%d percent", tempInteger,tempDecimel );
			sprintf(tempString2, "%d.%d percent", tempInteger,tempDecimel );
			graphic_lcd_clear_screen();
			graphic_lcd_write(0, 0, "relative humidity:");
			graphic_lcd_write(1, 0,tempString2);


			sprintf(TxData, tempString);
			//TxPayload.data = tempString;
			TxPayload.data = TxData;
			TxPayload.UseAck = 1;
			TxPayload.length = strlen(tempString);
			//TxPayload.length = strlen(tempString);
			TxPayload.address = 0x11223344EE;

			NRF24L01p_writePayload(&TxPayload);
			NRF24L01p_ErrorStatus_t ret = NRF24L01p_TransmitPayload(&TxPayload);

			if(ret == NRF24L01P_ERROR){
				graphic_lcd_write(3, 0, "Transmission Error");
			}


		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0){
			sprintf(TxData, "button pressed: C");
			//TxPayload.data = tempString;
			TxPayload.data = TxData;
			TxPayload.UseAck = 1;
			TxPayload.length = strlen(TxData);
			//TxPayload.length = strlen(tempString);
			TxPayload.address = 0x11223344EE;

			NRF24L01p_writePayload(&TxPayload);
			NRF24L01p_ErrorStatus_t ret = NRF24L01p_TransmitPayload(&TxPayload);

			graphic_lcd_clear_screen();
			graphic_lcd_write(0, 0, "pressed button: C");

			if(ret == NRF24L01P_ERROR){
				graphic_lcd_write(3, 0, "Transmission Error");
			}






		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0){
			//custom_print("you pressed button A\r\n");
			sprintf(TxData, "button pressed: D");
			//TxPayload.data = tempString;
			TxPayload.data = TxData;
			TxPayload.UseAck = 1;
			TxPayload.length = strlen(TxData);
			//TxPayload.length = strlen(tempString);
			TxPayload.address = 0x11223344EE;

			NRF24L01p_writePayload(&TxPayload);
			NRF24L01p_ErrorStatus_t ret = NRF24L01p_TransmitPayload(&TxPayload);



			graphic_lcd_clear_screen();
			graphic_lcd_write(0, 0, "pressed button: D");

			if(ret == NRF24L01P_ERROR){
				graphic_lcd_write(3, 0, "Transmission Error");
			}


		}


		if(NRF24L01p_readable()){
				xTaskNotify ( xNotificationHandle, (1<<0), eSetBits);
				//xTaskNotify ( xNotificationHandle, (1<<0), eSetBits);


				//Payload_t payload;
				Rxpayload.data = RxData;

				NRF24L01p_clear_data_ready_flag();
				NRF24L01p_readPayload(&Rxpayload);
				Rxpayload.data[Rxpayload.length] = '\0';
				//printf("received data\r\n");
				//graphic_lcd_write(1, 0, "RECEIVED DATA");
				//graphic_lcd_write(2, 0, Rxpayload.data);
				graphic_lcd_clear_screen();
				//graphic_lcd_write(3, 0, Rxpayload.data);
				//if(Rxpayload.data[0] == 'Q'){

					if(Rxpayload.data[0] == 'L'){//LED control
						uint8_t LedId = Rxpayload.data[1];
						uint8_t LedVal = Rxpayload.data[2];

						LED_Control(LedId,LedVal);
					}
					else if(Rxpayload.data[0] == 'G'){//GLCD control
						if(Rxpayload.data[1] == 'C'){//clear lcd
							//if(Rxpayload.data[3] == 'S')
							//	graphic_lcd_clear_screen();
							//else if(Rxpayload.data[3] == 'L'){
							//	if(Rxpayload.data[4] == '0')graphics_lcd_clear_line(0);
							//	else if(Rxpayload.data[4] == '1')graphics_lcd_clear_line(1);
							//	else if(Rxpayload.data[4] == '2')graphics_lcd_clear_line(2);
							//	else if(Rxpayload.data[4] == '3')graphics_lcd_clear_line(3);
							//}
						}
						if(Rxpayload.data[1] == 'P'){//print
							int line = Rxpayload.data[2];
							//int printSize = Rxpayload.data[4];

							//if(printSize >28) printSize = 28;

							char printMsg[32]; //28 + 1 extra for end char

							for(int k = 0;k<28;k++){
								printMsg[k] = Rxpayload.data[3+k];
							}

							graphics_lcd_clear_line(line);
							graphic_lcd_write(line, 0, printMsg);
						}
						else if(Rxpayload.data[1] == 'C'){//clear lcd
							graphic_lcd_clear_screen();
						}
						else if(Rxpayload.data[1] == 'B'){//lcd backlight
							if(Rxpayload.data[2] == '0'){//clear lcd
								DISPLAY_BACKLIGHT_OFF;
							}
							else if(Rxpayload.data[2] == '1'){//clear lcd
								DISPLAY_BACKLIGHT_ON;
							}
						}

					}



				//}
				else{

				}


				NRF24L01p_flush_rx();

			}

		vTaskDelay(100);

	}

}

void xTxNode( void *pvParameters ){


	while(1){

	}

}






/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_7;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 36;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV6;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_SAI1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 26;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV17;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /**Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();


}


/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00702991;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  */
static void MX_DMA_Init(void)
{


}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 PA6 PA7
                           PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC5 PC6 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}




static void pc_putc(char c){
	HAL_UART_Transmit(&huart1, &c, 1,0xFFFF);

}

static char pc_getc(){
	char c;
	HAL_UART_Receive(&huart1, &c, 1, 0);
	return c;
}

static void custom_print(char *str){
	HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str),0xFFFF);

}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
