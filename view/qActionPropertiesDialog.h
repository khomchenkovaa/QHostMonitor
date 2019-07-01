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

    TestAction *m_item;
public:
    explicit ActionPropertiesDialog(QWidget *parent = nullptr);
    ~ActionPropertiesDialog();

    void setAddFlag(const bool isBad);
    void setIndex(const int index);
    void init(TestAction *item);
    TestAction *getResult();
private slots:
    void on_cmbSelectMode_currentIndexChanged(int index);

    void on_btnAdvancedMode_clicked();

private:
    Ui::ActionPropertiesDialog *ui;

};

} // namespace SDPO

#endif // QACTIONPROPERTIESDIALOG_H
