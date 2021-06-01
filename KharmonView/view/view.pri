INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("../../views/about/about.pri")

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/snmpclient.h \
    $$PWD/snmpobject.h \
    $$PWD/snmpobjectdefaults.h \
    $$PWD/snmpobjectedit.h \
    $$PWD/snmpobjectloader.h \
    $$PWD/snmpobjectmodel.h \
    $$PWD/snmpobjectwidget.h \
    $$PWD/snmpresultlog.h \
    $$PWD/snmpresultwidget.h

SOURCES += \
    $$PWD/mainwindow.cpp \
    $$PWD/snmpclient.cpp \
    $$PWD/snmpobject.cpp \
    $$PWD/snmpobjectdefaults.cpp \
    $$PWD/snmpobjectedit.cpp \
    $$PWD/snmpobjectloader.cpp \
    $$PWD/snmpobjectmodel.cpp \
    $$PWD/snmpobjectwidget.cpp \
    $$PWD/snmpresultlog.cpp \
    $$PWD/snmpresultwidget.cpp
