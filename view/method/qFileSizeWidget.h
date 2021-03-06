#ifndef QFILESIZEWIDGET_H
#define QFILESIZEWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class FileSizeWidget;
}

namespace SDPO {

class FileSizeWidget : public TestMethodWidget
{
    Q_OBJECT
public:
    explicit FileSizeWidget(QWidget *parent = 0);
    ~FileSizeWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
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
