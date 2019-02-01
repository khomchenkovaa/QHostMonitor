#include "qPlaySoundWidget.h"
#include "ui_qPlaySoundWidget.h"
#include "action/tPlaySoundAction.h"
#include "QFileDialog"

namespace SDPO {

/******************************************************************/

PlaySoundWidget::PlaySoundWidget(QWidget *parent) :
    ActionWidget(parent),
    ui(new Ui::PlaySoundWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

PlaySoundWidget::~PlaySoundWidget()
{
    delete ui;
}

/******************************************************************/

void PlaySoundWidget::init(TestAction *item)
{
    if (!item || item->getAction() != TActionID::PlaySound) {
        return;
    }
    PlaySoundAction *action = qobject_cast<PlaySoundAction *>(item);
    ui->lineSoundFile->setText(action->getFile());
    ui->chkShowWakeup->setChecked(action->isWakeUp());
}

/******************************************************************/

TestAction *PlaySoundWidget::save(TestAction *item)
{
    if (!item || item->getAction() != TActionID::PlaySound) {
        item = new PlaySoundAction();
    }
    PlaySoundAction *action = qobject_cast<PlaySoundAction *>(item);
    action->setFile(ui->lineSoundFile->text());
    action->setWakeUp(ui->chkShowWakeup->isChecked());
    return action;
}

/******************************************************************/

void PlaySoundWidget::on_btnSoundFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Play sound file"),
                                                    ui->lineSoundFile->text(),
                                                    tr("Sound files (*.wav *.mp3)"));
    if (!fileName.isEmpty()) {
        ui->lineSoundFile->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO

