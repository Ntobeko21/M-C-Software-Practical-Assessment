#ifndef BXmlCanDbReader_H
#define BXmlCanDbReader_H

#include <QIODevice>
#include <QXmlStreamReader>
#include "BCanMsg.h"
#include "BCanMsgsDb.h"

class BXmlCanDbReader
{
public:
    BXmlCanDbReader(BCanMsgsDb* IN_canMsgsDb);
    bool read(QIODevice *device);
    QString errorString() const;
private:
    QXmlStreamReader reader;
    BCanMsgsDb* m_can_msgs_db;

    void readCanMsgsDb();
    void readCanMsg();
    void readMsgDef(BCanMsg *IN_CanMsg);
    void readSignal(BCanMsg *IN_CanMsg);
};

#endif // BXmlCanDbReader_H
