#include "qWmiWidget.h"
#include "ui_qWmiWidget.h"
#include "xMacroVar.h"
#include "method/tWmi.h"

namespace SDPO {

/******************************************************************/

WmiWidget::WmiWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::WmiWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

WmiWidget::~WmiWidget()
{
    delete ui;
}

/******************************************************************/

void WmiWidget::init(TestMethod *item)
{
    TWmi *wmi = qobject_cast<TWmi*>(item);
    ui->cmbHost->setCurrentText(wmi->getHost());
    ui->cmbNameSpace->setCurrentText(wmi->getNameSpace());
    ui->cmbQuery->setCurrentText(wmi->getQuery());
    ui->cmbAlertIf->setCurrentText(wmi->getAlertIf());
    ui->cmbAlertSelect->setCurrentText(wmi->getAlertIfCompare());
    ui->lnAlertIf->setText(wmi->getAlertIfCount());
    ui->cmbInstance->setCurrentText(wmi->getIfInstanChanged());
}

/******************************************************************/

TestMethod *WmiWidget::save(TestMethod *item)
{
    TWmi* wmi;
    if (item && (item->getTMethodID() == TMethodID::WMI)) {
        wmi = qobject_cast<TWmi*>(item);
    } else {
        wmi = new TWmi();
    }
    wmi->setHost(ui->cmbHost->currentText());
    wmi->setNameSpace(ui->cmbNameSpace->currentText());
    wmi->setQuery(ui->cmbQuery->currentText());
    wmi->setAlertIf(ui->cmbAlertIf->currentText());
    wmi->setAlertIfCompare(ui->cmbAlertSelect->currentText());
    wmi->setAlertIfCount(ui->lnAlertIf->text());
    wmi->setIfInstanChanged(ui->cmbInstance->currentText());
    return wmi;
}

/******************************************************************/

void WmiWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::WMI);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbHost->setCurrentText(QString("localhost"));
    ui->cmbNameSpace->clear();
    ui->cmbQuery->clear();
    ui->cmbAlertIf->setCurrentText(QString("any HandleCount"));
    ui->cmbAlertSelect->setCurrentText(QString("is < than"));
    ui->lnAlertIf->setText(QString("0"));
    ui->cmbInstance->setCurrentText(QString("Unknown status"));
}

/******************************************************************/

QStringList WmiWidget::validate()
{
    QStringList errors;
    return errors;
}

/******************************************************************/

QString WmiWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::WMI);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::WMI);
    case Macro::Host :return ui->cmbHost->currentText();
    case Macro::Path : return ui->cmbQuery->currentText();
    case Macro::Object : return ui->cmbQuery->currentText();
    case Macro::Object2 : return ui->lnAlertIf->text();
    case Macro::TestMode : return ui->cmbAlertSelect->currentText();
    default: return QString();
    }

}

/******************************************************************/

} // namespace SDPO
