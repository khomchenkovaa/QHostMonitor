#ifndef QACTIONPROPERTIESDIALOG_H
#define QACTIONPROPERTIESDIALOG_H

#include <QDialog>
#include "action/tTestAction.h"

namespace Ui {
class ActionPropertiesDialog;
}

namespace SDPO {

class ActionPropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActionPropertiesDialog(QWidget *parent = nullptr);
    ~ActionPropertiesDialog();

    void setAddFlag(const bool isBad);
    void setIndex(int index);
    void init(TestAction *item = nullptr);
    TestAction *getResult();

private slots:
    void on_cmbSelectMode_currentIndexChanged(int index);
    void on_btnAdvancedMode_clicked();
    void actionTypeChanged(int index);

private:
    Ui::ActionPropertiesDialog *ui;
    TestAction *m_item;

};

} // namespace SDPO

#endif // QACTIONPROPERTIESDIALOG_H
