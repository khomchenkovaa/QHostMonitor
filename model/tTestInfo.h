#pragma once

#include <QVariant>

namespace SDPO {

class TNode;

class TestInfo : public QObject
{
    Q_OBJECT

    TNode *m_test;
    QString m_path;

public:
    explicit TestInfo(TNode *test, QString path, QObject *parent = 0);

    QVariant getData(int line) const;
    TNode *getTest() const;
    QString path() const;

signals:

public slots:

};

} // namespace SDPO


