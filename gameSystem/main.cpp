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
    int packet[] = {0, 5, 1, 2, 3, 4, 5};
    size_t packetSize = 7;
    p.receivePacket(packet, packetSize);
    return 0;
}
