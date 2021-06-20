#include "qBackupLogOptionsWidget.h"
#include "ui_qBackupLogOptionsWidget.h"
#include "qMacroEditorDlg.h"
#include "qActionProfiles.h"
#include "io/ioActionProfileLoader.h"
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
              tr("Error code: %1\n%2").arg(db.lastError().nativeErrorCode(), db.lastError().text()));
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
    ui->cmbBackupLogType->setCurrentIndex(s->value(SKEY_LOG2_Target, SVAL_LOG2_Target).toInt());
    on_cmbBackupLogSelect(ui->cmbBackupLogType->currentIndex());
    connect(ui->cmbBackupLogType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbBackupLogSelect(int)));
    ui->cmbBackupLogMode->setCurrentIndex(s->value(SKEY_LOG2_SaveMode, SVAL_LOG2_SaveMode).toInt());
    ui->cmbBackupLogFile->setCurrentIndex(s->value(SKEY_LOG2_LogNameMethod, SVAL_LOG2_LogNameMethod).toInt());
    QString val = s->value(SKEY_LOG2_File2Name).toString();
    int idx = val.lastIndexOf("/");
    if (idx != -1) {
        curFolder = val.mid(0,idx);
    }
    ui->editBackupLogFileName->setText(val);
    switch (s->value(SKEY_LOG2_LogFormat, SVAL_LOG2_LogFormat).toInt()) {
    case 1: ui->rbBackupLogText->setChecked(true); break;
    case 2: ui->rbBackupLogDBF->setChecked(true); break;
    default: // case 0:
        ui->rbBackupLogHTML->setChecked(true); break;
    }
    ui->chkBackupLogAlertInaccessible->setChecked     (s->value(SKEY_LOG2_UseDeadAction, SVAL_LOG2_UseDeadAction).toInt() == 1);
    ui->cmbBackupLogAlertInaccessible->setCurrentIndex(s->value(SKEY_LOG2_DeadActionID, SVAL_LOG2_DeadActionID).toInt());
    ui->cmbBackupLogDatasource->setCurrentText        (s->value(SKEY_LOG2_OdbcLogSource).toString());
    ui->plainBackupLogSQL->clear();
    ui->plainBackupLogSQL->insertPlainText(s->value(SKEY_LOG2_OdbcLogSqlQuery, SVAL_LOGGING_OdbcLogSqlQuery).toString());
    ui->editBackupLogLogin->setText       (s->value(SKEY_LOG2_OdbcLogUser).toString());
    ui->editBackupLogPassword->setText    (s->value(SKEY_LOG2_OdbcLogPswd).toString());
    ui->spinBackupLogTimeout->setValue    (s->value(SKEY_LOG2_OdbcLogTimeout, SVAL_LOG2_OdbcLogTimeout).toInt());
}

/******************************************************************/

void BackupLogOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_LOG2_Target, ui->cmbBackupLogType->currentIndex());
    s->setValue(SKEY_LOG2_SaveMode, ui->cmbBackupLogMode->currentIndex());
    s->setValue(SKEY_LOG2_LogNameMethod, ui->cmbBackupLogFile->currentIndex());
    s->setValue(SKEY_LOG2_File2Name, ui->editBackupLogFileName->text());
    int logFormat = 0; // ui->rbBackupLogHTML->isChecked()
    if (ui->rbBackupLogText->isChecked()) {
        logFormat = 1;
    } else if (ui->rbBackupLogDBF->isChecked()) {
        logFormat = 2;
    }
    s->setValue(SKEY_LOG2_LogFormat, logFormat);
    s->setValue(SKEY_LOG2_UseDeadAction, ui->chkBackupLogAlertInaccessible->isChecked()?1:0);
    s->setValue(SKEY_LOG2_DeadActionID, ui->cmbBackupLogAlertInaccessible->currentIndex());
    s->setValue(SKEY_LOG2_OdbcLogSource, ui->cmbBackupLogDatasource->currentText());
    s->setValue(SKEY_LOG2_OdbcLogSqlQuery, ui->plainBackupLogSQL->toPlainText());
    s->setValue(SKEY_LOG2_OdbcLogUser, ui->editBackupLogLogin->text());
    s->setValue(SKEY_LOG2_OdbcLogPswd, ui->editBackupLogPassword->text());
    s->setValue(SKEY_LOG2_OdbcLogTimeout, ui->spinBackupLogTimeout->value());
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
