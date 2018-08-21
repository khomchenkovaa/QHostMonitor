#ifndef QMACROEDITORSCRIPTRUNNERDLG_H
#define QMACROEDITORSCRIPTRUNNERDLG_H

#include <QDialog>

namespace Ui {
class MacroEditorScriptRunnerDlg;
}

namespace SDPO {

class MacroEditorScriptRunnerDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MacroEditorScriptRunnerDlg(QWidget *parent = 0);
    ~MacroEditorScriptRunnerDlg();

    void setScript(const QString script);

private slots:
    void on_btnRun_clicked();

private:
    Ui::MacroEditorScriptRunnerDlg *ui;
};

} // namespace SDPO

#endif // QMACROEDITORSCRIPTRUNNERDLG_H
