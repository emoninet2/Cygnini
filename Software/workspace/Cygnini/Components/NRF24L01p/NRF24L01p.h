/*
 * NRF24L01p.h
 *
 *  Created on: Apr 23, 2019
 *      Author: emon1
 */

#include <stdint.h>
#include <stdbool.h>

#include "NRF24L01pDriver.h"


#ifndef NRF24L01P_PORT_NRF24L01P_H_
#define NRF24L01P_PORT_NRF24L01P_H_


typedef enum {
           NRF24L01P_MODE_UNKNOWN = 0,/**< NRF24L01+ unknown mode */
		   NRF24L01P_MODE_POWER_DOWN,/**< NRF24L01+ Power Down mode */
		   NRF24L01P_MODE_STANDBY,/**< NRF24L01+ Standby mode */
		   NRF24L01P_MODE_RX,/**< NRF24L01+ RX mode */
		   NRF24L01P_MODE_TX,/**< NRF24L01+ TX mode */
}NRF24L01p_RadioState_t;

/** the structure of the Radio Configuration
    * This structure stores the default configuration assigned by the user
   */
typedef struct {
       bool DataReadyInterruptEnabled; /**< setting this high will generate interrupt signal on IRQ pin if a new data has arrived */
       bool DataSentInterruptEnabled;  /**< setting this high will generate interrupt signal on IRQ pin if data has been sent successfully */
       bool MaxRetryInterruptEnabled;  /**< setting this high will generate interrupt signal on IRQ pin if data transmission failed and max retry has been reached*/
       NRF24L01p_crc_t Crc;                      /**< Choose if the payload crc has to be 8-bit or 16-bit. Default is 16-bit crc*/
       NRF24L01p_aw_t addressWidth;              /**< choose the address byte to be either 3, 4 or 5 bytes. Default is 5-bytes*/
       uint8_t AutoReTransmissionCount;/**< used in the EnhancedShockBurst to retransmit data automatically. Value range from 0 to 15*/
       uint8_t AutoReTransmitDelayX250us;/**< the number (0 to 15 ) times 250 uS is the waiting period before retransmitting the data on failure */
       uint8_t frequencyOffset;/**< frequency offset over 2400 mhz. Maximum value possible is 125, allowing frequency to shift until 2526Mhz*/
       NRF24L01p_datarate_t datarate;/**< the on air data rate can be either 250kbps, 1Mbps or 2Mbps*/
       NRF24L01p_RFpower_t RfPowerDb;/**< transmitting power of the radio can be either 0dBm, -6dBm, -12dBm, -18dBm. Default is 0dBm (maximum power)*/
       bool PllLock;/**< used during physical layer debugging when continuous carrier wave is generated*/
       bool ContWaveEnabled;/**< will generate a continuous carrier signal at the set frequency*/
       bool FeatureDynamicPayloadEnabled;/**< setting this high will allow the payload size to be dynamically set and read. */
       bool FeaturePayloadWithAckEnabled;/**< setting this high will allow the ack payload size to be dynamically set and read*/
       bool FeatureDynamicPayloadWithNoAckEnabled;/**< will allow transmission of a single payload with no ack request*/
}NRF24L01p_RadioConfig_t;


/**struucture of the 6 RxPipeConfig
    * Each individual pipe configurations such as to enable it, enable auto ack on the pipe the pipe address, maximum width and feature to allow dynamic payload
    */
typedef struct {
   bool PipeEnabled;           /** < set this to high to allow data reception on the pipe */
   bool autoAckEnabled;        /** < set this high to automatically send an ack packet if a data has been received on the pipe*/
   uint64_t address;           /** < the 5-byte (can be 3, or 4) unique address of the pipe*/
   uint8_t MaxWidth;           /** < the maximum byte allowed to be received on the pipe. (only use if dynamic payload size feature is disabled)*/
   bool dynamicPayloadEnabled; /** < setting this high will allow payload size to be automatically determined */
}NRF24L01p_RxPipeConfig_t;


/** the structure of the Payload configuration

 * This structure is common for both payload to send and receive

 */

typedef struct{

    /// to be deprecated

	NRF24L01p_pipe_t pipe; //if payload type is RX
    ///to be used
    uint8_t Data[_NRF24L01P_FIFO_SIZE ]; //*< this contains the 32 bytes buffer data to send and receive into */
    unsigned int length;//*< the length of the data to send  or received*/
    bool UseAck;//*< used in TX mode to send the payload with ack if set to high and without ack if set to low*/
    NRF24L01p_PipeAddr_t TxAddress;//*< this is the 5-byte hardware address of the radio to send data to*/
    NRF24L01p_pipe_t TxAckPipe;//*< used when an ack payload has to be written in RX mode. when a payload is received , the ack payload is automatically sent*/
    bool GotAck;//*< this value is set high if the transmitter receives and ack.*/
    NRF24L01p_pipe_t RxPipe; //*< the pipe in which the data the data has been received and read from*/

    //unsigned int RxDataLen;//*< the size of the data received. In Tx Mode, the size of the ack payload received*/

}NRF24L01p_Payload_t;


/**

     * The enum containing the types of possible errors

     */

typedef enum{
	NRF24L01P_SUCCESS = 0, /**< succes operation */
	NRF24L01P_ERROR = 1,  /**< failed operation */
}NRF24L01p_ErrorStatus_t;


/** The variable to remember the current state of the radio
     * The statue of the radio initially is unknown. However changing states may require entering one more step which requires knowledge of the current state
     */
	NRF24L01p_RadioState_t RadioState;

    /** The placeholder for the radio's states defined by the user
     * This needs to be set one time before initializing the radio. The radio may know what to configure in cases of reset or other cases.
     */
	NRF24L01p_RadioConfig_t RadioConfig;

    /* Placeholder for the RX pipe configurations
     * All the configurations of the 6 parallel pipes are registered in this placeholder
     */
	NRF24L01p_RxPipeConfig_t RxPipeConfig[6];


    /* Placeholder for the TX address
     * Usually the TX address changes every time depending on the address to send to. However this value can be used if user wants to register a default TX address
     */
	NRF24L01p_PipeAddr_t  TxPipeAddress;




    /* The flags status set by the IRQ interrupt handler
     * These variables are used when the radio uses the interrupt handler function. The radio may either block the process by method of polling (reading the status register) or checing these values set by the interrupt function
     */

    bool drFlag, dsFlag, mrFlag;



    /* Initialize radio based on the user defined configurations
         * initializes the radio based on the configurations set in the placeholder RadioConfig
         */
        void NRF24L01p_Initialize();
        /* ReInitialize radio based on the user defined configurations
         * same as initialization. However some ports may create conflicts during low level re-init.
         */
        void NRF24L01p_ReInitialize();

        /* reads the current status of the radio FSM
         * @return the state of the radio
         */
        NRF24L01p_RadioState_t NRF24L01p_read_RadioMode();
        /* sets the current status of the radio FSM
         * @param mode set the current mode as power down, standby, TX or RX.
         */
        void NRF24L01p_write_RadioMode(NRF24L01p_RadioState_t mode);

        /**check if the radio is has new data to read
         * this value is set if there is new data readable. It is determined by the FIFO status of the radio
         * @return high if there is new data readable. low if there is no new data
         */
        bool NRF24L01p_readable();
        /**check if the radio has its TX FIFO free to write
         * the value if high means that new data can be written for transmission. low means the radio is busy
         * @return high if the data is writable. low means the radio is busy or has pending transmission of data
         */
        bool NRF24L01p_writable();
        /**Function to check if a pipe have received any data
         * This function will check the pipe address of the last in the RX fifo. if data is readable, this function will tell which pipe has received the data
         * @param pipe the pipe in which the data has been received (0 to 6)
         * @return returns true if there is pending data to be read on the pipe. false if there is no received data on the pipe.
         */
        bool NRF24L01p_readableOnPipe(NRF24L01p_pipe_t pipe);

        /** write the payload to transmit
         * this will write the 32-byte max payload that needs to be transmitted.
         * This function will check if the payload needs to be sent with ack and determine the sub function to send with ack or without
         * @param payload The payload containing the data and its configurations.
         * @return returns the error status as success, or fail
         */
        NRF24L01p_ErrorStatus_t NRF24L01p_writePayload(NRF24L01p_Payload_t *payload);

        /**write the ack payload
         * This function is used during reception mode.
         * When a pipe receives a data, it may send an ack payload that can be empty or contain some data
         * This function will preload the data that will automatically be sent when data is arrived on that pipe
         * Set the pipe in the payload's member 'TxAckPipe'
         * This function does not need to be used by the user. It is used by the function TrnasmitPayload() and TransmitPayloadInterruptHandled()
         * @param payload the payload containing the data
         * @return returns the error status as success, or fail
         */
        NRF24L01p_ErrorStatus_t NRF24L01p_writeAckPayload(NRF24L01p_Payload_t *payload);

        /** reads data received in the radio
         * check if there is data to read by using the function readable() and then use this function to extract the data, data size and pipe
         * @param payload the payload the data has to be written into
         * @return returns the error status as success, or fail
         */
        NRF24L01p_ErrorStatus_t NRF24L01p_readPayload(NRF24L01p_Payload_t *payload);

        /** transmit the payload on air
         * this function will transmit the payload
         * @param payload the payload containing the data and other configurations such as address, use of act, etc
         * @return returns the error status as success, or fail
         */
        NRF24L01p_ErrorStatus_t NRF24L01p_TransmitPayload(NRF24L01p_Payload_t *payload);

        /** reads data received in the radio and flush the RX buffer on error
         * check if there is data to read by using the function readable() and then use this function to extract the data, data size and pipe
         * @param payload the payload the data has to be written into
         * @return returns the error status as success, or fail
         */
        NRF24L01p_ErrorStatus_t NRF24L01p_ReceivePayload(NRF24L01p_Payload_t *payload);

    #if (_NRF24L01P_INTERRUPT_FEATURE_API == 1)
        /** transmit the payload on air (interrupt handled)
         * this function will transmit the payload
         * @param payload the payload containing the data and other configurations such as address, use of act, etc
         * @return returns the error status as success, or fail
         */
        NRF24L01p_ErrorStatus_t NRF24L01p_TransmitPayloadInterruptHandled(NRF24L01p_Payload_t *payload);
        /** reads data received in the radio and flush the RX buffer on error (interrupt handled)
         * check if there is data to read by using the function readable() and then use this function to extract the data, data size and pipe
         * @param payload the payload the data has to be written into
         * @return returns the error status as success, or fail
         */
        NRF24L01p_ErrorStatus_t NRF24L01p_ReceivePayloadInterruptHandled(NRF24L01p_Payload_t *payload);

        /**
         * The function to handle the interrupt generated on the IRQ pin
         */
        void InterruptHandler(void);
    #endif


#endif /* NRF24L01P_PORT_NRF24L01P_H_ */
