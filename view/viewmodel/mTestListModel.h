#ifndef TESTLISTMODEL_H
#define TESTLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QColor>
#include <QIcon>

#include "tNode.h"

namespace SDPO {

class TestListModel : public QAbstractTableModel
{
    Q_OBJECT

    QList<TNode*> m_list;
    QColumnList   m_columns;
    GColorProfile m_colorProfile;
    bool          m_recursive;
    TNode        *m_current;

public:
    TestListModel(QObject *parent = nullptr);
    ~TestListModel() Q_DECL_OVERRIDE;

    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    TNode *itemFromIndex(const QModelIndex &index);

public slots:
    void setRecursive(const bool value);
    void setCurrent(TNode *value);
    void addTest(TNode *item);
    void removeTest(TNode *item);
    void updateTest(TNode *test);

private:
    void setProfile();
    void resetModel();
    QVariant getIcon(TNode *item) const;
    QVariant getColor(TNode *item) const;
    QVariant getBgColor(TNode *item) const;
    QVariant getColumn(TNode *item, int column) const;
};

} // namespace SDPO

#endif // TESTLISTMODEL_H
