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


void Processor::receivePacket(const int * packet, const size_t packetSize){
    // packet[0] is packet type (Audio, Display, Buttons)
    // packet[1] is payload size (how many data elements)
    // packet[2::] is the actual data.
    
    // Set the member sizeOfPacket to payload size + 2
    sizeOfPacket = packet[1] + 2;
    
    // Dynamically allocate memory for processedPacket
    processedPacket = new int [sizeOfPacket];
    
    // processedPacket[0] should hold the type
    processedPacket[0] = packet[0];
    
    // Set the member packetType accordingly.
    if (packet[0] == 0)
        packetType = "Audio";
    else if (packet[0] == 1)
        packetType = "Display";
    else if (packet[0] == 2)
        packetType = "Button";
    else
        packetType = "Other";
    
    // processedPacket[1] should hold the payload size
    processedPacket[1] = packet[1];
    
    // Process the packet
    if (packet[0] == 0){ // Audio
        for (int i = 2; i<packetSize; ++i){
            processedPacket[i] = packet[i] * volume;
        }
    }
    else if (packet[0] == 1) { // Display
        for (int i = 2; i<packetSize; ++i){
            processedPacket[i] = packet[i] * brightness;
        }
    }
    else if (packet[0] == 2) { //Buttons
        for (int i = 2; i<packetSize; ++i)
            // For buttons, there is nothing to do, except to store the button values.
            processedPacket[i] = packet[i];
    }
}

int * Processor::getProcessedPacket()
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
