/*!
 * \class SDPO::TSshTest
 * \brief Connect and login to specified remote system running the SSH daemon and execute a command or shell script
 *
 * Secure Shell or SSH is a network protocol that allows data to be exchanged using a secure channel between two networked devices.
 * Used primarily on UNIX based systems to access shell accounts, SSH was designed as a replacement for TELNET and other insecure remote shells
 * SSH is typically used to log into a remote machine and execute commands.
 * The encryption used by SSH provides confidentiality and integrity of data over an insecure network, such as the Internet.
 *
 * HostMonitor can connect and login to specified remote system running the SSH daemon and execute a command or shell script.
 * This allows you to perform some tests on UNIX systems without using Remote Monitoring Agent.
 * HostMonitor may perform SSH test directly or using RMA.
 *
 * In addition to the common test parameters, the SSH test has the following options:
 *
 * \bHost
 *
 * Host name or IP address of the system that provides SSH service
 *
 * \bPort
 *
 * Specify TCP port used by SSH server (SSH server, by default, listens on TCP port 22)
 *
 * \bTimeout
 *
 * Specify timeout in miliseconds
 *
 * \bCommand
 *
 * Specify command line that should be executed on target server
 *
 * <b>Check for</b>
 *
 * SSH test allows you to check result of the command execution in 3 different ways:
 *
 * <b> a) Check for exit code </b> (just like External test method does)
 *
 * In such case HostMonitor checks errorlevel returned by the command. You should choose one of the following conditions:
 * <b> Alert if exit code: </b>
 * \li <b> is < than </b> - alert if the errorlevel returned by the program is less than a specified code
 * \li <b> is > than </b> - alert if the errorlevel returned by the program is greater than a specified code
 * \li <b> is = to </b> - alert if the errorlevel returned by the program is equal to a specified code
 * \li <b> is <> from </b> - alert if the errorlevel returned by the program is different than a specified code
 *
 * <b> b) Check for text output </b>
 *
 * HostMonitor can search for a string in the command output and start alert actions when the string exists (or doesn't exist).
 * You should specify a string and condition to alert using the following options:
 * <b> Alert if </b>
 * \li <b> string present </b> - HostMonitor will set "Bad" status when output contains specified string
 * \li <b> string absent </b> - HostMonitor will set "Bad contents" status when output does not contain specified string
 * \li <b> expression true </b> - HostMonitor will consider provided text as boolean (logical) expression, evaluate this expression using data received from the server, and set "Bad" status when retrieved data does not satisfy the required conditions.
 * For example: if you define expression like "'No errors' and not ('Error' or 'Warning')", then HostMonitor will mark test as "Ok" when command output contains string 'No error' and does not contain either 'Error' or 'Warning'
 * In the expression you may use strings (must be put in quotes (') or in double quotes (")); round brackets; logical operators "and", "or", "not".
 *
 * Additional options:
 * <b> Case sensitive </b>
 * With this option enabled search is case sensitive
 * <b> Whole words only </b>
 * Searches are for words only. With this option disabled, the search string might be found within longer words.
 * <b> Macros </b>
 * This option allows you to use <b>date & time variables</b> in the search string.
 * E.g. if you provide <tt>“%mm%-%dd%-%yyyyy%”</tt> in the search string, HostMonitor will check retrieved data for the presence of a current date and will set “Bad” status for output without current date stamp.
 *
 * <b> c) Check for Shell Script result </b>
 *
 * HostMonitor checks output text for specially formatted result string.
 * I.e. result of the command execution should follow the same rules as <b>Shell Script</b>
 *
 * Note 1: Connection Manager allows you to setup user name and password for each remote system (also you may use some default account information for all target systems)
 *
 * Note 2: HostMonitor uses <tt>sshpass</tt> command, so it should be installed (<tt>yum install sshpass</tt>)
 *
 */
#ifndef TSSHTEST_H
#define TSSHTEST_H

#include "testmethod.h"

#define SSH_COMMAND "sshpass -p '$1' ssh -o StrictHostKeychecking=$2@$3 \"$4\""

namespace SDPO {

class TSshTest : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getSshCmd)

public:
    enum CheckMode {
        cmExitCode,
        cmTextOutput,
        cmScriptResult
    };

    enum ExitCodeMode {
        LT, GT, EQ, NE
    };

    enum TextOutputMode {
        toPresent,
        toAbsent,
        toExpression
    };

private:
    Q_ENUMS(CheckMode)
    Q_ENUMS(ExitCodeMode)
    Q_ENUMS(TextOutputMode)

    AUTO_PROPERTY(QString, Host)
    AUTO_PROPERTY(int, Port)
    AUTO_PROPERTY(int, Timeout)
    AUTO_PROPERTY(QString, SshCmd)
    AUTO_PROPERTY(CheckMode, Mode)
    AUTO_PROPERTY(ExitCodeMode, ExitCodeCriteria)
    AUTO_PROPERTY(int, ExitCodeValue)
    AUTO_PROPERTY(TextOutputMode, TextOutputCriteria)
    AUTO_PROPERTY(QString, TextOutputValue)
    BOOL_PROPERTY(CaseSensitive)
    BOOL_PROPERTY(WholeWordsOnly)
    BOOL_PROPERTY(TranslateMacros)

public:
    explicit TSshTest(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE;
    virtual void parseResult(QString data) Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TSSHTEST_H
