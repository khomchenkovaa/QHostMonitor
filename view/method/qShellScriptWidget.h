#ifndef QSHELLSCRIPTWIDGET_H
#define QSHELLSCRIPTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class ShellScriptWidget;
}

namespace SDPO {

class ShellScriptWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit ShellScriptWidget(QWidget *parent = 0);
    ~ShellScriptWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnScriptManager_clicked();
    void resetScriptMenu(QVariant data = QVariant());

    void on_cmbScript_currentIndexChanged(int index);

private:
    Ui::ShellScriptWidget *ui;
};

} // namespace SDPO
#endif // QSHELLSCRIPTWIDGET_H
