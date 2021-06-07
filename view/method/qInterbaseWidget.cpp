#include "qInterbaseWidget.h"
#include "ui_qInterbaseWidget.h"
#include "method/tInterbase.h"

namespace SDPO {

/*****************************************************************/

InterbaseWidget::InterbaseWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::InterbaseWidget)
{
    ui->setupUi(this);
    connect(ui->cmbServer, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbDatabase, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

InterbaseWidget::~InterbaseWidget()
{
    delete ui;
}

/*****************************************************************/

void InterbaseWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Interbase) ) {
        reset();
        return;
    }
    TInterbase* test = qobject_cast<TInterbase*>(item);
    ui->cmbServer->setCurrentText(test->getHost());
    ui->cmbProtocol->setCurrentText(test->getProtocol());
    ui->cmbDatabase->setCurrentText(test->getDatabase());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->linePassword->setText(test->getPassword());
}

/*****************************************************************/

TestMethod *InterbaseWidget::save(TestMethod *item)
{
    TInterbase* test;
    if (item && (item->getTMethodID() == TMethodID::Interbase)) {
        test = qobject_cast<TInterbase*>(item);
    } else {
        test = new TInterbase();
    }
    test->setHost(ui->cmbServer->currentText());
    test->setProtocol(ui->cmbProtocol->currentText());
    test->setDatabase(ui->cmbDatabase->currentText());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->linePassword->text());

    return test;
}

/*****************************************************************/

void InterbaseWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::Interbase);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->cmbProtocol->setCurrentText(QString());
    ui->cmbDatabase->clear();
    ui->cmbLogin->clear();
    ui->linePassword->clear();
}

/*****************************************************************/

QStringList InterbaseWidget::validate()
{
    QStringList errors;
    if(ui->cmbDatabase->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Database"));
    }
    return errors;
}

/*****************************************************************/

QString InterbaseWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Interbase);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::Interbase);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::Object : return ui->cmbDatabase->currentText();
    default: return QString();
    }
}

/*****************************************************************/

} // namespace SDPO
