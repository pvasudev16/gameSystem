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

//int main(int argc, const char * argv[]) {
//    int packet[] = {0, 5, 1, 2, 3, 4, 5};
//    for(int i=0; i<7; ++i)
//        std::cout << packet[i] << std::endl;
//    return 0;
//}

TEST_CASE("Get Packet Type")
{
    // Test the getPacketType function
    std::string packetType;
    
    // Create dummy test packet
    size_t testPacketSize = 3;
    int * testPacket = new int [testPacketSize];
    // Payload size 1, data 1
    testPacket[1] = 1;
    testPacket[2] = 1;
    
    // Uninitialized
    Processor p;
    packetType = p.getPacketType();
    REQUIRE(packetType == "None");
    
    // Audio
    testPacket[0] = 0;
    p.receivePacket(testPacket, testPacketSize);
    packetType = p.getPacketType();
    REQUIRE(packetType == "Audio");
    
    // Display
    testPacket[0] = 1;
    p.receivePacket(testPacket, testPacketSize);
    packetType = p.getPacketType();
    REQUIRE(packetType == "Display");
        
    // Button
    testPacket[0] = 2;
    p.receivePacket(testPacket, testPacketSize);
    packetType = p.getPacketType();
    REQUIRE(packetType == "Button");
    
    // Other
    testPacket[0] = 3;
    p.receivePacket(testPacket, testPacketSize);
    packetType = p.getPacketType();
    REQUIRE(packetType == "Other");
    
    delete [] testPacket;
}

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

TEST_CASE("Get Brightness")
{
    // Default ctor
    Processor p;
    REQUIRE(p.getBrightness() == 0);
    
    int brightness = 5;
    Processor q(0, brightness);
    REQUIRE(q.getBrightness() == brightness);
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
            REQUIRE(processedPacket[i] == testPacket[i] * volume);
    }
    delete [] testPacket;
}
