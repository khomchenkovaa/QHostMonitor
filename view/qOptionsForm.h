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
    explicit OptionsForm(QWidget *parent = nullptr);
    ~OptionsForm();

private slots:
    void on_optionsTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_backButton_clicked();
    void on_nextButton_clicked();

public slots:
    void setCurrentPage(const int idx);
    void init();
    void prepareToSave();
    void selectOptionsTreeItem(const int idx);

private:
    void setAutostart(bool autostart);

private:
    Ui::OptionsForm *ui;
};

} // namespace SDPO

#endif // OPTIONSFORM_H
