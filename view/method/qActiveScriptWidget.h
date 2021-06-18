#ifndef QACTIVESCRIPTWIDGET_H
#define QACTIVESCRIPTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class ActiveScriptWidget;
}

namespace SDPO {

class ActiveScriptWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit ActiveScriptWidget(QWidget *parent = nullptr);
    ~ActiveScriptWidget() Q_DECL_OVERRIDE;
    virtual void init(TestMethod *item = nullptr) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnRunScript_clicked();
    void on_btnEditStoreScript_clicked();
    void on_btnTestStoreScript_clicked();

private:
    Ui::ActiveScriptWidget *ui;
};

}// namespace SDPO
#endif // QACTIVESCRIPTWIDGET_H
