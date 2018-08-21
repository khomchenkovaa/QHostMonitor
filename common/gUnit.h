#ifndef GUNIT_H
#define GUNIT_H

#include "PropertyHelper.h"

namespace SDPO {

class GUnit : public QObject
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Text)
    AUTO_PROPERTY(int, Value)
    AUTO_PROPERTY(QString, Ext)
    AUTO_PROPERTY(double, Number)

public:
    explicit GUnit(const QString &text, QObject *parent = 0);
    explicit GUnit(const int value, const QString ext, QObject *parent = 0);

    bool convert();
    QString toString();
    double toNumber();
    int fromNumber();

};

} // namespace SDPO

#endif // GUNIT_H
