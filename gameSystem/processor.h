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
    void receivePacket(const unsigned char *packet, const size_t totalNumberOfBytes);
    float * getProcessedPacket();
    int getPacketSize();
    std::string getPacketType();
    const int getVolume();
    const int getBrightness();
private:
    int sizeOfPacket;
    std::string packetType;
    const int volume;
    const int brightness;
    float * processedPacket;
};

int unsignedCharToInt(const unsigned char *byte);
float unsignedCharToFloat(const unsigned char * byte);

#endif /* processor_h */
