#ifndef QSHELLSCRIPTWIDGET_H
#define QSHELLSCRIPTWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class ShellScriptWidget;
}

namespace SDPO {

class ShellScriptWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit ShellScriptWidget(QWidget *parent = 0);
    ~ShellScriptWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
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
