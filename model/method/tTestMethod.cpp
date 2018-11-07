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
}

/***********************************************/

TTestMethod *TTestMethod::clone()
{
    TTestMethod *result = new TTestMethod(m_TMethodID, parent());
    result->m_NamePattern = m_NamePattern;
    result->m_CommentPattern = m_CommentPattern;
    return result;
}

/***********************************************/

QString TTestMethod::getDefaultName() const
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

QString TTestMethod::getDefaultComments() const
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

QString TTestMethod::getTranslated(const QString &name, const bool translate) const
{
    if (!translate) {
        return name;
    }
    GMacroTranslator translator(name);
    return translator.translate();
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

