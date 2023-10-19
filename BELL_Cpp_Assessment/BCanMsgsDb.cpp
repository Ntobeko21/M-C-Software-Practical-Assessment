#include "BCanMsgsDb.h"
#include <QDebug>
#include "BXmlCanDbReader.h"
#include <QFileDialog>
#include <QDir>

BCanMsgsDb::BCanMsgsDb(void)
{
 // Use the QFileDialog and QDir Libraries to open a dialogue which prompts user to select database and read that file if selected
    QString dataFilePath = QFileDialog::getOpenFileName(nullptr, "Please open database file ", QDir::homePath(), "XML Files (*.xml)");
       if (!dataFilePath.isEmpty())
       {
           readXml(dataFilePath);
       }
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
        if(((canMsg->pgn() == ((IN_CanMsgId & 0x00FFFF00) >> 8))) )
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
