#ifndef QCOUNTFILESWIDGET_H
#define QCOUNTFILESWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class CountFilesWidget;
}

namespace SDPO {

class CountFilesWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit CountFilesWidget(QWidget *parent = 0);
    ~CountFilesWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_CountSelect();

    void on_btnEditFolder_clicked();

private:
    Ui::CountFilesWidget *ui;
};

} // namespace SDPO
#endif // QCOUNTFILESWIDGET_H
