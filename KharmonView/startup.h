#ifndef KHARMOVIEW_STARTUP_H
#define KHARMOVIEW_STARTUP_H

#include <QObject>

namespace KharmonView {

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

} // namespace KharmonView

#endif // KHARMOVIEW_STARTUP_H