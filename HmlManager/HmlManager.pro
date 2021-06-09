#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T14:26:54
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HmlManager
TEMPLATE = app

CONFIG += c++11

include("../common/common.pri")
include("../model/model.pri")
include("../service/service.pri")
include("../view/view.pri")

SOURCES += main.cpp \
    startup.cpp \
    qHmlMain.cpp

HEADERS  += \
    startup.h \
    qHmlMain.h

FORMS    += \
    qHmlMain.ui

RESOURCES += \
    ../qHostMonitor.qrc


