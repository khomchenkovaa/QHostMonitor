INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("../../service/io/io-snmp.pri")
include("../../views/snmpw/snmpw.pri")

HEADERS += \
    $$PWD/mainwindow.h

SOURCES += \
    $$PWD/mainwindow.cpp

