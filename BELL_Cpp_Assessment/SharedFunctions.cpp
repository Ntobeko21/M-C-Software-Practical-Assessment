#include <QtCore>

quint32 ExtractBits(UNALIGNED quint8 *pbyData,quint8 byBitStart,quint8 byNumBits)
{
    quint32 bitMask = (1 << byNumBits) - 1;
    quint32 extractedBits = (pbyData[0] >> byBitStart) & bitMask;

    return extractedBits;
}
