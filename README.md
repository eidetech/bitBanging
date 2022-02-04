# Variable conversion and decimal to binary operations

### Backstory
When working with CAN messages, it is necessary to know how to convert float variables to integer values, and decimal numbers to binary. This repository contains some example code on how this can be done.

### Theory
#### CAN bus datafield
A CAN datafield consists of 8 bytes, therefore it is necessary to convert decimal point variables (such as float and double) to whole numbers, that can then be converted from decimal representation to binary.
> A byte consists of 8 adjacent binary digits (bits), each of which consists of a 0 or 1 (https://www.britannica.com/technology/byte)

#### Storing numbers in variables
The size of the number one wish to send predicts the number of bytes that is required to send that number via CAN bus. For example, the number 43676 would need a 16 bit integer (such as uint16) to store its binary value. This is because the largest number one can store in a 16 bit integer variable is 2^16 = 65536. If, however, one would want to store a number larger than 65536, one would need to store that number in a 32 bit integer variable (such as uint32), because a 32 bit variable allows for numbers up to 2^32 = 4294967296.

#### CAN bus messages
As stated above, a CAN bus message can store up to 8 bytes. Since every byte consists of 8 bits, the message can store up to 8x8 = 64 bits in total.
Code example of coding and decoding 64 bits to (decimal->binary->decimal):

    // Testing coding and decoding the biggest possible number that can be sent in one CAN message.
    uint64_t bigNum = pow(2,64); // 0 through 18446744073709551615 (2^64 − 1). NOT 18446744073709551616!
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
  
The code above should output the following:

    Coding:   4294967296
    Decoding: 4294967296
