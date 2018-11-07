#ifndef TLINK_H
#define TLINK_H

#include "tNode.h"

namespace SDPO {

class TTest;

class TLink : public TNode
{
    Q_OBJECT

    TTest *m_test;
public:
    explicit TLink(const int id, TTest *test, QObject *parent = 0);

    QVariant property(QString name) const Q_DECL_OVERRIDE;
    virtual QVariant getGlobal(Macro::Variable globalVar) const;
    TTest *getTest() const;
};

} // namespace SDPO

#endif // TLINK_H
