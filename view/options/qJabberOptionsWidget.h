#ifndef QJABBEROPTIONSWIDGET_H
#define QJABBEROPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class JabberOptionsWidget;
}

namespace SDPO {

class JabberOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit JabberOptionsWidget(QWidget *parent = 0);
    ~JabberOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

    private slots:
        void on_btnSwitchJabberAccount_clicked();

private:
    Ui::JabberOptionsWidget *ui;
};

} // namespace SDPO

#endif // QJABBEROPTIONSWIDGET_H
