#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>

namespace SDPO {

class MainForm;
class MonitoringService;
class ActionService;
class LogService;
class HMListService;
class TNode;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup();
    void show() const;
    ~Startup();

signals:

public slots:

private:
    MainForm& m_mainForm;
    HMListService& m_HML;
    MonitoringService& m_testRunner;
    ActionService& m_actionService;
    LogService& m_logService;

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
