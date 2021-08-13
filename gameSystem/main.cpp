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

TEST_CASE("Hello World")
{
    // In this Hello World scenario, the unsignedCharToFloat
    // and unsignedCharToInt functions return 0. Receive a dummy
    // packet. This sets the packetType integer, in receivePacket(),
    // to 0, which then sets the Processor::packetType member to "Audio".
    Processor p;
    unsigned char * packet;
    packet = new unsigned char [3*sizeof(float)];
    for (int i=0; i<3*sizeof(float); ++i)
        packet[i] = 0;
    p.receivePacket(packet, 3*sizeof(float));
    REQUIRE(p.getPacketType() == "Audio");
    
    // In our hello world implementation of unsignedCharToInt(Float),
    // processedPacket will be 2 floats long, and all zeros
    float * processedPacket = p.getProcessedPacket();
    REQUIRE(processedPacket[0] == 0.0);
    REQUIRE(processedPacket[1] == 0.0);
    
    // size of the packet should be 2
    REQUIRE(p.getPacketSize() == 2);
    
    delete [] packet;
}

//TEST_CASE("Get Packet Type")
//{
//    // Test the getPacketType function
//    std::string packetType;
//    
//    // Create dummy test packet
//    size_t testPacketSize = 3;
//    int * testPacket = new int [testPacketSize];
//    // Payload size 1, data 1
//    testPacket[1] = 1;
//    testPacket[2] = 1;
//    
//    // Uninitialized
//    Processor p;
//    packetType = p.getPacketType();
//    REQUIRE(packetType == "None");
//    
//    // Audio
//    testPacket[0] = 0;
//    p.receivePacket(testPacket, testPacketSize);
//    packetType = p.getPacketType();
//    REQUIRE(packetType == "Audio");
//    
//    // Display
//    testPacket[0] = 1;
//    p.receivePacket(testPacket, testPacketSize);
//    packetType = p.getPacketType();
//    REQUIRE(packetType == "Display");
//        
//    // Button
//    testPacket[0] = 2;
//    p.receivePacket(testPacket, testPacketSize);
//    packetType = p.getPacketType();
//    REQUIRE(packetType == "Button");
//    
//    // Other
//    testPacket[0] = 3;
//    p.receivePacket(testPacket, testPacketSize);
//    packetType = p.getPacketType();
//    REQUIRE(packetType == "Other");
//    
//    delete [] testPacket;
//}
//
//TEST_CASE("Get Volume")
//{
//    // Test default ctor behaviour.
//    Processor p;
//    REQUIRE(p.getVolume() == 0);
//
//    // Set volume
//    int volume = 10;
//    Processor q(volume, 0);
//    REQUIRE(q.getVolume() == volume);
//}
//
//TEST_CASE("Get Brightness")
//{
//    // Default ctor
//    Processor p;
//    REQUIRE(p.getBrightness() == 0);
//    
//    int brightness = 5;
//    Processor q(0, brightness);
//    REQUIRE(q.getBrightness() == brightness);
//}
//
//TEST_CASE("Volume")
//{
//    // Check the basic volume processor works.
//    // Create testPacket = [0, 5, 1, 2, 3, 4, 5]
//    int * testPacket;
//    size_t testPacketSize = 7;
//    testPacket = new int [testPacketSize];
//    testPacket[0] = 0; // audio
//    testPacket[1] = 5; // payload size
//    for (int j=2; j<testPacketSize; ++j)
//        testPacket[j] = j-1;
//    
//    // Instantiate the Processor object.
//    int volume = 3;
//    int brightness = 0;
//    Processor p(volume, brightness);
//    
//    p.receivePacket(testPacket, testPacketSize);
//    int sizeOfPacket = p.getPacketSize();
//    REQUIRE(sizeOfPacket == testPacketSize);
//    int * processedPacket =  p.getProcessedPacket();
//    for (int i=0; i<sizeOfPacket; ++i)
//    {
//        if (i==0)
//            REQUIRE(processedPacket[i] == 0);
//        else if (i==1)
//            REQUIRE(processedPacket[i] == sizeOfPacket - 2);
//        else
//            REQUIRE(processedPacket[i] == testPacket[i] * volume);
//    }
//    delete [] testPacket;
//}
//
//TEST_CASE("Display")
//{
//    // Check the basic display processor works.
//    // Create testPacket = [1, 5, 1, 2, 3, 4, 5]
//    int * testPacket;
//    size_t testPacketSize = 7;
//    testPacket = new int [testPacketSize];
//    testPacket[0] = 1; // display
//    testPacket[1] = 5; // payload size
//    for (int j=2; j<testPacketSize; ++j)
//        testPacket[j] = j-1;
//    
//    // Instantiate the Processor object.
//    int volume = 0;
//    int brightness = 3;
//    Processor p(volume, brightness);
//    
//    p.receivePacket(testPacket, testPacketSize);
//    int sizeOfPacket = p.getPacketSize();
//    REQUIRE(sizeOfPacket == testPacketSize);
//    int * processedPacket = p.getProcessedPacket();
//    for (int i=0; i<sizeOfPacket; ++i)
//    {
//        if (i==0)
//            REQUIRE(processedPacket[i] == 1);
//        else if (i==1)
//            REQUIRE(processedPacket[i] == sizeOfPacket - 2);
//        else
//            REQUIRE(processedPacket[i] == testPacket[i] * brightness);
//    }
//    delete [] testPacket;
//}
//
//TEST_CASE("Button")
//{
//    // Check the button processor works
//    // Button test packet: [2, 6, 0, 0, 1, 0, 0, 0]
//    size_t testPacketSize = 8;
//    int * testPacket = new int [testPacketSize];
//    testPacket[0] = 2; // button
//    testPacket[1] = 6; // payload size
//    for (int j=2; j<testPacketSize; ++j)
//        j == 4 ? testPacket[j] = 1 : testPacket[j] = 0;
//    
//    Processor p;
//    p.receivePacket(testPacket, testPacketSize);
//    int sizeOfPacket = p.getPacketSize();
//    REQUIRE(sizeOfPacket == testPacketSize);
//    int * processedPacket = p.getProcessedPacket();
//    for (int i=0; i<sizeOfPacket; ++i)
//    {
//        if (i==0)
//            REQUIRE(processedPacket[i] == 2);
//        else if (i==1)
//            REQUIRE(processedPacket[i] == sizeOfPacket - 2);
//        else
//            REQUIRE(processedPacket[i] == testPacket[i]);
//    }
//    delete [] testPacket;
//}
