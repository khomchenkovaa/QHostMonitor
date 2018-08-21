#ifndef QIMPORTFROMTXTFILEDLG_H
#define QIMPORTFROMTXTFILEDLG_H

#include <QDialog>

namespace Ui {
class ImportFromTxtFileDlg;
}

namespace SDPO {

class IOTextFile;

class ImportFromTxtFileDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ImportFromTxtFileDlg(IOTextFile *importer, QWidget *parent = 0);
    ~ImportFromTxtFileDlg();

signals:
    void startImport();

public slots:
    void onMessage(QString message);
    void onMessageAppend(QString append);
    void onDone(int folders, int tests, int changed, int errors, int warnings);

private:
    Ui::ImportFromTxtFileDlg *ui;
    IOTextFile *m_importer;

};

} // namespace SDPO

#endif // QIMPORTFROMTXTFILEDLG_H
