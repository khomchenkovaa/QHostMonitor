#ifndef QODBCQUERYDLG_H
#define QODBCQUERYDLG_H

#include <QDialog>

namespace Ui {
class OdbcQueryDlg;
}

namespace SDPO {

class OdbcQueryDlg : public QDialog
{
    Q_OBJECT

public:
    explicit OdbcQueryDlg(QWidget *parent = 0);
    ~OdbcQueryDlg();

    void setFieldDataSource(const QString value);
    QString getFieldDataSource() const;
    void setFieldLogin(const QString value);
    QString getFieldLogin() const;
    void setFieldPassword(const QString value);
    QString getFieldPassword() const;
    void setFieldTimeout(const int value);
    int getFieldTimeout() const;
    void setFieldExecuteQuery(const bool value);
    bool isFieldExecuteQuery() const;
    void setFieldSqlQuery(const QString value);
    QString getFieldSqlQuery() const;
    void setFieldAlert(const bool value);
    bool isFieldAlert() const;
    void setFieldRow(const int value);
    int getFieldRow() const;
    void setFieldCol(const int value);
    int getFieldCol() const;
    void setFieldUnavailableStatus(const QString value);
    QString getFieldUnavailableStatus() const;
    void setFieldCriteriaMode(const int value);
    int getFieldCriteriaMode() const;
    void setFieldCriteriaValue(const QString value);
    QString getFieldCriteriaValue() const;

private slots:
    void onTestCheckChanged(bool connectionOnly);

    void on_btnOdbcTest_clicked();

private:
    Ui::OdbcQueryDlg *ui;
};

} // namespace SDPO

#endif // QODBCQUERYDLG_H
