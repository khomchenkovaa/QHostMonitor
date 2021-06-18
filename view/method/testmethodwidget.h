#ifndef TESTMETHODWIDGET_H
#define TESTMETHODWIDGET_H

#include <QWidget>
#include <QVariantMap>
#include "PropertyHelper.h"
#include "testmethod.h"
#include "xMacroVar.h"

namespace SDPO {

class TestMethod;

class TestMethodWidget : public QWidget
{
    Q_OBJECT

protected:
    QString m_NamePattern;
    QString m_CommentPattern;

public:
    explicit TestMethodWidget(QWidget *parent = nullptr)
      : QWidget(parent) {
    }

    virtual void init(TestMethod *item = nullptr) {
        Q_UNUSED(item)
    }

    virtual TestMethod* save(TestMethod *item) {
        return item;
    }

    virtual void reset(QVariant data=QVariant()) {
        Q_UNUSED(data)
    }

    virtual QStringList validate() {
        return QStringList();
    }

    virtual QString getTemplateValue(const QString var) const {
        Q_UNUSED(var)
        return QString();
    }

    QVariantMap setTemplateVars(const QStringList &params) const {
        QVariantMap result;
        foreach (const QString &key, params) {
            result.insert(key, getTemplateValue(key));
        }
        return result;
    }

    QString getNamePattern() const {
        return m_NamePattern;
    }

    QString getCommentPattern() const {
        return m_CommentPattern;
    }

public slots:
    void setNamePattern(const QString &value) {
        if (m_NamePattern == value) return;
        m_NamePattern = value;
        emit namePatternChanged(m_NamePattern);
    }

    void setCommentPattern(const QString &value) {
        if (m_CommentPattern == value) return;
        m_CommentPattern = value;
        emit commentPatternChanged(m_CommentPattern);
    }

signals:
    void propertiesChanged();
    void namePatternChanged(const QString &value);
    void commentPatternChanged(const QString &value);

};

} // namespace SDPO

#endif // TESTMETHODWIDGET_H
