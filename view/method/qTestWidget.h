#ifndef QTESTWIDGET_H
#define QTESTWIDGET_H

#include <QWidget>
#include <QVariant>
#include <QString>
#include "PropertyHelper.h"

namespace SDPO {

class TTestMethod;

class TestWidget : public QWidget
{
    Q_OBJECT

    AUTO_PROPERTY(QString, NamePattern)
    AUTO_PROPERTY(QString, CommentPattern)

public:
    explicit TestWidget(QWidget *parent = 0);
    virtual void init(TTestMethod *item = 0) {  Q_UNUSED(item) }
    virtual TTestMethod* save(TTestMethod *item) { return item; }
    virtual void reset(QVariant data=QVariant()) { Q_UNUSED(data) }
    virtual QStringList validate() { return QStringList(); }

    virtual QString getTemplateValue(const QString var) const { Q_UNUSED(var) return QString(); }
    QMap<QString, QString> setTemplateVars(const QStringList &params) const;

signals:
    void propertiesChanged();

public slots:

};

} // namespace SDPO

#endif // QTESTWIDGET_H
