#include "telnetWorker.h"

using namespace SDPO;

/******************************************************************/

TelnetWorker::TelnetWorker(qintptr socketDescriptor, QString address, quint16 port, int timeout) :
    QObject(nullptr),
    m_SocketDescriptor(socketDescriptor),
    m_RciAddress(address),
    m_RciPort(port),
    m_Timeout(timeout)
{
    // copy data from constructor arguments to internal variables here
}

TelnetWorker::~TelnetWorker()
{
    // free resources
}

void TelnetWorker::process()
{
    // allocate resources using new here
    m_Connection = new TelnetConnection(m_SocketDescriptor, m_RciAddress, m_RciPort, this);
    connect(m_Connection, SIGNAL(finished()), this, SIGNAL(finished()));
    connect(m_Connection, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
}

/******************************************************************/

