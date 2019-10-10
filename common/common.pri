INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("lib/qcron/qcron.pri")
include("lib/qdbf/qdbf.pri")
include("lib/qsimplecrypt/qsimplecrypt.pri")
include("lib/net-snmp/net-snmp.pri")
include("lib/libqxt/libqxt.pri")

HEADERS += \
    $$PWD/tEnums.h \
    $$PWD/PropertyHelper.h \
    $$PWD/gSettings.h \
    $$PWD/utils.h \
    $$PWD/xMacroVar.h \
    $$PWD/gUnitConverter.h

SOURCES += \
    $$PWD/utils.cpp \
    $$PWD/tEnums.cpp \
    $$PWD/xMacroVar.cpp \
    $$PWD/gUnitConverter.cpp

