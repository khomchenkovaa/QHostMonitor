#ifndef QOPERATORSDLG_H
#define QOPERATORSDLG_H

#include <QDialog>

#include "gData.h"

namespace Ui {
class OperatorsDlg;
}

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

namespace SDPO {

class OperatorsDlg : public QDialog
{
    Q_OBJECT

    Ui::OperatorsDlg *ui;
    GUserProfileList m_userProfiles;

public:
    explicit OperatorsDlg(QWidget *parent = 0);
    ~OperatorsDlg();

private slots:
    void on_listUserProfiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_btnBoxUserProfiles_accepted();

private:
    void init();
    void load(const int idx);
    void save(const int idx);
};

} // namespace SDPO

#endif // QOPERATORSDLG_H
