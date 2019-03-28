QT += network script multimedia sql

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("io/io.pri")
include("logger/logger.pri")
include("servers/servers.pri")

HEADERS += \
    $$PWD/monitoringTask.h \
    $$PWD/actionTask.h \
    $$PWD/manageableService.h \
    $$PWD/monitoringService.h \
    $$PWD/actionService.h \
    $$PWD/hmListService.h \
    $$PWD/hmScriptRunner.h \
    $$PWD/logService.h

SOURCES += \
    $$PWD/monitoringTask.cpp \
    $$PWD/actionTask.cpp \
    $$PWD/manageableService.cpp \
    $$PWD/monitoringService.cpp \
    $$PWD/actionService.cpp \
    $$PWD/hmListService.cpp \
    $$PWD/hmScriptRunner.cpp \
    $$PWD/logService.cpp
