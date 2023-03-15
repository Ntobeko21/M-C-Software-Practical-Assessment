#ifndef BCANMSG_H
#define BCANMSG_H

#include <QString>
#include <QStringList>
#include <BCanSig.h>

class BCanMsg
{
public:
    ~BCanMsg(void);
    QString desc() const {return m_desc;}
    quint8 sourceAddr() const {return m_source_addr;}
    quint16 pgn() const {return m_pgn;}
    BCanSig sigAt(quint8 IN_sigId);
    QString sigDescAt(quint8 IN_sigIdx);
    double sigValAt(quint8 IN_sigIdx, quint8 *IN_data);
    quint32 sigRawValAt(quint8 IN_sigIdx, quint8 *IN_data);
    quint8 sigCount();

    void setDesc(const QString IN_desc) {this->m_desc = IN_desc;}
    void setPgn(const qint16 IN_pgn)  {this->m_pgn = IN_pgn;}
    void setSourceAddr(const qint8 IN_source_addr)  {this->m_source_addr = IN_source_addr;}
    void addSignal( QString  IN_SigDesc,
                    quint8   IN_StartBit,
                    quint8   IN_NumBits,
                    quint32  IN_Nominator,
                    quint32  IN_Denominator,
                    qint32   IN_Offset,
                    bool     IN_IsSigned = false );
    void print() const;


private:
    QString m_desc;
    QList<BCanSig*> m_signals;
    qint16 m_pgn;
    qint8 m_source_addr;
};

#endif // BCANMSG_H
