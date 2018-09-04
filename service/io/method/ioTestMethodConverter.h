#ifndef IOTESTMETHODCONVERTER_H
#define IOTESTMETHODCONVERTER_H

#include "method/sdpoTestMethods.h"

#include <QTextStream>

namespace SDPO {

// Specific parameters
static QString SP_FILE       = QStringLiteral("File");
static QString SP_USE_MACROS = QStringLiteral("UseMacros");
static QString SP_TIMEOUT    = QStringLiteral("Timeout");
static QString SP_RETRIES    = QStringLiteral("Retries");
static QString SP_SERVER     = QStringLiteral("Server");
static QString SP_USER       = QStringLiteral("User");
static QString SP_PASSWORD   = QStringLiteral("Password");
static QString SP_PORT       = QStringLiteral("Port");
static QString SP_DATABASE   = QStringLiteral("Database");
static QString SP_VALUE      = QStringLiteral("Value");
static QString SP_CONDITION  = QStringLiteral("Condition");
static QString SP_HOST       = QStringLiteral("Host");
static QString SP_SUBFOLDERS = QStringLiteral("SubFolders");

class IOTestMethodConverter : public QObject
{
    Q_OBJECT

protected:
    TTestMethod *m_TestMethod;

public:
    explicit IOTestMethodConverter(QObject *parent = 0);

    void setTestMethod(TTestMethod *value) { m_TestMethod = value; }
    virtual TTestMethod *getTestMethod() { return m_TestMethod; }
    virtual bool setValue(QString key, QString value);
    virtual void exportTo(QTextStream &out);

};

} // namespace SDPO

#endif // IOTESTMETHODCONVERTER_H
