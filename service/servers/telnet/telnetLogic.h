#ifndef TELNETLOGIC_H
#define TELNETLOGIC_H

#include <QtGlobal>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMap>
#include <QVector>
#include <QList>
#include <QStringList>
#include <QCryptographicHash>

namespace SDPO {

class TelnetLogic : public QObject
{
    Q_OBJECT
public:
    explicit TelnetLogic(QObject *parent = nullptr); // constructor
    QString ProcessCommand(QString command); // process telnet command

protected:

    // command 'setpassword' [password]
    QString  ProcessSetPassword(QStringList slArgs, QString inRet);

    // TODO: define your own command
    QString  ProcessYourOwnCommand(QStringList slArgs, QString inRet);

};

} // namespace SDPO

#endif // TELNETLOGIC_H
