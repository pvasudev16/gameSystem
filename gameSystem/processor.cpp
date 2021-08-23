//
//  processor.cpp
//  gameSystem
//
//  Created by Pranai Vasudev on 2021-07-10.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "processor.h"

// Default constructor sets the volume, brightness to some defaults.
// Sets the size of the packet to zero by default.
// Sets the type of packet to "None" by default.
Processor::Processor() :
    volume(0),
    brightness(0),
    sizeOfPacket(0),
    packetType("None"),
    processedPacket(nullptr){};

// Constructor to set volume and brightness
Processor::Processor(const int volumeValue, const int brightnessValue) :
    volume(volumeValue),
    brightness(brightnessValue),
    sizeOfPacket(0),
    packetType("None"),
    processedPacket(nullptr){}

// Deconstructor
Processor::~Processor(){
    if (processedPacket != nullptr)
        delete [] processedPacket;
}

// Encode int as a sequence of unsigned chars
// TO-DO
//unsigned char * intToUnsignedChar(const int integer, unsigned char * buffer)
//{
//    for (int j=0; j<sizeof(int); ++j)
//    {
//        buffer[j] = integer >> (sizeof(int) - (j+1)*8);
//        ++buffer;
//    }
//    return buffer;
//}

// Encode unsigned chars to int
int unsignedCharToInt(const unsigned char *byte)
{
    int integerToReturn = 0;
    for (int j=0; j<sizeof(int); ++j)
    {
        integerToReturn += int(*byte << (sizeof(int) - (j+1))*8);
        ++byte;
    }
    return integerToReturn;
}

// Encode unsigned chars to float
// For an alternate solution, see https://godbolt.org/z/vYM5czqs8
float unsignedCharToFloat(const unsigned char * byte)
{
    union{
        float f;
        int i;
    } f;
    f.i = unsignedCharToInt(byte);
    return f.f;
}

// receivePacket receives an array of unsigned chars, and a packetSize.
void Processor::receivePacket(
                              const unsigned char * packet,
                              const size_t totalPacketSize
                              )
{
    // packet[0:sizeof(float)-1] is packet type (Audio, Display, Buttons), as an
    // int
    //     e.g. packet[0:3] are four unsigned chars encoding an int
    // packet[sizeof(float), 2*size(float)-1] is payload size (how many data
    // elements)
    //     e.g. packt[4:7] are four unsigned chars encoding an int
    // packet[2*sizeof(float)::] is the actual data.
    //     e.g. packet[8::] is the actual data
    
    // Get the packet type
    int packetType = unsignedCharToInt(&packet[0]);
    
    //Get the payload size
    int payloadSize = unsignedCharToInt(&packet[sizeof(int)]);
        
    // Assign member sizeOfPacket
    // Placeholder, as right now, sizeOfPacket == 2
    // Note: sizeOfPacket != totalPacketSize
    //    e.g. 8 ints means totalPacketSize == 32
    //    while we want sizeOfPacket == 8.
    sizeOfPacket = payloadSize + 2;
    
    // Processed packet
    processedPacket = new float [sizeOfPacket];
    
    // Set the packetType and payloadSize
    // in processedPacket.
    processedPacket[0] = float(packetType);
    processedPacket[1] = float(payloadSize);


    // Set the member packetType accordingly.
    if (packetType == 0)
        Processor::packetType = "Audio";
    else if (packetType == 1)
        Processor::packetType = "Display";
    else if (packetType == 2)
        Processor::packetType = "Button";
    else
        Processor::packetType = "Other";
    
    // Process the packet
    // We've already taken care of the first 2*sizeof(int) unsigned chars.
    int j = 2*sizeof(int);
    int k = 2;
    while(j<totalPacketSize && k<sizeOfPacket)
    {
        float multiplier;
        if (packetType == 0) // Audio
            multiplier = volume;
        else if (packetType == 1) // Display
            multiplier = brightness;
        else // Button or other
            multiplier = 1;
        processedPacket[k] = unsignedCharToFloat(&packet[j]) * multiplier;
        ++k;
        j = j + sizeof(float);
    }
}

float * Processor::getProcessedPacket()
{
    return processedPacket;
}

int Processor::getPacketSize()
{
    return sizeOfPacket;
}

std::string Processor::getPacketType()
{
    return packetType;
}

const int Processor::getVolume()
{
    return volume;
}

const int Processor::getBrightness()
{
    return brightness;
}
