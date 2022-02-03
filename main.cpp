#include <iostream>

using namespace std;

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
    canMessage[0] = outData[0];       //  1 byte
    canMessage[1] = outData[0] >> 8;  //  1 byte
    canMessage[2] = outData[0] >> 16; //= 3/8 bytes total

    canMessage[4] = outData[1];       //  4 byte
    canMessage[5] = outData[1] >> 8;  //  5 byte
    canMessage[6] = outData[1] >> 16; //= 6/8 bytes total

    // RECEIVING
    std::cout << "Receiving" << std::endl;
    // Combine received data and output correct values
    uint32_t receive_1 = 0;
    uint32_t receive_2 = 0;
    receive_1 = (canMessage[0]) | canMessage[1]<<8 | canMessage[2]<<16;
    receive_2 = (canMessage[4]) | canMessage[5]<<8 | canMessage[6]<<16;

    std::cout << receive_1 << std::endl;
    std::cout << receive_2<< std::endl;

return 0;
}
