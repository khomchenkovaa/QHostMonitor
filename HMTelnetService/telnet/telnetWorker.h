#ifndef TELNETWORKER_H
#define TELNETWORKER_H

#include <QObject>
#include <QString>

#include "telnetConnection.h"

namespace SDPO {

class TelnetWorker: public QObject
{
Q_OBJECT

    qintptr m_SocketDescriptor;
    QString m_RciAddress;
    quint16 m_RciPort;
    int     m_Timeout;
    TelnetConnection *m_Connection;

public:
    TelnetWorker(qintptr socketDescriptor, QString address, quint16 port, int timeout);
    virtual ~TelnetWorker();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);

};

} // namespace SDPO

#endif // TELNETWORKER_H
