#ifndef QACCESSMETHODOPTIONSWIDGET_H
#define QACCESSMETHODOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class AccessMethodOptionsWidget;
}

namespace SDPO {

class AccessMethodOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit AccessMethodOptionsWidget(QWidget *parent = 0);
    ~AccessMethodOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

private slots:
    void on_btnAccessProxy_clicked();
    void on_btnSelectAcessRetriveUrl();

private:
    Ui::AccessMethodOptionsWidget *ui;
};

} // namespace SDPO

#endif // QACCESSMETHODOPTIONSWIDGET_H
