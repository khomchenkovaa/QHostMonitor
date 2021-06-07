#include "qPingWidget.h"
#include "ui_qPingWidget.h"
#include "gSettings.h"
#include "method/tPing.h"

namespace SDPO {

/******************************************************************/

PingWidget::PingWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::PingWidget)
{
    ui->setupUi(this);
    connect(ui->cmbPingHost, SIGNAL(editTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

PingWidget::~PingWidget()
{
    delete ui;
}

/******************************************************************/

void PingWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Ping) ) {
        reset();
        return;
    }
    TPing* ping = qobject_cast<TPing*>(item);
    ui->cmbPingHost->setCurrentText(ping->getAddress());
    ui->chkPingDontFragment->setChecked(ping->isDontFragment());
    ui->sbPingTimeout->setValue(ping->getTimeout());
    ui->sbPingPacketSize->setValue(ping->getPacketSize());
    ui->sbPingPackets->setValue(ping->getPackets());
    ui->sbPingStatusBad->setValue(ping->getBadCriteria());
    switch (ping->getDisplayMode()) {
        case TPing::Time: ui->rbPingDisplayTime->setChecked(true); break;
        case TPing::Lost: ui->rbPingDisplayLost->setChecked(true); break;
        case TPing::Received: ui->rbPingDisplayReceived->setChecked(true); break;
    }
}

/******************************************************************/

TestMethod *PingWidget::save(TestMethod *item)
{
    QString host = ui->cmbPingHost->currentText().trimmed();
    ui->cmbPingHost->addItem(host);
    TPing* ping;
    if (item && (item->getTMethodID() == TMethodID::Ping)) {
        ping = qobject_cast<TPing*>(item);
        ping->setAddress(host);
    } else {
        ping = new TPing(host);
    }
    ping->setDontFragment(ui->chkPingDontFragment->isChecked());
    ping->setTimeout(ui->sbPingTimeout->value());
    ping->setPacketSize(ui->sbPingPacketSize->value());
    ping->setPackets(ui->sbPingPackets->value());
    ping->setBadCriteria(ui->sbPingStatusBad->value());
    TPing::DisplayMode mode = TPing::Time;
    if (ui->rbPingDisplayLost->isChecked()) mode = TPing::Lost;
    if (ui->rbPingDisplayReceived->isChecked()) mode = TPing::Received;
    ping->setDisplayMode(mode);
    return ping;
}

/******************************************************************/

void PingWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::Ping);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    QSettings s;
    ui->cmbPingHost->clearEditText();
    ui->chkPingDontFragment->setChecked(false);
    ui->sbPingTimeout->setValue(s.value(SKEY_PING_Timeout,0).toInt());
    ui->sbPingPacketSize->setValue(s.value(SKEY_PING_PacketSize,0).toInt());
    ui->sbPingPackets->setValue(s.value(SKEY_PING_Packets,1).toInt());
    ui->sbPingStatusBad->setValue(90);
    ui->rbPingDisplayTime->setChecked(true);
    ui->rbPingDisplayLost->setChecked(false);
    ui->rbPingDisplayReceived->setChecked(false);
}

/******************************************************************/

QStringList PingWidget::validate()
{
    QStringList errors;
    if(ui->cmbPingHost->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a host"));
    }
    return errors;
}

/******************************************************************/

QString PingWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Ping);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::Ping);
    case Macro::Host :
    case Macro::HostAddr : return ui->cmbPingHost->currentText().trimmed();
    default: return QString();
    }
}

} // namespace SDPO
