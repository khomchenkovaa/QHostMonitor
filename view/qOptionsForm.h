#ifndef OPTIONSFORM_H
#define OPTIONSFORM_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QTreeWidgetItem;
QT_END_NAMESPACE

namespace Ui {
    class OptionsForm;
}

namespace SDPO {

class OptionsForm : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsForm(QWidget *parent = 0);
    ~OptionsForm();

private slots:
    void on_optionsTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_backButton_clicked();
    void on_nextButton_clicked();
    void on_PageControl_tabBarClicked(int index);
    void on_FinishCancelHelpBtn_accepted();

public slots:
    void setCurrentPage(const int idx);

private:
    Ui::OptionsForm *ui;

    void init();
    void prepareToSave();
    void selectOptionsTreeItem(const int idx);
};

} // namespace SDPO

#endif // OPTIONSFORM_H
