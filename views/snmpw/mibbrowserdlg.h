#ifndef MIBBROWSERDLG_H
#define MIBBROWSERDLG_H

#include <QDialog>

namespace SDPO {

class MibBrowserWidget;

class MibBrowserDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MibBrowserDlg(QWidget *parent = nullptr);
    ~MibBrowserDlg();

    QString getOid() const;
    void setOid(const QString oid);

private slots:
    void openGetValueDlg();
    void openGetTableDlg();
    void openFindNameDlg();
    void openFindOidDlg();

private:
    void setupUI();

private:
    MibBrowserWidget *mibBrowserWidget;
};

} // namespace SDPO

#endif // MIBBROWSERDLG_H
