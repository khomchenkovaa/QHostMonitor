#ifndef QFOLDERDLG_H
#define QFOLDERDLG_H

#include <QDialog>
#include "viewmodel/mFoldersAndViewsModel.h"

QT_BEGIN_NAMESPACE
class QStandardItemModel;
class QStandardItem;
QT_END_NAMESPACE

namespace Ui {
class FolderDlg;
}

namespace SDPO {

class FoldersAndViewsModel;

class FolderDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FolderDlg(QWidget *parent = 0);
    ~FolderDlg();

    QString path();
    void setModel(FoldersAndViewsModel *model, QString path);
    void activateButtons();
    bool isDisabled();
    bool isEdit();

private slots:
    void on_btnCopy_clicked();
    void on_btnEdit_clicked();
    void on_btnDisable_clicked();

private:
    Ui::FolderDlg *ui;
    FoldersAndViewsModel *m_model;
};

} // namespace SDPO

#endif // QFOLDERDLG_H
