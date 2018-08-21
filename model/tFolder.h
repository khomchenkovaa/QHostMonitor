#ifndef TFOLDER_H
#define TFOLDER_H

#include "tNode.h"

namespace SDPO {

class TFolder : public TNode
{
    Q_OBJECT

    // The name of the folder containing the test
    Q_PROPERTY(QString Folder READ getName)
    // Represents unique ID of the folder (integer number)
    Q_PROPERTY(QString FolderID READ getID)
    // The full folder path name
    Q_PROPERTY(QString FullPath READ getPath)
    // Folder's comment (entire comment, lines separated by CRLF)
    Q_PROPERTY(QString FolderComment READ getComment)
    //! %FCommentLineNN%	Returns a line #NN of a folder`s comment

    /* Statistical variables */

    // Total number of the test items in the folder
    Q_PROPERTY(QString FolderCurrent_TotalTests READ testsTotal)
    // Number of the test items (in the folder) those have "Good" status
    Q_PROPERTY(QString FolderCurrent_GoodTests READ testsGood)
    // Number of the test items (in the folder) those have "Bad" status
    Q_PROPERTY(QString FolderCurrent_BadTests READ testsBad)
    // Number of the test items (in the folder) those have "Unknown" status
    Q_PROPERTY(QString FolderCurrent_UnknownTests READ testsUnknown)
    // Number of the test items (in the folder) those have "Warning" status
    Q_PROPERTY(QString FolderCurrent_WarningTests READ testsWarning)
    // Number of "Bad" acknowledged test items in the folder
    Q_PROPERTY(QString FolderCurrent_AcknowledgedBad READ testsBadAcknowleged)
    // Number of "Unknown" acknowledged test items in the folder
    Q_PROPERTY(QString FolderCurrent_AcknowledgedUnknown READ testsUnknownAcknowkeged)
    // Number of "Warning" acknowledged test items in the folder
    Q_PROPERTY(QString FolderCurrent_AcknowledgedWarning READ testsWarningAcknowkeged)

    /* Statistical variables recursive - count test items within folder AND all descendant subfolders */

    // Total number of the test items in the folder and its subfolders
    Q_PROPERTY(QString FolderRecursive_TotalTests READ testsTotalRecursive)
    // Number of the test items those have "Good" status
    Q_PROPERTY(QString FolderRecursive_GoodTests READ testsGoodRecursive)
    // Number of the test items those have "Bad" status
    Q_PROPERTY(QString FolderRecursive_BadTests READ testsBadRecursive)
    // Number of the test items those have "Unknown" status
    Q_PROPERTY(QString FolderRecursive_UnknownTests READ testsUnknownRecursive)
    // Number of the test items those have "Warning" status
    Q_PROPERTY(QString FolderRecursive_WarningTests READ testsWarningRecursive)
    // Number of "Bad" acknowledged test items
    Q_PROPERTY(QString FolderRecursive_AcknowledgedBad READ testsBadAcknowlegedRecursive)
    // Number of "Unknown" acknowledged test items
    Q_PROPERTY(QString FolderRecursive_AcknowledgedUnknown READ testsUnknownAcknowkegedRecursive)
    // Number of "Warning" acknowledged test items
    Q_PROPERTY(QString FolderRecursive_AcknowledgedWarning READ testsWarningAcknowkegedRecursive)

public:
    explicit TFolder(const QString& name, QObject *parent = 0);

    int testsTotal() const;
    int testsGood() const;
    int testsBad() const;
    int testsUnknown() const;
    int testsWarning() const;
    int testsBadAcknowleged() const;
    int testsUnknownAcknowkeged() const;
    int testsWarningAcknowkeged() const;

    int testsTotalRecursive() const;
    int testsGoodRecursive() const;
    int testsBadRecursive() const;
    int testsUnknownRecursive() const;
    int testsWarningRecursive() const;
    int testsBadAcknowlegedRecursive() const;
    int testsUnknownAcknowkegedRecursive() const;
    int testsWarningAcknowkegedRecursive() const;

    QVariant property(QString name) const Q_DECL_OVERRIDE;

private: // interface settings
    BOOL_PROPERTY(UseOwnRegionalSettings)
    bool b_ApplyRemoteTimeToGui;
    bool b_ApplyRemoteTimeToSchedules;
    QString m_TimeZoneIanaId;
    BOOL_PROPERTY(TestStatusesNotAffectTrayIconColor)
    BOOL_PROPERTY(NonSimultaneouslyTestExecution)

public: // interface settings
    bool isApplyRemoteTimeToGui() const;
    void setApplyRemoteTimeToGui(const bool value);
    bool isApplyRemoteTimeToSchedules() const;
    void setApplyRemoteTimeToSchedules(const bool value);
    QString getTimeZoneIanaId() const;
    void setTimeZoneIanaId(const QString &value);

};

} // namespace SDPO

#endif // TFOLDER_H
