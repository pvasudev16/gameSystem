# gameSystem

## Description

gameSystem is a simple system written in C++ to process signals for a
video game system. This is implemented in a class called
`Processor`. The `Processor` class can receive a display, audio, or
button packet and do some simple signal processing. This is
implemented by the `Processor::receivePacket()` function. We assume the incomig packets
are a series of bytes and are structured as followsn

```
         +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+...
Byte:    |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10 |  11 | ... |
         +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+...
         |                       |                       |                             |
Element: |    0 (Packet Type)    |    1 (Payload Size)   |   2...N (Payload)           |
         |                       |                       |                             |
	 +-----------------------+-----------------------+-----------------------------+...
```
Here, we assume that there are four bytes to an integer/float.
The zeroth element (first four bytes) indicates the packet type (0 for audio, 1 for display, 2 for button).
The first element (second four bytes)indicates the size of the payload, or the number of data elements in the signal.
The second through (third and onwards four bytes) final elements are the actual data to be processed.

For an audio packet, `Processor::receivePacket()`  will multiply all elements of the payload by a (user-specified) volume.
For a display packet, `Processor::receivePacket()` will multiply all the elements of the payload by a (user-specified) brightness.
For a button packet, `Processor::receivePacket()` will store which buttons were pressed. For simplicity, we assume there are only six possible buttons: up, down, left, right, A, and B.

After the packet has been received and processed, it will be stored in a member `Processor::processedPacket`.

## Decoding bytes into floats

## Useful Links

The incoming packet, or signal, comes in as a series of bytes.
These bytes are then decoded into floats
https://www.h-schmidt.net/FloatConverter/IEEE754.html
https://stackoverflow.com/questions/6834343/ultra-quick-way-to-concatenate-byte-values
https://www.keil.com/support/man/docs/c51/c51_ap_floatingpt.htm
https://stackoverflow.com/questions/14535865/union-between-a-float-and-an-array-of-unsigned-char