#include "qPrimaryLogOptionsWidget.h"
#include "ui_qPrimaryLogOptionsWidget.h"
#include "qMacroEditorDlg.h"
#include "qActionProfiles.h"
#include "global/ioActionProfileLoader.h"
#include "gData.h"

#include <QFileDialog>
#include "QMessageBox"
#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

PrimaryLogOptionsWidget::PrimaryLogOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::PrimaryLogOptionsWidget)
{
    ui->setupUi(this);
    curFolder = QCoreApplication::applicationDirPath() + "/logs" + "%ddmmyyyy%-log.txt";
    format << "log" << "%mmyyyy%-log" << "%wwyyyy%-log" << "%ddmmyyyy%-log";
    connect(ui->rbPrimaryLogHTML,SIGNAL(clicked()),this,SLOT(setPrimaryFileLogName()));
    connect(ui->rbPrimaryLogText,SIGNAL(clicked()),this,SLOT(setPrimaryFileLogName()));
    connect(ui->rbPrimaryLogDBF,SIGNAL(clicked()),this,SLOT(setPrimaryFileLogName()));
    connect(ui->cmbPrimaryLogFile, SIGNAL(currentIndexChanged(int)), this, SLOT(setPrimaryFileLogName()));
}

/******************************************************************/

PrimaryLogOptionsWidget::~PrimaryLogOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void PrimaryLogOptionsWidget::on_btnPrimaryLogDir_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this,tr("Folder"),curFolder);
    if (!fileName.isEmpty()) {
        curFolder = fileName;
        setPrimaryFileLogName();
    }
}

/******************************************************************/

void PrimaryLogOptionsWidget::reset_AlertInaccessible()
{
    ui->cmbPrimaryLogAlertInaccessible->clear();
    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbPrimaryLogAlertInaccessible->addItem(profile.name);
    }
}

/******************************************************************/

void PrimaryLogOptionsWidget::on_btnPrimaryLogAlertInaccessible_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbPrimaryLogAlertInaccessible->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertInaccessible();
        ui->cmbPrimaryLogAlertInaccessible->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void PrimaryLogOptionsWidget::reset_AlertAlive()
{
    ui->cmbPrimaryLogAlertAlive->clear();
    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbPrimaryLogAlertAlive->addItem(profile.name);
    }
}

/******************************************************************/

void PrimaryLogOptionsWidget::on_btnPrimaryLogAlertAlive_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbPrimaryLogAlertAlive->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertAlive();
        ui->cmbPrimaryLogAlertAlive->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void PrimaryLogOptionsWidget::on_btnPrimaryLogSqlEdit_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("SQL qury for primary log"));
    dlg.setScript(ui->plainPrimaryLogSQL->toPlainText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->plainPrimaryLogSQL->setPlainText(dlg.getScript());
    }
}

/******************************************************************/

void PrimaryLogOptionsWidget::on_btnPrimaryLogOdbcTest_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("primaryOdbcLogger");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QODBC", "primaryOdbcLogger");
    }
    db.setDatabaseName(ui->cmbPrimaryLogDatasource->currentText());
    db.setUserName(ui->editPrimaryLogLogin->text());
    db.setPassword(ui->editPrimaryLogPassword->text());
    bool ok = db.open();
    if (ok) {
        QMessageBox::information(this,tr("Information"),tr("Test completed successfully"));
        db.close();
    } else {
        QMessageBox::warning(this,tr("Warning"),
              tr("Error code: %1\n%2").arg(db.lastError().number()).arg(db.lastError().text()));
    }
}

/******************************************************************/

void PrimaryLogOptionsWidget::setPrimaryFileLogName()
{
    fileName = curFolder + "/" + format.at(ui->cmbPrimaryLogFile->currentIndex());
    QString oldFile = ui->editPrimaryLogFileName->text();
    QString ext = oldFile.mid(oldFile.lastIndexOf("."));
    QString msg = QString("Log file extansion (%1) doesn't match the log format Extension will be changed").arg(ext);

    if (ui->rbPrimaryLogHTML->isChecked()) {
        if (!ext.isEmpty() && ext != ".html") {
            QMessageBox::warning(this, QObject::tr("Warning"), msg);
        }
        fileName += ".html";
    }
    else if (ui->rbPrimaryLogText->isChecked()) {
        if (!ext.isEmpty() && ext != ".txt") {
            QMessageBox::warning(this, QObject::tr("Warning"), msg);
        }
        fileName += ".txt";
    }
    else if (ui->rbPrimaryLogDBF->isChecked()) {
        if (!ext.isEmpty() && ext != ".dbf") {
            QMessageBox::warning(this, QObject::tr("Warning"), msg);
        }
        fileName += ".dbf";
    }
    ui->editPrimaryLogFileName->setText(fileName);

}

/******************************************************************/

void PrimaryLogOptionsWidget::init(QSettings *s)
{
    reset_AlertInaccessible();
    reset_AlertAlive();

    QVariant value = Settings::get(Settings::Logging1, Settings::Target, QVariant(1));
        ui->cmbPrimaryLogType->setCurrentIndex(value.toInt());
        on_cmbPrimaryLogSelect(value.toInt());
        connect(ui->cmbPrimaryLogType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbPrimaryLogSelect(int)));

    value = Settings::get(Settings::Logging1, Settings::SaveMode, QVariant(2));
        ui->cmbPrimaryLogMode->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging1, Settings::LogNameMethod, QVariant(0));
        ui->cmbPrimaryLogFile->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging1, Settings::File2Name, QVariant());
    QString val = value.toString();
        int idx = val.lastIndexOf("/");
        if (idx != -1)
            curFolder = val.mid(0,idx);
        ui->editPrimaryLogFileName->setText(val);

    value = Settings::get(Settings::Logging1, Settings::LogFormat, QVariant(0));
        if (value.toInt() == 0)
            ui->rbPrimaryLogHTML->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbPrimaryLogText->setChecked(true);
        else if (value.toInt() == 2)
            ui->rbPrimaryLogDBF->setChecked(true);

    value = Settings::get(Settings::Logging1, Settings::UseDeadAction, QVariant(0));
        ui->chkPrimaryLogAlertInaccessible->setChecked(value.toInt() == 1);

    value = Settings::get(Settings::Logging1, Settings::DeadActionID, QVariant(-1));
        ui->cmbPrimaryLogAlertInaccessible->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging1, Settings::UseGoodAction, QVariant(0));
        ui->chkPrimaryLogAlertAlive->setChecked(value.toInt() == 1);

    value = Settings::get(Settings::Logging1, Settings::GoodActionID, QVariant(-1));
        ui->cmbPrimaryLogAlertAlive->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging, Settings::odbcLogSource, QVariant());
        ui->cmbPrimaryLogDatasource->setCurrentText(value.toString());

    value = Settings::get(Settings::Logging, Settings::odbcLogSQLQuer, QVariant("Insert into hmlog (eventtime, testname, status, reply, testid, testmethod) VALUES ('%DateTime%', '%TestName%', '%Status%', '%Reply%', %TestID%, '%TestMethod%')"));
        ui->plainPrimaryLogSQL->clear();
        ui->plainPrimaryLogSQL->insertPlainText(value.toString());

    value = Settings::get(Settings::Logging, Settings::odbcLogUser, QVariant());
        ui->editPrimaryLogLogin->setText(value.toString());

    value = Settings::get(Settings::Logging, Settings::odbcLogPswd, QVariant());
        ui->editPrimaryLogPassword->setText(value.toString());

    value = Settings::get(Settings::Logging, Settings::odbcLogTimeout, QVariant(10));
        ui->spinPrimaryLogTimeout->setValue(value.toInt());

}

/******************************************************************/

void PrimaryLogOptionsWidget::prepareToSave(QSettings *s)
{
    Settings::set(Settings::Logging1, Settings::Target) = QVariant(ui->cmbPrimaryLogType->currentIndex());
    Settings::set(Settings::Logging1, Settings::SaveMode) = QVariant(ui->cmbPrimaryLogMode->currentIndex());
    Settings::set(Settings::Logging1, Settings::LogNameMethod) = QVariant(ui->cmbPrimaryLogFile->currentIndex());
    Settings::set(Settings::Logging1, Settings::File2Name) = QVariant(ui->editPrimaryLogFileName->text());

    int LogFormat;
        if (ui->rbPrimaryLogHTML->isChecked()?1:0)
        LogFormat = 0;
        else if (ui->rbPrimaryLogText->isChecked()?1:0)
            LogFormat = 1;
        else if (ui->rbPrimaryLogDBF->isChecked()?1:0)
            LogFormat =2 ;

    Settings::set(Settings::Logging1, Settings::LogFormat) = QVariant(LogFormat);

    Settings::set(Settings::Logging1, Settings::UseDeadAction) = QVariant(ui->chkPrimaryLogAlertInaccessible->isChecked()?1:0);
    Settings::set(Settings::Logging1, Settings::DeadActionID) = QVariant(ui->cmbPrimaryLogAlertInaccessible->currentIndex());
    Settings::set(Settings::Logging1, Settings::UseGoodAction) =QVariant(ui->chkPrimaryLogAlertAlive->isChecked()?1:0);
    Settings::set(Settings::Logging1, Settings::GoodActionID) = QVariant(ui->cmbPrimaryLogAlertAlive->currentIndex());
    Settings::set(Settings::Logging, Settings::odbcLogSource) = QVariant(ui->cmbPrimaryLogDatasource->currentText());
    Settings::set(Settings::Logging, Settings::odbcLogSQLQuer) = QVariant(ui->plainPrimaryLogSQL->toPlainText());
    Settings::set(Settings::Logging, Settings::odbcLogUser) = QVariant(ui->editPrimaryLogLogin->text());
    Settings::set(Settings::Logging, Settings::odbcLogPswd) = QVariant(ui->editPrimaryLogPassword->text());
    Settings::set(Settings::Logging, Settings::odbcLogTimeout) = QVariant(ui->spinPrimaryLogTimeout->value());
}

/******************************************************************/

void PrimaryLogOptionsWidget::on_cmbPrimaryLogSelect(int index)
{
    switch(index) {
    case 0:
        ui->cmbPrimaryLogMode->setDisabled(true);
        ui->boxPrimaryLogFile->setDisabled(true);
        ui->boxPrimaryLogFormat->setDisabled(true);
        ui->frmPrimaryLogAlerts->setDisabled(true);
        ui->stwPrimaryLog->setCurrentIndex(0);
        ui->stwPrimaryLog->setDisabled(true);
        break;
    case 1:
        ui->cmbPrimaryLogMode->setEnabled(true);
        ui->boxPrimaryLogFile->setEnabled(true);
        ui->boxPrimaryLogFormat->setEnabled(true);
        ui->frmPrimaryLogAlerts->setEnabled(true);
        ui->stwPrimaryLog->setCurrentIndex(0);
        ui->stwPrimaryLog->setEnabled(true);
        break;
    case 2:
        ui->cmbPrimaryLogMode->setEnabled(true);
        ui->stwPrimaryLog->setCurrentIndex(1);
        ui->frmPrimaryLogAlerts->setEnabled(true);
        break;
    }
}

/******************************************************************/

} // namespace SDPO

