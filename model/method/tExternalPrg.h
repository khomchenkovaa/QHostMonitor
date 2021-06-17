/*!
 * \class SDPO::TExternalPrg
 * \brief Use an external application to perform a test
 *
 * HostMonitor has many built-in check types, but it can not support all possible check types.
 * That's why the program contains an External Test.
 * With the External Test, HostMonitor uses an external application to perform a test and, based on the returned errorlevel, will flag the test entry as being up or down.
 *
 * In addition to the common test parameters, the External test has the following options:
 *
 * <b>External program</b>
 * Specify command line to launch external application
 *
 * \b Condition
 * Choose condition to mark test as failed (and start alert action):
 * \li <tt>is < than</tt> - alert if the errorlevel returned by the program is less than a specified code.
 * \li <tt>is > than</tt> - alert if the errorlevel returned by the program is greater than a specified code.
 * \li <tt>is = to</tt>	- alert if the errorlevel returned by the program is equal to a specified code.
 * \li <tt>is <> from</tt> - alert if the errorlevel returned by the program is different than a specified code.
 *
 * <b>Window mode</b>
 * This parameter specifies how the application window is going to be shown. Choose one of the possible options:
 * \li \c SW_SHOWNORMAL displays an application window in its original size and position.
 * \li \c SW_HIDE starts application without displaying its window.
 * \li \c SW_MAXIMIZE displays an application window as a maximized window.
 * \li \c SW_MINIMIZE displays an application window as a minimized window.
 * \li \c SW_SHOWMINNOACTIVE displays an application window as a minimized window. The active window remains active.
 * \li \c SW_SHOWNOACTIVATE displays an application window in its original size and position. The active window remains active.
 *
 * <b>Kill application if not answer after N sec</b>
 * You may select the "Kill application after N sec" option and specify a timeout.
 * In this case if the external application hasn't returned an error level to HostMonitor within the given timeout, HostMonitor will flag the test entry as down and "kill" the external application.
 */
#ifndef TEXTERNALPRG_H
#define TEXTERNALPRG_H

#include "testmethod.h"

namespace SDPO {

class TExternalPrg : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getExternalPrg())
    Q_PROPERTY(QString Object READ getExternalPrg())

    AUTO_PROPERTY(QString, ExternalPrg)
    AUTO_PROPERTY(int, AlertMode)
    AUTO_PROPERTY(int, ExitCode)
    BOOL_PROPERTY(KillPrg)
    AUTO_PROPERTY(int, KillTimeout)

public:
    explicit TExternalPrg(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getObjectProperty() const;

    // getters and setters


    // command
    virtual void run() Q_DECL_OVERRIDE;
    virtual QString getCommand() const Q_DECL_OVERRIDE { return getExternalPrg(); }

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

private:
    TestStatus testStatusByExitCode(const int exitCode);

};

} // namespace SDPO

#endif // TEXTERNALPRG_H
