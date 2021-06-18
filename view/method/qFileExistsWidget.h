#ifndef QFILEEXISTSWIDGET_H
#define QFILEEXISTSWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class FileExistsWidget;
}

namespace SDPO {

class FileExistsWidget : public TestMethodWidget
{
    Q_OBJECT
public:
    explicit FileExistsWidget(QWidget *parent = 0);
    ~FileExistsWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

signals:

private slots:
    void on_btnFileName_clicked();
    void onFileExistanceChanged();
    void onTimeCriteriaChanged();
    void on_chkMaxAge_clicked(bool checked);
    void on_chkMinAge_clicked(bool checked);

private:
    Ui::FileExistsWidget *ui;

};

} // namespace SDPO

#endif // QFILEEXISTSWIDGET_H
