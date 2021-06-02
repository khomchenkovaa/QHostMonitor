#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T14:26:54
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HmlManager
TEMPLATE = app

include("../common/common.pri")
include("../model/model.pri")
include("../view/view.pri")

SOURCES += main.cpp \
    qAboutDlg.cpp \
    startup.cpp \
    qHmlMain.cpp

HEADERS  += \
    qAboutDlg.h \
    startup.h \
    qHmlMain.h

FORMS    += \
    qAboutDlg.ui \
    qHmlMain.ui

RESOURCES += \
    ../qHostMonitor.qrc



