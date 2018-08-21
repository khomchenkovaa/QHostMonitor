#ifndef QLINKSLIST_H
#define QLINKSLIST_H

#include <QDialog>

namespace Ui {
class LinksList;
}

namespace SDPO {

class TTest;

class LinksList : public QDialog
{
    Q_OBJECT

public:
    enum Result { DoNothing, RemoveLinks, RemoveTest };

    explicit LinksList(TTest *test, QWidget *parent = 0);
    ~LinksList();

    QStringList getChecked() const;
    Result getResult() const;
    void setReadOnly();

private slots:
    void on_btnRemoveLinks_clicked();
    void on_btnRemoveTest_clicked();

private:
    Ui::LinksList *ui;
    TTest* m_test;
    Result m_result;
};

} // namespace SDPO

#endif // QLINKSLIST_H
