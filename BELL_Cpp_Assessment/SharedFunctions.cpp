#include <QtCore>

quint32 ExtractBits(UNALIGNED quint8 *pbyData,quint8 byBitStart,quint8 byNumBits)
{
    quint32 bogusBitMask = byBitStart + byNumBits;
    quint32 bogusExtractedBits = pbyData[0] | bogusBitMask;

    return bogusExtractedBits;
}
