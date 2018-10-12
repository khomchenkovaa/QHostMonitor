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
    QSettings s;
    ui->wPreferences->init(&s);
    ui->wBehavior->init(&s);
    ui->wStartupOptions->init(&s);
    ui->wService->init(&s);
    ui->wAccessMethod->init(&s);
    ui->wProxy->init(&s);
    ui->wPrimaryLog->init(&s);
    ui->wBackupLog->init(&s);
    ui->wSystemLog->init(&s);
    ui->wLogProcessing->init(&s);
    ui->wHtmlColors->init(&s);
    ui->wViewers->init(&s);
    ui->wReports->init(&s);
    ui->wMsgWindow->init(&s);
    ui->wMailerSettings->init(&s);
    ui->wPagers->init(&s);
    ui->wIcq->init(&s);
    ui->wJabber->init(&s);
    ui->wSmsGsm->init(&s);
    ui->wSmsSmpp->init(&s);
    ui->wPingTrace->init(&s);
    ui->wRci->init(&s);
    ui->wActiveRma->init(&s);
    ui->wScheduler->init(&s);
    ui->wMisc->init(&s);
}

/******************************************************************/

void OptionsForm::prepareToSave()
{
    QSettings s;
    ui->wPreferences->prepareToSave(&s);
    ui->wBehavior->prepareToSave(&s);
    ui->wStartupOptions->prepareToSave(&s);
    ui->wService->prepareToSave(&s);
    ui->wAccessMethod->prepareToSave(&s);
    ui->wProxy->prepareToSave(&s);
    ui->wPrimaryLog->prepareToSave(&s);
    ui->wBackupLog->prepareToSave(&s);
    ui->wSystemLog->prepareToSave(&s);
    ui->wLogProcessing->prepareToSave(&s);
    ui->wHtmlColors->prepareToSave(&s);
    ui->wViewers->prepareToSave(&s);
    ui->wReports->prepareToSave(&s);
    ui->wMsgWindow->prepareToSave(&s);
    ui->wMailerSettings->prepareToSave(&s);
    ui->wPagers->prepareToSave(&s);
    ui->wIcq->prepareToSave(&s);
    ui->wJabber->prepareToSave(&s);
    ui->wSmsGsm->prepareToSave(&s);
    ui->wSmsSmpp->prepareToSave(&s);
    ui->wPingTrace->prepareToSave(&s);
    ui->wRci->prepareToSave(&s);
    ui->wActiveRma->prepareToSave(&s);
    ui->wScheduler->prepareToSave(&s);
    ui->wMisc->prepareToSave(&s);
}

/******************************************************************/

} // namespace SDPO


