#include "qMsSqlWidget.h"
#include "ui_qMsSqlWidget.h"
#include "method/tMsSql.h"

namespace SDPO {

/******************************************************************/

MsSqlWidget::MsSqlWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::MsSqlWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

MsSqlWidget::~MsSqlWidget()
{
    delete ui;
}

/******************************************************************/

void MsSqlWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::MSSQL) ) {
        reset();
        return;
    }
    TMsSql* test = qobject_cast<TMsSql*>(item);
    ui->cmbServer->setCurrentText(test->getServer());
    ui->cmbDatabase->setCurrentText(test->getDatabase());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->editPassword->setText(test->getPassword());
}

/*****************************************************************/

TTestMethod *MsSqlWidget::save(TTestMethod *item)
{
    TMsSql* test;
    if (item && (item->getTMethodID() == TMethodID::MSSQL)) {
        test = qobject_cast<TMsSql*>(item);
    } else {
        test = new TMsSql();
    }
    test->setServer(ui->cmbServer->currentText());
    test->setDatabase(ui->cmbDatabase->currentText());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->editPassword->text());
    return test;
}

/******************************************************************/

void MsSqlWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::MSSQL);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->cmbDatabase->clear();
    ui->cmbLogin->clear();
    ui->editPassword->clear();
}

/******************************************************************/

QStringList MsSqlWidget::validate()
{
    QStringList errors;
    if(ui->cmbDatabase->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a server"));
    }
    return errors;
}

/******************************************************************/

QString MsSqlWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::MSSQL);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::MSSQL);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::Object : return ui->cmbDatabase->currentText();
    default: return QString();
    }
}

/******************************************************************/
} //namespace SDPO
