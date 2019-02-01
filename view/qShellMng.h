#ifndef QSHELLMNG_H
#define QSHELLMNG_H

#include <QDialog>
#include "viewmodel/mShellScript.h"

QT_BEGIN_NAMESPACE
class QProcess;
class QFileSystemModel;
class QModelIndex;
QT_END_NAMESPACE

namespace Ui {
class ShellMng;
}

namespace SDPO {

class ShellMng : public QDialog
{
    Q_OBJECT

    Ui::ShellMng *ui;
    QFileSystemModel *m_fsModel;
    QProcess *m_process;
    ShellScript *m_current;
    int m_added;
    int m_removed;

public:
    explicit ShellMng(QWidget *parent = 0);
    ~ShellMng();

signals:
    void shellScriptsChanged();

private slots:
    void onModelDirectoryLoaded(QString path);
    void on_btnNew_clicked();
    void on_btnCopy_clicked();
    void on_btnDelete_clicked();
    void on_btnImport_clicked();
    void on_btnExport_clicked();
    void on_btnSortAlpha_clicked();
    void on_btnSortPlatform_clicked();
    void on_btnApply_clicked();
    void on_btnUsage_clicked();
    void on_btnRevoke_clicked();
    void on_btnTest_clicked();
    void onReadyRead();
    void onRunFinished(int exitCode);
    void onCurrentFileChanged(const QModelIndex &index);

private:
    void init();
    void runScriptWithStdio(const QStringList &scriptList, const QString &params);
    void runScriptWithFile(const QString &cmdLine, const QString &script, const QString &params);
    QString getTempScriptFile(const QString &script);
    void loadInfoFromFile(const QString fileName);
    void saveInfoToFile(const QString &fileName);
    void getValues();
    void setValues();
    QString getScriptDir() const;
};

} // namespace SDPO

#endif // QSHELLMNG_H
