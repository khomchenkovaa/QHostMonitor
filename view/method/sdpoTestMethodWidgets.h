#ifndef SDPOTESTMETHODWIDGETS_H
#define SDPOTESTMETHODWIDGETS_H

#include "qActiveScriptWidget.h"
#include "qCompareFilesWidget.h"
#include "qCountFilesWidget.h"
#include "qCpuUsageWidget.h"
#include "qDhcpWidget.h"
#include "qDicomWidget.h"
#include "qDnsTestWidget.h"
#include "qDominantProcessWidget.h"
#include "qDriveSpaceWidget.h"
#include "qExternalPrgWidget.h"
#include "qFileContentsWidget.h"
#include "qFileExistsWidget.h"
#include "qFileSizeWidget.h"
#include "qHttpWidget.h"
#include "qImapTestWidget.h"
#include "qInterbaseWidget.h"
#include "qLdapTestWidget.h"
#include "qMailRelayWidget.h"
#include "qMsSqlWidget.h"
#include "qMySqlWidget.h"
#include "qNtEventLogWidget.h"
#include "qNtpTestWidget.h"
#include "qOdbcQueryWidget.h"
#include "qOracleWidget.h"
#include "qPerformanceCounterWidget.h"
#include "qPingWidget.h"
#include "qPop3TestWidget.h"
#include "qPostgreSqlWidget.h"
#include "qProcessWidget.h"
#include "qRadiusWidget.h"
#include "qRasTestWidget.h"
#include "qSdpoMonitorWidget.h"
#include "qServiceWidget.h"
#include "qShellScriptWidget.h"
#include "qSmtpTestWidget.h"
#include "qSnmpGetWidget.h"
#include "qSnmpTrapWidget.h"
#include "qSshWidget.h"
#include "qSybaseWidget.h"
#include "qTcpWidget.h"
#include "qTemperatureMonitorWidget.h"
#include "qTextLogWidget.h"
#include "qTraceTestWidget.h"
#include "qTrafficMonitorWidget.h"
#include "qUdpTestWidget.h"
#include "qUncWidget.h"
#include "qUrlWidget.h"
#include "qWmiWidget.h"

#include "testmethod.h"

#include <QStackedWidget>
#include <QComboBox>

namespace SDPO {

class TestMethodUiHelper {
public:
    static void fillComboBox(QComboBox *box) {
        foreach(const TestMethodMetaInfo &meta, TestMethod::metaInfo) {
            box->addItem(QIcon(meta.icon), meta.text, static_cast<int>(meta.id));
        }
        box->setCurrentIndex(0);
    }

    static void fillStackedWidget(QStackedWidget *box) {
        box->addWidget(new PingWidget);
        box->addWidget(new TcpWidget);
        box->addWidget(new UrlWidget);
        box->addWidget(new DriveSpaceWidget);
        box->addWidget(new FileSizeWidget);
        box->addWidget(new FileExistsWidget);
        box->addWidget(new ExternalPrgWidget);
        box->addWidget(new SshWidget);
        box->addWidget(new FileContentsWidget);
        box->addWidget(new OracleWidget);
        box->addWidget(new UncWidget);
        box->addWidget(new InterbaseWidget);
        box->addWidget(new MsSqlWidget);
        box->addWidget(new MySqlWidget);
        box->addWidget(new PostgreSqlWidget);
        box->addWidget(new SybaseWidget);
        box->addWidget(new ProcessWidget);
        box->addWidget(new ServiceWidget);
        box->addWidget(new SnmpGetWidget);
        box->addWidget(new NtEventLogWidget);
        box->addWidget(new CpuUsageWidget);
        box->addWidget(new CompareFilesWidget);
        box->addWidget(new OdbcQueryWidget);
        box->addWidget(new SmtpTestWidget);
        box->addWidget(new Pop3TestWidget);
        box->addWidget(new ImapTestWidget);
        box->addWidget(new DnsTestWidget);
        box->addWidget(new LdapTestWidget);
        box->addWidget(new TraceTestWidget);
        box->addWidget(new CountFilesWidget);
        box->addWidget(new RasTestWidget);
        box->addWidget(new PerformanceCounterWidget);
        box->addWidget(new ActiveScriptWidget);
        box->addWidget(new UdpTestWidget);
        box->addWidget(new NtpTestWidget);
        box->addWidget(new RadiusWidget);
        box->addWidget(new HttpWidget);
        box->addWidget(new TextLogWidget);
        box->addWidget(new ShellScriptWidget);
        box->addWidget(new TemperatureMonitorWidget);
        box->addWidget(new TrafficMonitorWidget);
        box->addWidget(new SnmpTrapWidget);
        box->addWidget(new WmiWidget);
        box->addWidget(new MailRelayWidget);
        box->addWidget(new DicomWidget);
        box->addWidget(new DominantProcessWidget);
        box->addWidget(new DhcpWidget);
        box->addWidget(new SdpoMonitorWidget);
        box->setCurrentIndex(0);
    }

};

}

#endif // SDPOTESTMETHODWIDGETS_H
