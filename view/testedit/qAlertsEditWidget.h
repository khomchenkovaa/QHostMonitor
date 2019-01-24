#ifndef QALERTSEDITWIDGET_H
#define QALERTSEDITWIDGET_H

#include <QWidget>
#include <QVariant>

namespace Ui {
class AlertsEditWidget;
}

namespace SDPO {

class TTest;

class AlertsEditWidget : public QWidget
{
    Q_OBJECT

    QStringList m_headers;

public:
    explicit AlertsEditWidget(QWidget *parent = 0);
    ~AlertsEditWidget();

    void init(TTest *item = 0);
    void save(TTest *item);
    void reset();

private slots:
    void on_cmbActionProfile_currentIndexChanged(int index);
    void on_btnActionProfiles_clicked();

private:
    Ui::AlertsEditWidget *ui;
};

} // namespace SDPO

#endif // QALERTSEDITWIDGET_H
