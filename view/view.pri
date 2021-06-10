QT += sql

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("action/action.pri")
include("method/method.pri")
include("options/options.pri")
include("properties/properties.pri")
include("testedit/testedit.pri")
include("viewmodel/viewmodel.pri")
include("../views/about/about.pri")

HEADERS += \
    $$PWD/hostmondlg.h \
    $$PWD/qFolderDlg.h \
    $$PWD/qOptionsForm.h \
    $$PWD/qLinksList.h \
    $$PWD/qActionProfiles.h \
    $$PWD/qActionProfilesAddMenu.h \
    $$PWD/qActionPropertiesDialog.h \
    $$PWD/hIOShellScripts.h \
    $$PWD/qShellMng.h \
    $$PWD/qMacroEditorDlg.h \
    $$PWD/qGlobalUserVariables.h \
    $$PWD/qConnectionManagerDlg.h \
    $$PWD/qUserPreferencesDlg.h \
    $$PWD/qOperatorsDlg.h \
    $$PWD/qLoginAsDlg.h \
    $$PWD/qMacroEditorScriptRunnerDlg.h \
    $$PWD/qActionPopupEvent.h \
    $$PWD/qMailProfilesDlg.h \
    $$PWD/qReportProfilesDlg.h \
    $$PWD/qPalettesWin.h \
    $$PWD/qPatternsDlg.h \
    $$PWD/qDynamicViewPropertiesDlg.h \
    $$PWD/qFolderPropertiesDlg.h \
    $$PWD/qFolderPropertiesStatisticWidget.h \
    $$PWD/qDynamicViewReportsWidget.h \
    $$PWD/qUserPreferencesCopyDlg.h \
    $$PWD/qCommonViewPropertiesDlg.h

SOURCES += \
    $$PWD/hostmondlg.cpp \
    $$PWD/qFolderDlg.cpp \
    $$PWD/qOptionsForm.cpp \
    $$PWD/qLinksList.cpp \
    $$PWD/qActionProfiles.cpp \
    $$PWD/qActionProfilesAddMenu.cpp \
    $$PWD/qActionPropertiesDialog.cpp \
    $$PWD/hIOShellScripts.cpp \
    $$PWD/qShellMng.cpp \
    $$PWD/qMacroEditorDlg.cpp \
    $$PWD/qGlobalUserVariables.cpp \
    $$PWD/qConnectionManagerDlg.cpp \
    $$PWD/qUserPreferencesDlg.cpp \
    $$PWD/qOperatorsDlg.cpp \
    $$PWD/qLoginAsDlg.cpp \
    $$PWD/qMacroEditorScriptRunnerDlg.cpp \
    $$PWD/qActionPopupEvent.cpp \
    $$PWD/qMailProfilesDlg.cpp \
    $$PWD/qReportProfilesDlg.cpp \
    $$PWD/qPalettesWin.cpp \
    $$PWD/qPatternsDlg.cpp \
    $$PWD/qDynamicViewPropertiesDlg.cpp \
    $$PWD/qFolderPropertiesDlg.cpp \
    $$PWD/qFolderPropertiesStatisticWidget.cpp \
    $$PWD/qDynamicViewReportsWidget.cpp \
    $$PWD/qUserPreferencesCopyDlg.cpp \
    $$PWD/qCommonViewPropertiesDlg.cpp

FORMS    += \
    $$PWD/hostmondlg.ui \
    $$PWD/qFolderDlg.ui \
    $$PWD/qOptionsForm.ui \
    $$PWD/qLinksList.ui \
    $$PWD/qActionProfiles.ui \
    $$PWD/qActionProfilesAddMenu.ui \
    $$PWD/qActionPropertiesDialog.ui \
    $$PWD/qShellMng.ui \
    $$PWD/qMacroEditorDlg.ui \
    $$PWD/qGlobalUserVariables.ui \
    $$PWD/qConnectionManagerDlg.ui \
    $$PWD/qUserPreferencesDlg.ui \
    $$PWD/qOperatorsDlg.ui \
    $$PWD/qLoginAsDlg.ui \
    $$PWD/qMacroEditorScriptRunnerDlg.ui \
    $$PWD/qActionPopupEvent.ui \
    $$PWD/qMailProfilesDlg.ui \
    $$PWD/qReportProfilesDlg.ui \
    $$PWD/qPalettesWin.ui \
    $$PWD/qPatternsDlg.ui \
    $$PWD/qDynamicViewPropertiesDlg.ui \
    $$PWD/qFolderPropertiesDlg.ui \
    $$PWD/qFolderPropertiesStatisticWidget.ui \
    $$PWD/qDynamicViewReportsWidget.ui \
    $$PWD/qUserPreferencesCopyDlg.ui \
    $$PWD/qCommonViewPropertiesDlg.ui



