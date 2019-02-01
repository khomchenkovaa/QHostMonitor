#ifndef QUSERPREFERENCESDLG_H
#define QUSERPREFERENCESDLG_H

#include <QDialog>
#include "viewmodel/mPalettesTreeModel.h"

namespace Ui {
class UserPreferencesDlg;
}

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
class QListWidgetItem;
QT_END_NAMESPACE

namespace SDPO {

class UserPreferencesDlg : public QDialog
{
    Q_OBJECT

    Ui::UserPreferencesDlg *ui;
    PalettesTreeModel *m_PalettesModel;
    GUserProfileList m_userProfiles;
    QList<QColor> m_Colors;

public:
    explicit UserPreferencesDlg(QWidget *parent = 0);
    ~UserPreferencesDlg();

private slots:
    void on_listUserProfiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_btnColorScheme_clicked();
    void on_editColorScheme_textChanged(const QString &colorScheme);
    void on_btnCopy_clicked();
    void on_trwMonitorColors_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_btnLeft_clicked();
    void on_btnRight_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnRename_clicked();
    void on_btnCheckAll_clicked();
    void on_btnUncheckAll_clicked();
    void on_btnSortAscending_toggled(bool checked);
    void on_btnSortDescending_toggled(bool checked);
    void on_listVisibleColumns_itemSelectionChanged();
    void on_listSortColumns_itemSelectionChanged();
    void on_listSortColumns_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void onMonitorColorChanged(int id);

    void on_buttonBox_accepted();

private:
    void initColors();
    void init();
    void load(const int idx);
    void save(const int idx);

};

} // namespace SDPO

#endif // QUSERPREFERENCESDLG_H
