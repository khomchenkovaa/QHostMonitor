#ifndef QSQLQUERYWIDGET_H
#define QSQLQUERYWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class SqlQueryWidget;
}

namespace SDPO {

class SqlQueryWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit SqlQueryWidget(QWidget *parent = nullptr);
    ~SqlQueryWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnSqlQuery_clicked();

private:
    Ui::SqlQueryWidget *ui;
};

} // namespace SDPO

#endif // QSQLQUERYWIDGET_H
