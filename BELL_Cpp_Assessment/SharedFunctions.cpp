#include <QtCore>

quint32 ExtractBits(UNALIGNED quint8 *pbyData,quint8 byBitStart,quint8 byNumBits)
{
    quint32 extractedBits = 0;

        // Calculate the number of bytes to read from the data array.
        quint8 startByte = byBitStart / 8;
        quint8 endByte = (byBitStart + byNumBits - 1) / 8;

        for (quint8 byteIndex = startByte; byteIndex <= endByte; ++byteIndex)
        {
            // Determine the number of bits to read from the current byte.
            quint8 bitsToRead = 8;

            if (byteIndex == startByte)
                bitsToRead -= byBitStart % 8;

            if (byteIndex == endByte)
                bitsToRead -= (7 - (byBitStart + byNumBits - 1) % 8);

            // Extract the relevant bits from the current byte.
            quint8 mask = (1 << bitsToRead) - 1;
            quint32 byteValue = pbyData[byteIndex] & mask;

            // Shift and accumulate the extracted bits.
            extractedBits = (extractedBits << bitsToRead) | byteValue;
        }

        return extractedBits;
}
