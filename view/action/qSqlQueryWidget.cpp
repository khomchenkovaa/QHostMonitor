#include "qSqlQueryWidget.h"
#include "ui_qSqlQueryWidget.h"
#include "action/tSqlQueryAction.h"
#include "qMacroEditorDlg.h"

namespace SDPO {

/******************************************************************/

SqlQueryWidget::SqlQueryWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::SqlQueryWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SqlQueryWidget::~SqlQueryWidget()
{
    delete ui;
}

/******************************************************************/

void SqlQueryWidget::init(TestAction *item)
{
    reset();
    if (!item || item->getAction() != TActionID::SqlQuery) {
        return;
    }
    SqlQueryAction *action = qobject_cast<SqlQueryAction *>(item);
    ui->cmbOdbcDataSource->setCurrentText(action->getOdbcDataSource());
    ui->cmbLogin->setCurrentText(action->getLogin());
    ui->linePassword->setText(action->getPassword());
    ui->cmbSqlQuery->setCurrentText(action->getSqlQuery());
    ui->spinTimeout->setValue(action->getTimeout());
}

/******************************************************************/

TestAction *SqlQueryWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::SqlQuery) {
        item = new SqlQueryAction();
    }
    SqlQueryAction *action = qobject_cast<SqlQueryAction *>(item);
    action->setOdbcDataSource(ui->cmbOdbcDataSource->currentText());
    action->setLogin(ui->cmbLogin->currentText());
    action->setPassword(ui->linePassword->text());
    action->setSqlQuery(ui->cmbSqlQuery->currentText());
    action->setTimeout(ui->spinTimeout->value());
    return action;
}

/******************************************************************/

void SqlQueryWidget::on_btnSqlQuery_clicked()
{
    MacroEditorDlg dlg;
    dlg.setWindowTitle(tr("Condition to perform dependant test"));
    dlg.setScript(ui->cmbSqlQuery->currentText());
    if (dlg.exec() == QDialog::Accepted) {
        ui->cmbSqlQuery->setCurrentText(dlg.getScript());
    }
}

/******************************************************************/

} // namespace SDPO

