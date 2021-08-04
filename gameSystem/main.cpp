//
//  main.cpp
//  gameSystem
//
//  Created by Pranai Vasudev on 2021-07-10.
//

#include <iostream>
#include "processor.h"
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Get Volume")
{
    // Test default ctor behaviour.
    Processor p;
    REQUIRE(p.getVolume() == 0);

    // Set volume
    int volume = 10;
    Processor q(volume, 0);
    REQUIRE(q.getVolume() == volume);
}

TEST_CASE("Volume")
{
    // Check the basic volume processor works.
    // Create testPacket = [0, 5, 1, 2, 3, 4, 5]
    int * testPacket;
    size_t testPacketSize = 7;
    testPacket = new int [testPacketSize];
    testPacket[0] = 0; // audio
    testPacket[1] = 5; // payload size
    for (int j=2; j<testPacketSize; ++j)
        testPacket[j] = j-1;
    
    // Instantiate the Processor object.
    int volume = 3;
    int brightness = 0;
    Processor p(volume, brightness);
    
    
    p.receivePacket(testPacket, testPacketSize);
    int * processedPacket = p.getProcessedPacket();
    int sizeOfPacket = p.getPacketSize();
    REQUIRE(sizeOfPacket == 7);
    for (int i=0; i<sizeOfPacket; ++i)
    {
        if (i==0)
            REQUIRE(processedPacket[i] == 0);
        else if (i==1)
            REQUIRE(processedPacket[i] == sizeOfPacket - 2);
        else
            REQUIRE(processedPacket[i] == testPacket[i]);
    }

}
