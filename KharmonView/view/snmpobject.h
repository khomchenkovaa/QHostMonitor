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

    void append(SnmpObject* child) {
        m_Objects.append(child);
    }

    SnmpObject* childAt(int idx) {
        return m_Objects.at(idx);
    }

    int childCount() const {
        return m_Objects.size();
    }

    int indexOf(SnmpObject* child) {
        return m_Objects.indexOf(child);
    }

    QString getName() const;
    QString getHost() const;
    int getPort() const;
    SDPO::SnmpVersion getVersion() const;
    QString getCommunity() const;
    int getTimeout() const;
    int getRetries() const;

    bool setNameIfNotEmpty(const QString &value);
    bool setHostIfNotEmpty(const QString &value);
    bool setPortIfNotEmpty(const QString &value);
    bool setVersionIfNotEmpty(const QString &value);
    bool setCommunityIfNotEmpty(const QString &value);
    bool setTimeoutIfNotEmpty(const QString &value);
    bool setRetriesIfNotEmpty(const QString &value);
    bool setModuleIfNotEmpty(const QString &value);

    void setName(const QString &name) {
        m_Name = name;
    }

    void setHost(const QString& host) {
        m_Host = host;
    }

    void setPort(int port) {
        m_Port = port;
    }

    void setVersion(int version) {
        m_Version = version;
    }

    void setCommunity(const QString& community) {
        m_Community = community;
    }

    void setTimeout(int timeout) {
        m_Timeout = timeout;
    }

    void setRetries(int retries) {
        m_Retries = retries;
    }

    void setModIdx(int modIdx) {
        m_ModIdx = modIdx;
    }

protected:
    void timerEvent(QTimerEvent *event);

public slots:
    void startView();
    void stopView();

signals:

public:
    // Общие параметры
    static QString SYSTEM;      ///< Наименование контролируемой системы
    static QString SUBSYSTEM;   ///< Наименование контролируемого объекта верхнего уровня.
    static int     DLG_TIMEOUT; ///< Интервал основного цикла опроса в сек. (по умолчанию: 10 сек.)

    static SnmpObject* root;

private:
    QString  m_Name;
    QVariant m_Host;      ///< Сетевое имя или IP-адрес узла (по умолчанию: localhost)
    QVariant m_Port;      ///< Номер порта (по умолчанию 161)
    QVariant m_Version;   ///< Версия протокола SNMP (по умолчанию SNMPv2c)
    QVariant m_Community; ///< Имя SNMP-сообщества (по умолчанию: public)
    QVariant m_Timeout;   ///< Масксимальный интервал ожидания ответа от SNMP-агента, в сек. (по умолчанию: 1 сек.)
    QVariant m_Retries;   ///< Максимальное количество повторных SNMP-запросов в случае неудачи (по умолчанию: 3)
    QVariant m_ModIdx;    ///< Индекс модуля, начиная с 1
    QList<SnmpObject*> m_Objects;
    SnmpSystem    m_System;
    SnmpStatus    m_Status;
    SnmpModList   m_Modules;
    SnmpParamList m_Params;
    int m_TimerId;
};

} // namespace KharmonView

#endif // SNMPOBJECT_H
