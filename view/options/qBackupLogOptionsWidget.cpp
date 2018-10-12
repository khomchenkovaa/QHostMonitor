#include "qBackupLogOptionsWidget.h"
#include "ui_qBackupLogOptionsWidget.h"
#include "qMacroEditorDlg.h"
#include "qActionProfiles.h"
#include "global/ioActionProfileLoader.h"
#include "gData.h"

#include <QFileDialog>
#include "QMessageBox"
#include <QSqlDatabase>
#include <QSqlError>

namespace SDPO {

BackupLogOptionsWidget::BackupLogOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::BackupLogOptionsWidget)
{
    ui->setupUi(this);
    curFolder = QCoreApplication::applicationDirPath() + "/logs" + "%ddmmyyyy%-log.txt";
    format << "log" << "%mmyyyy%-log" << "%wwyyyy%-log" << "%ddmmyyyy%-log";
    connect(ui->rbBackupLogHTML,SIGNAL(clicked()),this,SLOT(setBackupFileLogName()));
    connect(ui->rbBackupLogText,SIGNAL(clicked()),this,SLOT(setBackupFileLogName()));
    connect(ui->rbBackupLogDBF,SIGNAL(clicked()),this,SLOT(setBackupFileLogName()));
    connect(ui->cmbBackupLogFile, SIGNAL(currentIndexChanged(int)), this, SLOT(setBackupFileLogName()));
}

/******************************************************************/

BackupLogOptionsWidget::~BackupLogOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void BackupLogOptionsWidget::on_btnBackupLogDir_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this,tr("Folder"),curFolder);
    if (!fileName.isEmpty()) {
        curFolder = fileName;
        setBackupFileLogName();
    }
}

/******************************************************************/

void BackupLogOptionsWidget::reset_AlertInaccessible()
{
    ui->cmbBackupLogAlertInaccessible->clear();
    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbBackupLogAlertInaccessible->addItem(profile.name);
    }
}

/******************************************************************/

void BackupLogOptionsWidget::on_btnBackupLogAlertInaccessible_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbBackupLogAlertInaccessible->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertInaccessible();
        ui->cmbBackupLogAlertInaccessible->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void BackupLogOptionsWidget::on_btnBackupLogSqlEdit_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("SQL qury for Backup log"));
    dlg.setScript(ui->plainBackupLogSQL->toPlainText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->plainBackupLogSQL->setPlainText(dlg.getScript());
    }
}

/******************************************************************/

void BackupLogOptionsWidget::on_btnBackupLogOdbcTest_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("backupOdbcLogger");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QODBC", "backupOdbcLogger");
    }
    db.setDatabaseName(ui->cmbBackupLogDatasource->currentText());
    db.setUserName(ui->editBackupLogLogin->text());
    db.setPassword(ui->editBackupLogPassword->text());
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

void BackupLogOptionsWidget::setBackupFileLogName()
{
    fileName = curFolder + "/" + format.at(ui->cmbBackupLogFile->currentIndex());
    QString oldFile = ui->editBackupLogFileName->text();
    QString ext = oldFile.mid(oldFile.lastIndexOf("."));
    QString msg = QString("Log file extansion (%1) doesn't match the log format Extension will be changed").arg(ext);

    if (ui->rbBackupLogHTML->isChecked()) {
        if (!ext.isEmpty() && ext != ".html") {
            QMessageBox::warning(this, QObject::tr("Warning"), msg);
        }
         fileName += ".html";
    }
    else if (ui->rbBackupLogText->isChecked()) {
        if (!ext.isEmpty() && ext != ".txt") {
            QMessageBox::warning(this, QObject::tr("Warning"), msg);
        }
        fileName += ".txt";
    }
    else if (ui->rbBackupLogDBF->isChecked()) {
        if (!ext.isEmpty() && ext != ".dbf") {
            QMessageBox::warning(this, QObject::tr("Warning"), msg);
        }
        fileName += ".dbf";
    }
    ui->editBackupLogFileName->setText(fileName);


}

/******************************************************************/
void BackupLogOptionsWidget::init(QSettings *s)
{
    reset_AlertInaccessible();

    QVariant value = Settings::get(Settings::Logging2, Settings::Target, QVariant(1));
        ui->cmbBackupLogType->setCurrentIndex(value.toInt());
        on_cmbBackupLogSelect(value.toInt());
        connect(ui->cmbBackupLogType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbBackupLogSelect(int)));

    value = Settings::get(Settings::Logging2, Settings::SaveMode, QVariant(2));
        ui->cmbBackupLogMode->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging2, Settings::LogNameMethod, QVariant(0));
        ui->cmbBackupLogFile->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging2, Settings::File2Name, QVariant());
    QString val = value.toString();
        int idx = val.lastIndexOf("/");
        if (idx != -1)
            curFolder = val.mid(0,idx);
        ui->editBackupLogFileName->setText(val);

    value = Settings::get(Settings::Logging2, Settings::LogFormat, QVariant(0));
        if (value.toInt() == 0)
            ui->rbBackupLogHTML->setChecked(true);
        else if (value.toInt() == 1)
            ui->rbBackupLogText->setChecked(true);
        else if (value.toInt() == 2)
            ui->rbBackupLogDBF->setChecked(true);

    value = Settings::get(Settings::Logging2, Settings::UseDeadAction, QVariant(0));
        ui->chkBackupLogAlertInaccessible->setChecked(value.toInt() == 1);

    value = Settings::get(Settings::Logging2, Settings::DeadActionID, QVariant(-1));
        ui->cmbBackupLogAlertInaccessible->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Logging2, Settings::odbcLogSource, QVariant());
        ui->cmbBackupLogDatasource->setCurrentText(value.toString());

    value = Settings::get(Settings::Logging2, Settings::odbcLogSQLQuer, QVariant("Insert into hmlog (eventtime, testname, status, reply, testid, testmethod) VALUES ('%DateTime%', '%TestName%', '%Status%', '%Reply%', %TestID%, '%TestMethod%')"));
        ui->plainBackupLogSQL->clear();
        ui->plainBackupLogSQL->insertPlainText(value.toString());

    value = Settings::get(Settings::Logging2, Settings::odbcLogUser, QVariant());
        ui->editBackupLogLogin->setText(value.toString());

    value = Settings::get(Settings::Logging2, Settings::odbcLogPswd, QVariant());
        ui->editBackupLogPassword->setText(value.toString());

    value = Settings::get(Settings::Logging2, Settings::odbcLogTimeout, QVariant(10));
        ui->spinBackupLogTimeout->setValue(value.toInt());
}

/******************************************************************/

void BackupLogOptionsWidget::prepareToSave(QSettings *s)
{
    Settings::set(Settings::Logging2, Settings::Target) = QVariant(ui->cmbBackupLogType->currentIndex());
    Settings::set(Settings::Logging2, Settings::SaveMode) = QVariant(ui->cmbBackupLogMode->currentIndex());
    Settings::set(Settings::Logging2, Settings::LogNameMethod) = QVariant(ui->cmbBackupLogFile->currentIndex());
    Settings::set(Settings::Logging2, Settings::File2Name) = QVariant(ui->editBackupLogFileName->text());

    int LogFormat;
        if (ui->rbBackupLogHTML->isChecked()?1:0)
        LogFormat = 0;
        else if (ui->rbBackupLogText->isChecked()?1:0)
            LogFormat = 1;
        else if (ui->rbBackupLogDBF->isChecked()?1:0)
            LogFormat =2 ;

    Settings::set(Settings::Logging2, Settings::LogFormat) = QVariant(LogFormat);

    Settings::set(Settings::Logging2, Settings::UseDeadAction) = QVariant(ui->chkBackupLogAlertInaccessible->isChecked()?1:0);
    Settings::set(Settings::Logging2, Settings::odbcLogSQLQuer) = QVariant(ui->plainBackupLogSQL->toPlainText());
    Settings::set(Settings::Logging2, Settings::DeadActionID) = QVariant(ui->cmbBackupLogAlertInaccessible->currentIndex());
    Settings::set(Settings::Logging2, Settings::odbcLogSource) = QVariant(ui->cmbBackupLogDatasource->currentText());
    Settings::set(Settings::Logging2, Settings::odbcLogUser) = QVariant(ui->editBackupLogLogin->text());
    Settings::set(Settings::Logging2, Settings::odbcLogPswd) = QVariant(ui->editBackupLogPassword->text());
    Settings::set(Settings::Logging2, Settings::odbcLogTimeout) = QVariant(ui->spinBackupLogTimeout->value());
}

/******************************************************************/

void BackupLogOptionsWidget::on_cmbBackupLogSelect(int index)
{
    switch(index) {
    case 0:
        ui->cmbBackupLogMode->setDisabled(true);
        ui->boxBackupLogFile->setDisabled(true);
        ui->boxBackupLogFormat->setDisabled(true);
        ui->frmBackupLogAlerts->setDisabled(true);
        ui->stwBackupLog->setCurrentIndex(0);
        ui->stwBackupLog->setDisabled(true);
        break;
    case 1:
        ui->cmbBackupLogMode->setEnabled(true);
        ui->boxBackupLogFile->setEnabled(true);
        ui->boxBackupLogFormat->setEnabled(true);
        ui->frmBackupLogAlerts->setEnabled(true);
        ui->stwBackupLog->setCurrentIndex(0);
        ui->stwBackupLog->setEnabled(true);
        break;
    case 2:
        ui->cmbBackupLogMode->setEnabled(true);
        ui->stwBackupLog->setCurrentIndex(1);
        ui->frmBackupLogAlerts->setEnabled(true);
        break;
    }
}

/******************************************************************/

} // namespace SDPO
