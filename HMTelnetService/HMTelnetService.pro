#-------------------------------------------------
#
# Project created by QtCreator 2019-03-04T15:22:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HMTelnetService
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += console

#include("../common/lib/qtservice/qtservice.pri")
include("../common/lib/qdaemon/qdaemon.pri")

SOURCES += \
        main.cpp \
        hmTelnetServiceDialog.cpp \
#    telnet/telnetConnection.cpp \
#    telnet/telnetServer.cpp \
#    telnet/telnetWorker.cpp \
#    hmTelnetInteractiveService.cpp \
    tcpserver/tcpsession.cpp \
    tcpserver/tcpserver.cpp

HEADERS += \
        hmTelnetServiceDialog.h \
#    telnet/telnetConnection.h \
#    telnet/telnetServer.h \
#    telnet/telnetWorker.h \
#    hmTelnetInteractiveService.h \
    tcpserver/tcpsession.h \
    tcpserver/tcpserver.h

FORMS += \
        hmTelnetServiceDialog.ui

