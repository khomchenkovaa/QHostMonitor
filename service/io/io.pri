INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("method/method.pri")

HEADERS += \
    $$PWD/ioConnectionLoader.h \
    $$PWD/ioDataLoader.h \
    $$PWD/ioTestMethodLoader.h \
    $$PWD/ioUserVarsLoader.h \
    $$PWD/ioMailProfileLoader.h \
    $$PWD/ioColorProfileLoader.h \
    $$PWD/ioActionProfileLoader.h \
    $$PWD/ioUserProfileLoader.h \
    $$PWD/ioHelper.h \
    $$PWD/ioTextFile.h \
    $$PWD/ioHMList.h

SOURCES += \
    $$PWD/ioConnectionLoader.cpp \
    $$PWD/ioDataLoader.cpp \
    $$PWD/ioTestMethodLoader.cpp \
    $$PWD/ioUserVarsLoader.cpp \
    $$PWD/ioMailProfileLoader.cpp \
    $$PWD/ioColorProfileLoader.cpp \
    $$PWD/ioActionProfileLoader.cpp \
    $$PWD/ioUserProfileLoader.cpp \
    $$PWD/ioHelper.cpp \
    $$PWD/ioTextFile.cpp \
    $$PWD/ioHMList.cpp
