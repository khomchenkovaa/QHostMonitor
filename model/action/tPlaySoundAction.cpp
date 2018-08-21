#include "tPlaySoundAction.h"
#include "QSound"

namespace SDPO {

/******************************************************************/

PlaySoundAction::PlaySoundAction(QObject *parent) :
    TestAction(parent)
{
    setAction(TActionID::PlaySound);
    b_WakeUp = false;
}

/******************************************************************/

void PlaySoundAction::run(TTest *test)
{
    Q_UNUSED(test)
    QSound::play(a_File);
}

/******************************************************************/

QStringList PlaySoundAction::description(bool isBad)
{
    QStringList result = TestAction::description(isBad);
    result.append(QString("File: %1").arg(a_File));
    result.append(QString("WakeUp: %1").arg(b_WakeUp?"Yes":"No"));
    return result;
}

/******************************************************************/

TestAction *PlaySoundAction::clone()
{
    PlaySoundAction *result = new PlaySoundAction();
    copyProperties(result);
    result->setFile(a_File);
    result->setWakeUp(b_WakeUp);
    return result;
}

/******************************************************************/

} // namespace SDPO
