#include "qDicomWidget.h"
#include "ui_qDicomWidget.h"
#include "method/tDicom.h"

namespace SDPO {

/******************************************************************/

DicomWidget::DicomWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DicomWidget)
{
    ui->setupUi(this);
     connect(ui->cmbHost, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

DicomWidget::~DicomWidget()
{
    delete ui;
}

/******************************************************************/

void DicomWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::DICOM) ) {
        reset();
        return;
    }
    TDicom *dicom = qobject_cast<TDicom*>(item);
    ui->cmbHost->setCurrentText(dicom->getHost());
    ui->spinPort->setValue(dicom->getPort());
    ui->spinTimeout->setValue(dicom->getTimeout());
    ui->cmbCalledAe->setCurrentText(dicom->getCalledAeTitle());
    ui->cmbCallingAe->setCurrentText(dicom->getCallingAeTitle());
}

/******************************************************************/

TTestMethod *DicomWidget::save(TTestMethod *item)
{
    TDicom* test;
    if (item && (item->getTMethodID() == TMethodID::DICOM)) {
        test = qobject_cast<TDicom*>(item);
    } else {
        test = new TDicom();
    }
    test->setHost(ui->cmbHost->currentText());
    test->setPort(ui->spinPort->value());
    test->setTimeout(ui->spinTimeout->value());
    test->setCalledAeTitle(ui->cmbCalledAe->currentText());
    test->setCallingAeTitle(ui->cmbCallingAe->currentText());

    return test;
}

/******************************************************************/

void DicomWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::DICOM);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbHost->clear();
    ui->spinPort->setValue(DICOM_DEFAULT_PORT);
    ui->spinTimeout->setValue(60);
    ui->cmbCalledAe->clear();
    ui->cmbCallingAe->clear();
}

/******************************************************************/

QStringList DicomWidget::validate()
{
    QStringList errors;
    if(ui->cmbHost->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a Server"));
    }
    return errors;
}

/******************************************************************/

QString DicomWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::DICOM);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::DICOM);
    case Macro::Host : return ui->cmbHost->currentText();
//    case Macro::Object : return ui->cmbDatabase->currentText();
    default: return QString();
    }
}

/*****************************************************************/

} // namespace SDPO
