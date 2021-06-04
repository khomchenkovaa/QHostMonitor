#include "qSybaseWidget.h"
#include "ui_qSybaseWidget.h"
#include "xMacroVar.h"
#include "method/tSybase.h"

namespace SDPO {

/******************************************************************/

SybaseWidget::SybaseWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::SybaseWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SybaseWidget::~SybaseWidget()
{
    delete ui;
}

/******************************************************************/

void SybaseWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Sybase) ) {
        reset();
        return;
    }
    TSybase* test = qobject_cast<TSybase*>(item);
    ui->cmbServer->setCurrentText(test->getServer());
    ui->cmbDatabase->setCurrentText(test->getDatabase());
    ui->cmbLogin->setCurrentText(test->getLogin());
    ui->editPassword->setText(test->getPassword());
}

/******************************************************************/

TTestMethod *SybaseWidget::save(TTestMethod *item)
{
    TSybase* test;
    if (item && (item->getTMethodID() == TMethodID::Sybase)) {
        test = qobject_cast<TSybase*>(item);
    } else {
        test = new TSybase();
    }
    test->setServer(ui->cmbServer->currentText());
    test->setDatabase(ui->cmbDatabase->currentText());
    test->setLogin(ui->cmbLogin->currentText());
    test->setPassword(ui->editPassword->text());
    return test;
}

/******************************************************************/

void SybaseWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::Sybase);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbServer->clear();
    ui->cmbDatabase->clear();
    ui->cmbLogin->clear();
    ui->editPassword->clear();
}

/******************************************************************/

QStringList SybaseWidget::validate()
{
    QStringList errors;
    if(ui->cmbDatabase->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a server"));
    }
    return errors;
}

/******************************************************************/

QString SybaseWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Sybase);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::Sybase);
    case Macro::Host : return ui->cmbServer->currentText();
    case Macro::Object : return ui->cmbDatabase->currentText();
    default: return QString();
    }
}

/******************************************************************/

} // namespace SDPO {
