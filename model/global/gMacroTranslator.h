#ifndef GSCRIPT_H
#define GSCRIPT_H

#include <QStringList>
#include <QVariantMap>

namespace SDPO {

class TNode;

class GMacroTranslator
{
    QString m_source;
    TNode *m_item;
    TNode *m_root;
    QStringList m_params;
    QVariantMap m_values;
public:
    explicit GMacroTranslator(QString source, TNode *item = nullptr);

    QStringList parse();
    void setValues(const QVariantMap &values);
    QVariantMap getValues() const;
    void buildValues();
    QString build() const;
    QString translate();
};

} // namespace SDPO

#endif // GSCRIPT_H
