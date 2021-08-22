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

//double decode_ieee_single(const unsigned char *v, int natural_order)
//{
//const unsigned char *data = v;
//int s, e;
//unsigned long src;
//long f;
//double value;
//
//if (natural_order) {
//src = ((unsigned long)data[0] << 24) |
//((unsigned long)data[1] << 16) |
//((unsigned long)data[2] << 8) |
//((unsigned long)data[3]);
//}
//else {
//src = ((unsigned long)data[3] << 24) |
//((unsigned long)data[2] << 16) |
//((unsigned long)data[1] << 8) |
//((unsigned long)data[0]);
//}
//}

// Encode unsigned chars to float
float unsignedCharToFloat(const unsigned char * byte)
{
    unsigned char byte0 = *byte;
    ++byte;
    unsigned char byte1 = *byte;
    ++byte;
    unsigned char byte2 = *byte;
    ++byte;
    unsigned char byte3 = *byte;
    union{
        float f;
        int i;
    } f;
    f.i = byte0 << 24
          | byte1 << 16
          | byte2 << 8
          | byte3;
    return f.f;
}

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
    // Placeholder, as right now, packetType == 0
    int packetType = unsignedCharToInt(&packet[0]);
    
    //Get the payload size
    // Placeholder, as right now, payloadSize == 0
    int payloadSize = unsignedCharToInt(&packet[sizeof(int)]);
    
    // to-do: Set the packetType and payloadSize
    // in processedPacket.
    
    // Assign member sizeOfPacket
    // Placeholder, as right now, sizeOfPacket == 2
    // Note: sizeOfPacket != totalPacketSize
    //    e.g. 8 ints means totalPacketSize == 32
    //    while we want sizeOfPacket == 8.
    sizeOfPacket = payloadSize + 2;
    
    // Processed packet
    processedPacket = new float [sizeOfPacket];

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
    // For testing purposes, set j=0; It should be 2*sizeof(int).
    int j = 0;
    // For testing purposes, set k=0; It should be 2.
    int k = 0;
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
