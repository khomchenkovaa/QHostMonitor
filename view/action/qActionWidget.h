#ifndef QACTIONWIDGET_H
#define QACTIONWIDGET_H

#include "tTestAction.h"

#include <QWidget>
#include <QVariant>

namespace SDPO {

class ActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActionWidget(QWidget *parent = nullptr);
    virtual ~ActionWidget();
    virtual void init(TestAction *item = nullptr) {  Q_UNUSED(item) }
    virtual TestAction* save(TestAction *item) { return item; }
    virtual void reset() { }
    virtual QStringList validate() { return QStringList(); }

signals:

public slots:

};

} // namespace SDPO

#endif // QACTIONWIDGET_H
