#ifndef QEXPORTTOTXTDLG_H
#define QEXPORTTOTXTDLG_H

#include <QDialog>

namespace Ui {
class ExportToTxtDlg;
}

namespace SDPO {

class ExportToTxtDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ExportToTxtDlg(QWidget *parent = 0);
    ~ExportToTxtDlg();

    QString targetFile() const;
    bool isFolderIncluded() const;
    bool isLinksIncluded() const;
    int exportType() const;
    void setSelectedTests(const bool value);
private slots:
    void on_btnTargerFile_clicked();

private:
    Ui::ExportToTxtDlg *ui;
};

} // namespace SDPO

#endif // QEXPORTTOTXTDLG_H
