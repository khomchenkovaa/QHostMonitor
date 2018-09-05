QT += network script multimedia sql

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/tNode.h \
    $$PWD/tView.h \
    $$PWD/tTest.h \
    $$PWD/tLink.h \
    $$PWD/tAgent.h \
    $$PWD/tSchedule.h \
    $$PWD/qcron/holiday.hpp \
    $$PWD/qcron/qcron.hpp \
    $$PWD/qcron/qcronfield.hpp \
    $$PWD/qcron/qcronnode.hpp \
    $$PWD/method/tTestMethod.h \
    $$PWD/method/tPing.h \
    $$PWD/method/tDriveSpace.h \
    $$PWD/method/tShellScript.h \
    $$PWD/method/tFolderSize.h \
    $$PWD/method/tFileExists.h \
    $$PWD/method/tSnmpGet.h \
    $$PWD/method/tExternalPrg.h \
    $$PWD/method/tOdbcQuery.h \
    $$PWD/method/tMySql.h \
    $$PWD/method/tPostgreSql.h \
    $$PWD/method/tOracle.h \
    $$PWD/global/tMethod.h \
    $$PWD/global/tAction.h \
    $$PWD/global/gUserVars.h \
    $$PWD/global/gProfiles.h \
    $$PWD/global/ioDataLoader.h \
    $$PWD/global/ioTestMethodLoader.h \
    $$PWD/global/ioUserVarsLoader.h \
    $$PWD/global/ioMailProfileLoader.h \
    $$PWD/global/ioColorProfileLoader.h \
    $$PWD/global/ioActionProfileLoader.h \
    $$PWD/global/gMacroTranslator.h \
    $$PWD/action/tTestAction.h \
    $$PWD/action/tWinPopupAction.h \
    $$PWD/action/tPlaySoundAction.h \
    $$PWD/action/tSendMessageToPagerTapAction.h \
    $$PWD/action/tSendMessageToPagerSnppAction.h \
    $$PWD/action/tSendMessageToBeeperAction.h \
    $$PWD/action/tSendSmsGsmModemAction.h \
    $$PWD/action/tSendSmsSmppAction.h \
    $$PWD/action/tSendEmailSmtpAction.h \
    $$PWD/action/tSendMessageToIcqAction.h \
    $$PWD/action/tSendMessageToJabberAction.h \
    $$PWD/action/tRecordSdpoLogAction.h \
    $$PWD/action/tGenerateReportsAction.h \
    $$PWD/action/tStopServiceAction.h \
    $$PWD/action/tStartServiceAction.h \
    $$PWD/action/tRestartServiceAction.h \
    $$PWD/action/tRebootRemoteSystemAction.h \
    $$PWD/options/pLogProperties.h \
    $$PWD/action/tRebootLocalMachineAction.h \
    $$PWD/action/tDialupToTheNetworkAction.h \
    $$PWD/action/tDisconnectDialupConnectionAction.h \
    $$PWD/action/tExecuteExternalProgramAction.h \
    $$PWD/action/tLogEventAction.h \
    $$PWD/action/tSqlQueryAction.h \
    $$PWD/action/tHttpRequestAction.h \
    $$PWD/action/tSendDataToTcpUdpPortAction.h \
    $$PWD/action/tSyslogAction.h \
    $$PWD/action/tSnmpSetAction.h \
    $$PWD/action/tSnmpTrapAction.h \
    $$PWD/action/tRepeatTestAction.h \
    $$PWD/action/tChangeTestIntervalAction.h \
    $$PWD/action/tRunHmsScriptAction.h \
    ../model/method/tInterbase.h \
    ../model/method/tActiveScript.h \
    ../model/method/tCompareFiles.h \
    ../model/method/tCountFiles.h \
    ../model/method/tCpuUsage.h \
    ../model/method/tDhcp.h \
    ../model/method/tDicom.h \
    ../model/tFolder.h \
    ../model/gData.h \
    ../model/tRoot.h \
    ../model/method/sdpoTestMethods.h \
    ../model/action/sdpoTestActions.h \
    ../model/global/ioUserProfileLoader.h \
    ../model/method/tDnsTest.h \
    ../model/method/tDominantProcess.h \
    ../model/method/tFileContents.h \
    ../model/method/tHttp.h \
    ../model/method/tImapTest.h

SOURCES += \
    $$PWD/tNode.cpp \
    $$PWD/tView.cpp \
    $$PWD/tTest.cpp \
    $$PWD/tLink.cpp \
    $$PWD/tAgent.cpp \
    $$PWD/tSchedule.cpp \
    $$PWD/qcron/holiday.cpp \
    $$PWD/qcron/qcron.cpp \
    $$PWD/qcron/qcronfield.cpp \
    $$PWD/qcron/qcronnode.cpp \
    $$PWD/method/tTestMethod.cpp \
    $$PWD/method/tPing.cpp \
    $$PWD/method/tDriveSpace.cpp \
    $$PWD/method/tShellScript.cpp \
    $$PWD/method/tFolderSize.cpp \
    $$PWD/method/tFileExists.cpp \
    $$PWD/method/tSnmpGet.cpp  \
    $$PWD/method/tExternalPrg.cpp \
    $$PWD/method/tOdbcQuery.cpp \
    $$PWD/method/tMySql.cpp \
    $$PWD/method/tPostgreSql.cpp \
    $$PWD/method/tOracle.cpp \
    $$PWD/global/ioDataLoader.cpp \
    $$PWD/global/tMethod.cpp \
    $$PWD/global/tAction.cpp \
    $$PWD/global/gUserVars.cpp \
    $$PWD/global/gProfiles.cpp \
    $$PWD/global/ioTestMethodLoader.cpp \
    $$PWD/global/ioUserVarsLoader.cpp \
    $$PWD/global/ioMailProfileLoader.cpp \
    $$PWD/global/ioColorProfileLoader.cpp \
    $$PWD/global/ioActionProfileLoader.cpp \
    $$PWD/global/gMacroTranslator.cpp \
    $$PWD/action/tTestAction.cpp \
    $$PWD/action/tWinPopupAction.cpp \
    $$PWD/action/tPlaySoundAction.cpp \
    $$PWD/action/tSendMessageToPagerTapAction.cpp \
    $$PWD/action/tSendMessageToPagerSnppAction.cpp \
    $$PWD/action/tSendMessageToBeeperAction.cpp \
    $$PWD/action/tSendSmsGsmModemAction.cpp \
    $$PWD/action/tSendSmsSmppAction.cpp \
    $$PWD/action/tSendEmailSmtpAction.cpp \
    $$PWD/action/tSendMessageToIcqAction.cpp \
    $$PWD/action/tSendMessageToJabberAction.cpp \
    $$PWD/action/tRecordSdpoLogAction.cpp \
    $$PWD/action/tGenerateReportsAction.cpp \
    $$PWD/action/tStopServiceAction.cpp \
    $$PWD/action/tStartServiceAction.cpp \
    $$PWD/action/tRestartServiceAction.cpp \
    $$PWD/action/tRebootRemoteSystemAction.cpp \
    $$PWD/options/pLogProperties.cpp \
    $$PWD/action/tRebootLocalMachineAction.cpp \
    $$PWD/action/tDialupToTheNetworkAction.cpp \
    $$PWD/action/tDisconnectDialupConnectionAction.cpp \
    $$PWD/action/tExecuteExternalProgramAction.cpp \
    $$PWD/action/tLogEventAction.cpp \
    $$PWD/action/tSqlQueryAction.cpp \
    $$PWD/action/tHttpRequestAction.cpp \
    $$PWD/action/tSendDataToTcpUdpPortAction.cpp \
    $$PWD/action/tSyslogAction.cpp \
    $$PWD/action/tSnmpSetAction.cpp \
    $$PWD/action/tSnmpTrapAction.cpp \
    $$PWD/action/tRepeatTestAction.cpp \
    $$PWD/action/tChangeTestIntervalAction.cpp \
    $$PWD/action/tRunHmsScriptAction.cpp \
    ../model/method/tInterbase.cpp \
    ../model/method/tActiveScript.cpp \
    ../model/method/tCompareFiles.cpp \
    ../model/method/tCountFiles.cpp \
    ../model/method/tCpuUsage.cpp \
    ../model/method/tDhcp.cpp \
    ../model/method/tDicom.cpp \
    ../model/tFolder.cpp \
    ../model/gData.cpp \
    ../model/tRoot.cpp \
    ../model/global/ioUserProfileLoader.cpp \
    ../model/method/tDnsTest.cpp \
    ../model/method/tDominantProcess.cpp \
    ../model/method/tFileContents.cpp \
    ../model/method/tHttp.cpp \
    ../model/method/tImapTest.cpp
