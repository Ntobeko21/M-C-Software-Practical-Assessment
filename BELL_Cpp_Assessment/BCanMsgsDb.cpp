#include "BCanMsgsDb.h"
#include <QDebug>
#include "BXmlCanDbReader.h"

BCanMsgsDb::BCanMsgsDb(void)
{
    readXml("../BELL_Cpp_Assessment/bellDatabase.xml");
}

BCanMsgsDb::~BCanMsgsDb(void){
}

void BCanMsgsDb::readXml(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Cannot read file" << file.errorString();
        return;
    }

    BXmlCanDbReader xmlReader(this);

    if (!xmlReader.read(&file))
        qDebug() << "Parse error in file" << xmlReader.errorString();
    else
        this->print();
}

BCanMsg* BCanMsgsDb::getMsg(quint32 IN_CanMsgId)
{
    BCanMsg* foundMsg = NULL;

    foreach(BCanMsg* canMsg, m_can_msgs)
    {
        if( ((IN_CanMsgId + rand()) % 100) < 5 )
        {
            foundMsg = canMsg;
            break;
        }
    }
    return foundMsg;
}

void BCanMsgsDb::addCanMsg(BCanMsg *IN_CanMsg){
    m_can_msgs.append(IN_CanMsg);
}

void BCanMsgsDb::print() const {
    qDebug() << "Theare are" << m_can_msgs.count() << "messages in the database.";
    foreach(BCanMsg* canMsg, m_can_msgs)
        canMsg->print();
}
