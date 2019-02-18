#ifndef QMAILPROFILESDLG_H
#define QMAILPROFILESDLG_H

#include <QDialog>

namespace Ui {
class MailProfilesDlg;
}

namespace SDPO {

class MailProfilesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MailProfilesDlg(QWidget *parent = nullptr);
    ~MailProfilesDlg();

    void init(int row = 0);
    int getSelected() const;
private slots:
    void currentChanged(int idx);

    void on_btnNew_clicked();
    void on_btnCopy_clicked();
    void on_btnRename_clicked();
    void on_btnDelete_clicked();
    void on_cmbEmailBody_currentIndexChanged(int index);
    void on_cmbCharset_currentTextChanged(const QString &charset);

    void on_emailEdit_textChanged();

private:
    Ui::MailProfilesDlg *ui;
};

} // namespace SDPO

#endif // QMAILPROFILESDLG_H
