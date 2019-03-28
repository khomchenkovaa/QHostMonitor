QT += network script multimedia sql

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("global/global.pri")
include("method/method.pri")
include("action/action.pri")
include("options/options.pri")

HEADERS += \
    $$PWD/tNode.h \
    $$PWD/tView.h \
    $$PWD/tTest.h \
    $$PWD/tLink.h \
    $$PWD/tFolder.h \
    $$PWD/tRoot.h \
    $$PWD/tAgent.h \
    $$PWD/tSchedule.h \
    $$PWD/gData.h

SOURCES += \
    $$PWD/tNode.cpp \
    $$PWD/tView.cpp \
    $$PWD/tTest.cpp \
    $$PWD/tLink.cpp \
    $$PWD/tFolder.cpp \
    $$PWD/tRoot.cpp \
    $$PWD/tAgent.cpp \
    $$PWD/tSchedule.cpp \
    $$PWD/gData.cpp

