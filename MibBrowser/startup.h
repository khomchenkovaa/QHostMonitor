#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>

namespace MibBrowser {

class MainWindow;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup();
    void show() const;
    ~Startup();

private:
    MainWindow &m_mainForm;

    // singleton
    explicit Startup(const Startup& rhs);
    Startup& operator= (const Startup& rhs);

    // functions
    void load();
};

} // namespace SDPO

#endif // STARTUP_H
