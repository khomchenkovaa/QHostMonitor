#include "qPrimaryLogOptionsWidget.h"
#include "ui_qPrimaryLogOptionsWidget.h"
#include "qMacroEditorDlg.h"
#include "qActionProfiles.h"
#include "io/ioActionProfileLoader.h"
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
              tr("Error code: %1\n%2").arg(db.lastError().nativeErrorCode(), db.lastError().text()));
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

    ui->cmbPrimaryLogType->setCurrentIndex(s->value(SKEY_LOG1_Target,1).toInt());
    on_cmbPrimaryLogSelect(ui->cmbPrimaryLogType->currentIndex());
    connect(ui->cmbPrimaryLogType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cmbPrimaryLogSelect(int)));

    ui->cmbPrimaryLogMode->setCurrentIndex(s->value(SKEY_LOG1_SaveMode,2).toInt());
    ui->cmbPrimaryLogFile->setCurrentIndex(s->value(SKEY_LOG1_LogNameMethod,0).toInt());

    QString val = s->value(SKEY_LOG1_File2Name).toString();
    int idx = val.lastIndexOf("/");
    if (idx != -1) {
        curFolder = val.mid(0,idx);
    }
    ui->editPrimaryLogFileName->setText(val);

    switch (s->value(SKEY_LOG1_LogFormat,0).toInt()) {
    case 1: ui->rbPrimaryLogText->setChecked(true); break;
    case 2: ui->rbPrimaryLogDBF->setChecked(true); break;
    default: // case 0:
        ui->rbPrimaryLogHTML->setChecked(true); break;
    }
    ui->chkPrimaryLogAlertInaccessible->setChecked(s->value(SKEY_LOG1_UseDeadAction,0).toInt());
    ui->cmbPrimaryLogAlertInaccessible->setCurrentIndex(s->value(SKEY_LOG1_DeadActionID,-1).toInt());
    ui->chkPrimaryLogAlertAlive->setChecked(s->value(SKEY_LOG1_UseGoodAction,0).toInt());
    ui->cmbPrimaryLogAlertAlive->setCurrentIndex(s->value(SKEY_LOG1_GoodActionID,-1).toInt());

    ui->cmbPrimaryLogDatasource->setCurrentText(s->value(SKEY_LOGGING_OdbcLogSource).toString());
    ui->plainPrimaryLogSQL->clear();
    ui->plainPrimaryLogSQL->insertPlainText(s->value(SKEY_LOGGING_OdbcLogSqlQuery,SVAL_LOGGING_OdbcLogSqlQuery).toString());
    ui->editPrimaryLogLogin->setText(s->value(SKEY_LOGGING_OdbcLogUser).toString());
    ui->editPrimaryLogPassword->setText(s->value(SKEY_LOGGING_OdbcLogPswd).toString());
    ui->spinPrimaryLogTimeout->setValue(s->value(SKEY_LOGGING_OdbcLogTimeout,10).toInt());
}

/******************************************************************/

void PrimaryLogOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_LOG1_Target, ui->cmbPrimaryLogType->currentIndex());
    s->setValue(SKEY_LOG1_SaveMode, ui->cmbPrimaryLogMode->currentIndex());
    s->setValue(SKEY_LOG1_LogNameMethod, ui->cmbPrimaryLogFile->currentIndex());
    s->setValue(SKEY_LOG1_File2Name, ui->editPrimaryLogFileName->text());

    int logFormat = 0; // ui->rbPrimaryLogHTML->isChecked()
    if (ui->rbPrimaryLogText->isChecked()) {
        logFormat = 1;
    } else if (ui->rbPrimaryLogDBF->isChecked()) {
        logFormat = 2 ;
    }
    s->setValue(SKEY_LOG1_LogFormat, logFormat);

    s->setValue(SKEY_LOG1_UseDeadAction, ui->chkPrimaryLogAlertInaccessible->isChecked()?1:0);
    s->setValue(SKEY_LOG1_DeadActionID, ui->cmbPrimaryLogAlertInaccessible->currentIndex());
    s->setValue(SKEY_LOG1_UseGoodAction, ui->chkPrimaryLogAlertAlive->isChecked()?1:0);
    s->setValue(SKEY_LOG1_GoodActionID, ui->cmbPrimaryLogAlertAlive->currentIndex());

    s->setValue(SKEY_LOGGING_OdbcLogSource, ui->cmbPrimaryLogDatasource->currentText());
    s->setValue(SKEY_LOGGING_OdbcLogSqlQuery, ui->plainPrimaryLogSQL->toPlainText());
    s->setValue(SKEY_LOGGING_OdbcLogUser, ui->editPrimaryLogLogin->text());
    s->setValue(SKEY_LOGGING_OdbcLogPswd, ui->editPrimaryLogPassword->text());
    s->setValue(SKEY_LOGGING_OdbcLogTimeout, ui->spinPrimaryLogTimeout->value());
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

