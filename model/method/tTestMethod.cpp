#include "tTestMethod.h"
#include "global/gMacroTranslator.h"
#include <QDebug>

namespace SDPO {

/***********************************************/

TTestMethod::TTestMethod(TMethodID methodId, QObject *parent) :
    QObject(parent),
    m_TMethodID(methodId)
{
    TMethod method = TMethod::tMethodList.at((int)methodId);
    m_NamePattern = method.namePattern;
    m_CommentPattern = method.commentPattern;
    clearResult();
}

/***********************************************/

void TTestMethod::clearResult()
{
    m_Status = TestStatus::Unknown;
    m_Reply = QString();
    m_ReplyDouble = 0.0;
    m_ReplyInt = 0;
    m_ErrorString = QString();
}

/***********************************************/

TTestMethod *TTestMethod::clone()
{
    TTestMethod *result = new TTestMethod(m_TMethodID, parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    result->clearResult();
    return result;
}

/***********************************************/

QString TTestMethod::getDafaultName() const
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

QString TTestMethod::getDafaultComments() const
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

QMap<QString, QString> TTestMethod::setVars(const QStringList &params) const
{
    QMap<QString, QString> result;
    foreach (const QString &key, params) {
        result.insert(key, property(key.toLatin1()).toString());
    }
    return result;
}

/***********************************************/

} // namespace SDPO

