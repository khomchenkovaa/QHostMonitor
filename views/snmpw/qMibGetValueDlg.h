#ifndef QMIBGETVALUEDLG_H
#define QMIBGETVALUEDLG_H

#include "netsnmpsession.h"

#include <QDialog>

#define CMD_SNMP_SYS_INFO  "cmdSysInfo"
#define CMD_SNMP_GET_VALUE "cmdGetValue"
#define CMD_SNMP_BULK_GET  "cmdBulkGet"
#define CMD_SNMP_GET_ROW   "cmdGetRow"
#define CMD_SNMP_GET_NEXT  "cmdGetNext"
#define CMD_SNMP_SET_VALUE "cmdSetValue"

namespace Ui {
class QMibGetValueDlg;
}

namespace SDPO {

class QMibGetValueDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QMibGetValueDlg(QWidget *parent = nullptr);
    ~QMibGetValueDlg();

    void setOid(const QString& oid);
    void runCmd(const QString& cmd = QString());

private slots:
    void cmdSysInfo();
    void cmdGetValue();
    void cmdBulkGet();
    void cmdGetRow();
    void cmdGetNext();
    void cmdSetValue();
    void openSnmpCredentialsDlg();

private:
    void setupUI();

private:
    Ui::QMibGetValueDlg *ui;
    NetSnmpSession ss;
};

} // namespace SDPO

#endif // QMIBGETVALUEDLG_H
