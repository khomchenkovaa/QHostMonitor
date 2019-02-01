#ifndef QFILESIZEWIDGET_H
#define QFILESIZEWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class FileSizeWidget;
}

namespace SDPO {

class FileSizeWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit FileSizeWidget(QWidget *parent = 0);
    ~FileSizeWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

signals:

private slots:
    void on_btnFolder_clicked();

private:
    Ui::FileSizeWidget *ui;
};

} // namespace SDPO

#endif // QFILESIZEWIDGET_H
