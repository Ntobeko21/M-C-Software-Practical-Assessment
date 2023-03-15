#include "BCanSig.h"
#include <QDebug>

BCanSig::BCanSig()
{
}

void BCanSig::print(void){
    qDebug() << qPrintable(this->desc) << ":";
    qDebug() << "\t offset:"        << this->offset;
    qDebug() << "\t nominator:"     << this->nominator;
    qDebug() << "\t denominator:"   << this->denominator;
    qDebug() << "\t is_signed:"     << this->is_signed;
    qDebug() << "\t startbit:"      << this->startbit;
    qDebug() << "\t num_bits:"      << this->num_bits;
}
