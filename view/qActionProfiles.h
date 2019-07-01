#ifndef QACTIONPROFILES_H
#define QACTIONPROFILES_H

#include <QDialog>
#include <QAbstractTableModel>
#include <QList>
#include "action/tTestAction.h"

namespace Ui {
class ActionProfiles;
}

namespace SDPO {

class ActionsTreeModel;

class ActionProfiles : public QDialog
{
    Q_OBJECT

    ActionsTreeModel *m_badModel;
    ActionsTreeModel *m_goodModel;
public:
    explicit ActionProfiles(QWidget *parent = 0);
    ~ActionProfiles();

    void init(int row = 0);
    int getSelected() const;
private slots:
    void currentChanged();
    void onBadCurrentChanged();
    void onGoodCurrentChanged();

    void on_btnProfilesNew_clicked();
    void on_btnProfilesCopy_clicked();
    void on_btnProfilesRename_clicked();
    void on_btnProfilesDelete_clicked();
    void on_btnProfilesSort_clicked();

    void on_btnBadAdd_clicked();
    void on_btnBadEdit_clicked();
    void on_btnBadDel_clicked();

    void on_btnGoodAdd_clicked();
    void on_btnGoodEdit_clicked();
    void on_btnGoodDel_clicked();

    void on_btnCommentAdd_clicked();

    void on_btnFindReplace_clicked();
    void on_btnUsageReport_clicked();

private:
    Ui::ActionProfiles *ui;

};

/******************************************************************/

class ActionsTreeModel : public QAbstractTableModel
{
    Q_OBJECT

    QList<TestAction*> m_data;
    QStringList m_header;
public:
    ActionsTreeModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    void setActionList(QList<TestAction *> &actions);
};

} // namespase SDPO

#endif // QACTIONPROFILES_H
