#include "snmpobjectdefaults.h"

#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

using namespace KharmonView;

/*************************************************************/

SnmpObjectDefaults::SnmpObjectDefaults(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    init();
}

/*************************************************************/

void SnmpObjectDefaults::onAccepted()
{
    QString err;
    if (!validate(&err)) {
        QMessageBox::critical(this, "Ошибка создания записи", err);
        return;
    }
    save();
    accept();
}

/*************************************************************/

void SnmpObjectDefaults::setupUI()
{

}

/*************************************************************/

void SnmpObjectDefaults::init()
{

}

/*************************************************************/

void SnmpObjectDefaults::save()
{

}

/*************************************************************/

bool SnmpObjectDefaults::validate(QString *err)
{
    return true;
}

/*************************************************************/

