#ifndef QMIBBROWSER_H
#define QMIBBROWSER_H

#include "mibtreemodel.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QStandardItem;
class QModelIndex;
QT_END_NAMESPACE

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
    void updateFields(const QModelIndex& proxyIndex);

    void on_btnGet_clicked();
    void on_btnGetTable_clicked();
    void on_btnFindName_clicked();
    void on_btnFindOid_clicked();

private:
    Ui::MibBrowser    *ui;
    MibTreeModel      *m_Model;
    MibTreeProxyModel *m_Proxy;
};

} // namespace SDPO

#endif // QMIBBROWSER_H
