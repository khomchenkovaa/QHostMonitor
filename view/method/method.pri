INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

include("../../views/snmpw/snmpw.pri")

HEADERS += \
    $$PWD/qTestWidget.h \
    $$PWD/qPingWidget.h \
    $$PWD/qTcpWidget.h \
    $$PWD/qUrlWidget.h \
    $$PWD/qUrlTestPropertiesDlg.h \
    $$PWD/qDriveSpaceWidget.h \
    $$PWD/qFileSizeWidget.h \
    $$PWD/qFileExistsWidget.h \
    $$PWD/qExternalPrgWidget.h \
    $$PWD/qSshWidget.h \
    $$PWD/qFileContentsWidget.h \
    $$PWD/qOracleWidget.h \
    $$PWD/qUncWidget.h \
    $$PWD/qInterbaseWidget.h \
    $$PWD/qMsSqlWidget.h \
    $$PWD/qMySqlWidget.h \
    $$PWD/qPostgreSqlWidget.h \
    $$PWD/qSybaseWidget.h \
    $$PWD/qProcessWidget.h \
    $$PWD/qServiceWidget.h \
    $$PWD/qServiceToMonitorDlg.h \
    $$PWD/qSnmpGetWidget.h \
    $$PWD/qNtEventLogWidget.h \
    $$PWD/qCpuUsageWidget.h \
    $$PWD/qCompareFilesWidget.h \
    $$PWD/qOdbcQueryWidget.h \
    $$PWD/qSmtpTestWidget.h \
    $$PWD/qOdbcQueryDlg.h \
    $$PWD/qPop3TestWidget.h \
    $$PWD/qImapTestWidget.h \
    $$PWD/qDnsTestWidget.h \
    $$PWD/qLdapTestWidget.h \
    $$PWD/qTraceTestWidget.h \
    $$PWD/qCountFilesWidget.h \
    $$PWD/qRasTestWidget.h \
    $$PWD/qPerformanceCounterWidget.h \
    $$PWD/qShellScriptWidget.h \
    $$PWD/qActiveScriptWidget.h \
    $$PWD/qUdpTestWidget.h \
    $$PWD/qNtpTestWidget.h \
    $$PWD/qRadiusWidget.h \
    $$PWD/qHttpWidget.h \
    $$PWD/qHttpTestPropertiesDlg.h \
    $$PWD/qHttpProxiesListDlg.h \
    $$PWD/qTextLogWidget.h \
    $$PWD/qTextLogPropertiesDlg.h \
    $$PWD/qTemperatureMonitorWidget.h \
    $$PWD/qTrafficMonitorWidget.h \
    $$PWD/qTrafficNetworkInterfaceDlg.h \
    $$PWD/qTrafficSnmpCredentialsDlg.h \
    $$PWD/qSnmpTrapWidget.h \
    $$PWD/qSnmpTrapFilterDlg.h \
    $$PWD/qWmiWidget.h \
    $$PWD/qMailRelayTestPropertiesDlg.h \
    $$PWD/qMailRelayWidget.h \
    $$PWD/qDicomWidget.h \
    $$PWD/qDominantProcessWidget.h \
    $$PWD/qDhcpWidget.h \
    $$PWD/qSdpoMonitorWidget.h

SOURCES += \
    $$PWD/qTestWidget.cpp \
    $$PWD/qPingWidget.cpp \
    $$PWD/qTcpWidget.cpp \
    $$PWD/qUrlWidget.cpp \
    $$PWD/qUrlTestPropertiesDlg.cpp \
    $$PWD/qDriveSpaceWidget.cpp \
    $$PWD/qFileSizeWidget.cpp \
    $$PWD/qFileExistsWidget.cpp \
    $$PWD/qExternalPrgWidget.cpp \
    $$PWD/qSshWidget.cpp \
    $$PWD/qFileContentsWidget.cpp \
    $$PWD/qOracleWidget.cpp \
    $$PWD/qUncWidget.cpp \
    $$PWD/qInterbaseWidget.cpp \
    $$PWD/qMsSqlWidget.cpp \
    $$PWD/qMySqlWidget.cpp \
    $$PWD/qPostgreSqlWidget.cpp \
    $$PWD/qSybaseWidget.cpp \
    $$PWD/qProcessWidget.cpp \
    $$PWD/qServiceWidget.cpp \
    $$PWD/qServiceToMonitorDlg.cpp \
    $$PWD/qSnmpGetWidget.cpp \
    $$PWD/qNtEventLogWidget.cpp \
    $$PWD/qCpuUsageWidget.cpp \
    $$PWD/qCompareFilesWidget.cpp \
    $$PWD/qOdbcQueryWidget.cpp \
    $$PWD/qSmtpTestWidget.cpp \
    $$PWD/qOdbcQueryDlg.cpp \
    $$PWD/qPop3TestWidget.cpp \
    $$PWD/qImapTestWidget.cpp \
    $$PWD/qDnsTestWidget.cpp \
    $$PWD/qLdapTestWidget.cpp \
    $$PWD/qTraceTestWidget.cpp \
    $$PWD/qCountFilesWidget.cpp \
    $$PWD/qRasTestWidget.cpp \
    $$PWD/qPerformanceCounterWidget.cpp \
    $$PWD/qShellScriptWidget.cpp \
    $$PWD/qActiveScriptWidget.cpp \
    $$PWD/qUdpTestWidget.cpp \
    $$PWD/qNtpTestWidget.cpp \
    $$PWD/qRadiusWidget.cpp \
    $$PWD/qHttpWidget.cpp \
    $$PWD/qHttpTestPropertiesDlg.cpp \
    $$PWD/qHttpProxiesListDlg.cpp \
    $$PWD/qTextLogWidget.cpp \
    $$PWD/qTextLogPropertiesDlg.cpp \
    $$PWD/qTemperatureMonitorWidget.cpp \
    $$PWD/qTrafficMonitorWidget.cpp \
    $$PWD/qTrafficNetworkInterfaceDlg.cpp \
    $$PWD/qTrafficSnmpCredentialsDlg.cpp \
    $$PWD/qSnmpTrapWidget.cpp \
    $$PWD/qSnmpTrapFilterDlg.cpp \
    $$PWD/qWmiWidget.cpp \
    $$PWD/qMailRelayTestPropertiesDlg.cpp \
    $$PWD/qMailRelayWidget.cpp \
    $$PWD/qDicomWidget.cpp \
    $$PWD/qDominantProcessWidget.cpp \
    $$PWD/qDhcpWidget.cpp \
    $$PWD/qSdpoMonitorWidget.cpp

FORMS    += \
    $$PWD/qPingWidget.ui \
    $$PWD/qTcpWidget.ui \
    $$PWD/qUrlWidget.ui \
    $$PWD/qUrlTestPropertiesDlg.ui\
    $$PWD/qDriveSpaceWidget.ui \
    $$PWD/qFileSizeWidget.ui \
    $$PWD/qFileExistsWidget.ui \
    $$PWD/qExternalPrgWidget.ui \
    $$PWD/qSshWidget.ui \
    $$PWD/qFileContentsWidget.ui \
    $$PWD/qOracleWidget.ui \
    $$PWD/qUncWidget.ui \
    $$PWD/qInterbaseWidget.ui \
    $$PWD/qMsSqlWidget.ui \
    $$PWD/qMySqlWidget.ui \
    $$PWD/qPostgreSqlWidget.ui \
    $$PWD/qSybaseWidget.ui \
    $$PWD/qProcessWidget.ui \
    $$PWD/qServiceWidget.ui \
    $$PWD/qServiceToMonitorDlg.ui \
    $$PWD/qSnmpGetWidget.ui \
    $$PWD/qNtEventLogWidget.ui \
    $$PWD/qCpuUsageWidget.ui \
    $$PWD/qCompareFilesWidget.ui \
    $$PWD/qOdbcQueryWidget.ui \
    $$PWD/qSmtpTestWidget.ui \
    $$PWD/qOdbcQueryDlg.ui \
    $$PWD/qPop3TestWidget.ui \
    $$PWD/qImapTestWidget.ui \
    $$PWD/qDnsTestWidget.ui \
    $$PWD/qLdapTestWidget.ui \
    $$PWD/qTraceTestWidget.ui \
    $$PWD/qCountFilesWidget.ui \
    $$PWD/qRasTestWidget.ui \
    $$PWD/qPerformanceCounterWidget.ui \
    $$PWD/qShellScriptWidget.ui \
    $$PWD/qActiveScriptWidget.ui \
    $$PWD/qUdpTestWidget.ui \
    $$PWD/qNtpTestWidget.ui \
    $$PWD/qRadiusWidget.ui \
    $$PWD/qHttpWidget.ui \
    $$PWD/qHttpTestPropertiesDlg.ui \
    $$PWD/qHttpProxiesListDlg.ui \
    $$PWD/qTextLogWidget.ui \
    $$PWD/qTextLogPropertiesDlg.ui \
    $$PWD/qTemperatureMonitorWidget.ui \
    $$PWD/qTrafficMonitorWidget.ui \
    $$PWD/qTrafficNetworkInterfaceDlg.ui \
    $$PWD/qTrafficSnmpCredentialsDlg.ui \
    $$PWD/qSnmpTrapWidget.ui \
    $$PWD/qSnmpTrapFilterDlg.ui \
    $$PWD/qWmiWidget.ui \
    $$PWD/qMailRelayTestPropertiesDlg.ui \
    $$PWD/qMailRelayWidget.ui \
    $$PWD/qDicomWidget.ui \
    $$PWD/qDominantProcessWidget.ui \
    $$PWD/qDhcpWidget.ui \
    $$PWD/qSdpoMonitorWidget.ui
