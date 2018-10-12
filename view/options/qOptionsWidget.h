#ifndef QOPTIONSWIDGET_H
#define QOPTIONSWIDGET_H

#include "gSettings.h"
#include "mSettings.h"

#include <QWidget>

namespace SDPO {

class OptionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsWidget(QWidget *parent = 0);

    virtual void init(QSettings *s) { Q_UNUSED(s) }
    virtual void prepareToSave(QSettings *s) { Q_UNUSED(s) }

signals:
    void goToPage(const int idx);
};

} // namespace SDPO

#endif // QOPTIONSWIDGET_H
