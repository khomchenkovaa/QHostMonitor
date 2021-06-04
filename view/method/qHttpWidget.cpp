#include "qHttpWidget.h"
#include "ui_qHttpWidget.h"
#include "qHttpTestPropertiesDlg.h"
#include "qHttpProxiesListDlg.h"
#include "method/tHttp.h"

namespace SDPO {

/*****************************************************************/

HttpWidget::HttpWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::HttpWidget)
{
    ui->setupUi(this);
}

/*****************************************************************/

HttpWidget::~HttpWidget()
{
    delete ui;
}
/*****************************************************************/

void HttpWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::HTTP) ) {
        reset();
        return;
    }
    THttp* test = qobject_cast<THttp*>(item);
    ui->cmbProxy->setCurrentText(test->getProxy());
    ui->cmbUrl->setCurrentText(test->getUrl());
    ui->cmbRequest->setCurrentText(test->getRequest());
    ui->chkRedirect->setChecked(test->isFollowRedirect());
    ui->spinTimeout->setValue(test->getTimeout());
}


/*****************************************************************/

TTestMethod *HttpWidget::save(TTestMethod *item)
{
    THttp* test;
    if (item && (item->getTMethodID() == TMethodID::HTTP)) {
        test = qobject_cast<THttp*>(item);
    } else {
        test = new THttp();
    }
    test->setProxy(ui->cmbProxy->currentText());
    test->setUrl(ui->cmbUrl->currentText());
    test->setRequest(ui->cmbRequest->currentText());
    test->setFollowRedirect(ui->chkRedirect->isChecked());
    test->setTimeout(ui->spinTimeout->value());
    return test;
}

/******************************************************************/

void HttpWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::HTTP);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbProxy->setCurrentText(QString("<none>"));
    ui->cmbUrl->setCurrentText(QString(""));
    ui->cmbRequest->setCurrentText(QString("POST"));
    ui->chkRedirect->setChecked(false);
    ui->spinTimeout->setValue(65);
}

/******************************************************************/

QStringList HttpWidget::validate()
{
    QStringList errors;
    if(ui->cmbUrl->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, provide URL"));
    }
    return errors;
}

/******************************************************************/

QString HttpWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::HTTP);
    case Macro::TestMethod : return TMethod::toName(TMethodID::HTTP);
    case Macro::Object : return ui->cmbUrl->currentText();
    default: return QString();
    }
}

/******************************************************************/

void HttpWidget::on_btnAdvanced_clicked()
{
    HttpTestPropertiesDlg dlg;
    dlg.exec();
}

/*****************************************************************/

void HttpWidget::on_btnProxy_clicked()
{
    HttpProxiesListDlg dlg;
    dlg.exec();
}

/*****************************************************************/

} // namespace SDPO
