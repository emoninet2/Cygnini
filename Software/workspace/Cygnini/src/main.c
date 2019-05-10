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

/* Includes */
#include "main.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "usb_device.h"


#include "NRF24L01p.h"
#include "C12832Port.h"
#include "graphic_lcd.h"
#include "Si7006.h"


/* Private macro */

/* Private variables */
/* Private function prototypes */
/* Private functions */
void SystemClock_Config(void);
void Error_Handler(void);


#define TX_UNIT 0
#define RX_UNIT 1


//SMBUS_HandleTypeDef hsmbus1;
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;



/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_SMBUS_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */


	hi2c1.Instance = I2C1;
	hi2c1.Mode = HAL_I2C_MODE_MASTER;
	hi2c1.Init.Timing = 0xA0120227;

	//hi2c1.Init.AnalogFilter = SMBUS_ANALOGFILTER_ENABLE;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = SMBUS_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = SMBUS_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = SMBUS_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = SMBUS_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = SMBUS_NOSTRETCH_DISABLE;
	//hi2c1.Init.PacketErrorCheckMode = SMBUS_PEC_DISABLE;
	//hi2c1.Init.PeripheralMode = SMBUS_PERIPHERAL_MODE_SMBUS_SLAVE;
	//hi2c1.Init.SMBusTimeout = 0x0000836E;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
	Error_Handler();
	}

	HAL_I2C_MspInit(&hi2c1);




/*
  hsmbus1.Instance = I2C1;
  hsmbus1.Init.Timing = 0x10808DD3;
  hsmbus1.Init.AnalogFilter = SMBUS_ANALOGFILTER_ENABLE;
  hsmbus1.Init.OwnAddress1 = 2;
  hsmbus1.Init.AddressingMode = SMBUS_ADDRESSINGMODE_7BIT;
  hsmbus1.Init.DualAddressMode = SMBUS_DUALADDRESS_DISABLE;
  hsmbus1.Init.OwnAddress2 = 0;
  hsmbus1.Init.OwnAddress2Masks = SMBUS_OA2_NOMASK;
  hsmbus1.Init.GeneralCallMode = SMBUS_GENERALCALL_DISABLE;
  hsmbus1.Init.NoStretchMode = SMBUS_NOSTRETCH_DISABLE;
  hsmbus1.Init.PacketErrorCheckMode = SMBUS_PEC_DISABLE;
  hsmbus1.Init.PeripheralMode = SMBUS_PERIPHERAL_MODE_SMBUS_SLAVE;
  hsmbus1.Init.SMBusTimeout = 0x0000836E;
  if (HAL_SMBUS_Init(&hsmbus1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SMBUS_MspInit(&hsmbus1);
*/

  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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

  HAL_UART_MspInit(&huart1);


  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}


void initLEDs(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 ;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


void initButtons(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0 ;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


}



void testLedAndButtones(){


	for(;;) {
			printf("hello world\r\n");
			vTaskDelay ((100 / portTICK_PERIOD_MS));

			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1){
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

				HAL_GPIO_WritePin (GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
				HAL_GPIO_WritePin (GPIOB, GPIO_PIN_9, GPIO_PIN_SET);

			}
			else{
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

				HAL_GPIO_WritePin (GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
				HAL_GPIO_WritePin (GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
			}


			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 1){
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			}
			else{
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			}


			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 1){
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
			}
			else{
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
			}


			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == 1){
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
			}
			else{
				HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
			}

	    }


}






Si7006_error_t Si7006_port_init(void){

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



NRF24L01p_RadioConfig_t NRF24L01p_RadioConfig;
NRF24L01p_RxPipeConfig_t RxPipeConfig[6];

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

static void custom_print(char *str){
	HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str),0xFFFF);
}


NRF24L01p_Payload_t Rxpayload;
NRF24L01p_Payload_t TxPayload;
uint8_t RxData[32];
uint8_t TxData[32];




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


	MX_I2C1_SMBUS_Init();
	MX_USART1_UART_Init();


	initLEDs();
	initButtons();


	//testLedAndButtones();


	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_9, GPIO_PIN_SET);


	HAL_GPIO_WritePin(DISPLAY_BACKLIGHT_GPIO_Port, DISPLAY_BACKLIGHT_Pin, GPIO_PIN_RESET);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DISPLAY_BACKLIGHT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DISPLAY_BACKLIGHT_GPIO_Port, &GPIO_InitStruct);

	DISPLAY_BACKLIGHT_OFF;

	HAL_Delay(2000);

	graphic_lcd_initialize ();
	graphic_lcd_clear_screen ();
	DISPLAY_BACKLIGHT_ON;
	graphic_lcd_write(0, 0, "TX NODE");
	HAL_Delay(1000);



	uint8_t Si7006DevAddr = 0x40<<1;
	uint8_t Si1133DevAddr = 0x55<<1;


	Si7006_t sensor;
	sensor.init = Si7006_port_init;
	sensor.i2c_init = Si7006_port_i2c_init;
	sensor.i2c_transmit = Si7006_port_i2c_transmit;
	sensor.i2c_receive = Si7006_port_i2c_receive;
	sensor.check_hardware = Si7006_port_check_hardware;
	sensor.delay = Si7006_port_delay;



	if(sensor.check_hardware() == SI7006_ERROR){
		graphic_lcd_write(0, 0, "Si7006 NOT READY");
	}else{
		graphic_lcd_write(0, 0, "Si7006 READY");
	}


	int x = HAL_I2C_IsDeviceReady(&hi2c1,Si1133DevAddr, 1000, 1000);
	if(x == HAL_OK) graphic_lcd_write(1, 0, "Si1133 READY");
	else graphic_lcd_write(1, 0, "Si1133 NOT READY");



	HAL_Delay(3000);
	graphic_lcd_clear_screen ();


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


	//testLedAndButtones();



	while(1){
		custom_print("what the hell \r\n");
		float temperature = Si7006_temperature(&sensor);

		int tempInteger = (int)temperature;
		int tempDecimel = ((float)temperature - (int)temperature)*100;

		char tempString[30];

		sprintf(tempString, "Temp: %d.%d deg C", tempInteger,tempDecimel );
		graphic_lcd_write(0, 0,tempString);


		//float relativeHumidity = Si7006_relativeHumidity(&sensor);
		//tempInteger = (int)relativeHumidity;
		//tempDecimel = ((float)relativeHumidity - (int)relativeHumidity)*100;

		//sprintf(tempString, "Humidity: %d.%d %%", tempInteger,tempDecimel );
		//graphic_lcd_write(1, 0,tempString);



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

			custom_print("received data\r\n");

		}


	}













	/* Infinite loop */
	while (1)
	{




		if(NRF24L01p_readable()){

				//xTaskNotify ( xNotificationHandle, (1<<0), eSetBits);


				//Payload_t payload;
				Rxpayload.data = RxData;

				NRF24L01p_clear_data_ready_flag();
				NRF24L01p_readPayload(&Rxpayload);
				Rxpayload.data[Rxpayload.length] = '\0';
				//printf("received data\r\n");
				graphic_lcd_write(1, 0, "RECEIVED DATA");
				graphic_lcd_write(3, 0, Rxpayload.data);
				NRF24L01p_flush_rx();

			}


		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1){
			graphic_lcd_write(0, 0, "1");

		}
		else{
			graphic_lcd_write(0, 0, "0");
			sprintf(TxData, "love you");
			//TxPayload.data = tempString;
			TxPayload.data = TxData;
			TxPayload.UseAck = 1;
			TxPayload.length = strlen(TxData);
			//TxPayload.length = strlen(tempString);
			TxPayload.address = 0x11223344EE;

			NRF24L01p_writePayload(&TxPayload);
			NRF24L01p_TransmitPayload(&TxPayload);
		}

	}










}






int main2(void)
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


	MX_I2C1_SMBUS_Init();



	initLEDs();
	initButtons();


	//testLedAndButtones();


	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_9, GPIO_PIN_SET);


	HAL_GPIO_WritePin(DISPLAY_BACKLIGHT_GPIO_Port, DISPLAY_BACKLIGHT_Pin, GPIO_PIN_RESET);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DISPLAY_BACKLIGHT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DISPLAY_BACKLIGHT_GPIO_Port, &GPIO_InitStruct);

	DISPLAY_BACKLIGHT_OFF;

	HAL_Delay(2000);

	graphic_lcd_initialize ();
	graphic_lcd_clear_screen ();
	DISPLAY_BACKLIGHT_ON;
	graphic_lcd_write(0, 0, "HELLO");
	HAL_Delay(1000);


	uint8_t Si7006DevAddr = 0x40<<1;
	uint8_t Si1133DevAddr = 0x55<<1;


	Si7006_t sensor;
	sensor.init = Si7006_port_init;
	sensor.i2c_init = Si7006_port_i2c_init;
	sensor.i2c_transmit = Si7006_port_i2c_transmit;
	sensor.i2c_receive = Si7006_port_i2c_receive;
	sensor.check_hardware = Si7006_port_check_hardware;
	sensor.delay = Si7006_port_delay;



	if(sensor.check_hardware() == SI7006_ERROR){
		graphic_lcd_write(0, 0, "Si7006 NOT READY");
	}else{
		graphic_lcd_write(0, 0, "Si7006 READY");
	}


	int x = HAL_I2C_IsDeviceReady(&hi2c1,Si1133DevAddr, 1000, 1000);
	if(x == HAL_OK) graphic_lcd_write(1, 0, "Si1133 READY");
	else graphic_lcd_write(1, 0, "Si1133 NOT READY");



	sensor.init();
	Si7006_read_firmware_revision(&sensor);

//	NRF24L01p_write_contWave(1);



	/* Infinite loop */
	while (1)
	{


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
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config2(void)
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI | RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_7;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV6;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
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
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
