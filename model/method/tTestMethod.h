#ifndef TTESTMETHOD_H
#define TTESTMETHOD_H

#include "PropertyHelper.h"
#include <QMap>
#include "tEnums.h"
#include "global/tMethod.h"


namespace SDPO {

class TTestMethod : public QObject
{
    Q_OBJECT

    // Represents short description of a testing method
    Q_PROPERTY(QString TestMethod READ getTestMethod)
    Q_PROPERTY(QString MethodName READ getTestMethodName)
    // Returns integer number that represents test method (test that has triggered action execution)
    Q_PROPERTY(QString MethodID READ getTestMethodID)
    // Provides information about tested object,
    // variable returns string value like 'MS SQL database "MainLog" on 192.168.10.15'.
    // This variable offers more information than %TestMethod% variable
    Q_PROPERTY(QString TestedObjectInfo READ getTestedObjectInfo)

protected:
    TMethodID m_TMethodID;
    QString m_NamePattern;
    QString m_CommentPattern;
    // result
    TestStatus m_Status;
    QString m_Reply;
    double m_ReplyDouble;
    int m_ReplyInt;
    QString m_ErrorString;

public:
    explicit TTestMethod(TMethodID methodId, QObject *parent = 0);

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

    TestStatus getStatus() const { return m_Status; }
    QString getReply() const { return m_Reply; }
    double getReplyDouble() const { return m_ReplyDouble; }
    int getReplyInt() const { return m_ReplyInt; }
    QString getErrorString() const { return m_ErrorString; }

    // command
    virtual void run() {} // Do nothing
    virtual QString getCommand() const { return QString(); }
    virtual void parseResult(QString data) { m_Reply = data; }
    void clearResult();

    virtual TTestMethod *clone();
    QString getDafaultName() const;
    QString getDafaultComments() const;

signals:
    void testSuccess();
    void testFailed();

private:
    QMap<QString, QString> setVars(const QStringList &params) const;

};

} // namespace SDPO

#endif // TTESTMETHOD_H
