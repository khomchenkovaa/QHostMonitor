#ifndef TTESTMETHOD_H
#define TTESTMETHOD_H

#include "PropertyHelper.h"
#include "tEnums.h"
#include "global/tMethod.h"

#include <QMap>
#include <QDateTime>

namespace SDPO {

/***********************************************/

struct TTestResult {
    TestStatus status;
    QString    reply;
    double     replyDouble;
    int        replyInt;
    QString    error;
    QDateTime  date;

    TTestResult() {
        clear();
    }

    void clear() {
        status = TestStatus::Unknown;
        reply = QString();
        replyDouble = 0.0;
        replyInt = 0;
        error = QString();
        date = QDateTime::currentDateTime();
    }

    void reverse() {
        switch (status) {
        case TestStatus::HostAlive:   status = TestStatus::Bad; break;
        case TestStatus::NoAnswer:    status = TestStatus::Ok;  break;
        case TestStatus::Ok:          status = TestStatus::Bad; break;
        case TestStatus::Bad:         status = TestStatus::Ok;  break;
        case TestStatus::BadContents: status = TestStatus::Ok;  break;
        default: break;
        }
    }

    SimpleStatusID simpleStatus(const bool unknownIsBad = false, const bool warningIsBad = false) const {
        SimpleStatusID result = SimpleStatusID::UNKNOWN;
        switch (status) {
            case TestStatus::HostAlive:
            case TestStatus::Ok:
            case TestStatus::Normal:
                result = SimpleStatusID::UP;
                break;
            case TestStatus::NoAnswer:
            case TestStatus::Bad:
            case TestStatus::BadContents:
                result = SimpleStatusID::DOWN;
                break;
            case TestStatus::Warning:
                result = SimpleStatusID::WARNING;
                break;
            default:
                break;
        }
        // Unknown, might be processed as “bad” statuses depending on “unknownIsBad” option
        if (unknownIsBad && result==SimpleStatusID::UNKNOWN) result = SimpleStatusID::DOWN;

        // Warning, might be processed as “bad” statuses depending on “warningIsBad” option
        if (warningIsBad && result==SimpleStatusID::WARNING) result = SimpleStatusID::DOWN;
        return result;
    }
};

/*!
 * Base class for all tests
 */
class TTestMethod : public QObject
{
    Q_OBJECT

    //! Represents short description of a testing method
    Q_PROPERTY(QString TestMethod READ getTestMethod)
    Q_PROPERTY(QString MethodName READ getTestMethodName)

    //! Returns integer number that represents test method (test that has triggered action execution)
    Q_PROPERTY(QString MethodID READ getTestMethodID)

    //! Provides information about tested object,
    //! variable returns string value like <tt>'MS SQL database "MainLog" on 192.168.10.15'</tt>.
    //! This variable offers more information than <tt>%TestMethod%</tt> variable
    Q_PROPERTY(QString TestedObjectInfo READ getTestedObjectInfo)

protected:
    TMethodID   m_TMethodID;
    QString     m_NamePattern;
    QString     m_CommentPattern;
    TTestResult m_Result;

public:
    explicit TTestMethod(TMethodID methodId, QObject *parent = 0);
    virtual ~TTestMethod();

    // properties
    int getTestMethodID() const { return (int)m_TMethodID; }
    QString getTestMethodName() const { return TMethod::toName(m_TMethodID); }
    virtual QString getTestMethod() const { return TMethod::toName(m_TMethodID); }
    virtual QString getTestedObjectInfo() const { return QString(); }

    // getters and setters
    TMethodID getTMethodID() const { return m_TMethodID; }
    void setTMethodID(const TMethodID value) { m_TMethodID = value; }
    QString getNamePattern() const { return m_NamePattern; }
    void setNamePattern(const QString value) { m_NamePattern = value; }
    QString getCommentPattern() const { return m_CommentPattern; }
    void setCommentPattern(const QString value) { m_CommentPattern = value; }
    TTestResult getResult() const { return m_Result; }

    // command
    virtual void run() {} // Do nothing
    virtual QString getCommand() const { return QString(); }
    virtual void parseResult(QString data) { m_Result.reply = data; }

    virtual TTestMethod *clone();
    QString getDefaultName() const;
    QString getDefaultComments() const;

protected:
    QString getTranslated(const QString &name, const bool translate) const;

signals:
    void testSuccess();
    void testFailed();

private:
    QMap<QString, QString> setVars(const QStringList &params) const;

};

} // namespace SDPO

#endif // TTESTMETHOD_H
