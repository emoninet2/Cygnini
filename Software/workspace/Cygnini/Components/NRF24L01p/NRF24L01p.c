/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   NRF24L01p.cpp
 * Author: emon1
 *
 * Created on January 29, 2017, 7:10 AM
 */

#include "NRF24L01p.h"




void NRF24L01p_ResetConfigValues(NRF24L01p_RadioConfig_t *_RadioConfig, NRF24L01p_RxPipeConfig_t *_RxPipeConfig){
    NRF24L01p_port_Initialize();
    //ResetConfigValues(_RadioConfig, _RxPipeConfig);


    NRF24L01p_port_write_Pin_CE(0);
    NRF24L01p_port_write_Pin_CSN(0);

    NRF24L01p_port_DelayMs(_NRF24L01P_TIMING_PowerOnReset_ms);

    NRF24L01p_RadioMode(NRF24L01P_MODE_POWER_DOWN);
    NRF24L01p_RadioMode(NRF24L01P_MODE_RX);

    NRF24L01p_clear_data_ready_flag();
    NRF24L01p_flush_rx();
    NRF24L01p_flush_tx();

    uint8_t status_rst_val = 0x70;//reset status
    NRF24L01p_write_register_buffer(_NRF24L01P_REG_STATUS, &status_rst_val,1);
    uint8_t config_rst_val = 0x0b;//reset config
    NRF24L01p_write_register_buffer(_NRF24L01P_REG_CONFIG, &config_rst_val,1);


    RadioConfig.DataReadyInterruptEnabled = _RadioConfig->DataReadyInterruptEnabled;
    RadioConfig.DataSentInterruptFlagEnabled = _RadioConfig->DataSentInterruptFlagEnabled;
    RadioConfig.MaxRetryInterruptFlagEnabled = _RadioConfig->MaxRetryInterruptFlagEnabled;
    RadioConfig.Crc = _RadioConfig->Crc;
    RadioConfig.AutoReTransmissionCount = _RadioConfig->AutoReTransmissionCount;
    RadioConfig.AutoReTransmitDelayX250us = _RadioConfig->AutoReTransmitDelayX250us;
    RadioConfig.frequencyOffset = _RadioConfig->frequencyOffset;
    RadioConfig.datarate = _RadioConfig->datarate;
    RadioConfig.RfPower = _RadioConfig->RfPower;
    RadioConfig.PllLock = _RadioConfig->PllLock;
    RadioConfig.ContWaveEnabled = _RadioConfig->ContWaveEnabled;
    RadioConfig.FeatureDynamicPayloadEnabled = _RadioConfig->FeatureDynamicPayloadEnabled;
    RadioConfig.FeaturePayloadWithAckEnabled = _RadioConfig->FeaturePayloadWithAckEnabled;
    RadioConfig.FeatureDynamicPayloadWithNoAckEnabled = _RadioConfig->FeatureDynamicPayloadWithNoAckEnabled;

	int i;
    for(i=0;i<6;i++){
        RxPipeConfig[i] = _RxPipeConfig[i];
    }


    NRF24L01p_enable_dynamic_payload(RadioConfig.FeatureDynamicPayloadEnabled);
    NRF24L01p_enable_payload_with_ack(RadioConfig.FeaturePayloadWithAckEnabled);
    NRF24L01p_enable_dynamic_payload_with_no_ack(RadioConfig.FeatureDynamicPayloadWithNoAckEnabled);
    NRF24L01p_set_auto_retransmission_count(RadioConfig.AutoReTransmissionCount);
    NRF24L01p_set_auto_retransmission_delay(RadioConfig.AutoReTransmitDelayX250us);
    NRF24L01p_set_DataRate(RadioConfig.datarate);

    for(i=0;i<6;i++){
    	NRF24L01p_enable_rx_on_pipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].PipeEnabled );
    	NRF24L01p_enable_auto_ack((NRF24L01p_pipe_t)i,RxPipeConfig[i].autoAckEnabled );
    	NRF24L01p_enable_dynamic_payload_pipe((NRF24L01p_pipe_t)i,RxPipeConfig[i].dynamicPayloadEnabled);
    	NRF24L01p_set_RX_pipe_address((NRF24L01p_pipe_t)i,RxPipeConfig[i].address);
    }
}

void NRF24L01p_RadioMode(NRF24L01p_RadioState_t mode){
    switch(mode){
        case NRF24L01P_MODE_POWER_DOWN: {
        	NRF24L01p_power_down();
            NRF24L01p_port_write_Pin_CE(0);
            RadioState = NRF24L01P_MODE_POWER_DOWN;
            break;
        }
        case NRF24L01P_MODE_STANDBY: {
            if(RadioState == NRF24L01P_MODE_POWER_DOWN){
            	NRF24L01p_power_up();
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
                NRF24L01p_rx_mode();
                NRF24L01p_port_write_Pin_CE(1);
                NRF24L01p_port_DelayUs(_NRF24L01P_TIMING_Tstby2a_us);
                RadioState = NRF24L01P_MODE_RX;
            }
            break;
        }
        case NRF24L01P_MODE_TX: {
            if(RadioState != NRF24L01P_MODE_TX){
                NRF24L01p_port_write_Pin_CE(0);
                NRF24L01p_tx_mode();
                NRF24L01p_port_write_Pin_CE(1);
                NRF24L01p_port_DelayUs(_NRF24L01P_TIMING_Tstby2a_us);
                RadioState = NRF24L01P_MODE_TX;
            }
            break;
        }
    }
}


bool NRF24L01p_readable(){
    //return (NRF24L01p_get_data_ready_flag() || !NRF24L01p_get_fifo_flag_rx_empty())&& (NRF24L01p_get_rx_payload_pipe() != 7)  ;
	return (!NRF24L01p_get_fifo_flag_rx_empty()) ;

}
bool NRF24L01p_writable(){
    return !NRF24L01p_get_fifo_flag_tx_full();

}
bool NRF24L01p_readableOnPipe(NRF24L01p_pipe_t pipe){

}


NRF24L01p_ErrorStatus_t NRF24L01p_writePayload(NRF24L01p_Payload_t *payload){
	NRF24L01p_set_TX_pipe_address(payload->address);
    if(payload->UseAck == 1){
    	NRF24L01p_write_tx_payload(payload->data,payload->length);
    }else{
        if(RadioConfig.FeatureDynamicPayloadWithNoAckEnabled == 1){
        	NRF24L01p_write_tx_payload_noack(payload->data,payload->length);
        }
    }
}

NRF24L01p_ErrorStatus_t NRF24L01p_writeAckPayload(NRF24L01p_Payload_t *payload){
	NRF24L01p_write_ack_payload(payload->pipe, payload->data, payload->length);
}
NRF24L01p_ErrorStatus_t NRF24L01p_readPayload(NRF24L01p_Payload_t *payload){
    NRF24L01p_ErrorStatus_t error;
    payload->pipe = NRF24L01p_get_rx_payload_pipe();

    if(payload->pipe>=0 && payload->pipe<=5){
        if(RadioConfig.FeatureDynamicPayloadEnabled == 1){
            payload->length = NRF24L01p_read_rx_payload_width();
        }else{
            payload->length = NRF24L01p_get_RX_pipe_width(payload->pipe);
        }


        if(payload->length <= 32){
        	NRF24L01p_read_rx_payload(payload->data,payload->length);
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
    NRF24L01p_RadioMode(NRF24L01P_MODE_STANDBY);




    if(TxPipeAddress != payload->address){
    	NRF24L01p_set_TX_pipe_address(payload->address);
	    TxPipeAddress = payload->address;
    }

    if(payload->UseAck){

	    if(RxPipeConfig[PIPE_P0].autoAckEnabled == 0){
	    	NRF24L01p_enable_auto_ack(PIPE_P0, 1);
	    }
	    if(RxPipeConfig[PIPE_P0].PipeEnabled == 0){
	    	NRF24L01p_enable_rx_on_pipe(PIPE_P0, 1);
	    }
	    NRF24L01p_set_RX_pipe_address(PIPE_P0, payload->address);


	    NRF24L01p_writePayload(payload);
	    NRF24L01p_clear_data_sent_flag();


	    if(NRF24L01p_writable()){
	    	NRF24L01p_clear_data_sent_flag();
		    while(1){
			    NRF24L01p_RadioMode(NRF24L01P_MODE_TX);
			    NRF24L01p_RadioMode(NRF24L01P_MODE_STANDBY);

			    if(NRF24L01p_get_data_sent_flag()){
				    error = NRF24L01P_SUCCESS;
				    break;
			    }
			    if(NRF24L01p_get_max_retry_flag()){
			    	NRF24L01p_clear_max_retry_flag();
				    if(NRF24L01p_get_plos_count()>=payload->retransmitCount){
				    	NRF24L01p_set_frequency_offset(RadioConfig.frequencyOffset);
					    error = NRF24L01P_ERROR;
					    break;
				    }
			    }
		    }

	    }

	    NRF24L01p_RadioMode(originalState);

	    NRF24L01p_set_RX_pipe_address(PIPE_P0, RxPipeConfig[PIPE_P0].address);
	    if(RxPipeConfig[PIPE_P0].autoAckEnabled == 0){
	    	NRF24L01p_enable_auto_ack(PIPE_P0, 0);
	    }
	    if(RxPipeConfig[PIPE_P0].PipeEnabled == 0){
	    	NRF24L01p_enable_rx_on_pipe(PIPE_P0, 0);
	    }
	    }else{
	    	NRF24L01p_set_TX_pipe_address(payload->address);
			NRF24L01p_writePayload(payload);
			NRF24L01p_RadioState_t originalState = RadioState;
			if(NRF24L01p_writable()){
				NRF24L01p_clear_data_sent_flag();
				while(1){
					NRF24L01p_RadioMode(NRF24L01P_MODE_TX);
					NRF24L01p_RadioMode(NRF24L01P_MODE_STANDBY);
					if(NRF24L01p_get_data_sent_flag()){
						error = NRF24L01P_SUCCESS;
						break;
					}
				}
			}
			NRF24L01p_RadioMode(originalState);
		}

    NRF24L01p_flush_tx();
    return error;
}
NRF24L01p_ErrorStatus_t NRF24L01p_ReceivePayload(NRF24L01p_Payload_t *payload){
    NRF24L01p_ErrorStatus_t error;
    NRF24L01p_clear_data_ready_flag();
    error = NRF24L01p_readPayload(payload);
    return error;
}
