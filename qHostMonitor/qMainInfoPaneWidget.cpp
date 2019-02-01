#include "qMainInfoPaneWidget.h"
#include "ui_qMainInfoPaneWidget.h"
#include "hmListService.h"

namespace SDPO {

/******************************************************************/

MainInfoPaneWidget::MainInfoPaneWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInfoPaneWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

MainInfoPaneWidget::~MainInfoPaneWidget()
{
    delete ui;
}

/******************************************************************/

void MainInfoPaneWidget::showSingleInfo(const bool isSingle)
{
    ui->boxInfo->setHidden(isSingle);
    ui->boxCurrentAndLastStatus->setHidden(!isSingle);
    ui->boxOperationComment->setHidden(!isSingle);
    ui->boxReply->setHidden(!isSingle);
    ui->boxStatistics->setHidden(!isSingle);
    ui->boxTestProperties->setHidden(!isSingle);
    ui->boxTime->setHidden(!isSingle);
}

/******************************************************************/

void MainInfoPaneWidget::testInfo(const TNode *test)
{
    showSingleInfo(true);
    // current and last status
    ui->valStatus->setText(test->getGlobal(Macro::Status).toString());
    ui->valIterations->setText(test->getGlobal(Macro::Recurrences).toString());
    ui->valReply->setText(test->getGlobal(Macro::Reply).toString());
    ui->valLastTestTime->setText(test->getGlobal(Macro::LastTestTime).toString());
    ui->valLastStatus->setText(test->getGlobal(Macro::LastStatus).toString());
    ui->valLastReply->setText(test->getGlobal(Macro::LastReply).toString());
    // reply
    ui->valMinValue->setText(test->getGlobal(Macro::MinReply).toString());
    ui->valMaxValue->setText(test->getGlobal(Macro::MaxReply).toString());
    ui->valAverage->setText(test->getGlobal(Macro::AverageReply).toString());
    // time
    ui->valStatusChangedAt->setText(test->getGlobal(Macro::StatusChangedTime).toString());
    ui->valDisabledAt->setText(QString()); //! TODO
    ui->valDisabledBy->setText(QString()); //! TODO
    // statistics
    ui->valTotalTests->setText(test->getGlobal(Macro::TotalTests).toString());
    ui->valPassed->setText(test->getGlobal(Macro::PassedCnt).toString());
    ui->valFailed->setText(test->getGlobal(Macro::FailedCnt).toString());
    ui->valUnknown->setText(test->getGlobal(Macro::UnknownCnt).toString());
    ui->valTotalTime->setText(test->getGlobal(Macro::TotalTime).toString());
    ui->valAliveTime->setText(test->getGlobal(Macro::AliveTime).toString() + " (" + test->getGlobal(Macro::AliveRatio).toString() + ")");
    ui->valDeadTime->setText(test->getGlobal(Macro::DeadTime).toString() + " (" + test->getGlobal(Macro::DeadRatio).toString() + ")");
    ui->valUnknownTime->setText(test->getGlobal(Macro::UnknownTime).toString() + " (" + test->getGlobal(Macro::UnknownRatio).toString() + ")");
    ui->valStatusChanges->setText(test->getGlobal(Macro::StatusChangesCnt).toString());
    ui->valAveragePeriod->setText(QString()); //!TODO
    // test properties
    ui->valTestBy->setText(test->getGlobal(Macro::Agent).toString());
    ui->valMethod->setText(test->getGlobal(Macro::TestMethod).toString());
    ui->valSchedule->setText(test->getGlobal(Macro::ScheduleName).toString());
    ui->valAlertProfile->setText(test->getGlobal(Macro::AlertProfile).toString());
    ui->valComment->setText(test->getGlobal(Macro::CommentLine1).toString());
    ui->valRelatedUrl->setText(test->getGlobal(Macro::RelatedURL).toString());
    ui->valMasterTest->setText(test->getGlobal(Macro::MasterTest).toString());
    ui->valPrivateLog->setText(test->getGlobal(Macro::PrivateLog).toString());
    ui->valCreatedAt->setText(test->getGlobal(Macro::CreatedTime).toString());
    ui->valModifiedAt->setText(test->getGlobal(Macro::ModifiedTime).toString());
    // operation comment
    ui->valOperationComment->setText(test->getGlobal(Macro::AckComment).toString());
}

/******************************************************************/

void MainInfoPaneWidget::folderInfo(HMListService *hml, const int testVisible, const int testSelected)
{
    showSingleInfo(false);
    // Info
    ui->valLoadedFile->setText(hml->currentFileName());
    ui->valFolders->setText(QString::number(hml->rootItem()->foldersCnt()));
    ui->valTests->setText(QString::number(hml->rootItem()->testsCnt()));
    ui->valVisibleTests->setText(QString("%1 in %2 folder(s)").arg(testVisible).arg(1)); //! TODO
    ui->valSelectedTests->setText(QString::number(testSelected));

    ui->valProgramStarted->setText(QString()); //! TODO
    ui->valPerformedTests->setText(QString()); //! TODO
    ui->valPerformedActions->setText(QString()); //! TODO
    ui->valLogRecords->setText(QString()); //! TODO
    ui->valLoggingPoolUsage->setText(QString("0.0%")); //! TODO

}

/******************************************************************/

} // namespace SDPO
