#include "qImportFromTxtFileDlg.h"
#include "ui_qImportFromTxtFileDlg.h"
#include "io/ioTextFile.h"

namespace SDPO {

/******************************************************************/

ImportFromTxtFileDlg::ImportFromTxtFileDlg(IOTextFile *importer, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportFromTxtFileDlg),
    m_importer(importer)
{
    ui->setupUi(this);
    ui->buttonBox->setDisabled(true);
    connect(m_importer, SIGNAL(importMessage(QString)), this, SLOT(onMessage(QString)), Qt::QueuedConnection);
    connect(m_importer, SIGNAL(importMessageAppend(QString)), this, SLOT(onMessageAppend(QString)), Qt::QueuedConnection);
    connect(m_importer, SIGNAL(importDone(int,int,int,int,int)), this, SLOT(onDone(int,int,int,int,int)), Qt::QueuedConnection);
    connect(this, SIGNAL(startImport()), m_importer, SLOT(importTextFile()));
    emit startImport();
}

/******************************************************************/

ImportFromTxtFileDlg::~ImportFromTxtFileDlg()
{
    delete ui;
}

/******************************************************************/

void ImportFromTxtFileDlg::onMessage(QString message)
{
    ui->plainTextEdit->appendPlainText(message);
}

/******************************************************************/

void ImportFromTxtFileDlg::onMessageAppend(QString append)
{
    QString text = ui->plainTextEdit->toPlainText();
    text.append(append);
    ui->plainTextEdit->setPlainText(text);
}

/******************************************************************/

void ImportFromTxtFileDlg::onDone(int folders, int tests, int changed, int errors, int warnings)
{
    ui->plainTextEdit->appendPlainText("Done");
    ui->plainTextEdit->appendPlainText(QString(" new folders: %1").arg(folders));
    ui->plainTextEdit->appendPlainText(QString(" new tests: %1").arg(tests));
    ui->plainTextEdit->appendPlainText(QString(" changed tests: %1").arg(changed));
    ui->plainTextEdit->appendPlainText(QString(" errors: %1").arg(errors));
    ui->plainTextEdit->appendPlainText(QString(" warnings: %1").arg(warnings));
    ui->buttonBox->setEnabled(true);
}

/******************************************************************/

} // namespace SDPO
