INCLUDEPATH += $$PWD $$PWD/lib
DEPENDPATH += $$PWD $$PWD/lib

HEADERS += \
    $$PWD/tEnums.h \
    $$PWD/PropertyHelper.h \
    $$PWD/mSettings.h \
    $$PWD/utils.h \
    $$PWD/xMacroVar.h \
    $$PWD/gUnit.h \
    $$PWD/lib/qdbf/qdbf_compat.h \
    $$PWD/lib/qdbf/qdbffield.h \
    $$PWD/lib/qdbf/qdbf_global.h \
    $$PWD/lib/qdbf/qdbfrecord.h \
    $$PWD/lib/qdbf/qdbftable.h \
    $$PWD/lib/qdbf/qdbftablemodel.h

SOURCES += \
    $$PWD/mSettings.cpp \
    $$PWD/utils.cpp \
    $$PWD/tEnums.cpp \
    $$PWD/xMacroVar.cpp \
    $$PWD/gUnit.cpp \
    $$PWD/lib/qdbf/qdbffield.cpp \
    $$PWD/lib/qdbf/qdbfrecord.cpp \
    $$PWD/lib/qdbf/qdbftable.cpp \
    $$PWD/lib/qdbf/qdbftablemodel.cpp

