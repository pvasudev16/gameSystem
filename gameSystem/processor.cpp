//
//  processor.cpp
//  gameSystem
//
//  Created by Pranai Vasudev on 2021-07-10.
//

#include <stdio.h>
#include <iostream>
#include "processor.h"

// Default constructor sets the volume, brightness, and buttonValues multipliers
// to some defaults. Sets the size of the packet to zero by default.
Processor::Processor() : volume(0), brightness(0), sizeOfPacket(0){};

// Constructor to set volume and brightness
Processor::Processor(const int volumeValue, const int brightnessValue) :
    volume(volumeValue),
    brightness(brightnessValue),
    sizeOfPacket(0){}

// Deconstructor to do cleanup.
Processor::~Processor(){
    delete[] processedPacket;
}


void Processor::receivePacket(const int *packet, const size_t packetSize){
    // packet[0] is packet type (Audio, Display, Buttons)
    // packet[1] is payload size (how many data elements)
    // packet[2::] is the actual data.
    processedPacket = new int [packetSize];
    
    // Set the member sizeOfPacket to payload size + 2
    sizeOfPacket = packet[1] + 2;
    
    // processedPacket[0] should hold the type
    // processedPacket[1] should hold the payload size
    processedPacket[0] = packet[0];
    processedPacket[1] = packet[1];
    if (packet[0] == 0){ // Audio
        for (int i = 2; i < packetSize; ++i){
            processedPacket[i] = packet[i] * volume;
        }
    }
    else if (packet[0] == 1) { // Display
        for (int i = 2; i< packetSize; ++i){
            processedPacket[i] = packet[i] * brightness;
        }
    }
    else if (packet[0] == 2) { //Buttons
        for (int i = 2; i < packetSize; ++i)
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
