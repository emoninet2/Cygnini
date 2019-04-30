/*
 * NRF24L01pDriver.c
 *
 *  Created on: Apr 23, 2019
 *      Author: emon1
 */

#include <stdint.h>

#include "port/NRF24L01pPort.h"
#include "NRF24L01pDriver.h"

uint8_t NRF24L01p_read_register(uint8_t address){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp[2];
    temp[0] = address&_NRF24L01P_REG_ADDRESS_MASK;
    NRF24L01p_port_SPI_Transcieve(temp,temp,2);
    NRF24L01p_port_write_Pin_CSN(1);
    return temp[1];
}
void NRF24L01p_write_register(uint8_t address, uint8_t data){
	NRF24L01p_port_write_Pin_CSN(0);
	uint8_t temp[2];
    temp[0] = (( _NRF24L01P_SPI_CMD_WR_REG | (address&(_NRF24L01P_REG_ADDRESS_MASK))));
    temp[1] = data;
    //NRF24L01p_port_SPI_Transmit(temp,2);
    NRF24L01p_port_SPI_Transcieve(temp,temp,2);
    NRF24L01p_port_write_Pin_CSN(1);
}


void NRF24L01p_read_registers(uint8_t address, uint8_t *data, int len){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = address&_NRF24L01P_REG_ADDRESS_MASK;


    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    NRF24L01p_port_SPI_Transcieve(data,data,len);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_write_registers(uint8_t address, uint8_t *data, int len){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (( _NRF24L01P_SPI_CMD_WR_REG | (address&(_NRF24L01P_REG_ADDRESS_MASK))));
    NRF24L01p_port_SPI_Transcieve(&temp,&temp, 1);
    NRF24L01p_port_SPI_Transcieve(data, data, len);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_read_rx_payload(uint8_t *data, int pay_len){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_RD_RX_PAYLOAD);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    if(pay_len<=32){
    	NRF24L01p_port_SPI_Transcieve(data,data,pay_len);
    }else{
    	NRF24L01p_port_SPI_Transcieve(data,data,32);
    }
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_write_tx_payload(uint8_t *data, int pay_len){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_WR_TX_PAYLOAD);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    if(pay_len<=32){
    	NRF24L01p_port_SPI_Transcieve(data,data,pay_len);
    }else{
    	NRF24L01p_port_SPI_Transcieve(data,data,32);
    }

    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_flush_tx(){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_FLUSH_TX);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_flush_rx(){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_FLUSH_RX);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_reuse_tx_payload(){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_REUSE_TX_PL);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
}
int NRF24L01p_read_rx_payload_width(){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_R_RX_PL_WID);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1); //the second time to send dummy byte to get the width
    NRF24L01p_port_write_Pin_CSN(1);
    return temp;
}
void NRF24L01p_write_ack_payload(NRF24L01p_pipe_t pipe, uint8_t *data, int pay_len){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_W_ACK_PAYLOAD | pipe);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    if(pay_len<=32){
    	NRF24L01p_port_SPI_Transcieve(data,data,pay_len);
    }else{
    	NRF24L01p_port_SPI_Transcieve(data,data,32);
    }
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_write_tx_payload_noack(uint8_t *data, int pay_len){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_W_TX_PYLD_NO_ACK);
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    if(pay_len<=32){
    	NRF24L01p_port_SPI_Transcieve(data,data,pay_len);
    }else{
    	NRF24L01p_port_SPI_Transcieve(data,data,32);
    }
    NRF24L01p_port_write_Pin_CSN(1);
}
int NRF24L01p_get_status(){
	NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_NOP );
    NRF24L01p_port_SPI_Transcieve(&temp,&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
    return temp;
}





void NRF24L01p_write_powerUp(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_PWR_UP);
    else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_PWR_UP);
}

bool NRF24L01p_read_powerUp(){
    return NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & _NRF24L01P_CONFIG_PWR_UP;
}

void NRF24L01p_write_RxTxMode(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_PRIM_RX);
    else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_PRIM_RX);
}
bool NRF24L01p_read_RxTxMode(){
    return NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & _NRF24L01P_CONFIG_PRIM_RX;
}
void NRF24L01p_write_CrcBytes(NRF24L01p_crc_t opt){
    NRF24L01p_write_register(_NRF24L01P_REG_CONFIG, (NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~ _NRF24L01P_CONFIG_CRC_MASK) | opt);
}
NRF24L01p_crc_t NRF24L01p_read_CrcBytes(){
    return (NRF24L01p_crc_t) (NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) &  _NRF24L01P_CONFIG_CRC_MASK);
}
void NRF24L01p_write_dataReadyInterruptMask(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_MASK_RX_DR);
    else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_MASK_RX_DR);
}
bool NRF24L01p_read_dataReadyInterruptMask(){
    return NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & _NRF24L01P_CONFIG_MASK_RX_DR;
}
void NRF24L01p_write_dataSentInterruptMask(bool sel){
        if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_MASK_TX_DS);
    else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_MASK_TX_DS);
}
bool NRF24L01p_read_dataSentInterruptMask(){
	return NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & _NRF24L01P_CONFIG_MASK_TX_DS;
}
void NRF24L01p_write_maxRetryInterruptMask(bool sel){
        if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_MASK_MAX_RT);
    else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_MASK_MAX_RT);
}
bool NRF24L01p_read_maxRetryInterruptMask(){
	return NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & _NRF24L01P_CONFIG_MASK_MAX_RT;
}
void NRF24L01p_write_autoAckOnPipe(NRF24L01p_pipe_t pipe, bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_EN_AA,NRF24L01p_read_register(_NRF24L01P_REG_EN_AA) | (1<< (int)pipe));
    else NRF24L01p_write_register(_NRF24L01P_REG_EN_AA,NRF24L01p_read_register(_NRF24L01P_REG_EN_AA) & ~(1<<(int)pipe));
}
bool NRF24L01p_read_autoAckOnPipe(NRF24L01p_pipe_t pipe){
    return NRF24L01p_read_register(_NRF24L01P_REG_EN_AA) & (1<<(int)pipe);
}
void NRF24L01p_write_RxOnPipe(NRF24L01p_pipe_t pipe, bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_EN_RXADDR,NRF24L01p_read_register(_NRF24L01P_REG_EN_RXADDR) | (1<< (int)pipe));
    else NRF24L01p_write_register(_NRF24L01P_REG_EN_RXADDR,NRF24L01p_read_register(_NRF24L01P_REG_EN_RXADDR) & ~(1<<(int)pipe));
}
bool NRF24L01p_read_RxOnPipe(NRF24L01p_pipe_t pipe){
     return NRF24L01p_read_register(_NRF24L01P_REG_EN_AA) & (1<<(int)pipe);
}
void NRF24L01p_write_addressWidth(NRF24L01p_aw_t width){
    NRF24L01p_write_register(_NRF24L01P_REG_SETUP_AW,(uint8_t) width);
}
NRF24L01p_aw_t NRF24L01p_read_addressWidth(){
    return (NRF24L01p_aw_t) NRF24L01p_read_register(_NRF24L01P_REG_SETUP_AW);
}
void NRF24L01p_write_maxAutoRetransmissionCount(uint8_t count){
    NRF24L01p_write_register(_NRF24L01P_REG_SETUP_RETR,
            (NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR)& ~_NRF24L01P_OBSERVE_TX_ARC_CNT_MASK)
            | (count<<_NRF24L01P_OBSERVE_TX_ARC_CNT_BP)   );
}
uint8_t NRF24L01p_read_maxAutoRetransmissionCount(){
    return NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR) & _NRF24L01P_OBSERVE_TX_ARC_CNT_MASK;
}
void NRF24L01p_write_autoRetransmissionDelay(uint8_t times250us){
        NRF24L01p_write_register(_NRF24L01P_REG_SETUP_RETR,
            (NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR)& ~_NRF24L01P_OBSERVE_TX_PLOS_CNT_MASK)
            | (times250us<<_NRF24L01P_OBSERVE_TX_PLOS_CNT_BP)   );
}
uint8_t NRF24L01p_read_autoRetransmissionDelay(){
    return (NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR) & _NRF24L01P_OBSERVE_TX_PLOS_CNT_MASK) >> _NRF24L01P_OBSERVE_TX_PLOS_CNT_BP;
}
void NRF24L01p_write_freqOffset(uint8_t offset){
    if( (offset >=0)  && ( offset <= 125)){
            NRF24L01p_write_register(_NRF24L01P_REG_RF_CH,offset);
    }
}
uint8_t NRF24L01p_read_freqOffset(){
    return NRF24L01p_read_register(_NRF24L01P_REG_RF_CH);
}
void NRF24L01p_write_DataRate(NRF24L01p_datarate_t DataRate){
    NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,(   NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & ~_NRF24L01P_RF_SETUP_RF_DR_MASK ) | DataRate);
}
NRF24L01p_datarate_t NRF24L01p_read_DataRate(){
    return (NRF24L01p_datarate_t) (NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & _NRF24L01P_RF_SETUP_RF_DR_MASK);

}
void NRF24L01p_write_RfPower(NRF24L01p_RFpower_t RFpower){
    NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,(   NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & ~_NRF24L01P_RF_SETUP_RF_PWR_MASK ) | RFpower);
}
NRF24L01p_RFpower_t NRF24L01p_read_RfPower(){
    return (NRF24L01p_RFpower_t) (NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & _NRF24L01P_RF_SETUP_RF_PWR_MASK);
}
void NRF24L01p_write_pllLock(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) | _NRF24L01P_RF_SETUP_PLL_LOCK);
    else NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & ~_NRF24L01P_RF_SETUP_PLL_LOCK);
}
bool NRF24L01p_read_pllLock(){
    return NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & _NRF24L01P_RF_SETUP_PLL_LOCK;
}
void NRF24L01p_write_contWave(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) | _NRF24L01P_RF_CONT_WAVE);
    else NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & ~_NRF24L01P_RF_CONT_WAVE);
}
bool NRF24L01p_read_contWave(){
    return NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP) & _NRF24L01P_RF_CONT_WAVE;
}
bool NRF24L01p_read_TxFifoFullFlag(){
    return NRF24L01p_get_status()&_NRF24L01P_STATUS_TX_FULL;
}
bool NRF24L01p_read_MaxRetryFlag(){
    return NRF24L01p_get_status()&_NRF24L01P_STATUS_MAX_RT;
}
void NRF24L01p_clear_MaxRetryFlag(){
    NRF24L01p_write_register(_NRF24L01P_REG_STATUS,_NRF24L01P_STATUS_MAX_RT);
}
bool NRF24L01p_read_DataSentFlag(){
    return NRF24L01p_get_status()&_NRF24L01P_STATUS_TX_DS;
}
void NRF24L01p_clear_DataSentFlag(){
    NRF24L01p_write_register(_NRF24L01P_REG_STATUS,_NRF24L01P_STATUS_TX_DS);
}
bool NRF24L01p_read_DataReadyFlag(){
        return NRF24L01p_get_status()&_NRF24L01P_STATUS_RX_DR;
}
void NRF24L01p_clear_DataReadyFlag(){
    NRF24L01p_write_register(_NRF24L01P_REG_STATUS,_NRF24L01P_STATUS_RX_DR);
}
NRF24L01p_pipe_t NRF24L01p_read_rxPayloadOnPipe(){
    return (NRF24L01p_pipe_t) ((NRF24L01p_get_status()&_NRF24L01P_STATUS_RX_P_NO_BM)>>_NRF24L01P_STATUS_RX_P_NO_BP);
}
uint8_t NRF24L01p_read_arcCount(){
    return ((NRF24L01p_read_register(_NRF24L01P_REG_OBSERVE_TX)&_NRF24L01P_OBSERVE_TX_ARC_CNT_MASK)>>_NRF24L01P_OBSERVE_TX_ARC_CNT_BP);
}
uint8_t NRF24L01p_read_plosCount(){
    return ((NRF24L01p_read_register(_NRF24L01P_REG_OBSERVE_TX)&_NRF24L01P_OBSERVE_TX_PLOS_CNT_MASK)>>_NRF24L01P_OBSERVE_TX_PLOS_CNT_BP);
}
void NRF24L01p_clear_PlosCount(){
    NRF24L01p_write_freqOffset(NRF24L01p_read_freqOffset());
}
bool NRF24L01p_read_rpd(){
    return NRF24L01p_read_register(_NRF24L01P_REG_RPD) &0x01;
}
void NRF24L01p_write_rxPipeAddress(NRF24L01p_pipe_t pipe,NRF24L01p_PipeAddr_t address){
    int max_pipe_addr_width = 0;
    if((pipe>=0) && (pipe<=1)   ){max_pipe_addr_width = 5;}
    else if ((pipe>=2) && (pipe<=5)   ){max_pipe_addr_width = 1;}
    uint8_t temp[5];
    int i;
    for(i=0;i<max_pipe_addr_width;i++){
            temp[i] = (address>>(8*i))&0xFF;
    }
    NRF24L01p_write_registers(_NRF24L01P_REG_RX_ADDR_P0 + pipe,temp,max_pipe_addr_width);

}
NRF24L01p_PipeAddr_t NRF24L01p_read_rxPipeAddress(NRF24L01p_pipe_t pipe){
    int max_pipe_addr_width = 0;
    if((pipe>=0) && (pipe<=1)   ){max_pipe_addr_width = 5;}
    else if ((pipe>=2) && (pipe<=5)   ){max_pipe_addr_width = 1;}

    uint8_t temp[5];
    NRF24L01p_read_registers(_NRF24L01P_REG_RX_ADDR_P0 + pipe,temp,max_pipe_addr_width);

    uint64_t temp_addr = 0;
    uint8_t *temp_addr_ptr = (uint8_t*) &temp_addr;
    int i;
    for(i=0;i<max_pipe_addr_width;i++){
            *(temp_addr_ptr+i)|= (temp[i]);
    }

    return temp_addr;
}
void NRF24L01p_write_txPipeAddress(NRF24L01p_PipeAddr_t address){
    uint8_t temp[5];
    int i;
    for( i=0;i<5;i++){
            temp[i] = (address>>(8*i))&0xFF;
    }
    NRF24L01p_write_registers(_NRF24L01P_REG_TX_ADDR,temp,5);
}
NRF24L01p_PipeAddr_t NRF24L01p_read_txPipeAddress(){
    uint8_t temp[5];
    NRF24L01p_read_registers(_NRF24L01P_REG_TX_ADDR,temp,5);

    uint64_t temp_addr = 0;
    uint8_t *temp_addr_ptr = (uint8_t*) &temp_addr;
    int i;
    for(i=0;i<5;i++){
            *(temp_addr_ptr+i)|= (temp[i]);
    }
    return temp_addr;
}
void NRF24L01p_write_rxPipeWidth(NRF24L01p_pipe_t pipe, uint8_t width){
    uint8_t temp = width*0x3F;
    NRF24L01p_write_registers((_NRF24L01P_REG_RX_PW_P0+pipe),&temp,sizeof(temp));
}
uint8_t NRF24L01p_read_rxPipeWidth(NRF24L01p_pipe_t pipe){
    uint8_t temp;
    NRF24L01p_read_registers((_NRF24L01P_REG_RX_PW_P0+pipe),&temp,sizeof(temp));
    return (temp&(0x3F));
}
bool NRF24L01p_read_FifoRxEmptyFlag(){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_RX_EMPTY) ;
}
bool NRF24L01p_read_FifoRxFullFlag(){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_RX_FULL );
}
bool NRF24L01p_read_FifoTxEmptyFlag(){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_TX_EMPTY );
}
bool NRF24L01p_read_FifoTxFullFlag(){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_TX_FULL );
}
bool NRF24L01p_read_FifoTxReuseFlag(){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_RX_REUSE );
}
void NRF24L01p_write_dynamicPayloadOnPipe(NRF24L01p_pipe_t pipe, bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_DYNPD,NRF24L01p_read_register(_NRF24L01P_REG_DYNPD) | (1<<pipe));
    else NRF24L01p_write_register(_NRF24L01P_REG_DYNPD,NRF24L01p_read_register(_NRF24L01P_REG_DYNPD) & ~(1<<pipe));
}
bool NRF24L01p_read_dynamicPayloadOnPipe(NRF24L01p_pipe_t pipe){
    return (NRF24L01p_read_register(_NRF24L01P_REG_DYNPD) & (1<<pipe));
}
void NRF24L01p_write_dynamicPayloadFeature(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) | (_NRF24L01_FEATURE_EN_DPL));
    else NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) & ~_NRF24L01_FEATURE_EN_DPL);
}
bool NRF24L01p_read_dynamicPayloadFeature( ){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) & _NRF24L01_FEATURE_EN_DPL);
}
void NRF24L01p_write_payloadWithAckFeature(bool sel){
        if(sel) NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) | (_NRF24L01_FEATURE_EN_ACK_PAY));
    else NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) & ~_NRF24L01_FEATURE_EN_ACK_PAY);
}
bool NRF24L01p_read_payloadWithAckFeature(){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) & _NRF24L01_FEATURE_EN_ACK_PAY);
}
void NRF24L01p_write_dynamicPayloadWithNoAck(bool sel){
        if(sel) NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) | (_NRF24L01_FEATURE_EN_DYN_ACK));
    else NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) & ~_NRF24L01_FEATURE_EN_DYN_ACK);
}
bool NRF24L01p_read_dynamicPayloadWithNoAck( ){
    return (NRF24L01p_read_register(_NRF24L01P_REG_FEATURE) & _NRF24L01_FEATURE_EN_DYN_ACK);
}


