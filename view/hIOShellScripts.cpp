#include "hIOShellScripts.h"
#include "viewmodel/mShellScript.h"

#include <QDir>
#include <QDebug>

namespace SDPO {

/******************************************************************/

IOShellScripts::IOShellScripts(QObject *parent) :
    QObject(parent)
{
}

/******************************************************************/

QList<ShellScript*> IOShellScripts::load(const QString dirName)
{
    QList<ShellScript*> result;
    QDir dir(dirName);
    if(dir.exists()){
        QStringList fileList=dir.entryList(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        foreach(QString fileName, fileList) {
            ShellScript *script = loadFromFile(dirName + "/" + fileName);
            if (script) {
                result.append(script);
            }
        }
    }
    return result;
}

/******************************************************************/
/* Script example
#!/bin/sh
#[Name] Process: # of instances
#[Hint] Params: <ProcName>  <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 04.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
# Parameters:
# - ProcName: name of the process that has to be checked. On Solaris you
#[History]
# Aug 04, 2017	v 1.3	KS-Soft: macOS support
# Nov 07, 2006	v 1.2	KS-Soft: NetBSD, OpenBSD support
 */

ShellScript *IOShellScripts::loadFromFile(const QString fileName)
{
    //qDebug() << "loading from file" << fileName;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ShellScript *script = new ShellScript();
        script->setFileName(fileName);
        bool readingComments(false);
        bool readingHistory(false);
        QString scrText, scrComment, scrHistory;
        QTextStream in(&file);
        while (!in.atEnd()) {
             QString line = in.readLine();
             if (line.startsWith("#")) {
                 if (line.startsWith("#!")) {
                     scrText.append(line + "\n");
                 } else if (line.contains("[Name]")) {
                     QString name = line.mid(line.indexOf("[Name]")+6).trimmed();
                     script->setName(name);
                     readingComments = readingHistory = false;
                 } else if (line.contains("[Hint]")) {
                     QString hint = line.mid(line.indexOf("[Hint]")+6).trimmed();
                     script->setHint(hint);
                     readingComments = readingHistory = false;
                 } else if (line.contains("[Developer]")) {
                     QString developer = line.mid(line.indexOf("[Developer]")+11).trimmed();
                     script->setDeveloper(developer);
                     readingComments = readingHistory = false;
                 } else if (line.contains("[Platform]")) {
                     QString platform = line.mid(line.indexOf("[Platform]")+10).trimmed();
                     script->setPlatform(platform);
                     readingComments = readingHistory = false;
                 } else if (line.contains("[Version]")) {
                     QString version = line.mid(line.indexOf("[Version]")+9).trimmed();
                     script->setVersion(version.toDouble());
                     readingComments = readingHistory = false;
                 } else if (line.contains("[Date]")) {
                     QString date = line.mid(line.indexOf("[Date]")+6).trimmed();
                     script->setDate(QDate::fromString(date, "dd.MM.yyyy"));
                     readingComments = readingHistory = false;
                 } else if (line.contains("[Start cmd]")) {
                     QString cmd = line.mid(line.indexOf("[Start cmd]")+11).trimmed();
                     script->setStartCmd(cmd);
                     readingComments = readingHistory = false;
                 } else if (line.contains("[Comment]")) {
                     readingComments = true;
                     readingHistory = false;
                 } else if (line.contains("[History]")) {
                     readingComments = false;
                     readingHistory = true;
                 } else if (readingComments) {
                     scrComment.append(line.mid(1) + "\n");
                 } else if (readingHistory) {
                     scrHistory.append(line.mid(1) + "\n");
                 }
             } else {
                 scrText.append(line + "\n");
             }
        }
        file.close();
        script->setComment(scrComment);
        script->setHistory(scrHistory);
        script->setScript(scrText);
        return script;
    }
    return 0;
}

void IOShellScripts::saveToFile(const QString fileName, const ShellScript *script)
{
    //qDebug() << "saving script" << script->getName() << "to file" << fileName;
    QStringList scrText = script->getScript().split("\n");
    if (!scrText.count()) {
        qDebug() << "No script presented";
        return;
    }
    QStringList scrComment = script->getComment().split("\n");
    QStringList scrHistory = script->getHistory().split("\n");
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        if (scrText.at(0).startsWith("#!")) {
            out << scrText.at(0) << endl;
        }
        out << "#[Name] " << script->getName() << endl;
        out << "#[Hint] " << script->getHint() << endl;
        out << "#[Developer] " << script->getDeveloper() << endl;
        out << "#[Platform] " << script->getPlatform() << endl;
        out << "#[Version] " << script->getVersion() << endl;
        out << "#[Date] " << script->getDate().toString("dd.MM.yyyy") << endl;
        out << "#[Start cmd] " << script->getStartCmd() << endl;
        out << "#[Comment]" << endl;
        foreach(QString line, scrComment) {
            out << "#" << line << endl;
        }
        out << "#[History]" << endl;
        foreach(QString line, scrHistory) {
            out << "#" << line << endl;
        }
        if (!scrText.at(0).startsWith("#!")) {
            out << scrText.at(0) << endl;
        }
        for (int i=1; i<scrText.count(); ++i) {
            out << scrText.at(i) << endl;
        }
        file.flush();
        file.close();
        file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner |
                            QFileDevice::ReadGroup | QFileDevice::WriteGroup | QFileDevice::ExeGroup );
    }
}

/******************************************************************/

} // namespace SDPO
