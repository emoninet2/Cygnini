/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   NRF24L01p.h
 * Author: emon1
 *
 * Created on January 29, 2017, 7:10 AM
 */

#ifndef NRF24L01P_H
#define NRF24L01P_H

#include "port/NRF24L01pPort.h"

#include "NRF24L01pDriver.h"
#include "NRF24L01pConfig.h"


    typedef enum {
           NRF24L01P_MODE_UNKNOWN = 0,/**< NRF24L01+ unknown mode */
		   NRF24L01P_MODE_POWER_DOWN,/**< NRF24L01+ Power Down mode */
		   NRF24L01P_MODE_STANDBY,/**< NRF24L01+ Standby mode */
		   NRF24L01P_MODE_RX,/**< NRF24L01+ RX mode */
		   NRF24L01P_MODE_TX,/**< NRF24L01+ TX mode */
    }NRF24L01p_RadioState_t;


    typedef struct {
        bool DataReadyInterruptEnabled;
        bool DataSentInterruptFlagEnabled;
        bool MaxRetryInterruptFlagEnabled;
        NRF24L01p_crc_t Crc;
        uint8_t AutoReTransmissionCount;
        uint8_t AutoReTransmitDelayX250us;
        uint8_t frequencyOffset;
        NRF24L01p_datarate_t datarate;
        NRF24L01p_RFpower_t RfPower;
        bool PllLock;
        bool ContWaveEnabled;
        bool FeatureDynamicPayloadEnabled;
        bool FeaturePayloadWithAckEnabled;
        bool FeatureDynamicPayloadWithNoAckEnabled;
    }NRF24L01p_RadioConfig_t;

    typedef struct {
        bool PipeEnabled;
        bool autoAckEnabled;
        uint64_t address;
        NRF24L01p_aw_t MaxWidth;
        bool dynamicPayloadEnabled;
    }NRF24L01p_RxPipeConfig_t;

    typedef struct{
    	NRF24L01p_PipeAddr_t address;
        NRF24L01p_pipe_t pipe;
        bool UseAck;
        uint8_t *data;
        unsigned int length;
        uint8_t retransmitCount;
    }NRF24L01p_Payload_t;

    typedef enum{
    	NRF24L01P_ERROR = 0,
        NRF24L01P_SUCCESS = !NRF24L01P_ERROR
    }NRF24L01p_ErrorStatus_t;


    NRF24L01p_RadioState_t RadioState;
    NRF24L01p_RadioConfig_t RadioConfig;
    NRF24L01p_RxPipeConfig_t RxPipeConfig[6];
    NRF24L01p_PipeAddr_t  TxPipeAddress;



    void NRF24L01p_ResetConfigValues(NRF24L01p_RadioConfig_t *_RadioConfig, NRF24L01p_RxPipeConfig_t *_RxPipeConfig);
    void NRF24L01p_RadioMode(NRF24L01p_RadioState_t mode);

    bool NRF24L01p_readable();
    bool NRF24L01p_writable();
    bool NRF24L01p_readableOnPipe(NRF24L01p_pipe_t pipe);

    NRF24L01p_ErrorStatus_t NRF24L01p_writePayload(NRF24L01p_Payload_t *payload);
    NRF24L01p_ErrorStatus_t NRF24L01p_writeAckPayload(NRF24L01p_Payload_t *payload);
    NRF24L01p_ErrorStatus_t NRF24L01p_readPayload(NRF24L01p_Payload_t *payload);

    NRF24L01p_ErrorStatus_t NRF24L01p_TransmitPayload(NRF24L01p_Payload_t *payload);
    NRF24L01p_ErrorStatus_t NRF24L01p_ReceivePayload(NRF24L01p_Payload_t *payload);



#endif /* NRF24L01P_H */
