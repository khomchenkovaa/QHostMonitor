/*!
 * \class SDPO::TCompareFiles
 * \brief Compare two files or search a string in the file
 *
 * This test is used to compare two files or to search a string in the file.
 * 6 alert conditions are available:
 * \li alert when files are different
 * \li alert when files are identical
 * \li alert when 1st file contains 2nd (in any position)
 * \li alert when 1st file does not contain 2nd
 * \li alert when file contains a specified string
 * \li alert when file does not contain a specified string
 *
 * You can specify one or more parameters to compare files: compare time, compare size, and compare contents.
 * If you set "compare contents" option but don't set "compare size" option, HostMonitor will consider two files to be identical when one file includes another one at offset 0 (one file can be smaller than another one).
 *
 * If you need to check some files that are dynamically created and do not have static name (e.g. some logs that are created on daily basis and have different file name every day), you may enable "Translate macros" options.
 * With this option enabled you may use special date macro variables, file-specific variables and User Defined Variables in file name.
 *
 * When you use Compare Files test to check file for some specific string, you should tell HostMonitor what encoding was used for the file.
 * HostMonitor supports several encoding methods.
 */
#ifndef TCOMPAREFILES_H
#define TCOMPAREFILES_H

#include "tTestMethod.h"

namespace SDPO {

class TCompareFiles : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Path READ getFirstFile())
    Q_PROPERTY(QString Object READ getFirstFile())
    Q_PROPERTY(QString Object2 READ getSecondFile())
    Q_PROPERTY(QString TestMode READ getAlertWhen())

public:
    enum AlertMode {
        FilesDifferent,
        FilesIdentical,
        ContainsFile,
        DoesntContainFile,
        ContainsString,
        DoesntContainString
    };

private:
    Q_ENUMS(AlertMode)

    AUTO_PROPERTY(AlertMode, AlertWhen)
    AUTO_PROPERTY(QString, FirstFile)
    AUTO_PROPERTY(QString, SecondFile)
    BOOL_PROPERTY(TranslateFirstMacros)
    BOOL_PROPERTY(TranslateSecondMacros)
    AUTO_PROPERTY(QString, String)
    AUTO_PROPERTY(int, CodecMibEnum)
    BOOL_PROPERTY(Time)
    BOOL_PROPERTY(Size)
    BOOL_PROPERTY(Contents)
    BOOL_PROPERTY(CaseSensitive)
    BOOL_PROPERTY(WholeWordsOnly)

public:
    explicit TCompareFiles(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

private:
    TTestResult compareFiles(bool identical);
    TTestResult containsFile(bool contains);
    TTestResult containsString(bool contains);
};

} // namespace SDPO

#endif // TCOMPAREFILES_H
