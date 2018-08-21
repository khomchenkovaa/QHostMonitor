#include "qAlertsEditWidget.h"
#include "ui_qAlertsEditWidget.h"
#include "tTest.h"
#include "gData.h"
#include "qActionProfiles.h"
#include "global/ioActionProfileLoader.h"
#include "QtWidgets"

namespace SDPO {

/******************************************************************/

AlertsEditWidget::AlertsEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlertsEditWidget)
{
    ui->setupUi(this);
    m_headers << "'Dead' actions" << "'Alive' actions";
}

/******************************************************************/

AlertsEditWidget::~AlertsEditWidget()
{
    delete ui;
}

/******************************************************************/

void AlertsEditWidget::init(TTest *item)
{
    reset();
    ui->cmbActionProfile->setCurrentIndex(item->getAlertProfileID());
}

/******************************************************************/

void AlertsEditWidget::save(TTest *item)
{
    item->setAlertProfileID(ui->cmbActionProfile->currentIndex());
}

/******************************************************************/

void AlertsEditWidget::reset()
{
    ui->cmbActionProfile->clear();
    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbActionProfile->addItem(profile.name);
    }
    ui->trvAlertProfile->clear();
    ui->trvAlertProfile->setHeaderLabels(m_headers);
}

/******************************************************************/

void AlertsEditWidget::on_cmbActionProfile_currentIndexChanged(int index)
{
    ui->trvAlertProfile->clear();

    if (index < 0 || index >= GData::actionProfiles.count()) {
        return;
    }

    GActionProfile curProfile = GData::actionProfiles.at(index);

    int rowCount = qMax (curProfile.onBad.count(), curProfile.onGood.count());
    if (rowCount) {
        QList<QTreeWidgetItem *> items;
        for (int i=0; i < rowCount; ++i) {
            QStringList names;
            if (i < curProfile.onBad.count()) {
                names << curProfile.onBad.at(i)->getName();
            } else {
                names << QString();
            }
            if (i < curProfile.onGood.count()) {
                names << curProfile.onGood.at(i)->getName();
            } else {
                names << QString();
            }
            items.append(new QTreeWidgetItem(names));
        }
        ui->trvAlertProfile->insertTopLevelItems(0,items);
    }
}

/******************************************************************/

void AlertsEditWidget::on_btnActionProfiles_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbActionProfile->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset();
        ui->cmbActionProfile->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

} // namespace SDPO

