#include "qPingWidget.h"
#include "ui_qPingWidget.h"
#include "mSettings.h"
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

void PingWidget::init(TTestMethod *item)
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
    switch (ping->getDisplayMode()) {
        case TPing::Time: ui->rbPingDisplayTime->setChecked(true); break;
        case TPing::Lost: ui->rbPingDisplayLost->setChecked(true); break;
        case TPing::Received: ui->rbPingDisplayReceived->setChecked(true); break;
    }
}

/******************************************************************/

TTestMethod *PingWidget::save(TTestMethod *item)
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
    TMethod method = TMethod::tMethodList.at((int)TMethodID::Ping);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbPingHost->clearEditText();
    ui->chkPingDontFragment->setChecked(false);
    ui->sbPingTimeout->setValue(Settings::get(Settings::Ping_Trace, Settings::Timeout, QVariant(0)).toInt());
    ui->sbPingPacketSize->setValue(Settings::get(Settings::Ping_Trace, Settings::PacketSize, QVariant(0)).toInt());
    ui->sbPingPackets->setValue(Settings::get(Settings::Ping_Trace, Settings::Packets, QVariant(1)).toInt());
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
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Ping);
    case Macro::TestMethod : return TMethod::toName(TMethodID::Ping);
    case Macro::Host :
    case Macro::HostAddr : return ui->cmbPingHost->currentText().trimmed();
    default: return QString();
    }
}

} // namespace SDPO
