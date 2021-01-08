#ifndef OIDSTRING_H
#define OIDSTRING_H

#include "snmp.h"

#include <QString>

namespace SDPO {

class OidString
{
    QString oidStr;
public:
    explicit OidString(const QString& str = QString());

    bool isEmpty() const;
    bool isNumeric() const;
    QString translateToOid(bool autoInit, int bestGuess);
    QString translateToTag(bool useLong, bool autoInit, bool includeModuleName);
    MibNode tag2oid(const QString& iid, MibOid& mibOid, int* type, int bestGuess);

public: // static
    static bool getLabelIid (const QString& name, QString& lastLabel, QString& iid, OidOptions flag);
    static bool isNumericOid(const QString& name);


};

} // namespace SDPO

#endif // OIDSTRING_H
