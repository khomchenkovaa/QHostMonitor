#ifndef QOPTIONSWIDGET_H
#define QOPTIONSWIDGET_H

#include "settings.h"

#include <QWidget>

namespace SDPO {

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual void init(QSettings *s) {
        Q_UNUSED(s)
    }

    virtual void prepareToSave(QSettings *s) {
        Q_UNUSED(s)
    }

signals:
    void goToPage(const int idx);
};

} // namespace SDPO

#endif // QOPTIONSWIDGET_H
