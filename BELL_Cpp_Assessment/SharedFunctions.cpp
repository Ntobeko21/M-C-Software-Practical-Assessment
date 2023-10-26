#include <QtCore>

quint32 ExtractBits(UNALIGNED quint8 *pbyData,quint8 byBitStart,quint8 byNumBits)
{
    quint32 retVal = 0;
    quint8 retValShift = 0;

    while(byNumBits > 0)
    {

        quint8 byByteIndex = (byBitStart / 8);                                          // Index of the byte containing the current bit to be extracted
        quint8 byBitIndex = (byBitStart % 8);                                           // bit index within the byte.
        quint8 byBitsInBytes = 8 - byBitIndex;                                          //  number of bits left in the current byte, starting from byBitIndex.
        quint8 byBitsToExtract = byNumBits > byBitsInBytes ? byBitsInBytes : byNumBits; //  bits to be extracted in the current iteration
        quint8 byByteMask = ((1 << byBitsToExtract) - 1);                               // Mask used to extract the desired bits from current byte
        quint8 tempVal = (pbyData[byByteIndex] >> byBitIndex) & byByteMask;             // Extract bits from current byte

        retVal = tempVal << retValShift;                                                // Shift the extracted bits to their final position in retVal and combine them with any previously extracted bits

        byNumBits -= byBitsToExtract;                                                   //bits left to be extracted
        byBitStart += byBitsToExtract;                                                  // starting bit index for the next iteration
        retValShift += byBitsToExtract;                                                 // shift amount for the next iteration
    }

    return retVal;

}
