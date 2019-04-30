/*
 * NRF24L01p.c
 *
 *  Created on: Apr 26, 2019
 *      Author: emon1
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "NRF24L01p.h"
#include "NRF24L01pDriver.h"
#include "port/NRF24L01pPort.h"

void NRF24L01p_Initialize(){


	RadioState = NRF24L01P_MODE_UNKNOWN;


	RadioConfig.DataReadyInterruptEnabled = 1;
	RadioConfig.DataSentInterruptEnabled = 1;
	RadioConfig.MaxRetryInterruptEnabled = 1;
	RadioConfig.Crc = NRF24L01P_CONFIG_CRC_16BIT;
	RadioConfig.AutoReTransmissionCount = 15;
	RadioConfig.AutoReTransmitDelayX250us = 15;
	RadioConfig.frequencyOffset = 2;
	RadioConfig.datarate = NRF24L01P_RF_SETUP_RF_DR_2MBPS;
	RadioConfig.RfPowerDb = NRF24L01P_RF_SETUP_RF_PWR_0DBM;
	RadioConfig.PllLock = 0;
	RadioConfig.ContWaveEnabled = 0;
	RadioConfig.FeatureDynamicPayloadEnabled = 1;
	RadioConfig.FeaturePayloadWithAckEnabled = 1;
	RadioConfig.FeatureDynamicPayloadWithNoAckEnabled = 1;

	RxPipeConfig[0].address = 0xe7e7e7e7e7;
	RxPipeConfig[1].address = 0xc2c2c2c2c2;
	RxPipeConfig[2].address = 0xc2c2c2c2c3;
	RxPipeConfig[3].address = 0xc2c2c2c2c4;
	RxPipeConfig[4].address = 0xc2c2c2c2c5;
	RxPipeConfig[5].address = 0xc2c2c2c2c6;


	NRF24L01p_port_Initialize();

	NRF24L01p_port_write_Pin_CE(0);
	NRF24L01p_port_write_Pin_CSN(0);

	NRF24L01p_port_DelayMs(_NRF24L01P_TIMING_PowerOnReset_ms);

	NRF24L01p_write_RadioMode(NRF24L01P_MODE_POWER_DOWN);
	NRF24L01p_write_RadioMode(NRF24L01P_MODE_RX);



	NRF24L01p_clear_DataReadyFlag();
	NRF24L01p_flush_rx();
	NRF24L01p_flush_tx();

	uint8_t status_rst_val = 0x70;//reset status
	NRF24L01p_write_register(_NRF24L01P_REG_STATUS, status_rst_val);
	uint8_t config_rst_val = 0x0b;//reset config
	NRF24L01p_write_register(_NRF24L01P_REG_CONFIG, config_rst_val);


	NRF24L01p_write_dataReadyInterruptMask(RadioConfig.DataReadyInterruptEnabled);
	NRF24L01p_write_dataSentInterruptMask(RadioConfig.DataSentInterruptEnabled);
	NRF24L01p_write_maxRetryInterruptMask(RadioConfig.MaxRetryInterruptEnabled);
	NRF24L01p_write_dynamicPayloadFeature(RadioConfig.FeatureDynamicPayloadEnabled);
	NRF24L01p_write_payloadWithAckFeature(RadioConfig.FeaturePayloadWithAckEnabled);
	NRF24L01p_write_dynamicPayloadWithNoAck(RadioConfig.FeatureDynamicPayloadWithNoAckEnabled);
	NRF24L01p_write_maxAutoRetransmissionCount(RadioConfig.AutoReTransmissionCount);
	NRF24L01p_write_autoRetransmissionDelay(RadioConfig.AutoReTransmitDelayX250us);
	NRF24L01p_write_DataRate(RadioConfig.datarate);
	NRF24L01p_write_RfPower( RadioConfig.RfPowerDb);

	int i;
	for(i=0;i<6;i++){
		NRF24L01p_write_RxOnPipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].PipeEnabled );
		NRF24L01p_write_autoAckOnPipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].autoAckEnabled );
		NRF24L01p_write_dynamicPayloadOnPipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].dynamicPayloadEnabled);
		NRF24L01p_write_rxPipeAddress((NRF24L01p_pipe_t)i,RxPipeConfig[i].address);
	}


}
void NRF24L01p_ReInitialize(){
	NRF24L01p_port_write_Pin_CE(0);
		NRF24L01p_port_write_Pin_CSN(0);

		NRF24L01p_port_DelayMs(_NRF24L01P_TIMING_PowerOnReset_ms);

		NRF24L01p_write_RadioMode(NRF24L01P_MODE_POWER_DOWN);
		NRF24L01p_write_RadioMode(NRF24L01P_MODE_RX);



		NRF24L01p_clear_DataReadyFlag();
		NRF24L01p_flush_rx();
		NRF24L01p_flush_tx();

		uint8_t status_rst_val = 0x70;//reset status
		NRF24L01p_write_register(_NRF24L01P_REG_STATUS, status_rst_val);
		uint8_t config_rst_val = 0x0b;//reset config
		NRF24L01p_write_register(_NRF24L01P_REG_CONFIG, config_rst_val);


		NRF24L01p_write_dataReadyInterruptMask(RadioConfig.DataReadyInterruptEnabled);
		NRF24L01p_write_dataSentInterruptMask(RadioConfig.DataSentInterruptEnabled);
		NRF24L01p_write_maxRetryInterruptMask(RadioConfig.MaxRetryInterruptEnabled);
		NRF24L01p_write_dynamicPayloadFeature(RadioConfig.FeatureDynamicPayloadEnabled);
		NRF24L01p_write_payloadWithAckFeature(RadioConfig.FeaturePayloadWithAckEnabled);
		NRF24L01p_write_dynamicPayloadWithNoAck(RadioConfig.FeatureDynamicPayloadWithNoAckEnabled);
		NRF24L01p_write_maxAutoRetransmissionCount(RadioConfig.AutoReTransmissionCount);
		NRF24L01p_write_autoRetransmissionDelay(RadioConfig.AutoReTransmitDelayX250us);
		NRF24L01p_write_DataRate(RadioConfig.datarate);

		int i;
		for(i=0;i<6;i++){
			NRF24L01p_write_RxOnPipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].PipeEnabled );
			NRF24L01p_write_autoAckOnPipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].autoAckEnabled );
			NRF24L01p_write_dynamicPayloadOnPipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].dynamicPayloadEnabled);
			NRF24L01p_write_rxPipeAddress((NRF24L01p_pipe_t)i,RxPipeConfig[i].address);
		}
}

NRF24L01p_RadioState_t NRF24L01p_read_RadioMode(){
	bool _ce = NRF24L01p_port_read_Pin_CE();
	uint8_t _config = NRF24L01p_read_register(_NRF24L01P_REG_CONFIG)  ;
	bool _pwr = (_config>>1)&0x01;
	bool _txrx = (_config>>0)&0x01;


	if(_pwr == 0){
		return NRF24L01P_MODE_POWER_DOWN;
	}
	else{
		if(_ce == 0){
			return NRF24L01P_MODE_STANDBY;
		}
		else{
			if(_txrx==0){
				return NRF24L01P_MODE_TX;
			}else{
				return NRF24L01P_MODE_RX;
			}
		}
	}
}

void NRF24L01p_write_RadioMode(NRF24L01p_RadioState_t mode){
	RadioState = NRF24L01p_read_RadioMode();

	switch(mode){
		case NRF24L01P_MODE_POWER_DOWN: {
			NRF24L01p_write_powerUp(0);
			NRF24L01p_port_write_Pin_CE(0);
			RadioState = NRF24L01P_MODE_POWER_DOWN;
			break;
		}
		case NRF24L01P_MODE_STANDBY: {
			if(RadioState == NRF24L01P_MODE_POWER_DOWN){
				NRF24L01p_write_powerUp(1);
				NRF24L01p_port_DelayUs(_NRF24L01P_TIMING_Tpd2stby_us);
			}
			else{
				NRF24L01p_port_write_Pin_CE(0);
			}
			RadioState = NRF24L01P_MODE_STANDBY;
			break;
		}
		case NRF24L01P_MODE_RX: {
			if(RadioState != NRF24L01P_MODE_RX){
				NRF24L01p_port_write_Pin_CE(0);
				NRF24L01p_write_RxTxMode(1);
				NRF24L01p_port_write_Pin_CE(1);
				NRF24L01p_port_DelayUs(_NRF24L01P_TIMING_Tstby2a_us);
				RadioState = NRF24L01P_MODE_RX;
			}
			break;
		}
		case NRF24L01P_MODE_TX: {
			if(RadioState != NRF24L01P_MODE_TX){
				NRF24L01p_port_write_Pin_CE(0);
				NRF24L01p_write_RxTxMode(0);
				NRF24L01p_port_write_Pin_CE(1);
				NRF24L01p_port_DelayUs(_NRF24L01P_TIMING_Tstby2a_us);
				RadioState = NRF24L01P_MODE_TX;
			}
			break;
		}
		case NRF24L01P_MODE_UNKNOWN: {
			//RadioState = NRF24L01P_MODE_UNKNOWN;
			break;
		}
	}
}

bool NRF24L01p_readable(){
	return (!NRF24L01p_read_FifoRxEmptyFlag()) ;
}

bool NRF24L01p_writable(){
	return !NRF24L01p_read_FifoTxEmptyFlag();
}

bool NRF24L01p_readableOnPipe(NRF24L01p_pipe_t pipe){

}

NRF24L01p_ErrorStatus_t NRF24L01p_writePayload(NRF24L01p_Payload_t *payload){
	NRF24L01p_ErrorStatus_t error;
	NRF24L01p_write_txPipeAddress(payload->TxAddress);
    if(payload->UseAck == 1){
    	NRF24L01p_write_tx_payload(payload->Data,payload->length);
        error = NRF24L01P_SUCCESS;
    }else{

        if(RadioConfig.FeatureDynamicPayloadWithNoAckEnabled == 1){
        	NRF24L01p_write_tx_payload_noack(payload->Data,payload->length);
            error = NRF24L01P_SUCCESS;
        }
        else{
            error = NRF24L01P_ERROR; //feature dynamic payload with no ack is not enabled
        }
    }
    return error;
}

NRF24L01p_ErrorStatus_t NRF24L01p_writeAckPayload(NRF24L01p_Payload_t *payload){
	NRF24L01p_write_ack_payload(payload->pipe, payload->Data, payload->length);
	return NRF24L01P_SUCCESS;
}

NRF24L01p_ErrorStatus_t NRF24L01p_readPayload(NRF24L01p_Payload_t *payload){
    NRF24L01p_ErrorStatus_t error = NRF24L01P_ERROR;
    payload->RxPipe = NRF24L01p_read_rxPayloadOnPipe();

    if(payload->RxPipe>=0 && payload->RxPipe<=5){
        if(RadioConfig.FeatureDynamicPayloadEnabled == 1){
            payload->length = NRF24L01p_read_rx_payload_width();
        }else{
            payload->length = NRF24L01p_read_rxPipeWidth(payload->RxPipe);
        }

        if(payload->length <= 32){
        	NRF24L01p_read_rx_payload(payload->Data,payload->length);
            error = NRF24L01P_SUCCESS;
        }
        else{
            error = NRF24L01P_ERROR;
        }
    }
    return error;
}


NRF24L01p_ErrorStatus_t NRF24L01p_TransmitPayload(NRF24L01p_Payload_t *payload){

	NRF24L01p_ErrorStatus_t error;
	NRF24L01p_RadioState_t originalState = RadioState;
	NRF24L01p_write_RadioMode(NRF24L01P_MODE_STANDBY);

	if(TxPipeAddress != payload->TxAddress){
		NRF24L01p_write_txPipeAddress(payload->TxAddress);
		TxPipeAddress = payload->TxAddress;
	}

	if(payload->UseAck){
		if(RxPipeConfig[NRF24L01P_PIPE_P0].autoAckEnabled == 0){
			NRF24L01p_write_autoAckOnPipe(NRF24L01P_PIPE_P0, 1);
		}
		if(RxPipeConfig[NRF24L01P_PIPE_P0].PipeEnabled == 0){
			NRF24L01p_write_RxOnPipe(NRF24L01P_PIPE_P0, 1);
		}
		NRF24L01p_write_rxPipeAddress(NRF24L01P_PIPE_P0, payload->TxAddress);

		NRF24L01p_writePayload(payload);
		NRF24L01p_clear_DataSentFlag();

		payload->GotAck = 0;

		while(1){


			NRF24L01p_write_RadioMode(NRF24L01P_MODE_TX);
			NRF24L01p_write_RadioMode(NRF24L01P_MODE_STANDBY);

			uint8_t status = NRF24L01p_get_status();

			if( (status & (_NRF24L01P_STATUS_TX_DS))  &&   (status & (_NRF24L01P_STATUS_RX_DR))   ){
				printf("ACK with PAYLOAD\r\n");
				NRF24L01p_clear_DataSentFlag();
				NRF24L01p_clear_DataReadyFlag();
					error = NRF24L01P_SUCCESS;
					NRF24L01p_readPayload(payload);
					payload->GotAck = 1;

					break;
			}

			else if( (status & (_NRF24L01P_STATUS_TX_DS))  &&   !(status & (_NRF24L01P_STATUS_RX_DR))   ){
				printf("ACK ONLY\r\n");
				NRF24L01p_clear_DataSentFlag();
									error = NRF24L01P_SUCCESS;
				payload->GotAck = 1;
									payload->length = 0;
				break;
			}

			else if((status & (_NRF24L01P_STATUS_MAX_RT))){
				printf("FAILED AFTER MAX RETRY\r\n");
				NRF24L01p_clear_MaxRetryFlag();
				error = NRF24L01P_ERROR;
									break;
			}
		}
		NRF24L01p_write_rxPipeAddress(NRF24L01P_PIPE_P0, RxPipeConfig[NRF24L01P_PIPE_P0].address);
		NRF24L01p_write_autoAckOnPipe(NRF24L01P_PIPE_P0, RxPipeConfig[NRF24L01P_PIPE_P0].autoAckEnabled);
		NRF24L01p_write_RxOnPipe(NRF24L01P_PIPE_P0, RxPipeConfig[NRF24L01P_PIPE_P0].PipeEnabled);
	}
	else{
		error = NRF24L01p_writePayload(payload);
		if(error == NRF24L01P_ERROR) return error;
		NRF24L01p_clear_DataSentFlag();
		NRF24L01p_clear_MaxRetryFlag();
		while(1){
			NRF24L01p_write_RadioMode(NRF24L01P_MODE_TX);
			NRF24L01p_write_RadioMode(NRF24L01P_MODE_STANDBY);

			if(NRF24L01p_read_DataSentFlag()){
				NRF24L01p_clear_DataSentFlag();
							error = NRF24L01P_SUCCESS;
							break;
			}
		}
	}
	NRF24L01p_write_RadioMode(originalState);
	return error;
}

NRF24L01p_ErrorStatus_t NRF24L01p_ReceivePayload(NRF24L01p_Payload_t *payload){
	NRF24L01p_ErrorStatus_t error;
	error = NRF24L01p_readPayload(payload);
	if(error == NRF24L01P_ERROR){
		NRF24L01p_flush_rx();
	}

    return error;
}


