#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T14:26:54
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KharmonMonitor
TEMPLATE = app

QMAKE_CXXFLAGS += -Wdeprecated
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x051000

CONFIG += c++11

include("../common/lib/modeltest/modeltest.pri")

include("../common/common.pri")
include("../model/model.pri")
include("../service/service.pri")
include("../view/view.pri")

HEADERS  += \
    qAckDlg.h \
    qExportToTxtDlg.h \
    qFolderDlg.h \
    qImportFromTxtFileDlg.h \
    qLocalSystemInfoDlg.h \
    qMainForm.h \
    qMainInfoPaneWidget.h \
    qPauseMonitoringDlg.h \
    qTestHistoryChartsDlg.h \
    qTestInfoDlg.h \
    qTestListProperties.h \
    qTestPauseDialog.h \
    qTestPlannedPauseDlg.h \
    startup.h

SOURCES += main.cpp \
    qAckDlg.cpp \
    qExportToTxtDlg.cpp \
    qFolderDlg.cpp \
    qImportFromTxtFileDlg.cpp \
    qLocalSystemInfoDlg.cpp \
    qMainForm.cpp \
    qMainInfoPaneWidget.cpp \
    qPauseMonitoringDlg.cpp \
    qTestHistoryChartsDlg.cpp \
    qTestInfoDlg.cpp \
    qTestListProperties.cpp \
    qTestPauseDialog.cpp \
    qTestPlannedPauseDlg.cpp \
    startup.cpp

FORMS    += \
    qAckDlg.ui \
    qExportToTxtDlg.ui \
    qFolderDlg.ui \
    qImportFromTxtFileDlg.ui \
    qLocalSystemInfoDlg.ui \
    qMainForm.ui \
    qMainInfoPaneWidget.ui \
    qPauseMonitoringDlg.ui \
    qTestHistoryChartsDlg.ui \
    qTestInfoDlg.ui \
    qTestListProperties.ui \
    qTestPauseDialog.ui \
    qTestPlannedPauseDlg.ui

RESOURCES += \
    ../qHostMonitor.qrc

LIBS += -lnetsnmp



