#include "qShellScriptWidget.h"
#include "ui_qShellScriptWidget.h"
#include "../qShellMng.h"
#include "../hIOShellScripts.h"
#include "method/tShellScript.h"

namespace SDPO {

/******************************************************************/

ShellScriptWidget::ShellScriptWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::ShellScriptWidget)
{
    ui->setupUi(this);
    connect(ui->cmbScript, SIGNAL(currentIndexChanged(int)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbParams, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

ShellScriptWidget::~ShellScriptWidget()
{
    delete ui;
}

/******************************************************************/

void ShellScriptWidget::init(TTestMethod *item)
{
    if (!item && (item->getTMethodID() != TMethodID::ShellScript) ) {
        reset();
        return;
    }
    TShellScript* script = qobject_cast<TShellScript*>(item);
    resetScriptMenu(script->getFileName());
    ui->cmbParams->setCurrentText(script->getParams());
    ui->spinTimeout->setValue(script->getTimeout());
    ui->chkTranslateMacros->setChecked(script->isTranslateMacros());
}

/******************************************************************/

TTestMethod *ShellScriptWidget::save(TTestMethod *item)
{
    TShellScript* scr;
    if (item && (item->getTMethodID() == TMethodID::ShellScript)) {
        scr = qobject_cast<TShellScript*>(item);
    } else {
        scr = new TShellScript();
    }
    int index = ui->cmbScript->currentIndex();
    QString fileName = ui->cmbScript->itemData(index).toString();
    scr->setName(ui->cmbScript->currentText());
    scr->setFileName(fileName);
    scr->setParams(ui->cmbParams->currentText());
    scr->setTimeout(ui->spinTimeout->value());
    scr->setTranslateMacros(ui->chkTranslateMacros->isChecked());
    IOShellScripts loader;
    ShellScript *script = loader.loadFromFile(fileName);
    if (script) {
        scr->setPlatform(script->getPlatform());
        scr->setStartCmd(script->getStartCmd());
        delete script;
    }
    return scr;
}

/******************************************************************/

void ShellScriptWidget::reset(QVariant data)
{
    TMethod method = TMethod::tMethodList.at((int)TMethodID::ShellScript);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    resetScriptMenu(data);
    ui->cmbParams->setCurrentText(QString());
    ui->spinTimeout->setValue(15);
    ui->chkTranslateMacros->setChecked(false);
}

/******************************************************************/

QStringList ShellScriptWidget::validate()
{
    QStringList errors;
    if(ui->cmbScript->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a script"));
    }
    return errors;
}

/******************************************************************/

QString ShellScriptWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::ShellScript);
    case Macro::TestMethod : return TMethod::toName(TMethodID::ShellScript);
    case Macro::Host :
    case Macro::HostAddr : return "localhost";
    case Macro::Path : return ui->cmbScript->currentText();
    case Macro::Object : return ui->cmbParams->currentText();
    default: return QString();
    }

}

/******************************************************************/

void SDPO::ShellScriptWidget::on_btnScriptManager_clicked()
{
    ShellMng shellMng;
    connect(&shellMng,SIGNAL(shellScriptsChanged()),this,SLOT(resetScriptMenu()));
    shellMng.exec();
}

/******************************************************************/

void ShellScriptWidget::resetScriptMenu(QVariant data)
{
    ui->cmbScript->clear();
    IOShellScripts loader;
    QList<ShellScript*> scripts = loader.load(QCoreApplication::applicationDirPath() + "/scripts");
    int idx = 0;
    foreach(ShellScript* script, scripts) {
        ui->cmbScript->addItem(*new QIcon(":/img/action/shScript.png"),script->getName(),script->getFileName());
        if (data.isValid() && script->getFileName() == data.toString()) {
            ui->cmbScript->setCurrentIndex(idx);
            ui->editHint->setText(script->getHint());
        }
        ++idx;
    }
    qDeleteAll(scripts);
}

/******************************************************************/

void ShellScriptWidget::on_cmbScript_currentIndexChanged(int index)
{
    QString fileName = ui->cmbScript->itemData(index).toString();
    IOShellScripts loader;
    ShellScript *script = loader.loadFromFile(fileName);
    if (script) {
        ui->editHint->setText(script->getHint());
        delete script;
    }
}

/******************************************************************/

} // namespace SDPO
