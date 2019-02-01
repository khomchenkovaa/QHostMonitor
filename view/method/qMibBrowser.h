#ifndef QMIBBROWSER_H
#define QMIBBROWSER_H

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
    explicit MibBrowser(QWidget *parent = 0);
    ~MibBrowser();

    QString getOid() const;
    void setOid(const QString oid);

private slots:
    void updateFields(const QModelIndex& index);

private:
    QAbstractItemModel *modelFromFile(const QString& fileName);

private:
    Ui::MibBrowser *ui;
    QAbstractItemModel *m_model;
    QStandardItem *m_topitem;
};

} // namespace SDPO

#endif // QMIBBROWSER_H
