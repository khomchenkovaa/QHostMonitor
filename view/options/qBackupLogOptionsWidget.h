#ifndef QBACKUPLOGOPTIONSWIDGET_H
#define QBACKUPLOGOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class BackupLogOptionsWidget;
}

namespace SDPO {

class BackupLogOptionsWidget : public OptionsWidget
{
    Q_OBJECT

    int names;
    QStringList format;
    QString curFolder;
    QString fileName;

public:
    explicit BackupLogOptionsWidget(QWidget *parent = 0);
    ~BackupLogOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);
    void reset_AlertInaccessible();

     private slots:
        void on_btnBackupLogDir_clicked();
        void on_cmbBackupLogSelect(int index);
        void on_btnBackupLogAlertInaccessible_clicked();
        void on_btnBackupLogSqlEdit_clicked();
        void on_btnBackupLogOdbcTest_clicked();
        void setBackupFileLogName();
private:
    Ui::BackupLogOptionsWidget *ui;
};

} // namespace SDPO

#endif // QBACKUPLOGOPTIONSWIDGET_H
