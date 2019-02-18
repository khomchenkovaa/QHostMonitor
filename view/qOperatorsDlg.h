#ifndef QOPERATORSDLG_H
#define QOPERATORSDLG_H

#include <QDialog>

#include "gData.h"
#include "hmListService.h"

#define ROLE_DEFAULT  "<Default>"
#define ROLE_ADMIN    "Admin"
#define ROLE_LOCAL    "local"
#define ROLE_WATCHDOG "watchdog"

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
    HMListService *m_HML;
    GUserProfileList m_userProfiles;

public:
    explicit OperatorsDlg(HMListService *hml = nullptr, QWidget *parent = nullptr);
    ~OperatorsDlg();

private slots:
    void on_listUserProfiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_btnBoxUserProfiles_accepted();
    void on_btnFolder_clicked();
    void on_btnNew_clicked();
    void on_btnCopy_clicked();
    void on_btnRename_clicked();
    void on_btnDelete_clicked();
    void on_listAcceptRemoteConnection_customContextMenuRequested(const QPoint &pos);
    void on_actAddIP_triggered();
    void on_actRemoveIP_triggered();

private:
    void init();
    void load(const int idx);
    bool save(const int idx);
    void setFieldsState(const QString &name);
};

} // namespace SDPO

#endif // QOPERATORSDLG_H
