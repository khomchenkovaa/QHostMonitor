#ifndef QOPTIONSWIDGET_H
#define QOPTIONSWIDGET_H

#include <QWidget>
#include "mSettings.h"

namespace SDPO {

class OptionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OptionsWidget(QWidget *parent = 0);

    virtual void init() {}
    virtual void prepareToSave() {}

signals:
    void goToPage(const int idx);
};

} // namespace SDPO

#endif // QOPTIONSWIDGET_H
