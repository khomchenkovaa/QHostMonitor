#include "qRegionalPropertiesWidget.h"
#include "ui_qRegionalPropertiesWidget.h"
#include "tFolder.h"

#include <QTimeZone>

namespace SDPO {

/******************************************************************/

RegionalPropertiesWidget::RegionalPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegionalPropertiesWidget)
{
    ui->setupUi(this);
    QList<QByteArray> ids = QTimeZone::availableTimeZoneIds();
    foreach (QByteArray id, ids) {
        ui->cmbGmtOffset->addItem(QString(id));
    }
}

/******************************************************************/

RegionalPropertiesWidget::~RegionalPropertiesWidget()
{
    delete ui;
}

/******************************************************************/

void RegionalPropertiesWidget::init(TNode *node)
{
    if (!node) {
        reset();
        return;
    }
    if (node->getType() != TNode::FOLDER) {
        reset();
        return;
    }
    TFolder *folder = qobject_cast<TFolder*>(node);
    if (folder->isRootFolder()) {
        ui->rbUseOwnRegionalSettings->setChecked(true);
        ui->rbUseInheritable->setDisabled(true);
        ui->rbUseOwnRegionalSettings->setDisabled(true);
    } else {
        if (folder->isUseOwnRegionalSettings()) {
            ui->rbUseOwnRegionalSettings->setChecked(true);
        } else {
            ui->rbUseInheritable->setChecked(true);
        }
    }
    ui->chkApplyToGui->setChecked(folder->isApplyRemoteTimeToGui());
    ui->chkApplyToSchedules->setChecked(folder->isApplyRemoteTimeToSchedules());
    ui->cmbGmtOffset->setCurrentText(folder->getTimeZoneIanaId());
}

/******************************************************************/

void RegionalPropertiesWidget::save(TNode *node)
{
    if (!node) {
        return;
    }
    if (node->getType() != TNode::FOLDER) {
        return;
    }
    TFolder *folder = qobject_cast<TFolder*>(node);
    folder->setUseOwnRegionalSettings(ui->rbUseOwnRegionalSettings->isChecked());
    folder->setApplyRemoteTimeToGui(ui->chkApplyToGui->isChecked());
    folder->setApplyRemoteTimeToSchedules(ui->chkApplyToSchedules->isChecked());
    folder->setTimeZoneIanaId(ui->cmbGmtOffset->currentText());
}

/******************************************************************/

void RegionalPropertiesWidget::reset()
{
    ui->rbUseInheritable->setChecked(true);
    ui->rbUseInheritable->setDisabled(true);
    ui->rbUseOwnRegionalSettings->setDisabled(true);
    ui->chkApplyToGui->setChecked(false);
    ui->chkApplyToSchedules->setChecked(false);
}

/******************************************************************/

void RegionalPropertiesWidget::on_rbUseOwnRegionalSettings_toggled(bool checked)
{
    ui->chkApplyToGui->setEnabled(checked);
    ui->chkApplyToSchedules->setEnabled(checked);
    ui->cmbGmtOffset->setEnabled(checked);
}

/******************************************************************/

} // namespace SDPO

