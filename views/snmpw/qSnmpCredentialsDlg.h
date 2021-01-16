#ifndef QSNMPCREDENTIALSDLG_H
#define QSNMPCREDENTIALSDLG_H

#include "snmp.h"
#include "snmpprofile.h"

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class QSnmpCredentialsDlg;
}

namespace SDPO {

class QSnmpCredentialsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSnmpCredentialsDlg(QWidget *parent = nullptr);
    ~QSnmpCredentialsDlg();

    void init(int idx = 0);
    int getSelected() const;

private slots:
    void on_btnNew_clicked();
    void on_btnRename_clicked();
    void on_btnDelete_clicked();
    void on_listProfiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void valueChanged();

    void on_btnBox_accepted();

private:
   void load(const int idx);
   void save(const int idx);

private:
    Ui::QSnmpCredentialsDlg *ui;
    GSnmpCredentials m_Profiles;

};

} // namespace SDPO

#endif // QSNMPCREDENTIALSDLG_H
