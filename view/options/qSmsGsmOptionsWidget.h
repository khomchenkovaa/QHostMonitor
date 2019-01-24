#ifndef QSMSGSMOPTIONSWIDGET_H
#define QSMSGSMOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class SmsGsmOptionsWidget;
}

namespace SDPO {

class SmsGsmOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit SmsGsmOptionsWidget(QWidget *parent = 0);
    ~SmsGsmOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

    private slots:
        void on_btnSelectLogFile_clicked();

private:
    Ui::SmsGsmOptionsWidget *ui;
};

} // namespace SDPO

#endif // QSMSGSMOPTIONSWIDGET_H
