#ifndef QPALETTESWIN_H
#define QPALETTESWIN_H

#include <QDialog>
#include "viewmodel/mPalettesTreeModel.h"

namespace Ui {
class PalettesWin;
}

namespace SDPO {

class PalettesWin : public QDialog
{
    Q_OBJECT

    Ui::PalettesWin *ui;
    PalettesTreeModel *m_model;

public:
    explicit PalettesWin(QWidget *parent = 0);
    ~PalettesWin();

    void init(const QString name = QString());
    QString getSelected() const;

private slots:
    void currentChanged();

    void on_btnNew_clicked();
    void on_btnCopy_clicked();
    void on_btnRename_clicked();
    void on_btnDelete_clicked();
    void on_trvReport_clicked(const QModelIndex &index);
    void on_trvReport_customContextMenuRequested(const QPoint &pos);

private:
    void changeColor(const int row, const int backgroundIdx);
    bool mouseEvent(const int row, QEvent *event);

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

} // namespace SDPO {

#endif // QPALETTESWIN_H
