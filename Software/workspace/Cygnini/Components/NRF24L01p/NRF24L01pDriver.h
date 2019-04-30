/*
 * NRF24L01pDriver.h
 *
 *  Created on: Apr 23, 2019
 *      Author: emon1
 */

#ifndef NRF24L01P_PORT_NRF24L01PDRIVER_H_
#define NRF24L01P_PORT_NRF24L01PDRIVER_H_


#include "NRF24L01pRegisters.h"


typedef enum {
	NRF24L01P_CONFIG_CRC_NONE      =  (0),
	NRF24L01P_CONFIG_CRC_8BIT      =  (_NRF24L01P_CONFIG_EN_CRC),
	NRF24L01P_CONFIG_CRC_16BIT     =  (_NRF24L01P_CONFIG_EN_CRC|_NRF24L01P_CONFIG_CRC0),
}NRF24L01p_crc_t;

typedef enum {
	NRF24L01P_SETUP_AW_AW_3BYTE   =  (0x1<<0),/**< 3 bytes address width */
	NRF24L01P_SETUP_AW_AW_4BYTE   =  (0x2<<0),/**< 4 bytes address width */
	NRF24L01P_SETUP_AW_AW_5BYTE   =  (0x3<<0),/**< 5 bytes address width */
}NRF24L01p_aw_t;

typedef enum {
	NRF24L01P_RF_SETUP_RF_PWR_0DBM        =  (0x3<<1),
	NRF24L01P_RF_SETUP_RF_PWR_MINUS_6DBM  =  (0x2<<1),
	NRF24L01P_RF_SETUP_RF_PWR_MINUS_12DBM =  (0x1<<1),
	NRF24L01P_RF_SETUP_RF_PWR_MINUS_18DBM =  (0x0<<1),
}NRF24L01p_RFpower_t;

typedef enum {
	NRF24L01P_RF_SETUP_RF_DR_250KBPS    =    (_NRF24L01P_RF_SETUP_RF_DR_LOW_BIT),//(1 << 5)
	NRF24L01P_RF_SETUP_RF_DR_1MBPS      =    (0),
	NRF24L01P_RF_SETUP_RF_DR_2MBPS      =    (_NRF24L01P_RF_SETUP_RF_DR_HIGH_BIT),//(1 << 3)
}NRF24L01p_datarate_t;

typedef enum {
	NRF24L01P_PIPE_P0       =    0,/**< Pipe 0 */
	NRF24L01P_PIPE_P1       =    1,/**< Pipe 1 */
	NRF24L01P_PIPE_P2       =    2,/**< Pipe 2 */
	NRF24L01P_PIPE_P3       =    3,/**< Pipe 3 */
	NRF24L01P_PIPE_P4       =    4,/**< Pipe 4 */
	NRF24L01P_PIPE_P5       =    5,/**< Pipe 5 */
}NRF24L01p_pipe_t;

typedef uint64_t NRF24L01p_PipeAddr_t;


uint8_t NRF24L01p_read_register(uint8_t address);
void NRF24L01p_write_register(uint8_t address, uint8_t data);
void NRF24L01p_read_registers(uint8_t address, uint8_t *data, int len);
void NRF24L01p_write_registers(uint8_t address, uint8_t *data, int len);
void NRF24L01p_read_rx_payload(uint8_t *data, int pay_len);
void NRF24L01p_write_tx_payload(uint8_t *data, int pay_len);
void NRF24L01p_flush_tx();
void NRF24L01p_flush_rx();
void NRF24L01p_reuse_tx_payload();
int NRF24L01p_read_rx_payload_width();
void NRF24L01p_write_ack_payload(NRF24L01p_pipe_t pipe, uint8_t *data, int pay_len);
void NRF24L01p_write_tx_payload_noack(uint8_t *data, int pay_len);
int NRF24L01p_get_status();




void NRF24L01p_write_powerUp(bool sel);
bool NRF24L01p_read_powerUp();
void NRF24L01p_write_RxTxMode(bool sel);
bool NRF24L01p_read_RxTxMode();
void NRF24L01p_write_CrcBytes(NRF24L01p_crc_t opt);
NRF24L01p_crc_t NRF24L01p_read_CrcBytes();
void NRF24L01p_write_dataReadyInterruptMask(bool sel);
bool NRF24L01p_read_dataReadyInterruptMask();
void NRF24L01p_write_dataSentInterruptMask(bool sel);
bool NRF24L01p_read_dataSentInterruptMask();
void NRF24L01p_write_maxRetryInterruptMask(bool sel);
bool NRF24L01p_read_maxRetryInterruptMask();
void NRF24L01p_write_autoAckOnPipe(NRF24L01p_pipe_t pipe, bool sel);
bool NRF24L01p_read_autoAckOnPipe(NRF24L01p_pipe_t pipe);
void NRF24L01p_write_RxOnPipe(NRF24L01p_pipe_t pipe, bool sel);
bool NRF24L01p_read_RxOnPipe(NRF24L01p_pipe_t pipe);
void NRF24L01p_write_addressWidth(NRF24L01p_aw_t width);
NRF24L01p_aw_t NRF24L01p_read_addressWidth();
void NRF24L01p_write_maxAutoRetransmissionCount(uint8_t count);
uint8_t NRF24L01p_read_maxAutoRetransmissionCount();
void NRF24L01p_write_autoRetransmissionDelay(uint8_t times250us);
uint8_t NRF24L01p_read_autoRetransmissionDelay();
void NRF24L01p_write_freqOffset(uint8_t offset);
uint8_t NRF24L01p_read_freqOffset();
void NRF24L01p_write_DataRate(NRF24L01p_datarate_t DataRate);
NRF24L01p_datarate_t NRF24L01p_read_DataRate();
void NRF24L01p_write_RfPower(NRF24L01p_RFpower_t RFpower);
NRF24L01p_RFpower_t NRF24L01p_read_RfPower();
void NRF24L01p_write_pllLock(bool sel);
bool NRF24L01p_read_pllLock();
void NRF24L01p_write_contWave(bool sel);
bool NRF24L01p_read_contWave();
bool NRF24L01p_read_TxFifoFullFlag();
bool NRF24L01p_read_MaxRetryFlag();
void NRF24L01p_clear_MaxRetryFlag();
bool NRF24L01p_read_DataSentFlag();
void NRF24L01p_clear_DataSentFlag();
bool NRF24L01p_read_DataReadyFlag();
void NRF24L01p_clear_DataReadyFlag();
NRF24L01p_pipe_t NRF24L01p_read_rxPayloadOnPipe();
uint8_t NRF24L01p_read_arcCount();
uint8_t NRF24L01p_read_plosCount();
void NRF24L01p_clear_PlosCount();
bool NRF24L01p_read_rpd();

void NRF24L01p_write_rxPipeAddress(NRF24L01p_pipe_t pipe,NRF24L01p_PipeAddr_t address);
NRF24L01p_PipeAddr_t NRF24L01p_read_rxPipeAddress(NRF24L01p_pipe_t pipe);
void NRF24L01p_write_txPipeAddress(NRF24L01p_PipeAddr_t address);
NRF24L01p_PipeAddr_t NRF24L01p_read_txPipeAddress();
void NRF24L01p_write_rxPipeWidth(NRF24L01p_pipe_t pipe, uint8_t width);
uint8_t NRF24L01p_read_rxPipeWidth(NRF24L01p_pipe_t pipe);
bool NRF24L01p_read_FifoRxEmptyFlag();
bool NRF24L01p_read_FifoRxFullFlag();
bool NRF24L01p_read_FifoTxEmptyFlag();
bool NRF24L01p_read_FifoTxFullFlag();
bool NRF24L01p_read_FifoTxReuseFlag();
void NRF24L01p_write_dynamicPayloadOnPipe(NRF24L01p_pipe_t pipe, bool sel);
bool NRF24L01p_read_dynamicPayloadOnPipe(NRF24L01p_pipe_t pipe);
void NRF24L01p_write_dynamicPayloadFeature(bool sel);
bool NRF24L01p_read_dynamicPayloadFeature( );
void NRF24L01p_write_payloadWithAckFeature(bool sel);
bool NRF24L01p_read_payloadWithAckFeature();
void NRF24L01p_write_dynamicPayloadWithNoAck(bool sel);
bool NRF24L01p_read_dynamicPayloadWithNoAck( );



#endif /* NRF24L01P_PORT_NRF24L01PDRIVER_H_ */
