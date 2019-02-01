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

    virtual void init(QSettings *s);
    virtual void prepareToSave(QSettings *s);

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
