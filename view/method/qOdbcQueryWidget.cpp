#include "qOdbcQueryWidget.h"
#include "ui_qOdbcQueryWidget.h"
#include "qOdbcQueryDlg.h"
#include "method/tOdbcQuery.h"


namespace SDPO {

/*****************************************************************/

OdbcQueryWidget::OdbcQueryWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::OdbcQueryWidget)
{
    ui->setupUi(this);
    m_TestAlert = false;
    m_AlertRow = 1;
    m_AlertCol = 1;
    m_CriteriaMode = 0;
    m_CriteriaValue = QString();
    m_UnavailableStatus = "Unknown";
    connect(ui->cmbDataSource, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->txtSqlQuery, SIGNAL(textChanged()), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

OdbcQueryWidget::~OdbcQueryWidget()
{
    delete ui;
}

/*****************************************************************/

void OdbcQueryWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::ODBC) ) {
        reset();
        return;
    }
    TOdbcQuery* test = qobject_cast<TOdbcQuery*>(item);
    ui->cmbDataSource->setCurrentText(test->getDataSource());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->editPassword->setText(test->getPassword());
    ui->chkExecuteQuery->setChecked(test->isExecuteQuery());
    ui->txtSqlQuery->setPlainText(test->getSqlQuery());
    ui->spinTimeout->setValue(test->getTimeout());
    m_TestAlert = test->isTestAlert();
    m_AlertRow = test->getAlertRow();
    m_AlertCol = test->getAlertCol();
    m_CriteriaMode = test->getCriteriaMode();
    m_CriteriaValue = test->getCriteriaValue();
    m_UnavailableStatus = test->getUnavailableStatus();
}

/*****************************************************************/

TestMethod *OdbcQueryWidget::save(TestMethod *item)
{
    TOdbcQuery* test;
    if (item && (item->getTMethodID() == TMethodID::ODBC)) {
        test = qobject_cast<TOdbcQuery*>(item);
    } else {
        test = new TOdbcQuery();
    }
    test->setDataSource(ui->cmbDataSource->currentText());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->editPassword->text());
    test->setExecuteQuery(ui->chkExecuteQuery->isChecked());
    test->setSqlQuery(ui->txtSqlQuery->toPlainText());
    test->setTimeout(ui->spinTimeout->value());
    test->setTestAlert(m_TestAlert);
    test->setAlertRow(m_AlertRow);
    test->setAlertCol(m_AlertCol);
    test->setCriteriaMode(m_CriteriaMode);
    test->setCriteriaValue(m_CriteriaValue);
    test->setUnavailableStatus(m_UnavailableStatus);

    return test;
}

/*****************************************************************/

void OdbcQueryWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::ODBC);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbDataSource->clear();
    ui->cmbLogin->clear();
    ui->editPassword->clear();
    ui->chkExecuteQuery->setChecked(false);
    ui->txtSqlQuery->clear();
    ui->spinTimeout->setValue(10);
    m_TestAlert = false;
    m_AlertRow = 1;
    m_AlertCol = 1;
    m_CriteriaMode = 0;
    m_CriteriaValue = QString();
    m_UnavailableStatus = "Unknown";
}

/*****************************************************************/

QStringList OdbcQueryWidget::validate()
{
    QStringList errors;
    if(ui->cmbDataSource->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a DataSource"));
    }
    if(ui->chkExecuteQuery->isChecked() && ui->txtSqlQuery->toPlainText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a SQL query"));
    }
    return errors;
}

/*****************************************************************/

QString OdbcQueryWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::ODBC);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::ODBC);
    case Macro::Path : return ui->txtSqlQuery->toPlainText();
    case Macro::Object : return ui->cmbDataSource->currentText();
    default: return QString();
    }

}

/*****************************************************************/

void OdbcQueryWidget::on_btnEdit_clicked()
{
    OdbcQueryDlg queryDlg;
    queryDlg.setFieldDataSource(ui->cmbDataSource->currentText());
    queryDlg.setFieldLogin(ui->cmbLogin->currentText());
    queryDlg.setFieldPassword(ui->editPassword->text());
    queryDlg.setFieldExecuteQuery(ui->chkExecuteQuery->isChecked());
    queryDlg.setFieldSqlQuery(ui->txtSqlQuery->toPlainText());
    queryDlg.setFieldAlert(m_TestAlert);
    queryDlg.setFieldRow(m_AlertRow);
    queryDlg.setFieldCol(m_AlertCol);
    queryDlg.setFieldCriteriaMode(m_CriteriaMode);
    queryDlg.setFieldCriteriaValue(m_CriteriaValue);
    queryDlg.setFieldUnavailableStatus(m_UnavailableStatus);
    if (queryDlg.exec() == QDialog::Accepted) {
        ui->cmbDataSource->setCurrentText(queryDlg.getFieldDataSource());
        ui->cmbLogin->setCurrentText(queryDlg.getFieldLogin());
        ui->editPassword->setText(queryDlg.getFieldPassword());
        ui->chkExecuteQuery->setChecked(queryDlg.isFieldExecuteQuery());
        ui->txtSqlQuery->setPlainText(queryDlg.getFieldSqlQuery());
        m_TestAlert = queryDlg.isFieldAlert();
        m_AlertRow = queryDlg.getFieldRow();
        m_AlertCol = queryDlg.getFieldCol();
        m_CriteriaMode = queryDlg.getFieldCriteriaMode();
        m_CriteriaValue = queryDlg.getFieldCriteriaValue();
        m_UnavailableStatus = queryDlg.getFieldUnavailableStatus();
    }
}

/*****************************************************************/

} // namespace SDPO

