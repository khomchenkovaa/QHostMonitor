#include "testmethod.h"
#include "global/gMacroTranslator.h"

#include <QMetaClassInfo>
#include <QDebug>

namespace SDPO {

/***********************************************/

QVector<TestGroup> TestMethod::groups;
QVector<TestMethodMetaInfo> TestMethod::metaInfo;

/***********************************************/

TestMethod::TestMethod(TMethodID methodId, QObject *parent) :
    QObject(parent),
    m_TMethodID(methodId)
{
    TestMethodMetaInfo method = metaInfoItem(methodId);
    m_NamePattern = method.namePattern;
    m_CommentPattern = method.commentPattern;
}

/***********************************************/

TestMethod::~TestMethod()
{

}

/***********************************************/

void TestMethod::run()
{
    writeLogTitle();
    // Do nothing
    m_Log.append("Warning!!! Test method not implemented\n");
}

/***********************************************/

void TestMethod::parseResult(const QString &data)
{
    m_Result.reply  = data;
}

/***********************************************/

TestMethod *TestMethod::clone()
{
    TestMethod *result = new TestMethod(m_TMethodID, parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    return result;
}

/***********************************************/

QString TestMethod::getDefaultName() const
{
    GMacroTranslator translator(m_NamePattern);
    QStringList params = translator.parse();
    if (params.count()) {
        translator.setValues(setVars(params));
        return translator.build();
    }
    return m_NamePattern;
}

/***********************************************/

QString TestMethod::getDefaultComments() const
{
    GMacroTranslator translator(m_CommentPattern);
    QStringList params = translator.parse();
    if (params.count()) {
        translator.setValues(setVars(params));
        return translator.build();
    }
    return m_CommentPattern;
}

/***********************************************/

QVariantMap TestMethod::toMap() const
{
    QVariantMap result;
    result.insert("TestMethod", getTestMethod());
    result.insert("MethodName", getTestMethodName());
    result.insert("MethodID", getTestMethodID());
    result.insert("TestedObjectInfo", getTestedObjectInfo());
    return result;
}

/***********************************************/

QString TestMethod::getTranslated(const QString &name, const bool translate) const
{
    if (!translate) {
        return name;
    }
    GMacroTranslator translator(name);
    return translator.translate();
}

/***********************************************/

void TestMethod::writeLogTitle()
{
    m_Log.clear();
    m_Log.append("*************************************************************\n");
    m_Log.append(QString("* Method type: %1\n").arg(getTestMethod()));
    m_Log.append(QString("* Method name: %1\n").arg(getDefaultName()));
    m_Log.append(QString("* Call time:   %1\n").arg(QDateTime::currentDateTime().toString()));
    m_Log.append("*************************************************************\n\n");
}

/***********************************************/

TestMethodMetaInfo TestMethod::metaInfoItem(TMethodID methodID)
{
    TestMethodMetaInfo result = metaInfo.first();
    foreach(const TestMethodMetaInfo &method, metaInfo) {
        if (method.id == methodID) {
            result = method;
            break;
        }
    }
    return result;
}

/***********************************************/

QString TestMethod::metaName(TMethodID methodID)
{
    return metaInfoItem(methodID).name;
}

/***********************************************/

TMethodID TestMethod::methodIdFromString(const QString name)
{
    TMethodID result = TMethodID::Unknown;
    foreach( const TestMethodMetaInfo &method, metaInfo) {
        if (name.compare(method.name, Qt::CaseInsensitive) == 0 ) {
            result = method.id;
            break;
        }
    }
    return result;
}

/***********************************************/

QVariantMap TestMethod::setVars(const QStringList &params) const
{
    QVariantMap result;
    foreach (const QString &key, params) {
        result.insert(key, property(key.toLatin1()).toString());
    }
    return result;
}

/***********************************************/

} // namespace SDPO

