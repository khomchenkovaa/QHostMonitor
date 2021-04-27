#ifndef SNMPOBJECT_H
#define SNMPOBJECT_H

#include "snmpprofile.h"

#include <QObject>

namespace KharmonView {

// system struct
struct SnmpSystem {
    QString sysName;
    QString sysDescr;
    QString sysLocation;
    QString sysContact;
    int     sysType;
    QString sysParentObjectURI;
};

// status struct
struct SnmpStatus {
    int     statStatus;
    QString statStatusDesc;
    QString statLastChangeDate;
};

/*
 * modules struct
 */
struct SnmpModule {
    long    modIndex;
    QString modName;
    QString modDesc;
    int     modType;
    int     modStatus;
    QString modStatusDesc;
    QString modLastChangeDate;
    QString modURI;
};

typedef QList<SnmpModule> SnmpModList;

/*
 * parameters struct
 */
struct SnmpParameter {
    long    paramIndex;
    QString paramName;
    QString paramDesc;
    QString paramCurrValue;
    QString paramCurrValueDesc;
    int     paramType;
    int     paramDataType;
    QString paramUnits;
    int     paramStatus;
    QString paramLastChangeDate;
    QString paramNormalValue;
    QString paramLowFailLimit;
    QString paramLowWarningLimit;
    QString paramHighFailLimit;
    QString paramHighWarningLimit;
    int     paramModuleIndex;
};

typedef QList<SnmpParameter> SnmpParamList;

class SnmpObject : public QObject
{
    Q_OBJECT
public:
    explicit SnmpObject(QObject *parent = nullptr);

    QString getHost() const;
    int getPort() const;
    SDPO::SnmpVersion getVersion() const;
    QString getCommunity() const;
    int getTimeout() const;
    int getRetries() const;

signals:

public:
    // Общие параметры
    static QString g_System;          ///< Наименование контролируемой системы
    static QString g_Subsystem;       ///< Наименование контролируемого объекта верхнего уровня.
    static int     DialogTimeout;   ///< Интервал основного цикла опроса в сек. (по умолчанию: 10 сек.)

    static SnmpObject* root;

private:
    QString name;
    QVariant host;      ///< Сетевое имя или IP-адрес узла (по умолчанию: localhost)
    QVariant port;      ///< Номер порта (по умолчанию 161)
    QVariant version;   ///< Версия протокола SNMP (по умолчанию SNMPv2c)
    QVariant community; ///< Имя SNMP-сообщества (по умолчанию: public)
    QVariant timeout;   ///< Масксимальный интервал ожидания ответа от SNMP-агента, в сек. (по умолчанию: 1 сек.)
    QVariant retries;   ///< Максимальное количество повторных SNMP-запросов в случае неудачи (по умолчанию: 3)
    QList<SnmpObject*> m_Objects;
    SnmpSystem    m_System;
    SnmpStatus    m_Status;
    SnmpModList   m_Modules;
    SnmpParamList m_Params;
};

} // namespace KharmonView

#endif // SNMPOBJECT_H
