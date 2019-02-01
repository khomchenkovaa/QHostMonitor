#ifndef QTEXTLOGWIDGET_H
#define QTEXTLOGWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class TextLogWidget;
}

namespace SDPO {

class TextLogWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit TextLogWidget(QWidget *parent = 0);
    ~TextLogWidget();

private slots:
    void openTextLogPropertiesDlg();

    void on_btnFileDlg_clicked();

private:
    Ui::TextLogWidget *ui;
};

} // namespace SDPO

#endif // QTEXTLOGWIDGET_H
