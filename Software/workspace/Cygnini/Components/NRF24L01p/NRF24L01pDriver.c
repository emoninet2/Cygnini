/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   NRF24L01pDriver.cpp
 * Author: emon1
 *
 * Created on January 29, 2017, 7:56 AM
 */

#include "NRF24L01pDriver.h"



uint8_t NRF24L01p_read_register(uint8_t address){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = address&_NRF24L01P_REG_ADDRESS_MASK;


    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);

    //port_SPI_Transcieve(&temp, 1);
    //port_SPI_Transcieve(&temp, 1);
    NRF24L01p_port_write_Pin_CSN(1);
    return temp;

}
void NRF24L01p_read_register_buffer(uint8_t address, uint8_t *dataout, int len){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = address&_NRF24L01P_REG_ADDRESS_MASK;
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(dataout, dataout,len);
    //port_SPI_Transcieve(&temp, 1);
    //port_SPI_Transcieve(dataout, len);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_write_register(uint8_t address, uint8_t datain){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (( _NRF24L01P_SPI_CMD_WR_REG | (address&(_NRF24L01P_REG_ADDRESS_MASK))));
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(&datain, &datain,1);
    //port_SPI_Transcieve(&temp, 1);
    //port_SPI_Transcieve(&datain, 1);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_write_register_buffer(uint8_t address, uint8_t *datain, int len){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (( _NRF24L01P_SPI_CMD_WR_REG | (address&(_NRF24L01P_REG_ADDRESS_MASK))));
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(datain, datain,len);
    //port_SPI_Transcieve(&temp, 1);
    //port_SPI_Transcieve(datain, len);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_read_rx_payload(uint8_t *dataout, int pay_len){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_RD_RX_PAYLOAD);

    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(dataout,dataout,pay_len);

    //port_SPI_Transcieve(&temp,1);
    //port_SPI_Transcieve(dataout,pay_len);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_write_tx_payload(uint8_t *datain, int pay_len){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_WR_TX_PAYLOAD);

    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(datain,datain,pay_len);

    //port_SPI_Transcieve(&temp,1);
    //port_SPI_Transcieve(datain,pay_len);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_flush_tx(){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_FLUSH_TX);
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    //port_SPI_Transcieve(&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_flush_rx(){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_FLUSH_RX);
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    //port_SPI_Transcieve(&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_reuse_tx_payload(){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_REUSE_TX_PL);
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    //port_SPI_Transcieve(&temp,1);

    NRF24L01p_port_write_Pin_CSN(1);
}
int NRF24L01p_read_rx_payload_width(){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_R_RX_PL_WID);

    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);

    //port_SPI_Transcieve(&temp,1);
    //port_SPI_Transcieve(&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
    return temp;
}
void NRF24L01p_write_ack_payload(NRF24L01p_pipe_t pipe, uint8_t *datain, int pay_len){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_W_ACK_PAYLOAD | pipe);

    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(datain, datain, pay_len);
    //port_SPI_Transcieve(&temp,1);
    //port_SPI_Transcieve(datain,pay_len);
    NRF24L01p_port_write_Pin_CSN(1);
}
void NRF24L01p_write_tx_payload_noack(uint8_t *datain, int pay_len){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_W_TX_PYLD_NO_ACK);

    NRF24L01p_port_SPI_Transcieve(&temp, &temp,1);
    NRF24L01p_port_SPI_Transcieve(datain, datain, pay_len);

    //port_SPI_Transcieve(&temp,1);
    //port_SPI_Transcieve(datain,pay_len);
    NRF24L01p_port_write_Pin_CSN(1);
}
int NRF24L01p_get_status(){
    NRF24L01p_port_write_Pin_CSN(0);
    uint8_t temp = (_NRF24L01P_SPI_CMD_NOP );
    NRF24L01p_port_SPI_Transcieve(&temp, &temp, 1);
    //port_SPI_Transcieve(&temp,1);
    NRF24L01p_port_write_Pin_CSN(1);
    return temp;
}


void NRF24L01p_power_up(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_CONFIG);
    temp |= _NRF24L01P_CONFIG_PWR_UP;
    NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,temp);
}
void NRF24L01p_power_down(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_CONFIG);
    temp &= ~_NRF24L01P_CONFIG_PWR_UP;
    NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,temp);
}
void NRF24L01p_rx_mode(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_CONFIG);
    temp |= _NRF24L01P_CONFIG_PRIM_RX;
    NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,temp);
}
void NRF24L01p_tx_mode(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_CONFIG);
    temp &= ~_NRF24L01P_CONFIG_PRIM_RX;
    NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,temp);
}
void NRF24L01p_set_CRC(NRF24L01p_crc_t opt){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_CONFIG);
    temp &= ~(_NRF24L01P_CONFIG_CRC_MASK);
    temp |= opt;
    NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,temp);
}


void NRF24L01p_enable_dataReady_interrupt(bool sel){
	  if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_MASK_RX_DR);
	    else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_MASK_RX_DR);
}

void NRF24L01p_enable_dataSent_interrupt(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_MASK_TX_DS);
else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_MASK_TX_DS);
}

void NRF24L01p_enable_maxRetry_interrupt(bool sel){
    if(sel) NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) | _NRF24L01P_CONFIG_MASK_MAX_RT);
else NRF24L01p_write_register(_NRF24L01P_REG_CONFIG,NRF24L01p_read_register(_NRF24L01P_REG_CONFIG) & ~_NRF24L01P_CONFIG_MASK_MAX_RT);
}


void NRF24L01p_enable_auto_ack(NRF24L01p_pipe_t pipe, bool sel){
    if (sel){
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_EN_AA);
        _nrf24l01p_set_bit(temp,pipe);
        NRF24L01p_write_register(_NRF24L01P_REG_EN_AA,temp);
    }else{
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_EN_AA);
        _nrf24l01p_clr_bit(temp,pipe);
        NRF24L01p_write_register(_NRF24L01P_REG_EN_AA,temp);
    }

}



void NRF24L01p_enable_rx_on_pipe(NRF24L01p_pipe_t pipe, bool sel){
    if(sel){
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_EN_RXADDR);
        _nrf24l01p_set_bit(temp,pipe);
        NRF24L01p_write_register(_NRF24L01P_REG_EN_RXADDR,temp);
    }else{
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_EN_RXADDR);
        _nrf24l01p_clr_bit(temp,pipe);
        NRF24L01p_write_register(_NRF24L01P_REG_EN_RXADDR,temp);
    }

}

void NRF24L01p_set_address_width(NRF24L01p_aw_t width){
    NRF24L01p_write_register(_NRF24L01P_REG_SETUP_AW,(uint8_t) width);
}
NRF24L01p_aw_t NRF24L01p_get_address_width(){
    return (NRF24L01p_aw_t) NRF24L01p_read_register(_NRF24L01P_REG_SETUP_AW);
}

void NRF24L01p_set_auto_retransmission_count(uint8_t count){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR);
    temp &= ~ 0x0F;
    temp |= (count<<0);
    NRF24L01p_write_register(_NRF24L01P_REG_SETUP_RETR,temp);
}
uint8_t NRF24L01p_read_auto_retransmission_count(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR);
    return temp & 0x0F;
}

void NRF24L01p_set_auto_retransmission_delay(uint8_t times250us){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR);
    temp &= ~(0xF0);
    temp |= (times250us<<4);
    NRF24L01p_write_register(_NRF24L01P_REG_SETUP_RETR,temp);
}
uint8_t NRF24L01p_read_auto_retransmission_delay(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_SETUP_RETR);
    return temp & 0xF0;
}

void NRF24L01p_set_frequency_offset(uint8_t offset){
    if( (offset >=0)  && ( offset <= 125)){
            NRF24L01p_write_register(_NRF24L01P_REG_RF_CH,offset);
    }
}
uint8_t NRF24L01p_get_frequency_offset(){
    return NRF24L01p_read_register(_NRF24L01P_REG_RF_CH);
}

void NRF24L01p_set_DataRate(NRF24L01p_datarate_t DataRate){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP);
    temp &= ~_NRF24L01P_RF_SETUP_RF_DR_MASK;
    temp |= DataRate;
    NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,temp);
}
NRF24L01p_datarate_t NRF24L01p_get_DataRate(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP);
    temp &= _NRF24L01P_RF_SETUP_RF_DR_MASK;
    return (NRF24L01p_datarate_t) temp;
}
void NRF24L01p_set_RF_Power(NRF24L01p_RFpower_t RFpower){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP);
    temp &= ~_NRF24L01P_RF_SETUP_RF_PWR_MASK;
    temp |= RFpower;
    NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,temp);
}
NRF24L01p_RFpower_t NRF24L01p_get_RF_Power(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP);
    temp &= _NRF24L01P_RF_SETUP_RF_PWR_MASK;
    return (NRF24L01p_RFpower_t) temp;
}
void NRF24L01p_enable_pll_lock(bool sel){

}

void NRF24L01p_enable_cont_wave(bool sel){
    if(sel){
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP);
        temp |= _NRF24L01P_RF_CONT_WAVE;
        NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,temp);
    }
    else{
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_RF_SETUP);
        temp &= ~_NRF24L01P_RF_CONT_WAVE;
        NRF24L01p_write_register(_NRF24L01P_REG_RF_SETUP,temp);
    }

}


bool NRF24L01p_get_tx_fifo_full_flag(){
    if(NRF24L01p_get_status()&_NRF24L01P_STATUS_TX_FULL) return 1;
    else return 0;
}
bool NRF24L01p_get_max_retry_flag(){
    if(NRF24L01p_get_status()&_NRF24L01P_STATUS_MAX_RT) return 1;
    else return 0;
}
void NRF24L01p_clear_max_retry_flag(){
    uint8_t temp = _NRF24L01P_STATUS_MAX_RT;
    NRF24L01p_write_register_buffer(_NRF24L01P_REG_STATUS,&temp,sizeof(temp));
}
bool NRF24L01p_get_data_sent_flag(){
    if(NRF24L01p_get_status()&_NRF24L01P_STATUS_TX_DS) return 1;
    else return 0;
}
void NRF24L01p_clear_data_sent_flag(){
    uint8_t temp = _NRF24L01P_STATUS_TX_DS;
    NRF24L01p_write_register_buffer(_NRF24L01P_REG_STATUS,&temp,sizeof(temp));
}
bool NRF24L01p_get_data_ready_flag(){
    if(NRF24L01p_get_status()&_NRF24L01P_STATUS_RX_DR) return 1;
    else return 0;
}
void NRF24L01p_clear_data_ready_flag(){
    uint8_t temp = _NRF24L01P_STATUS_RX_DR;
    NRF24L01p_write_register_buffer(_NRF24L01P_REG_STATUS,&temp,sizeof(temp));
}
NRF24L01p_pipe_t NRF24L01p_get_rx_payload_pipe(){
    return (NRF24L01p_pipe_t) ((NRF24L01p_get_status()&_NRF24L01P_STATUS_RX_P_NO)>>1);
}

uint8_t NRF24L01p_get_arc_count(){
    uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_OBSERVE_TX);
    return ((temp&_NRF24L01P_OBSERVE_TX_ARC_CNT_MASK)>>_NRF24L01P_OBSERVE_TX_ARC_CNT_BP);
    //return (temp&0x0F)>>0;

}
uint8_t NRF24L01p_get_plos_count(){
    uint8_t temp;
    NRF24L01p_read_register_buffer(_NRF24L01P_REG_OBSERVE_TX,&temp,sizeof(temp));
    return ((temp&_NRF24L01P_OBSERVE_TX_PLOS_CNT_MASK)>>_NRF24L01P_OBSERVE_TX_PLOS_CNT_BP);
    //return (temp&0xF0)>>4;
}
void NRF24L01p_clear_plos_count(){
	NRF24L01p_set_frequency_offset(NRF24L01p_get_frequency_offset());
}

bool NRF24L01p_get_rpd(){
    if(NRF24L01p_read_register(_NRF24L01P_REG_RPD)) return 1;
    else return 0;
}

void NRF24L01p_set_RX_pipe_address(NRF24L01p_pipe_t pipe,NRF24L01p_PipeAddr_t address){
    int max_pipe_addr_width = 0;
    if((pipe>=0) && (pipe<=1)   ){max_pipe_addr_width = 5;}
    else if ((pipe>=2) && (pipe<=5)   ){max_pipe_addr_width = 1;}
    uint8_t temp[5];
    int i;
    for(i=0;i<max_pipe_addr_width;i++){
            temp[i] = (address>>(8*i))&0xFF;
    }
    NRF24L01p_write_register_buffer(_NRF24L01P_REG_RX_ADDR_P0 + pipe,temp,max_pipe_addr_width);
}
NRF24L01p_PipeAddr_t NRF24L01p_get_RX_pipe_address(NRF24L01p_pipe_t pipe){
    int max_pipe_addr_width = 0;
    if((pipe>=0) && (pipe<=1)   ){max_pipe_addr_width = 5;}
    else if ((pipe>=2) && (pipe<=5)   ){max_pipe_addr_width = 1;}

    uint8_t temp[5];
    NRF24L01p_read_register_buffer(_NRF24L01P_REG_RX_ADDR_P0 + pipe,temp,max_pipe_addr_width);

    uint64_t temp_addr = 0;
    uint8_t *temp_addr_ptr = (uint8_t*) &temp_addr;
    int i;
    for(i=0;i<max_pipe_addr_width;i++){
            *(temp_addr_ptr+i)|= (temp[i]);
    }

    return temp_addr;
}

void NRF24L01p_set_TX_pipe_address(NRF24L01p_PipeAddr_t address){
    uint8_t temp[5];
    int i;
    for( i=0;i<5;i++){
            temp[i] = (address>>(8*i))&0xFF;
    }
    NRF24L01p_write_register_buffer(_NRF24L01P_REG_TX_ADDR,temp,5);
}
NRF24L01p_PipeAddr_t NRF24L01p_get_TX_pipe_address(){
    uint8_t temp[5];
    NRF24L01p_read_register_buffer(_NRF24L01P_REG_TX_ADDR,temp,5);

    uint64_t temp_addr = 0;
    uint8_t *temp_addr_ptr = (uint8_t*) &temp_addr;
    int i;
    for(i=0;i<5;i++){
            *(temp_addr_ptr+i)|= (temp[i]);
    }
    return temp_addr;
}

uint8_t NRF24L01p_get_RX_pipe_width(NRF24L01p_pipe_t pipe){
    uint8_t temp;
    NRF24L01p_read_register_buffer((_NRF24L01P_REG_RX_PW_P0+pipe),&temp,sizeof(temp));
    return (temp&(0x3F));
}

bool NRF24L01p_get_fifo_flag_rx_empty(){
    if(NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_RX_EMPTY ) return 1;
    else return 0;
}
bool NRF24L01p_get_fifo_flag_rx_full(){
    if(NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_RX_FULL ) return 1;
    else return 0;
}
bool NRF24L01p_get_fifo_flag_tx_empty(){
    if(NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_TX_EMPTY ) return 1;
    else return 0;
}
bool NRF24L01p_get_fifo_flag_tx_full(){
    if(NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_TX_FULL ) return 1;
    else return 0;
}
bool NRF24L01p_get_fifo_flag_tx_reuse(){
    if(NRF24L01p_read_register(_NRF24L01P_REG_FIFO_STATUS)&_NRF24L01P_FIFO_STATUS_RX_REUSE ) return 1;
    else return 0;
}

void NRF24L01p_enable_dynamic_payload_pipe(NRF24L01p_pipe_t pipe, bool sel){
    if(sel){
          uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_DYNPD);
        temp |= (1<<pipe);
        NRF24L01p_write_register(_NRF24L01P_REG_DYNPD,temp);
    }else{
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_DYNPD);
        temp &= ~(1<<pipe);
        NRF24L01p_write_register(_NRF24L01P_REG_DYNPD,temp);
    }

}



void NRF24L01p_enable_dynamic_payload(bool sel){
    if(sel){
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_FEATURE);
        temp |= _NRF24L01_FEATURE_EN_DPL;
        NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,temp);
    }
    else{
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_FEATURE);
        temp &= ~_NRF24L01_FEATURE_EN_DPL;
        NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,temp);
    }

}



void NRF24L01p_enable_payload_with_ack(bool sel){
    if(sel){
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_FEATURE);
        temp |= _NRF24L01_FEATURE_EN_ACK_PAY;
        NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,temp);
    }
    else{
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_FEATURE);
        temp &= ~_NRF24L01_FEATURE_EN_ACK_PAY;
        NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,temp);
    }

}



void NRF24L01p_enable_dynamic_payload_with_no_ack(bool sel){
    if(sel){
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_FEATURE);
        temp |= _NRF24L01_FEATURE_EN_DYN_ACK;
        NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,temp);
    }
    else{
        uint8_t temp = NRF24L01p_read_register(_NRF24L01P_REG_FEATURE);
        temp &= ~_NRF24L01_FEATURE_EN_DYN_ACK;
        NRF24L01p_write_register(_NRF24L01P_REG_FEATURE,temp);
    }

}
