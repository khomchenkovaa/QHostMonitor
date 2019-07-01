#ifndef QPLAYSOUNDWIDGET_H
#define QPLAYSOUNDWIDGET_H

#include "qActionWidget.h"

namespace Ui {
class PlaySoundWidget;
}

namespace SDPO {

class PlaySoundWidget : public ActionWidget
{
    Q_OBJECT

public:
    explicit PlaySoundWidget(QWidget *parent = nullptr);
    ~PlaySoundWidget();

    virtual void init(TestAction *item = nullptr);
    virtual TestAction *save(TestAction *item);

private slots:
    void on_btnSoundFile_clicked();

private:
    Ui::PlaySoundWidget *ui;
};

} // namespace SDPO

#endif // QPLAYSOUNDWIDGET_H
