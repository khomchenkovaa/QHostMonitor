#ifndef TSENDMESSAGETOPAGERTAPACTION_H
#define TSENDMESSAGETOPAGERTAPACTION_H

#include "tTestAction.h"

namespace SDPO {

class SendMessageToPagerTapAction : public TestAction
{
    Q_OBJECT

    AUTO_PROPERTY(QString, AccessNumber) // Access number
    AUTO_PROPERTY(QString, Password) // Password
    AUTO_PROPERTY(int, MaxCharacter) // Max Characters per block
    AUTO_PROPERTY(QString, Parity) // Parity/Data bits/Stop bits
    AUTO_PROPERTY(QString, PagerId) // Pager ID
    AUTO_PROPERTY(QString, MsgTemplate) // Msg Template

public:
    explicit SendMessageToPagerTapAction(QObject *parent = 0);

    virtual void run(TTest *test);
    virtual QStringList description(bool isBad);
    virtual TestAction *clone();

signals:

public slots:

};

} // namespace SDPO

#endif // TSENDMESSAGETOPAGERTAPACTION_H
