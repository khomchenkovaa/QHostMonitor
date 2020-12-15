#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T14:26:54
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MibBrowser
TEMPLATE = app

QMAKE_CXXFLAGS += -Wdeprecated
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x051000

CONFIG += c++11

include("../common/lib/net-snmp/net-snmp.pri")
include("view/view.pri")

HEADERS  += \
    startup.h

SOURCES += main.cpp \
    startup.cpp

RESOURCES += \
    ../qHostMonitor.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lnetsnmp



