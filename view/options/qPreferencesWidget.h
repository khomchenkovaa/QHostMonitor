#ifndef QPREFERENCESWIDGET_H
#define QPREFERENCESWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class PreferencesWidget;
}

namespace SDPO {

class PreferencesWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit PreferencesWidget(QWidget *parent = 0);
    ~PreferencesWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private:
    Ui::PreferencesWidget *ui;
};

} // namespace SDPO

#endif // QPREFERENCESWIDGET_H
