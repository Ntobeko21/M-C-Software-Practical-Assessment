#include <QtCore>

quint32 ExtractBits(UNALIGNED quint8 *pbyData,quint8 byBitStart,quint8 byNumBits)
{
    using extractedBits  = quint32;

    // Calculate the bit mask based on the number of bits
    quint8 bitMask = (1 << byNumBits) - 1 ;

    // Extract and return the raw value
    extractedBits  rawValue = ((pbyData[0] >> byBitStart) & bitMask);

    return rawValue;

}
