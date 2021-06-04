#include "qMySqlWidget.h"
#include "ui_qMySqlWidget.h"
#include "method/tMySql.h"

namespace SDPO {

/*****************************************************************/

MySqlWidget::MySqlWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::MySqlWidget)
{
    ui->setupUi(this);
    connect(ui->cmbServer, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbDatabase, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

MySqlWidget::~MySqlWidget()
{
    delete ui;
}

/*****************************************************************/

void MySqlWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::MySQL) ) {
        reset();
        return;
    }
    TMySql* test = qobject_cast<TMySql*>(item);
    ui->cmbServer->setCurrentText(test->getHost());
    ui->spinPort->setValue(test->getPort());
    ui->cmbDatabase->setCurrentText(test->getDatabase());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->editPassword->setText(test->getPassword());
}

/*****************************************************************/

TTestMethod *MySqlWidget::save(TTestMethod *item)
{
    TMySql* test;
    if (item && (item->getTMethodID() == TMethodID::MySQL)) {
        test = qobject_cast<TMySql*>(item);
    } else {
        test = new TMySql();
    }
    test->setHost(ui->cmbServer->currentText());
    test->setPort(ui->spinPort->value());
    test->setDatabase(ui->cmbDatabase->currentText());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->editPassword->text());

    return test;
}

/*****************************************************************/

void MySqlWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::MySQL);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->spinPort->setValue(MYSQL_DEFAULT_PORT);
    ui->cmbDatabase->clear();
    ui->cmbLogin->clear();
    ui->editPassword->clear();
}

/*****************************************************************/

QStringList MySqlWidget::validate()
{
    QStringList errors;
    if(ui->cmbServer->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Server"));
    }
    if(ui->cmbDatabase->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Database"));
    }
    return errors;

}

/*****************************************************************/

QString MySqlWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::MySQL);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::MySQL);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::Object : return ui->cmbDatabase->currentText();
    default: return QString();
    }
}

/*****************************************************************/

} // namespace SDPO
