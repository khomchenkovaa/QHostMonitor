#include "qMailRelayWidget.h"
#include "ui_qMailRelayWidget.h"
#include "qMailRelayTestPropertiesDlg.h"
#include "method/tMailRelay.h"

namespace SDPO {

/*****************************************************************/

MailRelayWidget::MailRelayWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::MailRelayWidget)
{
    ui->setupUi(this);
    connect(ui->btnIncoming, SIGNAL(clicked()), this, SLOT(openPropertiesDlg()));
    connect(ui->btnOutgoing, SIGNAL(clicked()), this, SLOT(openPropertiesDlg()));
    connect(ui->btnSender, SIGNAL(clicked()), this, SLOT(openPropertiesDlg()));
}

/*****************************************************************/

MailRelayWidget::~MailRelayWidget()
{
    delete ui;
}

/*****************************************************************/

void MailRelayWidget::openPropertiesDlg()
{
    MailRelayTestPropertiesDlg dlg(this);
    dlg.exec();
}

/*****************************************************************/
void MailRelayWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::MailRelay) ) {
        reset();
        return;
    }
    TMailRelay* test = qobject_cast<TMailRelay*>(item);
    ui->lnEditOutgoing->setText(test->getOutgoing());
    ui->lnEditIncoming->setText(test->getIncoming());
    ui->lnEditSender->setText(test->getSender());
}

/*****************************************************************/

TestMethod *MailRelayWidget::save(TestMethod *item)
{
    TMailRelay* test;
    if (item && (item->getTMethodID() == TMethodID::MailRelay)) {
        test = qobject_cast<TMailRelay*>(item);
    } else {
        test = new TMailRelay();
    }
    test->setOutgoing(ui->lnEditOutgoing->text());
    test->setIncoming(ui->lnEditIncoming->text());
    test->setSender(ui->lnEditSender->text());
    return test;
}

/******************************************************************/

void MailRelayWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::MailRelay);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->lnEditOutgoing->clear();
    ui->lnEditIncoming->clear();
    ui->lnEditSender->clear();
}

/******************************************************************/

QStringList MailRelayWidget::validate()
{
    QStringList errors;
    if(ui->lnEditOutgoing->text().trimmed().isEmpty()) {
        errors.append(tr("Test parametrs are not specified"));
    }
    return errors;
}

/******************************************************************/

QString MailRelayWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::MailRelay);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::MailRelay);
    case Macro::Host :return ui->lnEditOutgoing->text();
    case Macro::Object : return ui->lnEditIncoming->text();
    case Macro::Path : return ui->lnEditSender->text();
    default: return QString();
    }
}

/******************************************************************/

} // namespace SDPO
