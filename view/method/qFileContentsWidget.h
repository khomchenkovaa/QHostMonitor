#ifndef QFILECONTENTSWIDGET_H
#define QFILECONTENTSWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class FileContentsWidget;
}

namespace SDPO {

class FileContentsWidget : public TestMethodWidget
{
    Q_OBJECT
public:
    explicit FileContentsWidget(QWidget *parent = 0);
    ~FileContentsWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;

    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

signals:

private slots:
    void on_btnEditFile_clicked();

private:
    Ui::FileContentsWidget *ui;

};

} // namespace SDPO

#endif // QFILECONTENTSWIDGET_H
