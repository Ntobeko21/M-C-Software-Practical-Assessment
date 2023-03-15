QT       += xml
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    BXmlCanDbReader.cpp \
    BCanMsgsDb.cpp \
    BCanSig.cpp \
    BCanMsg.cpp \
    mainwindow.cpp \
    crc8.cpp \
    SharedFunctions.cpp

HEADERS += \
    BXmlCanDbReader.h \
    BCanMsgsDb.h \
    BCanSig.h \
    BCanMsg.h \
    mainwindow.h \
    crc8.h \
    SharedFunctions.h

OTHER_FILES += \
    bellDatabase.xml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui
