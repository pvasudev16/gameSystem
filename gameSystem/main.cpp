//
//  main.cpp
//  gameSystem
//
//  Created by Pranai Vasudev on 2021-07-10.
//

#include <iostream>
#include "processor.h"

int main(int argc, const char * argv[]) {
    Processor p;
    int packet = 5;
    size_t packetSize = 10;
    p.receivePacket(&packet, packetSize);
    return 0;
}
