QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KharmonView
TEMPLATE = app

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include("../common/lib/net-snmp/net-snmp.pri")
include("view/view.pri")

HEADERS += \
    startup.h

SOURCES += \
    main.cpp \
    startup.cpp

RESOURCES += \
    ../KharmonView.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lnetsnmp
