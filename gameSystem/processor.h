//
//  processor.h
//  gameSystem
//
//  Created by Pranai Vasudev on 2021-07-10.
//

#ifndef processor_h
#define processor_h

class Processor {
public:
    Processor();
    Processor(const int volume, const int brightness);
    ~Processor();
    void receivePacket(const int *packet, const size_t packetSize);
private:
    int *processedPacket;
    const int volume;
    const int brightness;
};

#endif /* processor_h */
