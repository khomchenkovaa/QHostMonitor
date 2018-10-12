#ifndef QSERVICEOPTIONSWIDGET_H
#define QSERVICEOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class ServiceOptionsWidget;
}

namespace SDPO {

class ServiceOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit ServiceOptionsWidget(QWidget *parent = 0);
    ~ServiceOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

private slots:
    void onLogOnAsChanged();

private:
    Ui::ServiceOptionsWidget *ui;
};

} // namespace SDPO

#endif // QSERVICEOPTIONSWIDGET_H
