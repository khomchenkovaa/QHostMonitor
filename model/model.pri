QT += network script multimedia sql

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/tNode.h \
    $$PWD/tView.h \
    $$PWD/tTest.h \
    $$PWD/tLink.h \
    $$PWD/tFolder.h \
    $$PWD/tRoot.h \
    $$PWD/tAgent.h \
    $$PWD/tSchedule.h \
    $$PWD/gData.h \
    $$PWD/global/tMethod.h \
    $$PWD/global/tAction.h \
    $$PWD/global/gUserVars.h \
    $$PWD/global/gProfiles.h \
    $$PWD/global/gMacroTranslator.h \
    $$PWD/method/sdpoTestMethods.h \
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
    $$PWD/method/tInterbase.h \
    $$PWD/method/tActiveScript.h \
    $$PWD/method/tCompareFiles.h \
    $$PWD/method/tCountFiles.h \
    $$PWD/method/tCpuUsage.h \
    $$PWD/method/tDhcp.h \
    $$PWD/method/tDicom.h \
    $$PWD/method/tDnsTest.h \
    $$PWD/method/tDominantProcess.h \
    $$PWD/method/tFileContents.h \
    $$PWD/method/tHttp.h \
    $$PWD/method/tImapTest.h \
    $$PWD/method/tLdapTest.h \
    $$PWD/method/tMailRelay.h \
    $$PWD/method/tMsSql.h \
    $$PWD/method/tNtEventLog.h \
    $$PWD/method/tSybase.h \
    $$PWD/action/sdpoTestActions.h \
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
    $$PWD/method/tNtpTest.h \
    $$PWD/options/pLogProperties.h \
    ../model/method/tPerformanceCounter.h


SOURCES += \
    $$PWD/tNode.cpp \
    $$PWD/tView.cpp \
    $$PWD/tTest.cpp \
    $$PWD/tLink.cpp \
    $$PWD/tFolder.cpp \
    $$PWD/tRoot.cpp \
    $$PWD/tAgent.cpp \
    $$PWD/tSchedule.cpp \
    $$PWD/gData.cpp \
    $$PWD/global/tMethod.cpp \
    $$PWD/global/tAction.cpp \
    $$PWD/global/gUserVars.cpp \
    $$PWD/global/gProfiles.cpp \
    $$PWD/global/gMacroTranslator.cpp \
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
    $$PWD/method/tInterbase.cpp \
    $$PWD/method/tActiveScript.cpp \
    $$PWD/method/tCompareFiles.cpp \
    $$PWD/method/tCountFiles.cpp \
    $$PWD/method/tCpuUsage.cpp \
    $$PWD/method/tDhcp.cpp \
    $$PWD/method/tDicom.cpp \
    $$PWD/method/tDnsTest.cpp \
    $$PWD/method/tDominantProcess.cpp \
    $$PWD/method/tFileContents.cpp \
    $$PWD/method/tHttp.cpp \
    $$PWD/method/tImapTest.cpp \
    $$PWD/method/tLdapTest.cpp \
    $$PWD/method/tMailRelay.cpp \
    $$PWD/method/tMsSql.cpp \
    $$PWD/method/tNtEventLog.cpp \
    $$PWD/method/tSybase.cpp \
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
    $$PWD/method/tNtpTest.cpp\
    $$PWD/options/pLogProperties.cpp \
    ../model/method/tPerformanceCounter.cpp

