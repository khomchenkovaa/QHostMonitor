#include "qMacroEditorScriptRunnerDlg.h"
#include "ui_qMacroEditorScriptRunnerDlg.h"
#include "tEnums.h"
#include "global/gUserVars.h"
#include "global/gMacroTranslator.h"
#include <QScriptEngine>
#include <QtWidgets>

namespace SDPO {

MacroEditorScriptRunnerDlg::MacroEditorScriptRunnerDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MacroEditorScriptRunnerDlg)
{
    ui->setupUi(this);
}

MacroEditorScriptRunnerDlg::~MacroEditorScriptRunnerDlg()
{
    delete ui;
}

void MacroEditorScriptRunnerDlg::setScript(const QString script)
{
    ui->editSource->setPlainText(script);
    GMacroTranslator translator(script);
    QStringList vars = translator.parse();
    QStringList headers;
    headers << "Value";
    ui->tableVariables->setColumnCount(1);
    ui->tableVariables->setHorizontalHeaderLabels(headers);
    ui->tableVariables->setRowCount(vars.count());
    ui->tableVariables->setVerticalHeaderLabels(vars);
    for (int i=0; i<vars.count(); i++) {
        if (GUserVars::variables.contains(vars.at(i))) {
            ui->tableVariables->setItem(i,0,new QTableWidgetItem(GUserVars::variables.value(vars.at(i))));
        }
    }
}

void MacroEditorScriptRunnerDlg::on_btnRun_clicked()
{
    QVariantMap vars;
    for (int i=0; i<ui->tableVariables->rowCount(); i++) {
        vars.insert(ui->tableVariables->verticalHeaderItem(i)->text(), ui->tableVariables->item(i,0)->text());
    }
    GMacroTranslator translator(ui->editSource->toPlainText());
    translator.setValues(vars);
    QString script = translator.build();
    ui->editScript->setPlainText(script);
    QScriptEngine scriptEngine;
    QScriptValue value = scriptEngine.evaluate(script);
    ui->editResult->setPlainText(value.toString());
}

} // namespace SDPO


