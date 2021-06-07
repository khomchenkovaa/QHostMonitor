#include "gMacroTranslator.h"
#include "tNode.h"
#include "global/gUserVars.h"
#include "gUnitConverter.h"

namespace SDPO {

/*****************************************************************/

GMacroTranslator::GMacroTranslator(QString source, TNode *item) :
    m_source(source),
    m_item(item)
{
    if (m_item) {
        m_root = m_item->getRoot();
    } else {
        m_root = nullptr;
    }
}

/*****************************************************************
 * Parse expressions like:
 * ('%::Ping Router::SimpleStatus%'=="UP") && ('%Reply%'<'800 ms')
 * and get keys:
 * ::Ping Router::SimpleStatus
 * Reply
 */

QStringList GMacroTranslator::parse()
{
    QString pattern = "%((::[\\w\\W]+::)?[\\w_]+[\\w_\\d]*)%";
    QRegExp rx(pattern);
    int pos = 0;
    while ((pos = rx.indexIn(m_source, pos)) != -1) {
        if (!m_params.contains(rx.cap(1))) {
            m_params.append(rx.cap(1));
        }
        pos += rx.matchedLength();
    }
    return m_params;
}

/*****************************************************************/

void GMacroTranslator::setValues(const QVariantMap &values)
{
    QMapIterator<QString, QVariant> it(values);
    while (it.hasNext()) {
        it.next();
        m_values.insert(it.key(), it.value());
    }
}

/*****************************************************************/

QVariantMap GMacroTranslator::getValues() const
{
    return m_values;
}

/*****************************************************************/

void GMacroTranslator::buildValues()
{
    foreach (const QString &key, m_params) {
        if (GUserVars::variables.contains(key)) { // global var
            m_values.insert(key, GUserVars::variables.value(key));
        } else if (m_root && key.startsWith("::")) { // macro with test name (::Ping Router::SimpleStatus)
            int idx = key.lastIndexOf("::");
            QString testName = key.mid(2,idx-2);
            QString newKey = key.mid(idx+2);
            TNode *test = m_root->findTest(testName);
            if (test) {
                Macro::Variable globalVar = TMacro::var(newKey);
                m_values.insert(key, test->getGlobal(globalVar).toString());
            } else {
                m_values.insert(key, QString());
            }
        } else if (m_item) {
            Macro::Variable globalVar = TMacro::var(key);
            m_values.insert(key, m_item->getGlobal(globalVar).toString());
        } else {
            m_values.insert(key, QString());
        }
    }
}

/*****************************************************************/

QString GMacroTranslator::build() const
{
    QString result = m_source;
    QMapIterator<QString, QVariant> it(m_values);
    while(it.hasNext()) {
        it.next();
        result = result.replace(QString("%%1%").arg(it.key()),it.value().toString());
    }

    QString pattern = "'(\\d+)\\s*(\\w\\w|%)'";
    QRegExp rx(pattern);
    while (rx.indexIn(result) != -1) {
        int value = rx.cap(1).toInt();
        QString ext = rx.cap(2);
        GUnitConverter conv(value, ext);
        result = result.replace(rx.cap(0), QString::number(conv.getNumber()));
    }
    return result;
}

/*****************************************************************/

QString GMacroTranslator::translate()
{
    parse();
    buildValues();
    return build();
}

/*****************************************************************/

} // namespace SDPO
