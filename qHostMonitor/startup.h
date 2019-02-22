#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>

namespace SDPO {

class MainForm;
class MonitoringService;
class ActionService;
class LogService;
class HMListService;
class RCIServer;
class TNode;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup();
    void show() const;
    ~Startup();

private:
    HMListService     &m_HML;
    LogService        &m_logService;
    ActionService     &m_actionService;
    MonitoringService &m_testRunner;
    RCIServer         &m_RCIServer;
    MainForm          &m_mainForm;

    // singleton
    explicit Startup(const Startup& rhs);
    Startup& operator= (const Startup& rhs);

    // functions
    void load();
    void loadUserDefinedVariables();
    void loadTestMethodDescription();
    void loadActionProfiles();
    void loadMailProfiles();
    void loadColorProfiles();
    void loadUserProfiles();
    void checkScriptsDir();
    void loadFoldersModel();
};

} // namespace SDPO

#endif // STARTUP_H
