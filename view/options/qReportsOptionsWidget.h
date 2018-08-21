#ifndef QREPORTSOPTIONSWIDGET_H
#define QREPORTSOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class ReportsOptionsWidget;
}

namespace SDPO {

class ReportsOptionsWidget : public OptionsWidget
{
    Q_OBJECT
    QString curFolder;

public:
    explicit ReportsOptionsWidget(QWidget *parent = 0);
    ~ReportsOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;
    void reset_ActionProfileSelect();

    private slots:
        void on_btnCreateReport_1_clicked();
        void on_btnelectReportFile_1_clicked();
        void on_btnelectReportFile_2_clicked();
        void on_btnelectReportFile_3_clicked();
        void on_btnelectReportFile_4_clicked();
        void on_btnelectReportFile_5_clicked();
        void on_btnelectReportFile_6_clicked();
        void on_btnSelectActionProfile_clicked();

private:
    Ui::ReportsOptionsWidget *ui;
};

} // namespace SDPO

#endif // QREPORTSOPTIONSWIDGET_H
