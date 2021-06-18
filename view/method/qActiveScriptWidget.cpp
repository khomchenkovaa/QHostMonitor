#include "qActiveScriptWidget.h"
#include "ui_qActiveScriptWidget.h"
#include "method/tActiveScript.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

ActiveScriptWidget::ActiveScriptWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::ActiveScriptWidget)
{
    ui->setupUi(this);
    connect(ui->cmbLanguage, SIGNAL(currentIndexChanged(int)), this, SIGNAL(propertiesChanged()));
    connect(ui->lnRunScript, SIGNAL(textChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

ActiveScriptWidget::~ActiveScriptWidget()
{
    delete ui;
}

/*****************************************************************/

void ActiveScriptWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Script) ) {
        reset();
        return;
    }
    TActiveScript* test = qobject_cast<TActiveScript*>(item);
    if (test->isScriptCriteria()) {
        ui->rdRunScript->setChecked(true);
    } else {
        ui->rdStoreScript->setChecked(true);
    }
    ui->lnRunScript->setText(test->getFileScript());
    ui->cmbLanguage->setCurrentText(test->getLanguage());
    ui->chkAllowUI->setChecked(test->isAllowUi());
    ui->spinTimeout->setValue(test->getTimeout());
    ui->chkTranslateMacros->setChecked(test->isTranslateMacros());
}

/*****************************************************************/

TestMethod *ActiveScriptWidget::save(TestMethod *item)
{
    TActiveScript* test;
    if (item && (item->getTMethodID() == TMethodID::Script)) {
        test = qobject_cast<TActiveScript*>(item);
    } else {
        test = new TActiveScript();
    }
    test->setScriptCriteria(ui->rdRunScript->isChecked());
    test->setFileScript(ui->lnRunScript->text());
    test->setLanguage(ui->cmbLanguage->currentText());
    test->setAllowUi(ui->chkAllowUI->isChecked());
    test->setTimeout(ui->spinTimeout->value());
    test->setTranslateMacros(ui->chkTranslateMacros->isChecked());
    return test;
}

/******************************************************************/

void ActiveScriptWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::Script);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->lnRunScript->clear();
    ui->rdRunScript->setChecked(true);
    ui->cmbLanguage->setCurrentIndex(0);
    ui->chkAllowUI->setChecked(false);
    ui->spinTimeout->setValue(10);
    ui->chkTranslateMacros->setChecked(false);
}

/******************************************************************/

QStringList ActiveScriptWidget::validate()
{
    QStringList errors;
    if(ui->lnRunScript->text().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a file name"));
    }
    return errors;
}

/******************************************************************/

QString ActiveScriptWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number(static_cast<int>(TMethodID::Script));
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::Script);
    case Macro::TestMode : return ui->cmbLanguage->currentText();
    case Macro::Object : return ui->lnRunScript->text();
    default: return QString();
    }
}

/******************************************************************/

void ActiveScriptWidget::on_btnRunScript_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->lnRunScript->text());
    if (!fileName.isEmpty()) {
        ui->lnRunScript->setText(fileName);
    }
}

/******************************************************************/

void ActiveScriptWidget::on_btnEditStoreScript_clicked()
{
    // do nothing
}

/******************************************************************/

void ActiveScriptWidget::on_btnTestStoreScript_clicked()
{
    // do nothing
}

/******************************************************************/

} // namespace SDPO


