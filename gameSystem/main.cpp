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

TEST_CASE("unsignedCharToInt")
{
    // Check that unsignedCharToInt is doing what it should for a few
    // positive numbers.
    unsigned char * representation;
    int integerRepresentation;

    // Check that zero is correctly reperesented
    representation = new unsigned char [4];
    // AL: Check that representation is NOT a nullptr, indicating that the
    // memory allocation failed. Use an ASSERT. Good practice to check that
    // memory allocation succeeds.
    
    // AL: Conside statically allocate memory, esp. for memory constrained systems
    // that might have only 16 KB memory.
    
    representation[0] = 0x00;
    representation[1] = 0x00;
    representation[2] = 0x00;
    representation[3] = 0x00;
    
    // Allen: how could this fail?
    // PV: What if I use 8 bytes? this fuct would fail. Use a function param.
    // AL: Think of the system. The context is an integer is four bytes.
    //     Let's impose this constraint. Make a test case to test this assumption!
    //     What if the platform we're building this code on has ints as 8 byes.
    //     Write a test that checks the REQUIRE(sizeof(int) == 4)
    integerRepresentation = unsignedCharToInt(representation);
    REQUIRE(integerRepresentation == 0);

    // Represent a number with a significant bit in each byte
    representation[0] = 0x01; // 2**24 = 16,777,216
    representation[1] = 0x02; // 2**17 = 131,072
    representation[2] = 0x04; // 2**10 = 1,024
    representation[3] = 0x08; // 2**3 = 8
    // Sum: 16,909,320
    integerRepresentation = unsignedCharToInt(representation);
    REQUIRE(integerRepresentation == 16909320);
    delete [] representation;
    
    // AL: Check negative numbers, largest possible +/- numbers.
    
    // AL:
 }

TEST_CASE("unsignedCharToFloat")
{
    // Check that unsignedCharToFloat is doing what it should for a few
    // numbers.
    unsigned char * representation;
    float floatRepresentation;

    // Check that zero is correctly reperesented
    representation = new unsigned char [4];
    representation[0] = 0x00;
    representation[1] = 0x00;
    representation[2] = 0x00;
    representation[3] = 0x00;
    floatRepresentation = unsignedCharToFloat(representation);
    REQUIRE(floatRepresentation == 0.0);

    // Represent 130.25
    representation[0] = 0x43; // SEEE EEEE = 0100 0011 = 0x43
    representation[1] = 0x02; // EMMM MMMM = 0000 0010 = 0x20
    representation[2] = 0x40; // MMMM MMMM = 0100 0000 = 0x40
    representation[3] = 0x00; // MMMM MMMM = 0000 0000 = 0x00
    floatRepresentation = unsignedCharToFloat(representation);
    REQUIRE(floatRepresentation == 130.25);
    delete [] representation;
}

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

TEST_CASE("Get Packet Type")
{
    // Test the getPacketType function
    std::string packetType;
    
    // Create dummy test packet
    size_t testPacketSize = 3;
    unsigned char * testPacket = new unsigned char [testPacketSize * sizeof(float)];
    // Payload: 1
    testPacket[4] = 0x00;
    testPacket[5] = 0x00;
    testPacket[6] = 0x00;
    testPacket[7] = 0x01;
    
    // Data: 1
    testPacket[8] = 0x00;
    testPacket[9] = 0x00;
    testPacket[10] = 0x00;
    testPacket[11] = 0x01;
    
    // Uninitialized
    Processor p;
    packetType = p.getPacketType();
    REQUIRE(packetType == "None");
    
    // Audio
    testPacket[0] = 0x00;
    testPacket[1] = 0x00;
    testPacket[2] = 0x00;
    testPacket[3] = 0x00;
    p.receivePacket(testPacket, testPacketSize);
    packetType = p.getPacketType();
    REQUIRE(packetType == "Audio");
    
    // Display
    testPacket[0] = 0x00;
    testPacket[1] = 0x00;
    testPacket[2] = 0x00;
    testPacket[3] = 0x01;
    p.receivePacket(testPacket, testPacketSize);
    packetType = p.getPacketType();
    REQUIRE(packetType == "Display");
        
    // Button
    testPacket[0] = 0x00;
    testPacket[1] = 0x00;
    testPacket[2] = 0x00;
    testPacket[3] = 0x02;
    p.receivePacket(testPacket, testPacketSize);
    packetType = p.getPacketType();
    REQUIRE(packetType == "Button");
    
    // Other
    testPacket[0] = 0x00;
    testPacket[1] = 0x00;
    testPacket[2] = 0x00;
    testPacket[3] = 0x03;
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
    unsigned char * testPacket;
    size_t testPacketSize = 7*sizeof(int);
    testPacket = new unsigned char [testPacketSize * sizeof(int)];
    
    testPacket[0] = 0x00; // audio
    testPacket[1] = 0x00;
    testPacket[2] = 0x00;
    testPacket[3] = 0x00;
    
    testPacket[4] = 0x00; // payload size
    testPacket[5] = 0x00;
    testPacket[6] = 0x00;
    testPacket[7] = 0x05;
    
    // testPacket[8:11] represents 1
    testPacket[8] = 0x3F;
    testPacket[9] = 0x80;
    testPacket[10] = 0x00;
    testPacket[11] = 0x00;
    
    // testPacket[12:15] represents 2
    testPacket[12] = 0x40;
    testPacket[13] = 0x00;
    testPacket[14] = 0x00;
    testPacket[15] = 0x00;
    
    // testPacket[16:19] represents 3
    testPacket[16] = 0x40;
    testPacket[17] = 0x40;
    testPacket[18] = 0x00;
    testPacket[19] = 0x00;
    
    // testPacket[20:23] represents 4
    testPacket[20] = 0x40;
    testPacket[21] = 0x80;
    testPacket[22] = 0x00;
    testPacket[23] = 0x00;
    
    // testPacket[24:27] represents 5
    testPacket[24] = 0x40;
    testPacket[25] = 0xa0;
    testPacket[26] = 0x00;
    testPacket[27] = 0x00;
    
    // Instantiate the Processor object.
    int volume = 3;
    int brightness = 0;
    Processor p(volume, brightness);
    
    p.receivePacket(testPacket, testPacketSize);
    int sizeOfPacket = p.getPacketSize();
    REQUIRE(sizeOfPacket == testPacketSize/sizeof(float));
    float * processedPacket =  p.getProcessedPacket();
    float testPacketAsFloat[5] = {1, 2, 3, 4, 5};
    for (int i=0; i<sizeOfPacket; ++i)
    {
        if (i==0)
            REQUIRE(processedPacket[i] == 0);
        else if (i==1)
            REQUIRE(processedPacket[i] == sizeOfPacket - 2);
        else
            REQUIRE(processedPacket[i] == testPacketAsFloat[i-2] * volume);
    }
    delete [] testPacket;
}

TEST_CASE("Display")
{// Check the basic display processor works.
    // Create testPacket = [0, 5, 1, 2, 3, 4, 5]
    unsigned char * testPacket;
    size_t testPacketSize = 7*sizeof(int);
    testPacket = new unsigned char [testPacketSize * sizeof(int)];
    
    testPacket[0] = 0x00; // display
    testPacket[1] = 0x00;
    testPacket[2] = 0x00;
    testPacket[3] = 0x01;
    
    testPacket[4] = 0x00; // payload size
    testPacket[5] = 0x00;
    testPacket[6] = 0x00;
    testPacket[7] = 0x05;
    
    // testPacket[8:11] represents 1
    testPacket[8] = 0x3F;
    testPacket[9] = 0x80;
    testPacket[10] = 0x00;
    testPacket[11] = 0x00;
    
    // testPacket[12:15] represents 2
    testPacket[12] = 0x40;
    testPacket[13] = 0x00;
    testPacket[14] = 0x00;
    testPacket[15] = 0x00;
    
    // testPacket[16:19] represents 3
    testPacket[16] = 0x40;
    testPacket[17] = 0x40;
    testPacket[18] = 0x00;
    testPacket[19] = 0x00;
    
    // testPacket[20:23] represents 4
    testPacket[20] = 0x40;
    testPacket[21] = 0x80;
    testPacket[22] = 0x00;
    testPacket[23] = 0x00;
    
    // testPacket[24:27] represents 5
    testPacket[24] = 0x40;
    testPacket[25] = 0xa0;
    testPacket[26] = 0x00;
    testPacket[27] = 0x00;
    
    
    // Instantiate the Processor object.
    int volume = 0;
    int brightness = 3;
    Processor p(volume, brightness);
    
    p.receivePacket(testPacket, testPacketSize);
    int sizeOfPacket = p.getPacketSize();
    REQUIRE(sizeOfPacket == testPacketSize/sizeof(float));
    float * processedPacket =  p.getProcessedPacket();
    float testPacketAsFloat[5] = {1, 2, 3, 4, 5};
    for (int i=0; i<sizeOfPacket; ++i)
    {
        if (i==0)
            REQUIRE(processedPacket[i] == 1);
        else if (i==1)
            REQUIRE(processedPacket[i] == sizeOfPacket - 2);
        else
            REQUIRE(processedPacket[i] == testPacketAsFloat[i-2] * brightness);
    }
    delete [] testPacket;
}

TEST_CASE("Button")
{
    // Check the button processor works
    // Button test packet: [2, 6, 0, 0, 1, 0, 0, 0]
    unsigned char * testPacket;
    size_t testPacketSize = 8*sizeof(int);
    testPacket = new unsigned char [testPacketSize * sizeof(int)];
    
    testPacket[0] = 0x00; // button
    testPacket[1] = 0x00;
    testPacket[2] = 0x00;
    testPacket[3] = 0x02;
    
    testPacket[4] = 0x00; // payload size
    testPacket[5] = 0x00;
    testPacket[6] = 0x00;
    testPacket[7] = 0x06;
    
    // testPacket[8:11] represents 0
    testPacket[8] = 0x00;
    testPacket[9] = 0x00;
    testPacket[10] = 0x00;
    testPacket[11] = 0x00;
    
    // testPacket[12:15] represents 0
    testPacket[12] = 0x00;
    testPacket[13] = 0x00;
    testPacket[14] = 0x00;
    testPacket[15] = 0x00;
    
    // testPacket[16:19] represents 1
    testPacket[16] = 0x3F;
    testPacket[17] = 0x80;
    testPacket[18] = 0x00;
    testPacket[19] = 0x00;
    
    // testPacket[20:23] represents 0
    testPacket[20] = 0x00;
    testPacket[21] = 0x00;
    testPacket[22] = 0x00;
    testPacket[23] = 0x00;
    
    // testPacket[24:27] represents 0
    testPacket[24] = 0x00;
    testPacket[25] = 0x00;
    testPacket[26] = 0x00;
    testPacket[27] = 0x00;
    
    // testPacket[28:31] represents 0
    testPacket[28] = 0x00;
    testPacket[29] = 0x00;
    testPacket[30] = 0x00;
    testPacket[31] = 0x00;
    
    
    // Instantiate the Processor object.
    // Use default constructor here, since there is no volume or brightness
    Processor p;
    
    p.receivePacket(testPacket, testPacketSize);
    int sizeOfPacket = p.getPacketSize();
    REQUIRE(sizeOfPacket == testPacketSize/sizeof(float));
    float * processedPacket =  p.getProcessedPacket();
    float testPacketAsFloat[6] = {0, 0, 1, 0, 0, 0};
    for (int i=0; i<sizeOfPacket; ++i)
    {
        if (i==0)
            REQUIRE(processedPacket[i] == 2);
        else if (i==1)
            REQUIRE(processedPacket[i] == sizeOfPacket - 2);
        else
            REQUIRE(processedPacket[i] == testPacketAsFloat[i-2]);
    }
    delete [] testPacket;
}
