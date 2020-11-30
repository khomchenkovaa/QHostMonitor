#ifndef QMIBBROWSER_H
#define QMIBBROWSER_H

#include <QDialog>

namespace Ui {
class MibBrowser;
}

namespace SDPO {

class MibBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit MibBrowser(QWidget *parent = nullptr);
    ~MibBrowser();

    QString getOid() const;
    void setOid(const QString oid);

private slots:
    void on_btnGet_clicked();
    void on_btnGetTable_clicked();
    void on_btnFindName_clicked();
    void on_btnFindOid_clicked();

private:
    Ui::MibBrowser    *ui;
};

} // namespace SDPO

#endif // QMIBBROWSER_H
