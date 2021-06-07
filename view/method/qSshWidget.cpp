#include "qSshWidget.h"
#include "ui_qSshWidget.h"
#include "xMacroVar.h"
#include "method/tSshTest.h"

namespace SDPO {

/******************************************************************/

SshWidget::SshWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::SshWidget)
{
    ui->setupUi(this);
    connect(ui->cmbCommand, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbHost, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

SshWidget::~SshWidget()
{
    delete ui;
}

/******************************************************************/

void SshWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::SSH) ) {
        reset();
        return;
    }
    TSshTest* test = qobject_cast<TSshTest*>(item);
    ui->cmbHost->setCurrentText(test->getHost());
    ui->spnPort->setValue(test->getPort());
    ui->spnTimeout->setValue(test->getTimeout());
    ui->cmbCommand->setCurrentText(test->getSshCmd());
    ui->cmbCheckFor->setCurrentIndex(static_cast<int>(test->getMode()));

    ui->cmbExitCodeCriteria->setCurrentIndex(static_cast<int>(test->getExitCodeCriteria()));
    ui->spnExitCodeValue->setValue(test->getExitCodeValue());

    ui->cmbCheckType->setCurrentIndex(static_cast<int>(test->getTextOutputCriteria()));
    ui->editValue->setText(test->getTextOutputValue());
    ui->chkCaseSensitive->setChecked(test->isCaseSensitive());
    ui->chkWholeWordsOnly->setChecked(test->isWholeWordsOnly());
    ui->chkMacros->setChecked(test->isTranslateMacros());
}

/******************************************************************/

TestMethod *SshWidget::save(TestMethod *item)
{
    TSshTest* test;
    if (item && (item->getTMethodID() == TMethodID::SSH)) {
        test = qobject_cast<TSshTest*>(item);
    } else {
        test = new TSshTest();
    }

    test->setHost(ui->cmbHost->currentText());
    test->setPort(ui->spnPort->value());
    test->setTimeout(ui->spnTimeout->value());
    test->setSshCmd(ui->cmbCommand->currentText());
    test->setMode(static_cast<TSshTest::CheckMode>(ui->cmbCheckFor->currentIndex()));

    test->setExitCodeCriteria(static_cast<TSshTest::ExitCodeMode>(ui->cmbExitCodeCriteria->currentIndex()));
    test->setExitCodeValue(ui->spnExitCodeValue->value());

    test->setTextOutputCriteria(static_cast<TSshTest::TextOutputMode>(ui->cmbCheckType->currentIndex()));
    test->setTextOutputValue(ui->editValue->text());
    test->setCaseSensitive(ui->chkCaseSensitive->isChecked());
    test->setWholeWordsOnly(ui->chkWholeWordsOnly->isChecked());
    test->setTranslateMacros(ui->chkMacros->isChecked());

    return test;
}

/******************************************************************/

void SshWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::SSH);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbHost->clear();
    ui->spnPort->setValue(20);
    ui->spnTimeout->setValue(5000);
    ui->cmbCommand->clear();
    ui->cmbCheckFor->setCurrentIndex(0);

    ui->cmbExitCodeCriteria->setCurrentIndex(0);
    ui->spnExitCodeValue->setValue(0);

    ui->cmbCheckType->setCurrentIndex(0);
    ui->editValue->clear();
    ui->chkCaseSensitive->setChecked(false);
    ui->chkWholeWordsOnly->setChecked(false);
    ui->chkMacros->setChecked(false);
}

/******************************************************************/

QStringList SshWidget::validate()
{
    QStringList errors;
    if(ui->cmbHost->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Host"));
    }
    if(ui->cmbCommand->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Command"));
    }
    return errors;
}

/******************************************************************/

QString SshWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number(static_cast<int>(TMethodID::SSH));
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::SSH);
    case Macro::Path : return ui->cmbCommand->currentText();
    case Macro::Host : return ui->cmbHost->currentText();
    default: return QString();
    }

}

/******************************************************************/

} // namespace SDPO
