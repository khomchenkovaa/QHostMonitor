#ifndef QPRIMARYLOGOPTIONSWIDGET_H
#define QPRIMARYLOGOPTIONSWIDGET_H

#include "qOptionsWidget.h"
#include <QStringList>

namespace Ui {
class PrimaryLogOptionsWidget;
}

namespace SDPO {

class PrimaryLogOptionsWidget : public OptionsWidget
{
    Q_OBJECT

    QStringList format;
    QString curFolder;
    QString fileName;

public:
    explicit PrimaryLogOptionsWidget(QWidget *parent = 0);
    ~PrimaryLogOptionsWidget();

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);
    void reset_AlertInaccessible();
    void reset_AlertAlive();

    private slots:
        void on_btnPrimaryLogDir_clicked();
        void on_cmbPrimaryLogSelect(int index);
        void on_btnPrimaryLogAlertInaccessible_clicked();
        void on_btnPrimaryLogAlertAlive_clicked();
        void on_btnPrimaryLogSqlEdit_clicked();
        void on_btnPrimaryLogOdbcTest_clicked();
        void setPrimaryFileLogName();

private:
    Ui::PrimaryLogOptionsWidget *ui;

};

} // namespace SDPO

#endif // QPRIMARYLOGOPTIONSWIDGET_H
