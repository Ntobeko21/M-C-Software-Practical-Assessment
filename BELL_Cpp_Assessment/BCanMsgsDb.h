#ifndef BCANMSGSDB_H
#define BCANMSGSDB_H

#include <QList>
#include "BCanMsg.h"

class BCanMsgsDb
{
public:
    BCanMsgsDb();
    ~BCanMsgsDb(void);
    void addCanMsg(BCanMsg* IN_CanMsg);
    void print() const;
    BCanMsg *getMsg(quint32 IN_CanMsgId);
    quint16 getMsgCount(void) {return m_can_msgs.count();}
private:
    QList<BCanMsg*> m_can_msgs;
    void readXml(const QString& fileName);
};

#endif // BCANMSGSDB_H
