#include "tCompareFiles.h"

#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QTextCodec>

namespace SDPO {

/******************************************************************/

TCompareFiles::TCompareFiles(QObject *parent) :
    TestMethod(TMethodID::CompareFiles, parent)
{
    a_AlertWhen = AlertMode::FilesDifferent;
    a_FirstFile = QString();
    a_SecondFile = QString();
    b_TranslateFirstMacros = false;
    b_TranslateSecondMacros = false;
    b_Time = false;
    b_Size = false;
    b_Contents = false;
    a_CodecMibEnum = 0;
}

/******************************************************************/

void TCompareFiles::run()
{
    writeLogTitle();
    switch (a_AlertWhen) {
    case AlertMode::FilesDifferent:
        m_Log.append("Alert Mode: FilesDifferent\n");
        m_Result = compareFiles(true);
        break;
    case AlertMode::FilesIdentical:
        m_Log.append("Alert Mode: FilesIdentical\n");
        m_Result = compareFiles(false);
        break;
    case AlertMode::ContainsFile:
        m_Log.append("Alert Mode: ContainsFile\n");
        m_Result = containsFile(false);
        break;
    case AlertMode::DoesntContainFile:
        m_Log.append("Alert Mode: DoesntContainFile\n");
        m_Result = containsFile(true);
        break;
    case AlertMode::ContainsString:
        m_Log.append("Alert Mode: ContainsString\n");
        m_Result = containsString(false);
        break;
    case AlertMode::DoesntContainString:
        m_Log.append("Alert Mode: DoesntContainString\n");
        m_Result = containsString(true);
        break;
    }

    if (!m_Result.error.isEmpty()) {
        m_Log.append("Error!!!\n");
        m_Log.append(m_Result.error);
    }

    if (m_Result.status == TestStatus::Ok) {
        m_Log.append("Test OK");
        emit testSuccess();
    } else {
        m_Log.append("Test Bad");
        emit testFailed();
    }
}

/******************************************************************/

TestMethod *TCompareFiles::clone()
{
    TCompareFiles *result = new TCompareFiles(parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    // test specific
    result->a_AlertWhen = a_AlertWhen;
    result->a_FirstFile = a_FirstFile;
    result->a_SecondFile = a_SecondFile;
    result->b_TranslateFirstMacros = b_TranslateFirstMacros;
    result->b_TranslateSecondMacros = b_TranslateSecondMacros;
    result->a_String = a_String;
    result->a_CodecMibEnum = a_CodecMibEnum;
    result->b_Time = b_Time;
    result->b_Size = b_Size;
    result->b_Contents = b_Contents;
    result->b_CaseSensitive = b_CaseSensitive;
    result->b_WholeWordsOnly = b_WholeWordsOnly;
    return result;
}

/******************************************************************/

TestResult TCompareFiles::compareFiles(bool identical)
{
    TestResult result;
    if (!b_Time && !b_Size && !b_Contents) {
        result.error = tr("no compare method");
        return result;
    }
    QString firstFile = getTranslated(a_FirstFile, b_TranslateFirstMacros);
    QFileInfo fInfo1(firstFile);
    if (!fInfo1.exists()) {
        result.error = tr("file %1 does not exists").arg(firstFile);
        return result;
    }

    QString secondFile = getTranslated(a_SecondFile, b_TranslateSecondMacros);
    QFileInfo fInfo2(secondFile);
    if (!fInfo2.exists()) {
        result.error = tr("file %2 does not exists").arg(secondFile);
        return result;
    }

    if (b_Time) {
        m_Log.append("Comparing last modified time... ");
        if (fInfo1.lastModified() == fInfo2.lastModified()) {
            m_Log.append("EQUALS\n");
            result.status = identical? TestStatus::Ok : TestStatus::Bad;
        } else {
            m_Log.append("Different\n");
            result.status = identical? TestStatus::Bad : TestStatus::Ok;
            return result;
        }
    }

    if (b_Size) {
        m_Log.append("Comparing file sizes...");
        if (fInfo1.size() == fInfo2.size()) {
            m_Log.append("EQUALS\n");
            result.status = identical? TestStatus::Ok : TestStatus::Bad;
        } else {
            m_Log.append("Different\n");
            result.status = identical? TestStatus::Bad : TestStatus::Ok;
            return result;
        }
    }

    if (b_Contents) {
        result = containsFile(!identical);
    }
    return result;
}

/******************************************************************/

TestResult TCompareFiles::containsFile(bool contains)
{
    TestResult result;

    QString firstFile = getTranslated(a_FirstFile, b_TranslateFirstMacros);
    QFile file1(firstFile);
    if ( !file1.open( QIODevice::ReadOnly ) ) {
        result.error = tr("cannot open file %1").arg(firstFile);
        result.status = TestStatus::Unknown;
        return result;
    }
    const QByteArray content = file1.readAll();
    file1.close();

    QString secondFile = getTranslated(a_SecondFile, b_TranslateSecondMacros);
    QFile file2(secondFile);
    if ( !file2.open( QIODevice::ReadOnly ) ) {
        result.error = tr("cannot open file %1").arg(secondFile);
        result.status = TestStatus::Unknown;
        return result;
    }
    const QByteArray searchStr = file2.readAll();
    file2.close();

    m_Log.append("Comparing file contents...");
    if (content.contains(searchStr)) {
        m_Log.append("Contains\n");
        result.status = contains? TestStatus::Ok : TestStatus::Bad;
    } else {
        m_Log.append("Does not\n");
        result.status = contains? TestStatus::Bad : TestStatus::Ok;
    }
    return result;
}

/******************************************************************/

TestResult TCompareFiles::containsString(bool contains)
{
    TestResult result;
    QString firstFile = getTranslated(a_FirstFile, b_TranslateFirstMacros);
    QFile file(firstFile);
    if ( !file.open( QIODevice::ReadOnly ) ) {
        result.error = tr("cannot open file %1").arg(firstFile);
        result.status = TestStatus::Unknown;
        return result;
    }
    QTextCodec *codec = QTextCodec::codecForMib(a_CodecMibEnum);
    QTextStream in (&file);
    if (codec) {
        in.setAutoDetectUnicode(false);
        in.setCodec(codec);
    }
    QString decodedStr = in.readAll();
    file.close();
    m_Log.append("Comparing file contents with string...");
    QString searchStr = b_WholeWordsOnly? "\\b" + a_String + "\\b" : a_String;
    Qt::CaseSensitivity cs = b_CaseSensitive? Qt::CaseSensitive : Qt::CaseInsensitive;
    QRegExp rx(searchStr,cs);
    if (decodedStr.contains(rx)) {
        m_Log.append("Contains\n");
        result.status = contains? TestStatus::Ok : TestStatus::Bad;
    } else {
        m_Log.append("Does not\n");
        result.status = contains? TestStatus::Bad : TestStatus::Ok;
    }
    return result;
}

/******************************************************************/

QString TCompareFiles::getTestMethod() const
{
    return QString("compare %1 & %2").arg(a_FirstFile).arg(a_SecondFile);
}

/******************************************************************/

QString TCompareFiles::getTestedObjectInfo() const
{
    return QString("file compare (%1 & %2)").arg(a_FirstFile).arg(a_SecondFile);
}

/******************************************************************/

} // namespace SDPO
