#ifndef IOTESTMETHODCONVERTER_H
#define IOTESTMETHODCONVERTER_H

#include "method/sdpoTestMethods.h"

#include <QTextStream>
#include <QJsonObject>

namespace SDPO {

class IOTestMethodConverter : public QObject
{
    Q_OBJECT

protected:
    TestMethod *m_TestMethod;

public:
    explicit IOTestMethodConverter(QObject *parent = 0);

    void    setTestMethod(TestMethod *value) { m_TestMethod = value; }
    virtual TestMethod *getTestMethod() { return m_TestMethod; }
    virtual bool setValue(QString key, QString value);
    virtual void exportTo(QTextStream &out);

    virtual QJsonObject toJsonObject() { return QJsonObject(); }
    virtual TestMethod *fromJsonObject(QJsonObject jsonObj);


};

} // namespace SDPO

#endif // IOTESTMETHODCONVERTER_H
