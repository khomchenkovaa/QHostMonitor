#ifndef KHARMOVIEW_STARTUP_H
#define KHARMOVIEW_STARTUP_H

#include <QObject>

namespace KharmonView {

class MainWindow;
class SnmpObjectLoader;
class SnmpObjectModel;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup();
    void show() const;
    ~Startup();

private:
    MainWindow       &m_MainForm;
    SnmpObjectLoader &m_ObjectLoader;
    SnmpObjectModel  &m_ObjectModel;

    // singleton
    explicit Startup(const Startup& rhs);
    Startup& operator= (const Startup& rhs);

    // functions
    void setup();
};

} // namespace KharmonView

#endif // KHARMOVIEW_STARTUP_H
