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
// to some defaults.
Processor::Processor() : volume{3}, brightness{3}{};

// Constructor to set volume and brightness
Processor::Processor(const int volumeValue, const int brightnessValue) :
    volume{volumeValue},
    brightness{brightnessValue}{}

// Deconstructor to do cleanup.
Processor::~Processor(){
    delete[] processedPacket;
}


void Processor::receivePacket(const int *packet, const size_t packetSize){
    // packet[0] is packet type (Audio, Display, Buttons)
    // packet[1] is payload size (how many data elements)
    // packet[2::] is the actual data.
    int payloadSize = packet[1];
    processedPacket = new int [payloadSize];
    if (packet[0] == 0){ // Audio
        for (int i = 0; i < payloadSize; ++i){
            processedPacket[i] = packet[i+2] * volume;
        }
    }
    else if (packet[0] == 1) { // Display
        for (int i = 0; i< payloadSize; ++i){
            processedPacket[i] = packet[i+2] * brightness;
        }
    }
    else if (packet[0] == 2) { //Buttons
        for (int i = 0; i < 6; ++i)
            // For buttons, there is nothing to do, except to store the button values.
            processedPacket[i] = packet[i+2];
    }
}
