#include "qShellMng.h"
#include "ui_qShellMng.h"
#include "hIOShellScripts.h"
#include <QtWidgets>

namespace SDPO {

/******************************************************************/

ShellMng::ShellMng(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShellMng),
    m_fsModel(new QFileSystemModel()),
    m_process(nullptr),
    m_current(new ShellScript())
{
    ui->setupUi(this);

    init();
}

/******************************************************************/

ShellMng::~ShellMng()
{
    delete ui;
    delete m_fsModel;
    delete m_current;
}

/******************************************************************/

void ShellMng::init()
{
    QString rootPath = getScriptDir();
    m_fsModel->setRootPath("");
    ui->lstScripts->setModel(m_fsModel);
    const QModelIndex rootIndex = m_fsModel->index(QDir::cleanPath(rootPath));
    if (rootIndex.isValid()) {
        ui->lstScripts->setRootIndex(rootIndex);
    }

    connect(m_fsModel,SIGNAL(directoryLoaded(QString)),this,SLOT(onModelDirectoryLoaded(QString)));
    connect(ui->lstScripts, SIGNAL(activated(QModelIndex)), this, SLOT(onCurrentFileChanged(QModelIndex)));
    connect(ui->lstScripts, SIGNAL(clicked(QModelIndex)), this, SLOT(onCurrentFileChanged(QModelIndex)));

    m_added = m_removed = 0;
    setValues();
}

/******************************************************************/

void ShellMng::onModelDirectoryLoaded(QString path)
{
    Q_UNUSED(path)
    m_fsModel->sort(0, Qt::AscendingOrder);
    ui->lstScripts->setCurrentIndex(m_fsModel->index(0, 0, ui->lstScripts->rootIndex()));
    onCurrentFileChanged(ui->lstScripts->currentIndex());
}

/******************************************************************/

void ShellMng::on_btnNew_clicked()
{
    QModelIndex index = ui->lstScripts->currentIndex();
    if (!index.isValid()) return;
    QString fileName = m_current->getFileName();
    QString newName = fileName.mid(fileName.lastIndexOf("/")+1);
    QDir scriptDir(getScriptDir());
    bool firstTime = true;
    while (scriptDir.exists(newName)) {
        if (!firstTime) QMessageBox::warning(this, tr("File exists"),tr("File exists. Try another name"));
        firstTime=false;
        bool ok;
        newName = QInputDialog::getText(this, tr("New script"),tr("New script name"), QLineEdit::Normal, newName, &ok);
        if (!ok) return;
    }
    m_current->loadDefaults();
    saveInfoToFile(getScriptDir() + "/" +newName);
    getValues();
    emit shellScriptsChanged();
}

/******************************************************************/

void ShellMng::on_btnCopy_clicked()
{
    QModelIndex index = ui->lstScripts->currentIndex();
    if (!index.isValid()) return;
    QString fileName = m_current->getFileName();
    QString newName = fileName.mid(fileName.lastIndexOf("/")+1);
    QDir scriptDir(getScriptDir());
    bool firstTime = true;
    while (scriptDir.exists(newName)) {
        if (!firstTime) QMessageBox::warning(this, tr("File exists"),tr("File exists. Try another name"));
        firstTime=false;
        bool ok;
        newName = QInputDialog::getText(this, tr("Copy script"),tr("Script name"), QLineEdit::Normal, newName, &ok);
        if (!ok) return;
    }
    saveInfoToFile(getScriptDir() + "/" +newName);
    emit shellScriptsChanged();
}

/******************************************************************/

void ShellMng::on_btnDelete_clicked()
{
    QModelIndex index = ui->lstScripts->currentIndex();
    if (index.isValid()) {
        m_fsModel->remove(index);
        emit shellScriptsChanged();
    }
}

/******************************************************************/

void ShellMng::on_btnImport_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Import script file"),QString(),"ScriptFiles(*.sh *.cmd)");
    if (fileName.isEmpty()) return;
    loadInfoFromFile(fileName);
    QString shortName = fileName.mid(fileName.lastIndexOf("/"));
    QString newName = getScriptDir() + shortName;
    saveInfoToFile(newName);
    getValues();
    emit shellScriptsChanged();
}

/******************************************************************/

void ShellMng::on_btnExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Export script file"),QString(),"ScriptFiles(*.sh *.cmd *.ps1)");
    if (fileName.isEmpty()) return;
    saveInfoToFile(fileName);
}

/******************************************************************/

void ShellMng::on_btnSortAlpha_clicked()
{
    if (ui->btnSortAlpha->isChecked()) {
        m_fsModel->sort(0, Qt::AscendingOrder);
    } else {
        m_fsModel->sort(0, Qt::DescendingOrder);
    }

}

/******************************************************************/

void ShellMng::on_btnSortPlatform_clicked()
{
    if (ui->btnSortPlatform->isChecked()) {
        ui->lstScripts->setViewMode(QListView::IconMode);
    } else {
        ui->lstScripts->setViewMode(QListView::ListMode);
    }

}

/******************************************************************/

void ShellMng::on_btnApply_clicked()
{
    getValues();
    saveInfoToFile(m_current->getFileName());
    emit shellScriptsChanged();
}

/******************************************************************/

void ShellMng::on_btnUsage_clicked()
{
    //! TODO implement Shell Script usage dialog
}

/******************************************************************/

void ShellMng::on_btnRevoke_clicked()
{
    setValues();
}

/******************************************************************/

void ShellMng::on_btnTest_clicked()
{
    if (ui->chbClear->isChecked()) {
        ui->txtResult->clear();
    }
    QString startCmd = ui->cmbStartCmd->currentText();
    QString script = ui->txtScript->toPlainText();
    QString params = ui->editParams->text();

    runScriptWithFile(startCmd, script, params);

    /*
    if (script.contains("#!/bin/sh")) {
        QStringList scriptLines = script.split("\n");
        if (scriptLines.count() < 2) {
            ui->txtResult->appendPlainText("Error!!! script not found");
            return;
        }
        runScriptWithStdio(scriptLines,params);
    } else {
        runScriptWithFile(startCmd, script, params);
    } */
}

/******************************************************************/

void ShellMng::onReadyRead()
{
    QString data;
    data.append(m_process->readAll());
    qDebug() << "data:" << data;
    ui->txtResult->appendPlainText(data);
}

/******************************************************************/

void ShellMng::onRunFinished(int exitCode)
{
    qDebug() << "process finished:" << exitCode;
    if( exitCode ) {
        ui->txtResult->appendPlainText(m_process->errorString());
    }
    disconnect(m_process, SIGNAL(finished(int)), this, SLOT(onRunFinished(int)));
    disconnect(m_process, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    delete m_process;
    m_process=nullptr;
}

/******************************************************************/

void ShellMng::onCurrentFileChanged(const QModelIndex &index)
{
    QFileInfo fileInfo = m_fsModel->fileInfo(index);
    loadInfoFromFile(fileInfo.absoluteFilePath());
}

/******************************************************************/

void ShellMng::runScriptWithStdio(const QStringList &scriptList, const QString &params)
{
    QString command = scriptList.at(0);
    command.remove("#!");
    m_process = new QProcess();
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, SIGNAL(finished(int)), this, SLOT(onRunFinished(int)));
    connect(m_process, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    m_process->start(command);
    if (!m_process->waitForStarted()) {
        qDebug() << "process cannot start";
        return;
    }
    QTextStream out(m_process);
    out << "script() {" << endl;
    foreach(QString scriptLine, scriptList) {
        if (!scriptLine.startsWith("#")) {
            out << scriptLine << endl;
        }
    }
    out << "}" << endl;
    out << "script " << params << endl;
    m_process->closeWriteChannel();
    if (!m_process->waitForFinished()) {
        qDebug() << "process cannot finished";
        return;
    }
}
/******************************************************************/

void ShellMng::runScriptWithFile(const QString &cmdLine, const QString &script, const QString &params)
{
    QString fileName = getTempScriptFile(script);
    if (fileName.isEmpty()) {
        qDebug() << "unknown fileName";
    }
    QString command = cmdLine;
    command.replace("%Script%",fileName,Qt::CaseInsensitive).replace("%Params%", params, Qt::CaseInsensitive);
    qDebug() << "cmd:" << command;
    m_process = new QProcess();
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, SIGNAL(finished(int)), this, SLOT(onRunFinished(int)));
    connect(m_process, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    m_process->start(command);
    if (!m_process->waitForStarted()) {
        qDebug() << "process cannot start";
        return;
    }
    if (!m_process->waitForFinished()) {
        qDebug() << "process cannot finished";
        return;
    }
    QFile tempFile(fileName);
    if (tempFile.exists()) {
        tempFile.remove();
    }
}

/******************************************************************/

QString ShellMng::getTempScriptFile(const QString &script)
{
    QTemporaryFile tempFile;
    tempFile.setAutoRemove(false);
    if (tempFile.open()) {
        QTextStream out(&tempFile);
        out << script;
        tempFile.flush();
        tempFile.close();
        if (!tempFile.setPermissions(QFileDevice::ExeOther | QFileDevice::ExeOwner | QFileDevice::ReadOwner | QFileDevice::ReadOther)) {
             qDebug() << "No permissions";
        }
        return tempFile.fileName();
    }
    return QString();
}

/******************************************************************/

void ShellMng::loadInfoFromFile(const QString fileName) {
    IOShellScripts loader;
    ShellScript *script = loader.loadFromFile(fileName);
    if (script) {
        if (m_current) {
            delete m_current;
        }
        m_current = script;
        setValues();
    }
}

/******************************************************************/

void ShellMng::saveInfoToFile(const QString &fileName) {
    IOShellScripts saver;
    saver.saveToFile(fileName, m_current);
}

/******************************************************************/

void ShellMng::getValues()
{
    m_current->setName(ui->editName->text());
    m_current->setHint(ui->editHint->text());
    m_current->setDeveloper(ui->cmbDeveloper->currentText());
    m_current->setPlatform(ui->cmbPlatform->currentText());
    m_current->setVersion(ui->spinVersion->value());
    m_current->setDate(ui->spinDate->date());
    m_current->setStartCmd(ui->cmbStartCmd->currentText());
    m_current->setScript(ui->txtScript->toPlainText());
    m_current->setComment(ui->txtComment->toPlainText());
    m_current->setHistory(ui->txtHistory->toPlainText());
}

/******************************************************************/

void ShellMng::setValues()
{
    ui->editName->setText(m_current->getName());
    ui->editHint->setText(m_current->getHint());
    ui->cmbDeveloper->setCurrentText(m_current->getDeveloper());
    ui->cmbPlatform->setCurrentText(m_current->getPlatform());
    ui->spinVersion->setValue(m_current->getVersion());
    ui->spinDate->setDate(m_current->getDate());
    ui->cmbStartCmd->setCurrentText(m_current->getStartCmd());
    ui->txtScript->setPlainText(m_current->getScript());
    ui->txtComment->setPlainText(m_current->getComment());
    ui->txtHistory->setPlainText(m_current->getHistory());
}

/******************************************************************/

QString ShellMng::getScriptDir() const
{
    QString path = QCoreApplication::applicationDirPath();
    QDir dir(path);
    dir.cd("scripts");
    return dir.absolutePath();
}

/******************************************************************/

} // namespace SDPO

