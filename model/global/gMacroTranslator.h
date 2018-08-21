#ifndef GSCRIPT_H
#define GSCRIPT_H

#include <QStringList>
#include <QMap>
#include <QVariant>

namespace SDPO {

class TNode;

class GMacroTranslator
{
    QString m_source;
    TNode *m_item;
    TNode *m_root;
    QStringList m_params;
    QMap<QString, QString> m_values;
public:
    explicit GMacroTranslator(QString source, TNode *item = 0);

    QStringList parse();
    void setValues(const QMap<QString, QString> &values);
    QMap<QString, QString> getValues() const;
    void buildValues();
    QString build() const;
    QString translate();
};

} // namespace SDPO

#endif // GSCRIPT_H
