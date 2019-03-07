INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += core
QT += dbus

SOURCES += \
    $$PWD/qdaemonapplication.cpp \
    $$PWD/qdaemonlog.cpp \
    $$PWD/qdaemonlog_p.cpp \
    $$PWD/qdaemonapplication_p.cpp \
    $$PWD/qabstractdaemonbackend.cpp \
    $$PWD/controllerbackend_linux.cpp \
    $$PWD/daemonbackend_linux.cpp

HEADERS += \
    $$PWD/qdaemonapplication.h \
    $$PWD/qdaemonlog.h \
    $$PWD/qdaemonapplication_p.h \
    $$PWD/qdaemonlog_p.h \
    $$PWD/qabstractdaemonbackend.h \
    $$PWD/controllerbackend_linux.h \
    $$PWD/daemonbackend_linux.h

RESOURCES += $$PWD/qdaemon.qrc

DISTFILES += \
        $$PWD/resources/init \
        $$PWD/resources/dbus

