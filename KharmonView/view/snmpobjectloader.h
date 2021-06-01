#ifndef SNMPOBJECTLOADER_H
#define SNMPOBJECTLOADER_H

#include "snmpobject.h"

#include <QTextStream>

namespace KharmonView {

/*************************************************************/

struct UnicodedStream : QTextStream
{
    using QTextStream::QTextStream;

    template<typename T>
    UnicodedStream& operator<<(T const& t) {
        return static_cast<UnicodedStream&>(static_cast<QTextStream&>(*this) << t);
    }

    UnicodedStream& operator<<(char const* ptr) {
        return static_cast<UnicodedStream&>(*this << QString(ptr));
    }
};

/*************************************************************/

class SnmpObjectLoader : public QObject
{
    Q_OBJECT
public:
    explicit SnmpObjectLoader(QObject *parent = nullptr);

    QString fileName() const {
        return m_FileName;
    }

public slots:
    void create();
    void load(const QString &fileName = QString());
    void save(const QString &fileName = QString());

signals:
    void loadFailed(const QString &err);
    void saveFailed(const QString &err);

private:
    bool parseConf(const QString &diagConf);
    QString valueForKey(const QString &line, const QString &key) const;
    void printObject(UnicodedStream &out, SnmpObject *node, const QString &indent = QString());

private:
    QString m_FileName;

};

/*************************************************************/

} // namespace KharmonView

#endif // SNMPOBJECTLOADER_H
