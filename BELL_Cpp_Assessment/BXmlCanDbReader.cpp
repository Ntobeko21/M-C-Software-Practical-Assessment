#include "BXmlCanDbReader.h"

BXmlCanDbReader::BXmlCanDbReader(BCanMsgsDb* IN_canMsgsDb)
{
    m_can_msgs_db = IN_canMsgsDb;
}

bool BXmlCanDbReader::read(QIODevice *IN_device)
{
    reader.setDevice(IN_device);

    if (reader.readNextStartElement()) {
        if (reader.name() == "BELL_DATABASE")
            readCanMsgsDb();
        else
            reader.raiseError(QObject::tr("Not a BELL CAN Messages Database File"));
    }
    return !reader.error();
}

void BXmlCanDbReader::readCanMsgsDb(){
    while(reader.readNextStartElement()){
        if(reader.name() == "Message")
            readCanMsg();
        else
            reader.skipCurrentElement();
    }
}

void BXmlCanDbReader::readCanMsg(){
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "Message");

    BCanMsg* rec = new BCanMsg;

    readMsgDef(rec);

    while (reader.readNextStartElement()) {
        if (reader.name() == "Signal")
            readSignal(rec);
        else
            reader.skipCurrentElement();
    }

    m_can_msgs_db->addCanMsg(rec);
}

void BXmlCanDbReader::readMsgDef(BCanMsg *IN_CanMsg){
    Q_ASSERT(reader.name() == "Message"
             && reader.attributes().hasAttribute("msg_desc")
             && reader.attributes().hasAttribute("pgn")
             && reader.attributes().hasAttribute("sa") );

    IN_CanMsg->setDesc(reader.attributes().value("msg_desc").toString());
    IN_CanMsg->setPgn(reader.attributes().value("pgn").toUInt());
    IN_CanMsg->setSourceAddr(reader.attributes().value("sa").toUInt());
}

void BXmlCanDbReader::readSignal(BCanMsg *IN_CanMsg){
    Q_ASSERT(reader.isStartElement() &&
             reader.name() == "Signal");

    Q_ASSERT(   reader.attributes().hasAttribute("sig_desc")
                && reader.attributes().hasAttribute("startbit")
                && reader.attributes().hasAttribute("num_bits"));

    IN_CanMsg->addSignal(
                reader.attributes().value("sig_desc").toString(),
                reader.attributes().value("startbit").toUInt(),
                reader.attributes().value("num_bits").toUInt(),
                reader.attributes().value("nominator").toUInt(),
                reader.attributes().value("denominator").toUInt(),
                reader.attributes().value("offset").toInt(),
                reader.attributes().value("isigned").toUInt());
    reader.skipCurrentElement();
}

QString BXmlCanDbReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(reader.errorString())
            .arg(reader.lineNumber())
            .arg(reader.columnNumber());
}
