#ifndef QMAILERSETTINGSWIDGET_H
#define QMAILERSETTINGSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class MailerSettingsWidget;
}

namespace SDPO {

class MailerSettingsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit MailerSettingsWidget(QWidget *parent = 0);
    ~MailerSettingsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

    private slots:
        void ShowMessagePrimaryPortChange();
        void ShowMessageBackUpPortChange();
        void on_cmbPrimaryAuthSelect(int);
        void on_cmbBackupAuthSelect(int);

private:
    Ui::MailerSettingsWidget *ui;
};

} // namespace SDPO

#endif // QMAILERSETTINGSWIDGET_H
