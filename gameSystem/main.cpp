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
//    Processor p;
//    int packet[] = {0, 5, 1, 2, 3, 4, 5};
//    size_t packetSize = 7;
//    p.receivePacket(packet, packetSize);
//    return 0;
//}

TEST_CASE("Volume")
{
    int volume = 3;
    int brightness = 0;
    Processor p(volume, brightness);
    int testPacket[] = {0, 5, 1, 2, 3, 4, 5};
    size_t testPacketSize = 7;
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
    
}
