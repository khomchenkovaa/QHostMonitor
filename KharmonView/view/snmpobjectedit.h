#ifndef SNMPOBJECTEDIT_H
#define SNMPOBJECTEDIT_H

#include "snmpobject.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QDialogButtonBox;
QT_END_NAMESPACE

namespace KharmonView {

class SnmpObjectEdit : public QDialog
{
    Q_OBJECT
public:
    explicit SnmpObjectEdit(SnmpObject *item = Q_NULLPTR, QWidget *parent = nullptr);

    SnmpObject *getObject();

private slots:
    void onAccepted();
    void onNameChanged(const QString &text);

private:
    void setupUI();
    void init();
    void save();
    bool validate(QString *err);

private:
    SnmpObject *m_Item;
    // ui
    QLineEdit *uiName;
    QLineEdit *uiHost;
    QLineEdit *uiModule;
    QLineEdit *uiPort;
    QComboBox *uiVersion;
    QLineEdit *uiCommunity;
    QLineEdit *uiTimeout;
    QLineEdit *uiRetries;
};

} // namespace KharmonView

#endif // SNMPOBJECTEDIT_H
