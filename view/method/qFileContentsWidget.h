#ifndef QFILECONTENTSWIDGET_H
#define QFILECONTENTSWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class FileContentsWidget;
}

namespace SDPO {

class FileContentsWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit FileContentsWidget(QWidget *parent = 0);
    ~FileContentsWidget();

signals:

private slots:
    void on_btnEditFile_clicked();

private:
    Ui::FileContentsWidget *ui;

};

} // namespace SDPO

#endif // QFILECONTENTSWIDGET_H
