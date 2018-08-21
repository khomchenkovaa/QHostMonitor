#include "qOptionsForm.h"
#include "ui_qOptionsForm.h"

#include <QTreeWidgetItem>
#include "mSettings.h"
#include <QDebug>

namespace SDPO {

/******************************************************************/

OptionsForm::OptionsForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsForm)
{
    ui->setupUi(this);
    ui->optionsTree->setColumnHidden(1,true);
    connect(ui->wAccessMethod, SIGNAL(goToPage(int)), this, SLOT(setCurrentPage(int)));
    init();
}

/******************************************************************/

OptionsForm::~OptionsForm()
{
    delete ui;
}

/******************************************************************/

void OptionsForm::setCurrentPage(const int idx)
{
    ui->PageControl->setCurrentIndex(idx);
    selectOptionsTreeItem(idx);
}

/******************************************************************/

void OptionsForm::on_optionsTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // activate panel
    Q_UNUSED(previous);
    ui->PageControl->setCurrentIndex(current->text(1).toInt());
}

/******************************************************************/

void OptionsForm::on_backButton_clicked()
{
    // previous panel
    int curIdx = ui->PageControl->currentIndex();
    if(curIdx > 0) {
        ui->PageControl->setCurrentIndex(curIdx-1);
        selectOptionsTreeItem(curIdx-1);
    }
}

/******************************************************************/

void OptionsForm::on_nextButton_clicked()
{
    // next panel
    int curIdx = ui->PageControl->currentIndex();
    if(curIdx < (ui->PageControl->count()-1)) {
        ui->PageControl->setCurrentIndex(curIdx+1);
        selectOptionsTreeItem(curIdx+1);
    }
}

/******************************************************************/

void OptionsForm::on_PageControl_tabBarClicked(int index)
{
    // activate tree
    selectOptionsTreeItem(index);
}

/******************************************************************/

void OptionsForm::selectOptionsTreeItem(const int idx)
{
    QList<QTreeWidgetItem*> items = ui->optionsTree->findItems(QString().setNum(idx),Qt::MatchExactly,1);
    if(items.count() > 0) {
        ui->optionsTree->setCurrentItem(items.at(0));
        return;
    }
    if (idx==3) {
        items = ui->optionsTree->findItems(QString().setNum(2),Qt::MatchExactly,1);
        ui->optionsTree->setCurrentItem(items.at(0)->child(0));
    } else if (idx==5) {
        items = ui->optionsTree->findItems(QString().setNum(4),Qt::MatchExactly,1);
        ui->optionsTree->setCurrentItem(items.at(0)->child(0));
    } else if ((idx>6) & (idx<12)) {
        items = ui->optionsTree->findItems(QString().setNum(6),Qt::MatchExactly,1);
        ui->optionsTree->setCurrentItem(items.at(0)->child(idx-7));
    }

}

/******************************************************************/

void OptionsForm::on_FinishCancelHelpBtn_accepted()
{
    prepareToSave();
    Settings::save();
}

/******************************************************************/

void OptionsForm::init()
{
    ui->wPreferences->init();
    ui->wBehavior->init();
    ui->wStartupOptions->init();
    ui->wService->init();
    ui->wAccessMethod->init();
    ui->wProxy->init();
    ui->wPrimaryLog->init();
    ui->wBackupLog->init();
    ui->wSystemLog->init();
    ui->wLogProcessing->init();
    ui->wHtmlColors->init();
    ui->wViewers->init();
    ui->wReports->init();
    ui->wMsgWindow->init();
    ui->wMailerSettings->init();
    ui->wPagers->init();
    ui->wIcq->init();
    ui->wJabber->init();
    ui->wSmsGsm->init();
    ui->wSmsSmpp->init();
    ui->wPingTrace->init();
    ui->wRci->init();
    ui->wActiveRma->init();
    ui->wScheduler->init();
    ui->wMisc->init();
}

/******************************************************************/

void OptionsForm::prepareToSave()
{
    ui->wPreferences->prepareToSave();
    ui->wBehavior->prepareToSave();
    ui->wStartupOptions->prepareToSave();
    ui->wService->prepareToSave();
    ui->wAccessMethod->prepareToSave();
    ui->wProxy->prepareToSave();
    ui->wPrimaryLog->prepareToSave();
    ui->wBackupLog->prepareToSave();
    ui->wSystemLog->prepareToSave();
    ui->wLogProcessing->prepareToSave();
    ui->wHtmlColors->prepareToSave();
    ui->wViewers->prepareToSave();
    ui->wReports->prepareToSave();
    ui->wMsgWindow->prepareToSave();
    ui->wMailerSettings->prepareToSave();
    ui->wPagers->prepareToSave();
    ui->wIcq->prepareToSave();
    ui->wJabber->prepareToSave();
    ui->wSmsGsm->prepareToSave();
    ui->wSmsSmpp->prepareToSave();
    ui->wPingTrace->prepareToSave();
    ui->wRci->prepareToSave();
    ui->wActiveRma->prepareToSave();
    ui->wScheduler->prepareToSave();
    ui->wMisc->prepareToSave();
}

/******************************************************************/

} // namespace SDPO


