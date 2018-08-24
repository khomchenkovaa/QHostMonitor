#ifndef GUNITCONVERTER_H
#define GUNITCONVERTER_H

#include "PropertyHelper.h"

namespace SDPO {

class GUnitConverter : public QObject
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Text)
    AUTO_PROPERTY(int, Value)
    AUTO_PROPERTY(QString, Ext)
    AUTO_PROPERTY(double, Number)

public:
    explicit GUnitConverter(const QString &text, QObject *parent = 0);
    explicit GUnitConverter(const int value, const QString ext, QObject *parent = 0);

    bool convert();
    QString toString();
    double toNumber();
    int fromNumber();

};

} // namespace SDPO

#endif // GUNITCONVERTER_H
