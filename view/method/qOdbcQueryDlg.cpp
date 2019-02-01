#include "qOdbcQueryDlg.h"
#include "ui_qOdbcQueryDlg.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace SDPO {

/*****************************************************************/

OdbcQueryDlg::OdbcQueryDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OdbcQueryDlg)
{
    ui->setupUi(this);
    connect(ui->rbConnectionOnly, SIGNAL(toggled(bool)), this, SLOT(onTestCheckChanged(bool)));
    ui->rbConnectionOnly->setChecked(true);
}

/*****************************************************************/

OdbcQueryDlg::~OdbcQueryDlg()
{
    delete ui;
}

/*****************************************************************/

void OdbcQueryDlg::setFieldDataSource(const QString value)
{
    ui->cmbDataSource->setCurrentText(value);
}

/*****************************************************************/

QString OdbcQueryDlg::getFieldDataSource() const
{
    return ui->cmbDataSource->currentText();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldLogin(const QString value)
{
    ui->cmbLogin->setCurrentText(value);
}

/*****************************************************************/

QString OdbcQueryDlg::getFieldLogin() const
{
    return ui->cmbLogin->currentText();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldPassword(const QString value)
{
    ui->editPassword->setText(value);
}

/*****************************************************************/

QString OdbcQueryDlg::getFieldPassword() const
{
    return ui->editPassword->text();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldTimeout(const int value)
{
    ui->spinTimeout->setValue(value);
}

/*****************************************************************/

int OdbcQueryDlg::getFieldTimeout() const
{
    return ui->spinTimeout->value();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldExecuteQuery(const bool value)
{
    ui->rbExecuteQuery->setChecked(value);
}

/*****************************************************************/

bool OdbcQueryDlg::isFieldExecuteQuery() const
{
    return ui->rbExecuteQuery->isChecked();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldSqlQuery(const QString value)
{
    ui->txtSqlQuery->setPlainText(value);
}

/*****************************************************************/

QString OdbcQueryDlg::getFieldSqlQuery() const
{
    return ui->txtSqlQuery->toPlainText();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldAlert(const bool value)
{
    ui->chkTestAlert->setChecked(value);
}

/*****************************************************************/

bool OdbcQueryDlg::isFieldAlert() const
{
    return ui->chkTestAlert->isChecked();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldRow(const int value)
{
    ui->spinAlertRow->setValue(value);
}

/*****************************************************************/

int OdbcQueryDlg::getFieldRow() const
{
    return ui->spinAlertRow->value();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldCol(const int value)
{
    ui->spinAlertCol->setValue(value);
}

/*****************************************************************/

int OdbcQueryDlg::getFieldCol() const
{
    return ui->spinAlertCol->value();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldUnavailableStatus(const QString value)
{
    ui->cmbUnavailableStatus->setCurrentText(value);
}

/*****************************************************************/

QString OdbcQueryDlg::getFieldUnavailableStatus() const
{
    return ui->cmbUnavailableStatus->currentText();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldCriteriaMode(const int value)
{
    ui->cmbCriteriaMode->setCurrentIndex(value);
}

/*****************************************************************/

int OdbcQueryDlg::getFieldCriteriaMode() const
{
    return ui->cmbCriteriaMode->currentIndex();
}

/*****************************************************************/

void OdbcQueryDlg::setFieldCriteriaValue(const QString value)
{
    ui->editCriteriaValue->setText(value);
}

/*****************************************************************/

QString OdbcQueryDlg::getFieldCriteriaValue() const
{
    return ui->editCriteriaValue->text();
}

/*****************************************************************/

void OdbcQueryDlg::onTestCheckChanged(bool connectionOnly)
{
    ui->txtSqlQuery->setDisabled(connectionOnly);
    ui->chkTestAlert->setDisabled(connectionOnly);
    ui->spinAlertCol->setDisabled(connectionOnly);
    ui->spinAlertRow->setDisabled(connectionOnly);
    ui->cmbCriteriaMode->setDisabled(connectionOnly);
    ui->editCriteriaValue->setDisabled(connectionOnly);
    ui->cmbUnavailableStatus->setDisabled(connectionOnly);
}

/*****************************************************************/

void OdbcQueryDlg::on_btnOdbcTest_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("testOdbcQuery");
    if (!db.isValid()) {
        db = QSqlDatabase::addDatabase("QODBC", "testOdbcQuery");
    }
    db.setDatabaseName(ui->cmbDataSource->currentText());
    db.setUserName(ui->cmbLogin->currentText());
    db.setPassword(ui->editPassword->text());
    bool ok = db.open();
    if (!ok) {
        QMessageBox::warning(this,tr("Connection error"),
              tr("Error code: %1\n%2").arg(db.lastError().number()).arg(db.lastError().text()));
        return;
    }
    if (ui->rbConnectionOnly->isChecked()) {
        QMessageBox::information(this,tr("Information"),tr("Test completed successfully"));
        db.close();
        return;
    }
    QSqlQuery query(db);
    bool result = query.exec(ui->txtSqlQuery->toPlainText());
    if (!result) {
        QMessageBox::warning(this,tr("Query error"),
             tr("Error code: %1\n%2").arg(query.lastError().number()).arg(query.lastError().text()));
    } else {
        QMessageBox::information(this,tr("Information"),tr("Query executed successfully"));
    }
    db.close();
}

/*****************************************************************/

} // namespace SDPO


