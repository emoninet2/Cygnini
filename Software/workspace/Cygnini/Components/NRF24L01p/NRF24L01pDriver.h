/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   NRF24L01pDriver.h
 * Author: emon1
 *
 * Created on January 29, 2017, 7:56 AM
 */

#ifndef NRF24L01PDRIVER_H
#define NRF24L01PDRIVER_H

#include <stdio.h>
#include <stdint.h>
#include "port/NRF24L01pPort.h"
#include "NRF24L01pRegisters.h"


     typedef enum {
           CONFIG_CRC_NONE      =  (0),
           CONFIG_CRC_8BIT      =  (_NRF24L01P_CONFIG_EN_CRC),
           CONFIG_CRC_16BIT     =  (_NRF24L01P_CONFIG_EN_CRC|_NRF24L01P_CONFIG_CRC0),
    }NRF24L01p_crc_t;

    typedef enum {
           SETUP_AW_AW_3BYTE   =  (0x1<<0),/**< 3 bytes address width */
           SETUP_AW_AW_4BYTE   =  (0x2<<0),/**< 4 bytes address width */
           SETUP_AW_AW_5BYTE   =  (0x3<<0),/**< 5 bytes address width */
    }NRF24L01p_aw_t;

    typedef enum {
           RF_SETUP_RF_PWR_0DBM        =  (0x3<<1),
           RF_SETUP_RF_PWR_MINUS_6DBM  =  (0x2<<1),
           RF_SETUP_RF_PWR_MINUS_12DBM =  (0x1<<1),
           RF_SETUP_RF_PWR_MINUS_18DBM =  (0x0<<1),
    }NRF24L01p_RFpower_t;

    typedef enum {
           RF_SETUP_RF_DR_250KBPS    =    (_NRF24L01P_RF_SETUP_RF_DR_LOW_BIT),
           RF_SETUP_RF_DR_1MBPS      =    (0),
           RF_SETUP_RF_DR_2MBPS      =    (_NRF24L01P_RF_SETUP_RF_DR_HIGH_BIT),
    }NRF24L01p_datarate_t;

    typedef enum {
           PIPE_P0       =    0,/**< Pipe 0 */
           PIPE_P1       =    1,/**< Pipe 1 */
           PIPE_P2       =    2,/**< Pipe 2 */
           PIPE_P3       =    3,/**< Pipe 3 */
           PIPE_P4       =    4,/**< Pipe 4 */
           PIPE_P5       =    5,/**< Pipe 5 */
    }NRF24L01p_pipe_t;

    typedef uint64_t NRF24L01p_PipeAddr_t;



    void NRF24L01p_power_up();
    void NRF24L01p_power_down();
    void NRF24L01p_rx_mode();
    void NRF24L01p_tx_mode();
    void NRF24L01p_set_CRC(NRF24L01p_crc_t opt);
    NRF24L01p_crc_t NRF24L01p_get_CRC(void);
    void NRF24L01p_enable_dataReady_interrupt(bool sel);
    void NRF24L01p_enable_dataSent_interrupt(bool sel);
    void NRF24L01p_enable_maxRetry_interrupt(bool sel);

    void NRF24L01p_enable_auto_ack(NRF24L01p_pipe_t pipe, bool sel);
    void NRF24L01p_enable_rx_on_pipe(NRF24L01p_pipe_t pipe, bool sel);

    void NRF24L01p_set_address_width(NRF24L01p_aw_t width);
    NRF24L01p_aw_t NRF24L01p_get_address_width();

    void NRF24L01p_set_auto_retransmission_count(uint8_t count);
    uint8_t NRF24L01p_read_auto_retransmission_count();

    void NRF24L01p_set_auto_retransmission_delay(uint8_t times250us);
    uint8_t NRF24L01p_read_auto_retransmission_delay();

    void NRF24L01p_set_frequency_offset(uint8_t offset);
    uint8_t NRF24L01p_get_frequency_offset();

    void NRF24L01p_set_DataRate(NRF24L01p_datarate_t DataRate);
    NRF24L01p_datarate_t NRF24L01p_get_DataRate();
    void NRF24L01p_set_RF_Power(NRF24L01p_RFpower_t RFpower);
    NRF24L01p_RFpower_t NRF24L01p_get_RF_Power();
    void NRF24L01p_enable_pll_lock(bool sel);

    void NRF24L01p_enable_cont_wave(bool sel);

    bool NRF24L01p_get_tx_fifo_full_flag();
    bool NRF24L01p_get_max_retry_flag();
    void NRF24L01p_clear_max_retry_flag();
    bool NRF24L01p_get_data_sent_flag();
    void NRF24L01p_clear_data_sent_flag();
    bool NRF24L01p_get_data_ready_flag();
    void NRF24L01p_clear_data_ready_flag();
    NRF24L01p_pipe_t NRF24L01p_get_rx_payload_pipe();

    uint8_t NRF24L01p_get_arc_count();
    uint8_t NRF24L01p_get_plos_count();
    void NRF24L01p_clear_plos_count();

    bool NRF24L01p_get_rpd();

    void NRF24L01p_set_RX_pipe_address(NRF24L01p_pipe_t pipe,NRF24L01p_PipeAddr_t address);
    NRF24L01p_PipeAddr_t NRF24L01p_get_RX_pipe_address(NRF24L01p_pipe_t pipe);

    void NRF24L01p_set_TX_pipe_address(NRF24L01p_PipeAddr_t address);
    NRF24L01p_PipeAddr_t NRF24L01p_get_TX_pipe_address();

    uint8_t NRF24L01p_get_RX_pipe_width(NRF24L01p_pipe_t pipe);

    bool NRF24L01p_get_fifo_flag_rx_empty();
    bool NRF24L01p_get_fifo_flag_rx_full();
    bool NRF24L01p_get_fifo_flag_tx_empty();
    bool NRF24L01p_get_fifo_flag_tx_full();
    bool NRF24L01p_get_fifo_flag_tx_reuse();

    void NRF24L01p_enable_dynamic_payload_pipe(NRF24L01p_pipe_t pipe, bool sel);

    void NRF24L01p_enable_dynamic_payload(bool sel);
    void NRF24L01p_enable_payload_with_ack(bool sel);
    void NRF24L01p_enable_dynamic_payload_with_no_ack(bool sel);

    uint8_t NRF24L01p_read_register(uint8_t address);
    void NRF24L01p_read_register_buffer(uint8_t address, uint8_t *dataout, int len);
    void NRF24L01p_write_register(uint8_t address, uint8_t datain);
    void NRF24L01p_write_register_buffer(uint8_t address, uint8_t *datain, int len);
    void NRF24L01p_read_rx_payload(uint8_t *dataout, int pay_len);
    void NRF24L01p_write_tx_payload(uint8_t *datain, int pay_len);
    void NRF24L01p_flush_tx();
    void NRF24L01p_flush_rx();
    void NRF24L01p_reuse_tx_payload();
    int NRF24L01p_read_rx_payload_width();
    void NRF24L01p_write_ack_payload(NRF24L01p_pipe_t pipe, uint8_t *datain, int pay_len);
    void NRF24L01p_write_tx_payload_noack(uint8_t *datain, int pay_len);
    uint8_t NRF24L01p_get_status();


#endif /* NRF24L01PDRIVER_H */
