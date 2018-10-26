#ifndef IOTESTMETHODCONVERTER_H
#define IOTESTMETHODCONVERTER_H

#include "method/sdpoTestMethods.h"

#include <QTextStream>
#include <QJsonValue>

namespace SDPO {

class IOTestMethodConverter : public QObject
{
    Q_OBJECT

protected:
    TTestMethod *m_TestMethod;

public:
    explicit IOTestMethodConverter(QObject *parent = 0);

    void    setTestMethod(TTestMethod *value) { m_TestMethod = value; }
    virtual TTestMethod *getTestMethod() { return m_TestMethod; }
    virtual bool setValue(QString key, QString value);
    virtual void exportTo(QTextStream &out);

    virtual QJsonValue toJson() { return QJsonValue(); }
    virtual TTestMethod *fromJson(QJsonValue jsonValue);


};

} // namespace SDPO

#endif // IOTESTMETHODCONVERTER_H
