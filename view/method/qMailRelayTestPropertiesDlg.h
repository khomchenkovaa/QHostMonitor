#ifndef QMAILRELAYTESTPROPERTIESDLG_H
#define QMAILRELAYTESTPROPERTIESDLG_H

#include <QDialog>

namespace Ui {
class MailRelayTestPropertiesDlg;
}

namespace SDPO {

class MailRelayTestPropertiesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MailRelayTestPropertiesDlg(QWidget *parent = 0);
    ~MailRelayTestPropertiesDlg();

private:
    Ui::MailRelayTestPropertiesDlg *ui;
};

} // namespace SDPO

#endif // QMAILRELAYTESTPROPERTIESDLG_H
