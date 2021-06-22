#include "tCountFiles.h"

#include <QFileInfo>
#include <QFileInfoList>

#include <QDebug>

namespace SDPO {

/******************************************************************/

TCountFiles::TCountFiles(QObject *parent) :
    TestMethod(TMethodID::CountFiles, parent)
{
    a_Folder = QString();
    b_TranslateMacros = false;
    a_FileNameMask = QString("*");
    b_IncludeSybFolder = false;
    a_Condition = CountCondition::AllFiles;
    a_CountValue = 60;
    a_AlertWhen = 100;
}

/******************************************************************/

void TCountFiles::run()
{
    writeLogTitle();
    TestResult result;
    QString folder = getTranslated(a_Folder, b_TranslateMacros);
    QDir dir(folder);
    if (!dir.exists()) {
        QString errString = tr("Path %1 does not exists").arg(folder);
        result.error = errString;
        m_Log.append("Error!!! ").append(errString);
        m_Result = result;
        emit testFailed();
        return;
    }
    int cnt = countFiles(dir);
    result.reply = cnt;
    result.replyDesc = QString("%1 files found").arg(cnt);
    result.status = cnt > a_AlertWhen ? TestStatus::Bad : TestStatus::Ok;
    m_Result = result;
    m_Log.append(result.replyDesc);
    emit testSuccess();
}

/******************************************************************/

TestMethod *TCountFiles::clone()
{
    TCountFiles *result = new TCountFiles(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Folder = a_Folder;
    result->b_TranslateMacros = b_TranslateMacros;
    result->a_FileNameMask = a_FileNameMask;
    result->b_IncludeSybFolder = b_IncludeSybFolder;
    result->a_Condition = a_Condition;
    result->a_CountValue = a_CountValue;
    result->a_AlertWhen = a_AlertWhen;
    return result;
}

/******************************************************************/

int TCountFiles::countFiles(QDir dir)
{
    int result = 0;
    QFileInfoList fileList = dir.entryInfoList(QStringList(a_FileNameMask), QDir::Files | QDir::NoSymLinks);
    QFileInfoList subdirList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    switch (a_Condition) {
    case TCountFiles::AllFiles :
        result = fileList.count();
        break;
    case TCountFiles::OlderThan : {
        QDateTime controlDate = QDateTime::currentDateTime().addSecs((-60) * a_CountValue);
        foreach (const QFileInfo &file, fileList) {
            if (file.lastModified() < controlDate) {
                result++;
            }
        }
    }
        break;
    case TCountFiles::NewerThan : {
        QDateTime controlDate = QDateTime::currentDateTime().addSecs((-60) * a_CountValue);
        foreach (const QFileInfo &file, fileList) {
            if (file.lastModified() > controlDate) {
                result++;
            }
        }
    }
        break;
    case TCountFiles::BiggerThan :
        foreach (const QFileInfo &file, fileList) {
            if (file.size() > a_CountValue) {
                result++;
            }
        }
        break;
    case TCountFiles::SmallerThan :
        foreach (const QFileInfo &file, fileList) {
            if (file.size() < a_CountValue) {
                result++;
            }
        }
        break;
    case TCountFiles::SubfolderOnly :
        result = subdirList.count();
        break;
    }

    if (b_IncludeSybFolder) {
        foreach (const QFileInfo &subdirInfo, subdirList) {
            QDir subdir(subdirInfo.canonicalFilePath());
            result += countFiles(subdir);
        }
    }

    return result;
}

/******************************************************************/

QString TCountFiles::getTestMethod() const
{
    return QString("Count Files: %1/%2").arg(a_Folder).arg(a_FileNameMask);
}

/******************************************************************/

QString TCountFiles::getTestedObjectInfo() const
{
    return QString("Count Files test (%1)").arg(a_Folder);
}

/******************************************************************/


} // namespace SDPO
