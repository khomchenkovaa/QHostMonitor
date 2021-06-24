#include "diagtestwidget.h"
#include "ui_diagtestwidget.h"

#include "tdiagtest.h"

using namespace SDPO;

/******************************************************************/

DiagTestWidget::DiagTestWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::DiagTestWidget)
{
    ui->setupUi(this);
    setupUI();
}

/******************************************************************/

DiagTestWidget::~DiagTestWidget()
{
    delete ui;
}

/******************************************************************/

void DiagTestWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Diag) ) {
        reset();
        return;
    }
    TDiagTest *t = qobject_cast<TDiagTest*>(item);
    ui->editParamName->setText(t->getParamName());
    ui->editParamDesc->setText(t->getParamDesc());
    ui->cmbDataType->setCurrentIndex(t->getDataType()); // Warn: index, not data
    ui->editCommand->setText(t->getCmd());
    ui->editNormValue->setText(t->getNormalValue().toString());
    ui->spinWarning->setValue(t->getWarning().toInt());
    ui->spinFail->setValue(t->getFail().toInt());
    ui->editLowFail->setText(t->getLowFailLimit().toString());
    ui->editLowWarning->setText(t->getLowWarningLimit().toString());
    ui->editHighFail->setText(t->getHighFailLimit().toString());
    ui->editHighWarning->setText(t->getHighWarningLimit().toString());
}

/******************************************************************/

TestMethod *DiagTestWidget::save(TestMethod *item)
{
    TDiagTest *t;
    if (item && (item->getTMethodID() == TMethodID::Diag)) {
        t = qobject_cast<TDiagTest*>(item);
    } else {
        t = new TDiagTest();
    }
    t->setParamName(ui->editParamName->text());
    t->setParamDesc(ui->editParamDesc->text());
    t->setDataType(ui->cmbDataType->currentData().toInt());
    t->setCmd(ui->editCommand->text());
    if (ui->editNormValue->text().isEmpty()) {
        t->setNormalValue(QVariant());
    } else {
        t->setNormalValue(ui->editNormValue->text());
    }
    if (ui->spinWarning->value()) {
        t->setWarning(ui->spinWarning->value());
    } else {
        t->setWarning(QVariant());
    }
    if (ui->spinFail->value()) {
        t->setFail(ui->spinFail->value());
    } else {
        t->setFail(QVariant());
    }
    bool ok;
    double value = ui->editLowFail->text().toDouble(&ok);
    t->setLowFailLimit(ok? value : QVariant());
    value = ui->editLowWarning->text().toDouble(&ok);
    t->setLowWarningLimit(ok? value : QVariant());
    value = ui->editHighFail->text().toDouble(&ok);
    t->setHighFailLimit(ok? value : QVariant());
    value = ui->editHighWarning->text().toDouble(&ok);
    t->setHighWarningLimit(ok? value : QVariant());
    return t;
}

/******************************************************************/

void DiagTestWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::Diag);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);

    ui->editParamName->clear();
    ui->editParamDesc->clear();
    ui->editCommand->clear();
    ui->cmbDataType->setCurrentIndex(0);
    ui->editNormValue->clear();
    ui->spinWarning->setValue(0);
    ui->spinFail->setValue(0);
    ui->editLowWarning->clear();
    ui->editHighWarning->clear();
    ui->editLowFail->clear();
    ui->editHighFail->clear();
}

/******************************************************************/

QStringList DiagTestWidget::validate()
{
    QStringList errors;
    if (ui->editParamName->text().trimmed().isEmpty()) {
        errors.append(tr("Please provide name to param"));
    }
    if (ui->editParamDesc->text().trimmed().isEmpty()) {
        errors.append(tr("Please provide description to param"));
    }
    if (ui->editCommand->text().trimmed().isEmpty()) {
        errors.append(tr("Please provide command to run"));
    }
    return errors;
}

/******************************************************************/

QString DiagTestWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Diag);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::Diag);
    case Macro::Path : return ui->editParamDesc->text();
    case Macro::Object : return ui->editParamName->text();
    default: return QString();
    }
}

/******************************************************************/

void DiagTestWidget::setupUI()
{
    connect(ui->editParamName, &QLineEdit::textChanged,
            this, &TestMethodWidget::propertiesChanged);
    connect(ui->editParamDesc, &QLineEdit::textChanged,
            this, &TestMethodWidget::propertiesChanged);

    connect(ui->cmbDataType, &QComboBox::currentTextChanged,
            this, &DiagTestWidget::onDataTypeChanged);
    connect(ui->editNormValue, &QLineEdit::textChanged,
            this, &DiagTestWidget::recalculateLimits);
    connect(ui->spinWarning, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &DiagTestWidget::recalculateLimits);
    connect(ui->spinFail, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &DiagTestWidget::recalculateLimits);
    ui->cmbDataType->addItem("Default", 2);
    ui->cmbDataType->addItem("String", 1);
    ui->cmbDataType->addItem("Float", 2);

    // TODO continue with units
}

/******************************************************************/

void DiagTestWidget::onDataTypeChanged()
{
    if (ui->cmbDataType->currentData().toInt() == 1) { // String
        ui->spinWarning->setDisabled(true);
        ui->spinFail->setDisabled(true);
        ui->valWarming->setHidden(true);
        ui->valFail->setHidden(true);
        ui->editLowWarning->setDisabled(true);
        ui->editHighWarning->setDisabled(true);
        ui->editLowFail->setDisabled(true);
        ui->editHighFail->setDisabled(true);
    } else {
        ui->spinWarning->setEnabled(true);
        ui->spinFail->setEnabled(true);
        ui->valWarming->setEnabled(true);
        ui->valFail->setEnabled(true);
        ui->editLowWarning->setEnabled(true);
        ui->editHighWarning->setEnabled(true);
        ui->editLowFail->setEnabled(true);
        ui->editHighFail->setEnabled(true);
    }
}

/******************************************************************/

void DiagTestWidget::recalculateLimits()
{
    ui->valWarming->clear();
    ui->valFail->clear();
    if (ui->cmbDataType->currentData().toInt() == 1) return;
    bool ok = true;
    double normValue = ui->editNormValue->text().toDouble(&ok);
    if (!ok) return;
    int warn = ui->spinWarning->value();
    if (warn) {
        double low = normValue * (100.0 - warn) / 100.0;
        double high = normValue * (100.0 + warn) / 100.0;
        ui->valWarming->setText(QString("%1 - %2").arg(low).arg(high));
    }
    int fail = ui->spinFail->value();
    if (fail) {
        double low = normValue * (100.0 - fail) / 100.0;
        double high = normValue * (100.0 + fail) / 100.0;
        ui->valFail->setText(QString("%1 - %2").arg(low).arg(high));
    }
}

/******************************************************************/
