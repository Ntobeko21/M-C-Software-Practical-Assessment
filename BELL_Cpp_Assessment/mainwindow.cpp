#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QDateTime>
#include <QRegExp>

#define TESTMSG1_id  "217056256"
#define TESTMSG1_b0  "240"
#define TESTMSG1_b1  "125"
#define TESTMSG1_b2  "132"
#define TESTMSG1_b3  "164"
#define TESTMSG1_b4  "21"
#define TESTMSG1_b5  "33"
#define TESTMSG1_b6  "255"
#define TESTMSG1_b7  "132"
#define TESTMSG1_crc "19"

#define TESTMSG2_id "418386939"
#define TESTMSG2_b0 "188"
#define TESTMSG2_b1 "127"
#define TESTMSG2_b2 "138"
#define TESTMSG2_b3 "127"
#define TESTMSG2_b4 "255"
#define TESTMSG2_b5 "255"
#define TESTMSG2_b6 "255"
#define TESTMSG2_b7 "255"
#define TESTMSG2_crc "132"

#define INITMSG_id     TESTMSG1_id
#define INITMSG_b0     TESTMSG1_b0
#define INITMSG_b1     TESTMSG1_b1
#define INITMSG_b2     TESTMSG1_b2
#define INITMSG_b3     TESTMSG1_b3
#define INITMSG_b4     TESTMSG1_b4
#define INITMSG_b5     TESTMSG1_b5
#define INITMSG_b6     TESTMSG1_b6
#define INITMSG_b7     TESTMSG1_b7
#define INITMSG_crc    TESTMSG1_crc

#define FEED_HEADER QString("_________________________________________\n") + \
                    QDateTime::currentDateTime().toString()

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canDb = new BCanMsgsDb();
    
    ui->txtFeed->append(FEED_HEADER);

    if(canDb->getMsgCount()){
        ui->txtFeed->append(
                    "ℹ INFO:\tA database has been loaded that\n"
                    "\tcontains [" + QString::number(canDb->getMsgCount()) + "] CAN message definitions.\n");
    }
    else {
        ui->txtFeed->append("⚠ ATTENTION:\tNo messages defined in [" + dbFilename + "]!\n");
    }

    ui->boxMsgId->setText(INITMSG_id);

    ui->boxByte0->setText(INITMSG_b0);
    ui->boxByte1->setText(INITMSG_b1);
    ui->boxByte2->setText(INITMSG_b2);
    ui->boxByte3->setText(INITMSG_b3);
    ui->boxByte4->setText(INITMSG_b4);
    ui->boxByte5->setText(INITMSG_b5);
    ui->boxByte6->setText(INITMSG_b6);
    ui->boxByte7->setText(INITMSG_b7);

    ui->boxCRC->setText(INITMSG_crc);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete canDb;
}

union uCanMsgRaw {
    struct {
        quint32  msgId;
        quint8   dataBytes[8];
    } tMsgparts;
    quint8 rawBytes[4+8];
} ;

void MainWindow::on_btnProcess_clicked()
{
   QRegExp rxValidEasyPaste("^\\s*\\d+(\\t\\d+){9,9}\\s*$");
   if(rxValidEasyPaste.exactMatch(ui->boxEasyPaste->text()))
   {
       qDebug("It looks like it was copied from the spreadsheet!");

       QStringList pastedFields = ui->boxEasyPaste->text().split('\t');

       ui->boxMsgId->setText(pastedFields.at(0));

       ui->boxByte0->setText(pastedFields.at(1));
       ui->boxByte1->setText(pastedFields.at(2));
       ui->boxByte2->setText(pastedFields.at(3));
       ui->boxByte3->setText(pastedFields.at(4));
       ui->boxByte4->setText(pastedFields.at(5));
       ui->boxByte5->setText(pastedFields.at(6));
       ui->boxByte6->setText(pastedFields.at(7));
       ui->boxByte7->setText(pastedFields.at(8));

       ui->boxCRC->setText(pastedFields.at(9));
   }

   uCanMsgRaw msgToProcess;

   msgToProcess.tMsgparts.msgId = ui->boxMsgId->text().toLong();

   quint8 *dataBytes = msgToProcess.tMsgparts.dataBytes;

   dataBytes[0] = ui->boxByte0->text().toUInt();
   dataBytes[1] = ui->boxByte1->text().toUInt();
   dataBytes[2] = ui->boxByte2->text().toUInt();
   dataBytes[3] = ui->boxByte3->text().toUInt();
   dataBytes[4] = ui->boxByte4->text().toUInt();
   dataBytes[5] = ui->boxByte5->text().toUInt();
   dataBytes[6] = ui->boxByte6->text().toUInt();
   dataBytes[7] = ui->boxByte7->text().toUInt();

   quint8 dataCrc = ui->boxCRC->text().toUInt();

   QString feedLine;
   feedLine += FEED_HEADER;



   feedLine += "\nData: [";
   for(quint8 byteIdx = 0; byteIdx < sizeof(msgToProcess.tMsgparts.dataBytes); byteIdx++)
   {
       feedLine += QString::asprintf("%02X ", msgToProcess.tMsgparts.dataBytes[byteIdx]);
   }
   feedLine += "]\n";



   feedLine += "CRC: [";
   feedLine += QString::asprintf("%02X", dataCrc);
   feedLine += "] Result: [__crc_result__]\n";
   quint8 calculatedCrc = (quint8)rand();

   QString crcResult = "✔ pass";
   if(calculatedCrc != dataCrc)
   {
       crcResult = "✖ FAIL! (__calced_crc__)";
       crcResult.replace("__calced_crc__", QString::number(calculatedCrc));
   }
   feedLine.replace("__crc_result__", crcResult);



   feedLine += "Message ID [__msg_id__ (__msg_id_raw__)]  was searched for. ";
   feedLine += "\nIt is called [__msg_desc__] and comes from SA [__source_addr__].";
   feedLine += "\nSignals in Message: [__signal_count__].\n";


   feedLine.replace("__msg_id__", QString::number(msgToProcess.tMsgparts.msgId));
   feedLine.replace("__msg_id_raw__", QString::asprintf("0x%08X", msgToProcess.tMsgparts.msgId));
   feedLine.replace("__source_addr__", QString::asprintf("%u", (quint8)rand()));

   BCanMsg *canMsg = canDb->getMsg(msgToProcess.tMsgparts.msgId);
   if(canMsg)
   {
       quint8 sigCount = canMsg->sigCount();

       feedLine.replace("__msg_desc__", canMsg->desc());
       feedLine.replace("__signal_count__", QString::number(sigCount));

       for(quint8 sigIdx = 0; sigIdx < sigCount; sigIdx++)
       {

           feedLine += "   ◾  Bits: [__start_bit__:__num_bits__]\t-    __sig_desc__:    [__val_eng__]    (__val_raw__)\n";

           feedLine.replace("__sig_desc__", canMsg->sigDescAt(sigIdx));
           feedLine.replace("__val_eng__", QString::number(canMsg->sigValAt(sigIdx, dataBytes)));
           feedLine.replace("__val_raw__", QString::asprintf("0x%X", canMsg->sigRawValAt(sigIdx, dataBytes)));

           BCanSig thisSig = canMsg->sigAt(sigIdx);
           feedLine.replace("__start_bit__", QString::number(thisSig.startbit));
           feedLine.replace("__num_bits__", QString::number(thisSig.num_bits));
       }
   }
   else
   {
       feedLine.replace("__msg_desc__", "NOT FOUND!");
       feedLine.replace("__signal_count__", "NOT FOUND!");
   }

   ui->txtFeed->append(feedLine);
}

void MainWindow::on_btnClose_clicked()
{
    qApp->closeAllWindows();
}

void MainWindow::on_btnClear_clicked()
{
    ui->boxMsgId->clear();

    ui->boxByte0->clear();
    ui->boxByte1->clear();
    ui->boxByte2->clear();
    ui->boxByte3->clear();
    ui->boxByte4->clear();
    ui->boxByte5->clear();
    ui->boxByte6->clear();
    ui->boxByte7->clear();

    ui->boxCRC->clear();

    ui->txtFeed->clear();

    ui->boxEasyPaste->clear();
}

void MainWindow::on_actionOpenDatabase_triggered()
{
    dbFilename = QFileDialog::getOpenFileName(this,
        tr("Open BELL CAN Messages Database"), ".", tr("BELL CAN Database XML(*.xml)"));

    ui->txtFeed->append(FEED_HEADER);
    ui->txtFeed->append("The user indicated intent to use database located");
    ui->txtFeed->append("at [" + dbFilename + "].");
}

void MainWindow::on_actionExit_triggered()
{
    qApp->closeAllWindows();
}
