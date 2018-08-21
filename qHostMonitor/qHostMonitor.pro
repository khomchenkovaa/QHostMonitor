#-------------------------------------------------
#
# Project created by QtCreator 2012-08-25T14:26:54
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qHostMonitor
TEMPLATE = app

include("../common/common.pri")
include("../model/model.pri")
include("../service/service.pri")
include("../view/view.pri")

SOURCES += main.cpp\
     qMainForm.cpp \
     qAboutDlg.cpp \
     startup.cpp \
     qFolderDlg.cpp \
     qAckDlg.cpp \
     qTestListProperties.cpp \
     qExportToTxtDlg.cpp \
     qImportFromTxtFileDlg.cpp \
     qPauseMonitoringDlg.cpp \
     qTestPlannedPauseDlg.cpp \
     qTestHistoryChartsDlg.cpp \
     qMainInfoPaneWidget.cpp \
     qTestInfoDlg.cpp \
     qTestPauseDialog.cpp

HEADERS  += \
    qMainForm.h \
    qAboutDlg.h \
    startup.h \
    qFolderDlg.h \
    qAckDlg.h \
    qTestListProperties.h \
    qExportToTxtDlg.h \
    qImportFromTxtFileDlg.h \
    qPauseMonitoringDlg.h \
    qTestPlannedPauseDlg.h \
    qTestHistoryChartsDlg.h \
    qMainInfoPaneWidget.h \
    qTestInfoDlg.h \
    qTestPauseDialog.h

FORMS    += qMainForm.ui \
    qAboutDlg.ui \
    qFolderDlg.ui \
    qAckDlg.ui \
    qTestListProperties.ui \
    qExportToTxtDlg.ui \
    qImportFromTxtFileDlg.ui \
    qPauseMonitoringDlg.ui \
    qTestPlannedPauseDlg.ui \
    qTestHistoryChartsDlg.ui \
    qMainInfoPaneWidget.ui \
    qTestInfoDlg.ui \
    qTestPauseDialog.ui

RESOURCES += \
    ../qHostMonitor.qrc



