#ifndef STARTUP_H
#define STARTUP_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
QT_END_NAMESPACE

namespace SDPO {

class HMLMain;
class TestListModel;

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
    HMLMain& m_mainForm;

    QSortFilterProxyModel* filterModel;
    TestListModel* model;

    // singleton
    explicit Startup(const Startup& rhs);
    Startup& operator= (const Startup& rhs);

};

} // namespace SDPO

#endif // STARTUP_H
