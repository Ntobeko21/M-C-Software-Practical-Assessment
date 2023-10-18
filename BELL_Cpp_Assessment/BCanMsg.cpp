#include "BCanMsg.h"
#include <QDebug>
#include "SharedFunctions.h"

void BCanMsg::addSignal(   QString  IN_SigDesc,
                           quint8   IN_StartBit,
                           quint8   IN_NumBits,
                           quint32  IN_Nominator,
                           quint32  IN_Denominator,
                           qint32   IN_Offset,
                           bool     IN_IsSigned     )
{
    BCanSig *addedSig = new BCanSig;
    m_signals.append(addedSig);

    addedSig->desc          = IN_SigDesc;
    addedSig->startbit      = IN_StartBit;
    addedSig->num_bits      = IN_NumBits;
    addedSig->nominator     = IN_Nominator;
    addedSig->denominator   = IN_Denominator;
    addedSig->offset        = IN_Offset;
    addedSig->is_signed     = IN_IsSigned;
}

BCanMsg::~BCanMsg(void){
}

void BCanMsg::print() const {
    qDebug() << "Description: " << m_desc.toLocal8Bit();
    qDebug() << "Signals:" << m_signals.count();
    foreach(BCanSig *pSig, m_signals) {
        pSig->print();
    }
}

BCanSig BCanMsg::sigAt(quint8 sigIdx)
{
    Q_ASSERT(sigIdx < m_signals.count());

    return *m_signals.at(sigIdx);
}

quint8 BCanMsg::sigCount()
{
    return m_signals.count();
}

QString BCanMsg::sigDescAt(quint8 sigIdx)
{
    Q_ASSERT(sigIdx < m_signals.count());

    return m_signals.at(sigIdx)->desc;
}

quint32 BCanMsg::sigRawValAt(quint8 IN_sigIdx, quint8 *IN_data)
{
    Q_ASSERT(IN_sigIdx < m_signals.count());

    BCanSig *pSig = m_signals.at(IN_sigIdx);

    Q_ASSERT((pSig->startbit + pSig->num_bits) <= 64);

    return ExtractBits(IN_data, pSig->startbit, pSig->num_bits);
}

#define BOGUS_ENG_VALUE_FACTOR 1.234

double BCanMsg::sigValAt(quint8 IN_sigIdx, quint8 *IN_data)
{
    Q_ASSERT(IN_sigIdx < m_signals.count());

    BCanSig *pSig = m_signals.at(IN_sigIdx);

    // Get the raw value from the data
    double rawValue = sigRawValAt(IN_sigIdx, IN_data);

    rawValue *= pSig->is_signed ? -1 : 1;

    // Decoding the engineering signal value from the raw value
    double engValue = rawValue *(pSig->nominator/pSig->denominator) + pSig->offset;

    return engValue;
}


