#ifndef QUSERPREFERENCESCOPYDLG_H
#define QUSERPREFERENCESCOPYDLG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class UserPreferencesCopyDlg;
}

namespace SDPO {

class UserPreferencesCopyDlg : public QDialog
{
    Q_OBJECT

public:
    explicit UserPreferencesCopyDlg(QWidget *parent = 0);
    ~UserPreferencesCopyDlg();

    void setItems(QStringList profiles, int hiddenIdx = -1);
    QList<int> getSelectedIds();

private:
    Ui::UserPreferencesCopyDlg *ui;
};

} // namespace SDPO

#endif // QUSERPREFERENCESCOPYDLG_H
