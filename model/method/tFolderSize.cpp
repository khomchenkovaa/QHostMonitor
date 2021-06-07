#include "tFolderSize.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QDir>

namespace SDPO {

/******************************************************************/

TFolderSize::TFolderSize(QObject *parent) :
    TestMethod(TMethodID::FileSize, parent)
{
    a_Path = QCoreApplication::applicationDirPath();
    b_IncludeSubfolders = false;
    b_TranslateMacros = false;
    a_MaxSize = 64;
    a_Dimension = "Kb";
}

/******************************************************************/

void TFolderSize::run()
{
    TTestResult result;

    qint64 folderSize = diskUsage(a_Path); // bytes
    if (a_Dimension.startsWith("K")) { // KB
        folderSize = folderSize / 1024;
    } else if (a_Dimension.startsWith("M")) { // MB
        folderSize = folderSize / 1024 / 1024;
    } else if (a_Dimension.startsWith("G")) { // Gb
        folderSize = folderSize / 1024 / 1024 / 1024;
    }

    result.replyInt = (int)folderSize;
    result.replyDouble = folderSize;
    result.reply = QString::number(folderSize) + a_Dimension;

    if (folderSize > a_MaxSize) {
        result.status = TestStatus::Bad;
    } else {
        result.status = TestStatus::Ok;
    }

    m_Result = result;

    emit testSuccess();
}

/******************************************************************/

TestMethod *TFolderSize::clone()
{
    TFolderSize *result = new TFolderSize(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_Path = a_Path;
    result->b_IncludeSubfolders = b_IncludeSubfolders;
    result->b_TranslateMacros = b_TranslateMacros;
    result->a_MaxSize = a_MaxSize;
    result->a_Dimension = a_Dimension;
    return result;

}

/******************************************************************/

QString TFolderSize::getTestMethod() const
{
    return QString("Folder size");
}

/******************************************************************/

QString TFolderSize::getTestedObjectInfo() const
{
    return QString("Folder size %1").arg(a_Path);
}

/******************************************************************/

QString TFolderSize::getObjectProperty() const
{
    QFileInfo fInfo(a_Path);
    return fInfo.baseName();
}

/******************************************************************/
// designed to match the results of the standard
// cross platform utility "du" (Disk Usage)
// compare to du -b [path]
quint64 TFolderSize::diskUsage( const QString &absPath, int &itemCount )
{
    QFileInfo parentInfo( absPath );
    if( parentInfo.exists() ) itemCount++;
    quint64 totalBytes =
        parentInfo.isSymLink() ?
// handle symlink size correctly
        parentInfo.symLinkTarget().length()
        : parentInfo.size();
    if( parentInfo.isDir() )
    {
        QFileInfoList childInfoList = QDir( absPath ).entryInfoList(
            QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoDotAndDotDot );
        foreach( const QFileInfo &childInfo, childInfoList )
        {
            if (!b_IncludeSubfolders && childInfo.isDir()) continue;
            totalBytes += diskUsage(
                childInfo.absoluteFilePath(), itemCount );
        }
    }
    return totalBytes;
}

/******************************************************************/
// convenience overload
quint64 TFolderSize::diskUsage( const QString &absPath )
{
    int itemCount=0;
    return diskUsage( absPath, itemCount );
}

/******************************************************************/

} // namespace SDPO
