#ifndef QMISCELLANEOUSOPTIONSWIDGET_H
#define QMISCELLANEOUSOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class MiscellaneousOptionsWidget;
}

namespace SDPO {

class MiscellaneousOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit MiscellaneousOptionsWidget(QWidget *parent = 0);
    ~MiscellaneousOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);
    void reset_SnmpTrapAction();

private slots:
    void on_tableMisc_cellClicked(int row, int column);
    void on_selectDateFormat();

    void on_btnSelectActionProfile_clicked();

private:
    Ui::MiscellaneousOptionsWidget *ui;
};

} // namespace SDPO

#endif // QMISCELLANEOUSOPTIONSWIDGET_H
