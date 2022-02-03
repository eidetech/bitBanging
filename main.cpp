#include <iostream>

int main()
{
uint32_t canMessage[8];
uint32_t outData[8];

    // SENDING
    std::cout << "Sending" << std::endl;
    // Read data and generate CAN message to send
    float inData[8] = {0.327654, 0.987456, 0.987123, 0.987000,
    0.123654, 0.123456, 0.758934, 0.678243};

    //  Converting to whole number (uint32_t type)
    for(int i = 0; i < 8; i++)
    {
        outData[i] = (uint32_t)(inData[i]*1000000.);
        std::cout << outData[i] << std::endl;
    }

    // Combining each whole number into
    canMessage[0] = outData[0];       //  1/8 bytes
    canMessage[1] = outData[0] >> 8;  //  2/8 bytes
    canMessage[2] = outData[0] >> 16; //  3/8 bytes

    canMessage[4] = outData[1];       //  4/8 bytes
    canMessage[5] = outData[1] >> 8;  //  5/8 bytes
    canMessage[6] = outData[1] >> 16; //  6/8 bytes

    // RECEIVING
    std::cout << "Receiving" << std::endl;
    // Combine received data and output correct values
    uint32_t receive_1 = 0;
    uint32_t receive_2 = 0;
    receive_1 = (canMessage[0]) | canMessage[1]<<8 | canMessage[2]<<16;
    receive_2 = (canMessage[4]) | canMessage[5]<<8 | canMessage[6]<<16;
    // Could go on decoding the received messages, but this proves that it works.

    // Printing the combined output for each received variable.
    std::cout << receive_1 << std::endl;
    std::cout << receive_2 << std::endl;

    // Testing coding and decoding the biggest possible number that can be sent in one CAN message.
    uint64_t bigNum = 4294967296;
    uint64_t canMessage_2[8];

    std::cout <<  "Coding:   ";
    std::cout << bigNum << std::endl;
    // CODING CAN message
    canMessage_2[0] = bigNum;       //  1/8 bytes
    canMessage_2[1] = bigNum >> 8;  //  2/8 bytes
    canMessage_2[2] = bigNum >> 16; //  3/8 bytes
    canMessage_2[3] = bigNum >> 24; //  4/8 bytes
    canMessage_2[4] = bigNum >> 32; //  5/8 bytes
    canMessage_2[5] = bigNum >> 40; //  6/8 bytes
    canMessage_2[6] = bigNum >> 48; //  7/8 bytes
    canMessage_2[7] = bigNum >> 56; //  8/8 bytes

    std::cout <<  "Decoding: ";
    // DECODING CAN message
    uint64_t receiveCanMessage =  canMessage_2[0]
                                | canMessage_2[1]<<8
                                | canMessage_2[2]<<16
                                | canMessage_2[3]<<24
                                | canMessage_2[4]<<32
                                | canMessage_2[5]<<40
                                | canMessage_2[6]<<48
                                | canMessage_2[7]<<56;

    // Print out combined output
    std::cout << receiveCanMessage << std::endl;

    return 0;
}
