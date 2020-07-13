/*
 * board.c
 *
 *  Created on: Jul 12, 2020
 *      Author: hr193
 */

#include <cygnini.h>
#include "cmsis_os.h"
#include "NRF24L01p.h"
#include "C12832Port.h"
#include "graphic_lcd.h"
#include "Si7006.h"
#include "FreeRTOS.h"
#include "task.h"

#define TX_NODE 1
#define RX_NODE 0


extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern UART_HandleTypeDef huart1;

Si7006_t Si7006;
uint8_t Si7006DevAddr = 0x40<<1;

uint8_t Si1133DevAddr = 0x55<<1;

NRF24L01p_Payload_t Rxpayload;
NRF24L01p_Payload_t TxPayload;
uint8_t RxData[32];
uint8_t TxData[32];
uint8_t radioRxData[32];
NRF24L01p_RadioConfig_t NRF24L01p_RadioConfig;
NRF24L01p_RxPipeConfig_t RxPipeConfig[6];


int cygnini();
int initialize_board();
void RadioReset();
void LED_Control(uint8_t id, uint8_t val);

void ButtonsTask(void *argument);
void LEDsTask(void *argument);
void RadioTask(void *argument);
void SensorsTask(void *argument);
void LCDTask(void *argument);
void NotificationsTask(void *argument);

TaskHandle_t ButtonsHandle = NULL;
TaskHandle_t LEDsHandle = NULL;
TaskHandle_t RadioHandle = NULL;
TaskHandle_t SensorsHandle = NULL;
TaskHandle_t LCDHandle = NULL;
TaskHandle_t NotificationsHandle = NULL;

#define TX_NODE 0
#define RX_NODE 1



int cygnini(){

	HAL_Delay(500);
	printf("starting CYGNINI\r\n");
	initialize_board();

#if TX_NODE == 1
	xTaskCreate(ButtonsTask,(signed portCHAR *) "t4", 1024, NULL, tskIDLE_PRIORITY, &ButtonsHandle );
#endif

#if RX_NODE == 1
	xTaskCreate(RadioTask,(signed portCHAR *) "t4", 1024, NULL, tskIDLE_PRIORITY, &RadioHandle );

#endif

	xTaskCreate(LEDsTask,(signed portCHAR *) "t4", 1024, NULL, tskIDLE_PRIORITY, &LEDsHandle );

	xTaskCreate(SensorsTask,(signed portCHAR *) "t4", 1024, NULL, tskIDLE_PRIORITY, &SensorsHandle );
	xTaskCreate(LCDTask,(signed portCHAR *) "t4", 1024, NULL, tskIDLE_PRIORITY, &LCDHandle );
	xTaskCreate(NotificationsTask,(signed portCHAR *) "t4", 1024, NULL, tskIDLE_PRIORITY, &NotificationsHandle );

	vTaskStartScheduler();

	while(1);



	while(1);
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
  * @brief  This function sends character for standard io
  * @param ch character to send
  * @retval None
  */
int __io_putchar(int ch){
	ITM_SendChar(ch);
	return 0;
}
/**
  * @brief  This function receives character from standard io
  * @retval None
  */
int __io_getchar(void){

	return 0;
}


int initialize_board(){
	  graphic_lcd_initialize ();
	  graphic_lcd_clear_screen ();
	  DISPLAY_BACKLIGHT_ON;
	  Si7006_port_init();


	  if(Si7006.check_hardware() == SI7006_ERROR){
		  graphic_lcd_write(0, 0, "Si7006 NOT READY");
	  }else{
		  graphic_lcd_write(0, 0, "Si7006 READY");
	  }


	  int x = HAL_I2C_IsDeviceReady(&hi2c1,Si1133DevAddr, 1000, 1000);
	  if(x == HAL_OK) graphic_lcd_write(1, 0, "Si1133 READY");
	  else graphic_lcd_write(1, 0, "Si1133 NOT READY");



}






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



/* USER CODE BEGIN Header_ButtonsTask */
/**
* @brief Function implementing the Buttons thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ButtonsTask */
void ButtonsTask(void *argument)
{
  /* USER CODE BEGIN ButtonsTask */
	RadioReset();



	Rxpayload.retransmitCount = 15;

	graphic_lcd_write(0, 0, "PRESS ANY BUTTON");
	graphic_lcd_write(3, 0, "A     B     C     D");


	//printf("button loop\r\n");
  /* Infinite loop */
  for(;;)
  {
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 0){
		  	float temperature = Si7006_temperature(&Si7006);

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
			Rxpayload.retransmitCount = 15;
			//TxPayload.length = strlen(tempString);
			TxPayload.address = 0x11223344EE;

			NRF24L01p_writePayload(&TxPayload);
			NRF24L01p_ErrorStatus_t ret = NRF24L01p_TransmitPayload(&TxPayload);

			if(ret == NRF24L01P_ERROR){
				graphic_lcd_write(3, 0, "Transmission Error");
			}

		}
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 0){
			float relativeHumidity = Si7006_relativeHumidity(&Si7006);
			int tempInteger = (int)relativeHumidity;
			int tempDecimel = ((float)relativeHumidity - (int)relativeHumidity)*100;

			char tempString[30];
			char tempString2[30];
			sprintf(tempString, "Humidity: %d.%d %%", tempInteger,tempDecimel );
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
	    osDelay(1);

  }
  /* USER CODE END ButtonsTask */
}

/* USER CODE BEGIN Header_LEDsTask */
/**
* @brief Function implementing the LEDs thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LEDsTask */
void LEDsTask(void *argument)
{
  /* USER CODE BEGIN LEDsTask */
  /* Infinite loop */
  for(;;)
  {



  }
  /* USER CODE END LEDsTask */
}

/* USER CODE BEGIN Header_RadioTask */
/**
* @brief Function implementing the Radio thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RadioTask */
void RadioTask(void *argument)
{
  /* USER CODE BEGIN RadioTask */
	RadioReset();

	char myMesg[32];

	Rxpayload.UseAck = 1;


	Rxpayload.address = 0x11223344EE;
	Rxpayload.data = (uint8_t*)myMesg;
	Rxpayload.length = strlen(myMesg);
	Rxpayload.retransmitCount = 15;
  /* Infinite loop */
  for(;;)
  {
	  int i = 0;
	  		char c;
	  		while(1){
	  			//c = pc_getc();
	  			HAL_StatusTypeDef rxerr = HAL_UART_Receive(&huart1, &c, 1, 0);



	  			if(NRF24L01p_readable()){
	  				xTaskNotify ( NotificationsHandle, (1<<0), eSetBits);
	  				//custom_print("message received\r\n");

	  				Rxpayload.data = RxData;

	  				NRF24L01p_clear_data_ready_flag();
	  				NRF24L01p_readPayload(&Rxpayload);
	  				Rxpayload.data[Rxpayload.length] = '\0';

	  				graphics_lcd_clear_line(0);
	  				graphics_lcd_clear_line(1);
	  				graphics_lcd_clear_line(2);
	  				graphic_lcd_write(1, 0, "RECEIVED DATA");
	  				graphic_lcd_write(2, 0, Rxpayload.data);

	  				//custom_print("\r\n\r\n");
	  				//custom_print(Rxpayload.data);
	  				//custom_print("\r\n\r\n");

	  				//xTaskNotify ( xGLCDHandle, (1<<0), eSetBits);
	  				NRF24L01p_flush_rx();


	  				//custom_print("\r\n\e[1;32mCygnini>>\e[0m");





	  			}



	  		}
	osDelay(100);

  }
  /* USER CODE END RadioTask */
}

/* USER CODE BEGIN Header_SensorsTask */
/**
* @brief Function implementing the Sensors thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SensorsTask */
void SensorsTask(void *argument)
{
  /* USER CODE BEGIN SensorsTask */
  /* Infinite loop */
  for(;;)
  {
	    osDelay(800);
	    HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	    osDelay(800);
	    HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
  }
  /* USER CODE END SensorsTask */
}

/* USER CODE BEGIN Header_LCDTask */
/**
* @brief Function implementing the LCD thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LCDTask */
void LCDTask(void *argument)
{

  /* USER CODE BEGIN LCDTask */
	uint32_t ulNotifiedValue;

	int dataCount = 0;
	char msg[30];
  /* Infinite loop */
  for(;;)
  {
		if(xTaskNotifyWait (0 , 0xFFFFFFFF, &ulNotifiedValue, portMAX_DELAY) == pdTRUE){
			dataCount++;
			sprintf(msg, "total messages: %d", dataCount);
			graphic_lcd_clear_screen ();
			graphic_lcd_write(1, 0, msg);
			//graphic_lcd_write(3, 0, cmdMsg);
						//DigitalPin_SetValue(&led1);
		}

		osDelay(100);
  }
  /* USER CODE END LCDTask */
}




void NotificationsTask( void *pvParameters ){
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






