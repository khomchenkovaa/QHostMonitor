/*!
 * \class SDPO::TPop3Test
 * \brief Test that your mail server's POP functions are functioning perfectly
 *
 * E-mail is commonly posted and transferred between mail servers using SMTP, but access to mail is provided through POP3 (Post Office Protocol version 3).
 * POP3 test can be used to test that your mail server's POP functions are functioning perfectly.
 * To perform test HostMonitor login to the server and logout using specified user account.
 * As an option HostMonitor can check number of messages and size of messages for a specified user.
 * If messages count/size exceed specified limit, the program can start alert actions.
 *
 * In addition to the common test parameters, the POP3 test has the following options:
 *
 * \bServer
 * This is the name or IP address of the mail server you want to test, usually in the form "mail.yourcom.com".
 *
 * \bPort
 * The default POP3 port for unencrypted connection is 110;
 * POP3 servers that support secured SSL connections usually accept connections using TCP port 995.
 * If your server configured to use some non-standard port, specify port number using this property.
 *
 * \bTLS
 * This option allows you to use secured and encrypted connection (SSL).
 * You may set “None” option to use unencrypted connection, select “Implicit” or “Explicit” to use encrypted connection.
 * Supported SSL protocols: TLS1, SSL3, SSL2 and PCT1.
 * Additional SSL options located on Misc page in the Options dialog.
 *
 * \bTimeout
 * This is the amount of time in seconds the program will wait for a response from the server before the request fails.
 * Set this to 0 for no timeout (not recommended).
 *
 * <b>User Name</b>
 * HostMonitor will test the POP server by logging in to it using an existing account.
 * In the user name field, supply the name of an account that can be used for testing.
 * HostMonitor will log into the account and check the status of its mailbox without accessing, modifying or deleting any of the messages held in it.
 *
 * \bPassword
 * Supply the password for the user account HostMonitor will log into during the test.
 *
 * <b>Alert when mailbox contains more then [NN] messages</b>
 * Mark this option and specify limit amount of messages in a mailbox.
 * When this limit is reached, HostMonitor will change test status to Bad.
 *
 * <b>Alert when total size of messages bigger than [NN] MB</b>
 * Mark this option and specify the size limit of all messages in a mailbox.
 * When this limit is reached, HostMonitor will change test status to Bad.
 *
 * Note: Value of the 'Reply' field depends on the test's settings:
 * \li if test checks number of messages, HostMonitor will display number of messages
 * \li if test checks total size of messages, HostMonitor will display total size of messages.
 * \li if both these options disabled and test checks server status only (connect, login and logout), Reply value will contain the test execution time (that shows the reply speed of the server).
 * \li Reply value is empty when the program cannot connect or login to server
 */
#ifndef TPOP3TEST_H
#define TPOP3TEST_H

#include "testmethod.h"

namespace SDPO {

class TPop3Test : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getServer())
    Q_PROPERTY(QString Object READ  getLogin())
    Q_PROPERTY(QString TargetPort READ  getPort())

    AUTO_PROPERTY(QString, Server)
    AUTO_PROPERTY(quint16, Port)
    AUTO_PROPERTY(QString, Login)
    AUTO_PROPERTY(QString, TLS)
    AUTO_PROPERTY(QString, Password)
    AUTO_PROPERTY(int, Timeout)
    BOOL_PROPERTY(AlertMessage)
    AUTO_PROPERTY(int, Messages)
    BOOL_PROPERTY(AlertSize)
    AUTO_PROPERTY(int, Size)

public:
    explicit TPop3Test(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHost() const { return "localhost"; }

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual TestMethod *clone() Q_DECL_OVERRIDE;
signals:

public slots:

};

} // namespace SDPO

#endif // TPOP3TEST_H
