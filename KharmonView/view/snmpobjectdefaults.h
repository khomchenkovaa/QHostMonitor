#ifndef SNMPOBJECTDEFAULTS_H
#define SNMPOBJECTDEFAULTS_H

#include "snmpobject.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
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

};

} // namespace KharmonView

#endif // SNMPOBJECTDEFAULTS_H
