# gameSystem

## Description

gameSystem is a simple system written in C++ to process signals for a
video game system. This is implemented in a class called
`Processor`. The `Processor` class can receive a display, audio, or
button packet and do some simple signal processing. This is
implemented by the `Processor::receivePacket()` function. We assume the incoming packets
are a series of bytes and are structured as follows.

```
         +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+...
Byte:    |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  11 | ... |
         +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+...
         |                       |                       |                             |
Element: |    0 (Packet Type)    |    1 (Payload Size)   |   2...N (Payload)           |
         |      (Integer)        |      (Integer)        |         (Floats)            |
	 +-----------------------+-----------------------+-----------------------------+...
```
Here, we assume that there are four bytes to an integer/float.
The zeroth element (first four bytes) encode an integer, which indicates the packet type (0 for audio, 1 for display, 2 for button).
The first element (second four bytes) encode an integer, indicating the size of the payload, or the number of data elements in the signal.
The second through (third and onwards four bytes) final elements encode floats, which are the actual data to be processed.

If the processor receives an audio packet, it  will multiply all elements of the payload by a (user-specified) volume.
If the processor receives a display packet, it  will multiply all the elements of the payload by a (user-specified) brightness.
If the processor receives a button packet, it will store which buttons were pressed. For simplicity, we assume there are only six possible buttons: up, down, left, right, A, and B.

## Use
We assume there is an incoming packet, structured as shown above, called `packet` (of type `unsigned char *`).
We also assume we know the `totalNumberOfBytes`, which is the number of bytes in the packet we wish to process.
We also assume that we know the `volume` and `brightness` we'd like to use for audio and display packets.

Instantiate a `Processor` object. You can specify the volume and brightness, or use the default constructor to set the audio and volume both to zero.
```c++
float volume; // define the volume
float brightness; // define the brightness
Processor p(volume, brightness)
// OR
Processor p; // default constructor
```

With an instance of the processor, call the `receivePacket(const unsigned char * packet, const size_t totalNumberOfBytes)`method.
```c++
p.receivePacket(packet, totalNumberOfBytes);
```

The processed packet is stored in the `float * processedPacket` member of `Processor`. To access it use the `getProcessedPacket` method.
```c++
float * processedPacket = p.getProcessedPacket();
```

The `Processor` class holds information about the processed packet. To obtain the number of elements in the packet (see diagram above), use the
`getPacketSize()` method.
```c++
int numberOfElementsInPacket = p.getPacketSize();
```

To get the type of packet held by the processor, call the `getPacketType()` method.
```c++
std::string packetType = p.getPacketType();

```
## Decoding bytes into `int` and `float`
The functions `unsignedCharToInt(const unsigned char * bytes)` and `unsignedCharToFloat(const unsigned char * byte)`
convert an array of (four) bytes into an integer and a float, respectively. The implementation here (see [processor.cpp](https://github.com/pvasudev16/gameSystem/blob/dddf26fb8db5539d8b9895e2290c7b14b4a815dd/gameSystem/processor.cpp#L51)) assumes a little endian
system in which the least significant byte is stored first. In `unsignedCharToInt`, bytes are bitwise left-shifted to produce the integer.

The implementaiton of `unsignedCharToFloat` first converts the bytes that define the float into an integer. Then, using a `union`, the same area of memory
is interpreted as a float. (This is not the only way to solve this problem.)


## Useful Links
[See how floats are stored in memory](https://www.h-schmidt.net/FloatConverter/IEEE754.html)
[See how to bitwise left-shift bytes to create an integer](https://stackoverflow.com/questions/6834343/ultra-quick-way-to-concatenate-byte-values)
[More details on how floats are stored in memory](https://www.keil.com/support/man/docs/c51/c51_ap_floatingpt.htm)
[See how to use a union between an array of unsigned chars and a float](https://stackoverflow.com/questions/14535865/union-between-a-float-and-an-array-of-unsigned-char)
[An alternate implementation of unsignedCharToFloat](https://godbolt.org/z/vYM5czqs8)