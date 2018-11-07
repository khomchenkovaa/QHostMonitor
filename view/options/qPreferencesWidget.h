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

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

private:
    Ui::PreferencesWidget *ui;
};

} // namespace SDPO

#endif // QPREFERENCESWIDGET_H
