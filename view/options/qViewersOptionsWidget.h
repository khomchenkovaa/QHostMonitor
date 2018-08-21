#ifndef QVIEWERSOPTIONSWIDGET_H
#define QVIEWERSOPTIONSWIDGET_H

#include "qOptionsWidget.h"

namespace Ui {
class ViewersOptionsWidget;
}

namespace SDPO {

class ViewersOptionsWidget : public OptionsWidget
{
    Q_OBJECT

public:
    explicit ViewersOptionsWidget(QWidget *parent = 0);
    ~ViewersOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

    private slots:
    void on_SelectLogViewer();

    void on_btnViewersTxtLogFiles_clicked();

    void on_btnViewersHtmlLogFiles_clicked();

    void on_btnViewersDbfLogFiles_clicked();

private:
    Ui::ViewersOptionsWidget *ui;
};

} // namespace SDPO

#endif // QVIEWERSOPTIONSWIDGET_H
