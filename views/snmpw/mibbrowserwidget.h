#ifndef MIBBROWSERWIDGET_H
#define MIBBROWSERWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QModelIndex;
class QTreeView;
class QLineEdit;
class QPlainTextEdit;
QT_END_NAMESPACE

namespace SDPO {

class MibTreeModel;
class MibTreeProxyModel;

class MibBrowserWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MibBrowserWidget(QWidget *parent = nullptr);

    QString getOid() const;
    void setOid(const QString& oid);
    void findByName(const QString& name);

private slots:
    void updateFields(const QModelIndex& proxyIndex);

private:
    void setupUI();
    void init();

private:
    MibTreeModel      *m_Model;
    MibTreeProxyModel *m_Proxy;
    QTreeView         *treeMibs;
    QLineEdit         *editMib;
    QLineEdit         *editOid;
    QLineEdit         *editSyntax;
    QLineEdit         *editAccess;
    QLineEdit         *editStatus;
    QPlainTextEdit    *txtDescription;
};

} // namespace SDPO

#endif // MIBBROWSERWIDGET_H
