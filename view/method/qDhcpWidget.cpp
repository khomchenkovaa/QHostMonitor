#include "qDhcpWidget.h"
#include "ui_qDhcpWidget.h"
#include "method/tDhcp.h"
#include <QRegExp>
#include <QValidator>

namespace SDPO {

/*****************************************************************/

DhcpWidget::DhcpWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DhcpWidget)
{
    ui->setupUi(this);
}

/*****************************************************************/

DhcpWidget::~DhcpWidget()
{
    delete ui;
}

/*****************************************************************/

void DhcpWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::DHCP) ) {
        reset();
        return;
    }
    TDhcp* test = qobject_cast<TDhcp*>(item);
    ui->cmbHost->setCurrentText(test->getHost());
    ui->spinTimeout->setValue(test->getTimeout());
    ui->cmbRequestIp->setCurrentText(test->getRequestIp());
}

/*****************************************************************/

TTestMethod *DhcpWidget::save(TTestMethod *item)
{
    TDhcp* test;
    if (item && (item->getTMethodID() == TMethodID::DHCP)) {
        test = qobject_cast<TDhcp*>(item);
    } else {
        test = new TDhcp();
    }
    test->setHost(ui->cmbHost->currentText());
    test->setTimeout(ui->spinTimeout->value());
    test->setRequestIp(ui->cmbRequestIp->currentText());
    return test;
}

/******************************************************************/

void DhcpWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::DHCP);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbHost->clear();
    ui->spinTimeout->setValue(5000);
    ui->cmbRequestIp->setCurrentText(QString("<current local IP>"));
}

/******************************************************************/

QStringList DhcpWidget::validate()
{
    QStringList errors;

    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange+ "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->cmbHost->setValidator(ipValidator);


    if(ui->cmbHost->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a server"));
    }
    if(ui->cmbHost->validator()?0:1) {
        errors.append(tr("Please, specify a server"));
    }
    if (ui->cmbRequestIp->currentText().trimmed().isEmpty())
    {
        errors.append(tr("Please, specify a file name mask"));
    }
    return errors;
}

/******************************************************************/

QString DhcpWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::CountFiles);
    case Macro::TestMethod : return TMethod::toName(TMethodID::CountFiles);
    case Macro::Host : return ui->cmbHost->currentText();
    default: return QString();
    }
}

/*****************************************************************/

} // namespace SDPO
