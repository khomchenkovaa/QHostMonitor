#ifndef QACTIONWIDGET_H
#define QACTIONWIDGET_H

#include <QWidget>
#include <QVariant>

namespace SDPO {

class TestAction;

class ActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActionWidget(QWidget *parent = 0);
    virtual void init(TestAction *item = 0) {  Q_UNUSED(item) }
    virtual TestAction* save(TestAction *item) { return item; }
    virtual void reset() { }
    virtual QStringList validate() { return QStringList(); }

signals:

public slots:

};

} // namespace SDPO

#endif // QACTIONWIDGET_H
