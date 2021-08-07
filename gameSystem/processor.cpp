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

// Decode an integer as a char
void int2char(int integerToConvert, char & arrayToWrite)
{
    char * integerRepresentation;
    integerRepresentation = new char [4];
    // Code to represent the four chars of the integer.
    // For now, some dummy code to set them all to zero.
    for (int i=0; i<4; ++i)
        integerRepresentation[i] = 0;
    
    // Code to write the four bytes.
    // Write the first byte to where arrayToWrite points
    // Increment the pointer, and repeat this
    char * ptr = &arrayToWrite;
    for (int i=0; i<4; ++i)
    {
        *ptr = integerRepresentation[i];
        ++ptr;
    }
}

// For now, assume that receivePacket receives an array of integers.
void Processor::receivePacket(const int * packet, const size_t packetSize){
    // packet[0] is packet type (Audio, Display, Buttons)
    // packet[1] is payload size (how many data elements)
    // packet[2::] is the actual data.
    
    // Set the member sizeOfPacket to payload size + 2
    sizeOfPacket = packet[1] + 2;
    
    // Set the member packetType accordingly.
    if (packet[0] == 0)
    {
        packetType = "Audio";
        // Audio data is in integer/floats, which are each four bytes
        processedPacket = new char [sizeOfPacket * 4];
    }
    else if (packet[0] == 1)
    {
        packetType = "Display";
        // Display data is in unsigned char, which are each a byte
        // Need six extra bytes to store the data type and payload size
        // as integers
        processedPacket = new char [sizeOfPacket + 6];
    }
    else if (packet[0] == 2)
    {
        packetType = "Button";
        processedPacket = new char [sizeOfPacket * 4];
    }
    else
    {
        packetType = "Other";
        processedPacket = new char [sizeOfPacket * 4];
    }
    
    // processedPacket[0] should hold the type
    int2char(packet[0], processedPacket[0]);
    
    
    // processedPacket[1] should hold the payload size
    int2char(packet[1], processedPacket[4]);
    
//    // Process the packet
//    if (packet[0] == 0){ // Audio
//        for (int i = 2; i<packetSize; ++i){
//            processedPacket[i] = packet[i] * volume;
//        }
//    }
//    else if (packet[0] == 1) { // Display
//        for (int i = 2; i<packetSize; ++i){
//            processedPacket[i] = packet[i] * brightness;
//        }
//    }
//    else if (packet[0] == 2) { //Buttons
//        for (int i = 2; i<packetSize; ++i)
//            // For buttons, there is nothing to do, except to store the button values.
//            processedPacket[i] = packet[i];
//    }
}

char * Processor::getProcessedPacket()
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
