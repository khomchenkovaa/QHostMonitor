#ifndef SNMPOBJECTDEFAULTS_H
#define SNMPOBJECTDEFAULTS_H

#include "snmpobject.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QSpinBox;
class QDialogButtonBox;
QT_END_NAMESPACE

namespace KharmonView {

class SnmpObjectDefaults : public QDialog
{
    Q_OBJECT
public:
    explicit SnmpObjectDefaults(QWidget *parent = nullptr);

private slots:
    void onAccepted();

private:
    void setupUI();
    void init();
    void save();
    bool validate(QString *err);

private:
    QLineEdit *uiSystem;
    QLineEdit *uiSubsystem;
    QSpinBox  *uiDlgTimeout;
    QLineEdit *uiHost;
    QLineEdit *uiPort;
    QComboBox *uiVersion;
    QLineEdit *uiCommunity;
    QLineEdit *uiTimeout;
    QLineEdit *uiRetries;
};

} // namespace KharmonView

#endif // SNMPOBJECTDEFAULTS_H
