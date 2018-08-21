#ifndef QMACROEDITORDLG_H
#define QMACROEDITORDLG_H

#include <QDialog>

namespace Ui {
class MacroEditorDlg;
}

namespace SDPO {

class MacroEditorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MacroEditorDlg(QWidget *parent = 0);
    ~MacroEditorDlg();

    QString getScript() const;
    void setScript(const QString script);

private slots:
    void currentUserMacroChanged(const int row);
    void initMacroVars();
    void on_listStandartMacroVariables_customContextMenuRequested(const QPoint &pos);
    void on_listUserDefinedMacroVariables_customContextMenuRequested(const QPoint &pos);
    void on_listFavoriteMacroVariables_customContextMenuRequested(const QPoint &pos);
    void appentStandartMacroVariable();
    void addFavoriteStandartMacroVariable();
    void appendUserDefinedVariable();
    void addFavoriteUserDefinedVariable();
    void appendFavoriteVariable();
    void moveFavoriteUp();
    void moveFavoriteDown();
    void sortFavorite();
    void removeFromFavorite();
    void on_btnRun_clicked();

private:
    Ui::MacroEditorDlg *ui;

    void init();
    void initFavorites();

};

} // namespace SDPO

#endif // QMACROEDITORDLG_H
