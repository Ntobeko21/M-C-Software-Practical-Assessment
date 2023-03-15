#ifndef BCANSIG_H
#define BCANSIG_H
#include <QString>

class BCanSig
{
public:
    void print(void);
    BCanSig();
    QString desc;
    qint32  offset;
    qint32  nominator;
    qint32  denominator;
    bool    is_signed;
    quint8  startbit;
    quint8  num_bits;
};

#endif // BCANSIG_H
