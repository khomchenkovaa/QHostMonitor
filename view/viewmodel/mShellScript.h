#ifndef MSHELLSCRIPT_H
#define MSHELLSCRIPT_H

#include "PropertyHelper.h"
#include <QDate>

namespace SDPO {

class ShellScript : public QObject
{
    Q_OBJECT

    AUTO_PROPERTY(QString, Name)
    AUTO_PROPERTY(QString, Hint)
    AUTO_PROPERTY(QString, Developer)
    AUTO_PROPERTY(QString, Platform)
    AUTO_PROPERTY(double, Version)
    AUTO_PROPERTY(QDate, Date)
    AUTO_PROPERTY(QString, StartCmd)
    AUTO_PROPERTY(QString, Script)
    AUTO_PROPERTY(QString, Comment)
    AUTO_PROPERTY(QString, History)
    AUTO_PROPERTY(QString, FileName)

public:
    explicit ShellScript(QObject *parent = 0);
    void loadDefaults();
signals:

public slots:



};

} // namespace SDPO

#endif // MSHELLSCRIPT_H
