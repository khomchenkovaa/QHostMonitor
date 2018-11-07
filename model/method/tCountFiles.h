/*
 * This test allows you to check number of files in the specified directory.
 * Let`s say you have a mailserver that uses a spool directory.
 * If the mail server is running correctly, it should deliver the mail within 5 minutes to the internet.
 * Using Count Files test HostMonitor can check the number of files in the mail server`s spool directory and warn you when number of files exceed specified limit.
 * In addition to the common test parameters, the Count Files test has the following options:
 *
 * Folder
 * Specify the directory in which you want to count the amount of files.
 *
 * File name mask
 * Specify file name mask. Usually mask contains wildcard characters, e.g. use ‘*.*’ mask to count all files in the folder; use ‘*.eml’ mask to count files with .EML extension.
 *
 * If you want to perform the test using an agent installed on UNIX-like system, you should have in mind:
 * • use slash (/) in the path (instead of backslash (\) that you are using on Windows systems);
 * • on UNIX-like systems name of the file is case sensitive (so "/etc/RMA" and "/etc/rma" are different files);
 * • on Windows system file masks '*' and '*.*' represent any file. On UNIX-like system only '*' represents any file; '*.*' can be used for any file that has dot (.) in the name.
 *
 * Translate macros
 * With this option enabled you can use special date macro variables and User Defined Variables in the folder name and in the file name mask.
 *
 * Include sub-folders
 * If the option is disabled, HostMonitor will count files directly in the specified folder.
 * If the option is enabled, files in the specified folder and in all of its descending subfolders will be counted.
 *
 * Conditions to count files
 * Specify additional condition to count files. Choose one of the options:
 * • Count all files
 * • Count files older than NN min
 * • Count files newer than NN min
 * • Count files bigger than NN bytes
 * • Count files smaller than NN bytes
 * • Count subfolder only
 *
 * Alert when folder contains more than NN files
 * Specify limit for the file amount. When this limit is reached, HostMonitor will change test status to “Bad”.
 * If you need to start alert actions when file amount become lower than specified, use “Reverse alert” option.
 */
#ifndef TCOUNTFILES_H
#define TCOUNTFILES_H

#include "tTestMethod.h"

#include <QDir>

namespace SDPO {

class TCountFiles : public TTestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getHostAddr())
    Q_PROPERTY(QString Path READ getFolder())
    Q_PROPERTY(QString Object READ getFolderMask())

public:
    enum CountCondition {
        AllFiles,
        OlderThan,
        NewerThan,
        BiggerThan,
        SmallerThan,
        SubfolderOnly
    };
    Q_ENUM(CountCondition)

    AUTO_PROPERTY(QString, Folder)
    BOOL_PROPERTY(TranslateMacros)
    AUTO_PROPERTY(QString, FileNameMask)
    BOOL_PROPERTY(IncludeSybFolder)
    AUTO_PROPERTY(CountCondition, Condition)
    AUTO_PROPERTY(int, CountValue)
    AUTO_PROPERTY(int, AlertWhen)

public:
    explicit TCountFiles(QObject *parent = 0);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }

    // getters and setters
    QString getFolderMask() const { return QString("%1\%2").arg(a_Folder).arg(a_FileNameMask); }

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TTestMethod *clone() Q_DECL_OVERRIDE;

private:
    int countFiles(QDir dir);

};

} // namespace SDPO

#endif // TCOUNTFILES_H
