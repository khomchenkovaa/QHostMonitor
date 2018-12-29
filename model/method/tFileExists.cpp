#include "tFileExists.h"
#include <QFileInfo>
#include <QDateTime>

namespace SDPO {

/******************************************************************/

TFileExists::TFileExists(QObject *parent) :
    TTestMethod(TMethodID::FileExists, parent)
{
    a_FileName = QString();
    b_TranslateMacros = false;
    b_FileExistsCriteria = true;
    b_FileOlderFlag = false;
    b_FileNewerFlag = false;
    a_FileOlderValue = 60;
    a_FileNewerValue = 60;
}

/******************************************************************/

void TFileExists::run()
{
    TTestResult result;
    result.status = TestStatus::Ok;
    writeLogTitle();

    QFileInfo fileInfo(a_FileName);
    bool fileExists = fileInfo.exists();
    qint64 fileAge = fileExists ? fileInfo.lastModified().secsTo(QDateTime::currentDateTime()) / 60 : -1;
    m_Log.append(QString("File %1 %2\n").arg(a_FileName).arg(fileExists?"exists":"doesn't exists"));
    m_Log.append(QString("Last modified %1\n").arg(fileInfo.lastModified().toString()));

    if (b_FileExistsCriteria) { // Alert: file exists AND time criteria
        if (fileExists) {
            result.status = TestStatus::Bad;
            if (b_FileOlderFlag && fileAge < a_FileOlderValue) {
                result.status = TestStatus::Ok;
            }
            if (b_FileNewerFlag && fileAge > a_FileNewerValue) {
                result.status = TestStatus::Ok;
            }
        }
    } else { // Alert: file does't exists OR time criteria
        if (!fileExists) {
            result.status = TestStatus::Bad;
        } else {
            if (b_FileOlderFlag && fileAge > a_FileOlderValue) {
                result.status = TestStatus::Bad;
            }
            if (b_FileNewerFlag && fileAge < a_FileNewerValue) {
                result.status = TestStatus::Bad;
            }
        }
    }

    m_Result = result;

    emit testSuccess();
}

/******************************************************************/

TTestMethod *TFileExists::clone()
{
    TFileExists *result = new TFileExists(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_FileName = a_FileName;
    result->b_TranslateMacros = b_TranslateMacros;
    result->b_FileExistsCriteria = b_FileExistsCriteria;
    result->b_FileOlderFlag = b_FileOlderFlag;
    result->b_FileNewerFlag = b_FileNewerFlag;
    result->a_FileOlderValue = a_FileOlderValue;
    result->a_FileNewerValue = a_FileNewerValue;
    return result;
}

/******************************************************************/

QString TFileExists::getTestMethod() const
{
    return b_FileExistsCriteria ? QString("File not exists") : QString("File exists");
}

/******************************************************************/

QString TFileExists::getTestedObjectInfo() const
{
    return b_FileExistsCriteria ?
                QString("File %1 not exists").arg(a_FileName) :
                QString("File %1 exists").arg(a_FileName);
}

/******************************************************************/

QString TFileExists::getObjectProperty() const
{
    QFileInfo fInfo(a_FileName);
    return fInfo.baseName();
}

/******************************************************************/

} // namespace SDPO
