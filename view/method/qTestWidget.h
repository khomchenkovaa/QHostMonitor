#ifndef QTESTWIDGET_H
#define QTESTWIDGET_H

#include <QWidget>
#include <QVariant>
#include <QString>
#include "PropertyHelper.h"
#include "xMacroVar.h"

namespace SDPO {

class TTestMethod;

class TestWidget : public QWidget
{
    Q_OBJECT

    AUTO_PROPERTY(QString, NamePattern)
    AUTO_PROPERTY(QString, CommentPattern)

public:
    explicit TestWidget(QWidget *parent = nullptr);
    virtual ~TestWidget();
    virtual void init(TTestMethod *item = nullptr) {  Q_UNUSED(item) }
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
