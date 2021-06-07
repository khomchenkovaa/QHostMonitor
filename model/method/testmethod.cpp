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

TestMethodMetaInfo TestMethod::metaInfoItem(TMethodID method)
{
    return metaInfo.at(static_cast<int>(method));
}

/***********************************************/

QString TestMethod::metaName(TMethodID method)
{
    return metaInfoItem(method).name;
}

/***********************************************/

TMethodID TestMethod::methodIdFromString(const QString name)
{
    TMethodID result = TMethodID::Empty;
    foreach( const TestMethodMetaInfo &method, metaInfo) {
        if (name.compare(method.name, Qt::CaseInsensitive) == 0 ) {
            result = method.id;
            break;
        }
    }
    return result;
}

/***********************************************/

QMap<QString, QString> TestMethod::setVars(const QStringList &params) const
{
    QMap<QString, QString> result;
    foreach (const QString &key, params) {
        result.insert(key, property(key.toLatin1()).toString());
    }
    return result;
}

/***********************************************/

} // namespace SDPO

