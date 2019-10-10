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
    explicit MailerSettingsWidget(QWidget *parent = nullptr);
    ~MailerSettingsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

    private slots:
        void onPrimaryPortChange();
        void onBackUpPortChange();
        void on_cmbPrimaryAuthSelect(int);
        void on_cmbBackupAuthSelect(int);

private:
    Ui::MailerSettingsWidget *ui;
};

} // namespace SDPO

#endif // QMAILERSETTINGSWIDGET_H
