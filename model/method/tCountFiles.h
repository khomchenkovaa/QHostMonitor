/*!
 * \class SDPO::TCountFiles
 * \brief Check number of files in the specified directory
 *
 * This test allows you to check number of files in the specified directory.
 * Let`s say you have a mailserver that uses a spool directory.
 * If the mail server is running correctly, it should deliver the mail within 5 minutes to the internet.
 * Using Count Files test HostMonitor can check the number of files in the mail server`s spool directory and warn you when number of files exceed specified limit.
 * In addition to the common test parameters, the Count Files test has the following options:
 *
 * \b Folder
 *
 * Specify the directory in which you want to count the amount of files.
 *
 * <b> File name mask </b>
 *
 * Specify file name mask. Usually mask contains wildcard characters, e.g. use <tt>‘*.*’</tt> mask to count all files in the folder; use <tt>‘*.eml’</tt> mask to count files with .EML extension.
 *
 * If you want to perform the test using an agent installed on UNIX-like system, you should have in mind:
 * \li use slash (/) in the path (instead of backslash (\) that you are using on Windows systems);
 * \li on UNIX-like systems name of the file is case sensitive (so "/etc/RMA" and "/etc/rma" are different files);
 * \li on Windows system file masks '*' and '*.*' represent any file. On UNIX-like system only '*' represents any file; '*.*' can be used for any file that has dot (.) in the name.
 *
 * <b> Translate macros </b>
 *
 * With this option enabled you can use special date macro variables and User Defined Variables in the folder name and in the file name mask.
 *
 * <b> Include sub-folders </b>
 *
 * If the option is disabled, HostMonitor will count files directly in the specified folder.
 * If the option is enabled, files in the specified folder and in all of its descending subfolders will be counted.
 *
 * <b> Conditions to count files </b>
 *
 * Specify additional condition to count files. Choose one of the options:
 * \li Count all files
 * \li Count files older than NN min
 * \li Count files newer than NN min
 * \li Count files bigger than NN bytes
 * \li Count files smaller than NN bytes
 * \li Count subfolder only
 *
 * <b> Alert when folder contains more than NN files </b>
 *
 * Specify limit for the file amount. When this limit is reached, HostMonitor will change test status to “Bad”.
 * If you need to start alert actions when file amount become lower than specified, use “Reverse alert” option.
 */
#ifndef TCOUNTFILES_H
#define TCOUNTFILES_H

#include "testmethod.h"

#include <QDir>

namespace SDPO {

class TCountFiles : public TestMethod
{
    Q_OBJECT

    Q_PROPERTY(QString Host READ  getHostAddr())
    Q_PROPERTY(QString Path READ getFolder())
    Q_PROPERTY(QString Object READ getFolderMask())

public:
    //! Conditions to count files
    enum CountCondition {
        AllFiles,      //!< Count all files
        OlderThan,     //!< Count files older than NN min
        NewerThan,     //!< Count files newer than NN min
        BiggerThan,    //!< Count files bigger than NN bytes
        SmallerThan,   //!< Count files smaller than NN bytes
        SubfolderOnly  //!< Count subfolder only
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
    explicit TCountFiles(QObject *parent = nullptr);

    // properties
    virtual QString getTestMethod() const Q_DECL_OVERRIDE;
    virtual QString getTestedObjectInfo() const Q_DECL_OVERRIDE;
    QString getHostAddr() const { return "localhost"; }

    // getters and setters
    QString getFolderMask() const { return QString("%1/%2").arg(a_Folder).arg(a_FileNameMask); }

    // command
    virtual void run() Q_DECL_OVERRIDE;

    virtual TestMethod *clone() Q_DECL_OVERRIDE;

private:
    int countFiles(QDir dir);

};

} // namespace SDPO

#endif // TCOUNTFILES_H
