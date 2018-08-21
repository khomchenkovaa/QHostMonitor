#ifndef TAGENT_H
#define TAGENT_H

#include <QObject>
#include <QMetaEnum>

namespace SDPO {

/**
 * @brief RMA (Remote Monitoring Agent) is a small application that accepts requests from HostMonitor, performs test and provides information about test result back to HostMonitor.
 */
class TAgent : public QObject
{
    Q_OBJECT
    Q_ENUMS(TypeRMA)
    Q_ENUMS(StatusRMA)
public:
    enum TypeRMA {
        HostMonitor,
        PassiveRMA, // accepts requests from HostMonitor, performs test (or action) and provides information about test result back to HostMonitor
        ActiveRMA // establishes connection with HostMonitor and RMA Manager
    };
    enum StatusRMA {
        OperableRMA,
        NoAnswerRMA,
        BadAnswerRMA
    };
    explicit TAgent(QObject *parent = 0);
    ~TAgent();

    QString name() const { return _name; }
    void setName(const QString value) { _name = value; }

signals:

public slots:

private:
    // connection parameters
    TypeRMA _type;
    QString _address; // the host name or an IP address of the system where RMA is installed
    QString _name; // name of the agent. By default an address of an agent will be used as name for it
    int _port; // TCP port that will be used for communication between HostMonitor and the agent. (by default agent uses port #1055)
    int _timeout; // communication timeout in seconds. A maximum amount of time that HostMonitor will wait for an answer from the agent
    QString _password; // the same password that specified when an agent was installed and configured on a remote system.

    //! No Backup agents at this time

    // Information from agent
    QString _agent; // an internal name of an agent;
    QString _platform; // OS platform that this agent is designed for
    QString _version; // the version number of the agent
    QString _developer; // the company that created RMA software
    QString _comment; // the content of a comment field that you or system administrator had provided when a remote agent was installed and configured
    QString _host;

    /** Tests supported for *nix:
     * TCP, UDP, UNC, Folder/File Size, Count Files, File/Folder Availability, File Integrity
     * Text Log, Compare Files, Process, CPU Usage, Shell Script, External
     */
    QStringList _testsSupported;

    /** Actions supported for *nix:
     * Execute external command, TCP/UDP send, Syslog
     */
    QStringList _actionsSupported;

    /** If connection with an agent was established, HostMonitor updates all agent information and sets status of the agent to "operable".
     * If HostMonitor was not able to get proper information from an agent, it sets its` status to "no answer" (if no answer from agent received)
     * or "bad answer" (if some error code was received from an agent, e.g. wrong password).
     */
    StatusRMA _status; //

};

} // namespace SDPO

#endif // TAGENT_H
