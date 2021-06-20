#include "qSchedulerOptionsWidget.h"
#include "ui_qSchedulerOptionsWidget.h"
#include "qActionProfiles.h"
#include "io/ioActionProfileLoader.h"
#include "gData.h"

namespace SDPO {

/******************************************************************/

SchedulerOptionsWidget::SchedulerOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::SchedulerOptionsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SchedulerOptionsWidget::~SchedulerOptionsWidget()
{
    delete ui;
}

/******************************************************************/

void SchedulerOptionsWidget::reset_AlertProfiles()
{
    ui->cmbAlertSelect_1->clear();
    ui->cmbAlertSelect_2->clear();
    ui->cmbAlertSelect_3->clear();
    ui->cmbAlertSelect_4->clear();
    ui->cmbAlertSelect_5->clear();

    foreach(const GActionProfile &profile, GData::actionProfiles) {
        ui->cmbAlertSelect_1->addItem(profile.name);
        ui->cmbAlertSelect_2->addItem(profile.name);
        ui->cmbAlertSelect_3->addItem(profile.name);
        ui->cmbAlertSelect_4->addItem(profile.name);
        ui->cmbAlertSelect_5->addItem(profile.name);
    }
}

/******************************************************************/

void SchedulerOptionsWidget::on_btnAlertSelect_1_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbAlertSelect_1->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertProfiles();
        ui->cmbAlertSelect_1->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void SchedulerOptionsWidget::on_btnAlertSelect_2_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbAlertSelect_2->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertProfiles();
        ui->cmbAlertSelect_2->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void SchedulerOptionsWidget::on_btnAlertSelect_3_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbAlertSelect_3->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertProfiles();
        ui->cmbAlertSelect_3->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void SchedulerOptionsWidget::on_btnAlertSelect_4_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbAlertSelect_4->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertProfiles();
        ui->cmbAlertSelect_4->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void SchedulerOptionsWidget::on_btnAlertSelect_5_clicked()
{
    IOActionProfileLoader loader;
    ActionProfiles dlg;
    dlg.init(ui->cmbAlertSelect_5->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        loader.save();
        reset_AlertProfiles();
        ui->cmbAlertSelect_5->setCurrentIndex(dlg.getSelected());
    } else {
        loader.load();
    }
}

/******************************************************************/

void SchedulerOptionsWidget::init(QSettings *s)
{
    reset_AlertProfiles();

    ui->cmbScheduleSelect_1->setCurrentIndex(s->value(SKEY_SCHEDULER_Mode1, SVAL_SCHEDULER_Mode1).toInt());
    ui->timeEdit_1->setTime                 (s->value(SKEY_SCHEDULER_Time1).toTime());
    ui->spinMinute_1->setValue              (s->value(SKEY_SCHEDULER_Interval1, SVAL_SCHEDULER_Interval1).toInt());
    ui->cmbSelectDay_1->setCurrentIndex     (s->value(SKEY_SCHEDULER_Day1, SVAL_SCHEDULER_Day1).toInt());
    ui->cmbMonthDay_1->setCurrentIndex      (s->value(SKEY_SCHEDULER_Day1, SVAL_SCHEDULER_Day1).toInt());
    ui->cmbAlertSelect_1->setCurrentIndex   (s->value(SKEY_SCHEDULER_SchedAlerts1, SVAL_SCHEDULER_SchedAlerts1).toInt());

    ui->cmbScheduleSelect_2->setCurrentIndex(s->value(SKEY_SCHEDULER_Mode2, SVAL_SCHEDULER_Mode2).toInt());
    ui->timeEdit_2->setTime                 (s->value(SKEY_SCHEDULER_Time2).toTime());
    ui->spinMinute_2->setValue              (s->value(SKEY_SCHEDULER_Interval2, SVAL_SCHEDULER_Interval2).toInt());
    ui->cmbSelectDay_2->setCurrentIndex     (s->value(SKEY_SCHEDULER_Day2, SVAL_SCHEDULER_Day2).toInt());
    ui->cmbMonthDay_2->setCurrentIndex      (s->value(SKEY_SCHEDULER_Day2, SVAL_SCHEDULER_Day2).toInt());
    ui->cmbAlertSelect_2->setCurrentIndex   (s->value(SKEY_SCHEDULER_SchedAlerts2, SVAL_SCHEDULER_SchedAlerts2).toInt());

    ui->cmbScheduleSelect_3->setCurrentIndex(s->value(SKEY_SCHEDULER_Mode3, SVAL_SCHEDULER_Mode3).toInt());
    ui->timeEdit_3->setTime                 (s->value(SKEY_SCHEDULER_Time3).toTime());
    ui->spinMinute_3->setValue              (s->value(SKEY_SCHEDULER_Interval3, SVAL_SCHEDULER_Interval3).toInt());
    ui->cmbSelectDay_3->setCurrentIndex     (s->value(SKEY_SCHEDULER_Day3, SVAL_SCHEDULER_Day3).toInt());
    ui->cmbMonthDay_3->setCurrentIndex      (s->value(SKEY_SCHEDULER_Day3, SVAL_SCHEDULER_Day3).toInt());
    ui->cmbAlertSelect_3->setCurrentIndex   (s->value(SKEY_SCHEDULER_SchedAlerts3, SVAL_SCHEDULER_SchedAlerts3).toInt());

    ui->cmbScheduleSelect_4->setCurrentIndex(s->value(SKEY_SCHEDULER_Mode4, SVAL_SCHEDULER_Mode4).toInt());
    ui->timeEdit_4->setTime                 (s->value(SKEY_SCHEDULER_Time4).toTime());
    ui->spinMinute_4->setValue              (s->value(SKEY_SCHEDULER_Interval4, SVAL_SCHEDULER_Interval4).toInt());
    ui->cmbSelectDay_4->setCurrentIndex     (s->value(SKEY_SCHEDULER_Day4, SVAL_SCHEDULER_Day4).toInt());
    ui->cmbMonthDay_4->setCurrentIndex      (s->value(SKEY_SCHEDULER_Day4, SVAL_SCHEDULER_Day4).toInt());
    ui->cmbAlertSelect_4->setCurrentIndex   (s->value(SKEY_SCHEDULER_SchedAlerts4, SVAL_SCHEDULER_SchedAlerts4).toInt());

    ui->cmbScheduleSelect_5->setCurrentIndex(s->value(SKEY_SCHEDULER_Mode5, SVAL_SCHEDULER_Mode5).toInt());
    ui->timeEdit_5->setTime                 (s->value(SKEY_SCHEDULER_Time5).toTime());
    ui->spinMinute_5->setValue              (s->value(SKEY_SCHEDULER_Interval5, SVAL_SCHEDULER_Interval5).toInt());
    ui->cmbSelectDay_5->setCurrentIndex     (s->value(SKEY_SCHEDULER_Day5, SVAL_SCHEDULER_Day5).toInt());
    ui->cmbMonthDay_5->setCurrentIndex      (s->value(SKEY_SCHEDULER_Day5, SVAL_SCHEDULER_Day5).toInt());
    ui->cmbAlertSelect_5->setCurrentIndex   (s->value(SKEY_SCHEDULER_SchedAlerts5, SVAL_SCHEDULER_SchedAlerts5).toInt());

    on_SchedulerSelect();
    connect(ui->cmbScheduleSelect_1, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));
    connect(ui->cmbScheduleSelect_2, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));
    connect(ui->cmbScheduleSelect_3, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));
    connect(ui->cmbScheduleSelect_4, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));
    connect(ui->cmbScheduleSelect_5, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));
}

/******************************************************************/

void SchedulerOptionsWidget::prepareToSave(QSettings *s)
{
    int mode1 = ui->cmbScheduleSelect_1->currentIndex();
    s->setValue(SKEY_SCHEDULER_Mode1, mode1);
    s->setValue(SKEY_SCHEDULER_Time1, ui->timeEdit_1->text());
    s->setValue(SKEY_SCHEDULER_Interval1, ui->spinMinute_1->value());
    if (mode1 < 4) { // monthly, quaterly
        s->setValue(SKEY_SCHEDULER_Day1, ui->cmbSelectDay_1->currentIndex());
    } else {
        s->setValue(SKEY_SCHEDULER_Day1, ui->cmbMonthDay_1->currentIndex());
    }
    s->setValue(SKEY_SCHEDULER_SchedAlerts1, ui->cmbAlertSelect_1->currentIndex());

    int mode2 = ui->cmbScheduleSelect_2->currentIndex();
    s->setValue(SKEY_SCHEDULER_Mode2, mode2);
    s->setValue(SKEY_SCHEDULER_Time2, ui->timeEdit_2->text());
    s->setValue(SKEY_SCHEDULER_Interval2, ui->spinMinute_2->value());
    if (mode2 < 4) { // monthly, quaterly
        s->setValue(SKEY_SCHEDULER_Day2, ui->cmbSelectDay_2->currentIndex());
    } else {
        s->setValue(SKEY_SCHEDULER_Day2, ui->cmbMonthDay_2->currentIndex());
    }
    s->setValue(SKEY_SCHEDULER_SchedAlerts2, ui->cmbAlertSelect_2->currentIndex());

    int mode3 = ui->cmbScheduleSelect_3->currentIndex();
    s->setValue(SKEY_SCHEDULER_Mode3, mode3);
    s->setValue(SKEY_SCHEDULER_Time3, ui->timeEdit_3->text());
    s->setValue(SKEY_SCHEDULER_Interval3, ui->spinMinute_3->value());
    if (mode3 < 4) { // monthly, quaterly
        s->setValue(SKEY_SCHEDULER_Day3, ui->cmbSelectDay_3->currentIndex());
    } else {
        s->setValue(SKEY_SCHEDULER_Day3, ui->cmbMonthDay_3->currentIndex());
    }
    s->setValue(SKEY_SCHEDULER_SchedAlerts3, ui->cmbAlertSelect_3->currentIndex());

    int mode4 = ui->cmbScheduleSelect_4->currentIndex();
    s->setValue(SKEY_SCHEDULER_Mode4, mode4);
    s->setValue(SKEY_SCHEDULER_Time4, ui->timeEdit_4->text());
    s->setValue(SKEY_SCHEDULER_Interval4, ui->spinMinute_4->value());
    if (mode4 < 4) { // monthly, quaterly
        s->setValue(SKEY_SCHEDULER_Day4, ui->cmbSelectDay_4->currentIndex());
    } else {
        s->setValue(SKEY_SCHEDULER_Day4, ui->cmbMonthDay_4->currentIndex());
    }
    s->setValue(SKEY_SCHEDULER_SchedAlerts4, ui->cmbAlertSelect_4->currentIndex());

    int mode5 = ui->cmbScheduleSelect_5->currentIndex();
    s->setValue(SKEY_SCHEDULER_Mode5, mode5);
    s->setValue(SKEY_SCHEDULER_Time5, ui->timeEdit_5->text());
    s->setValue(SKEY_SCHEDULER_Interval5, ui->spinMinute_5->value());
    if (mode5 < 4) { // monthly, quaterly
        s->setValue(SKEY_SCHEDULER_Day5, ui->cmbSelectDay_5->currentIndex());
    } else {
        s->setValue(SKEY_SCHEDULER_Day5, ui->cmbMonthDay_5->currentIndex());
    }
    s->setValue(SKEY_SCHEDULER_SchedAlerts5, ui->cmbAlertSelect_5->currentIndex());
}

/******************************************************************/

void SchedulerOptionsWidget::on_SchedulerSelect()
{
    int CurrentSelect_1 = ui->cmbScheduleSelect_1->currentIndex();
    switch (CurrentSelect_1) {
    case 0:
        ui->lblEvery_1->setHidden(true);
        ui->lblDay_1->setHidden(true);
        ui->spinMinute_1->setHidden(true);
        ui->lblMinute_1->setHidden(true);
        ui->cmbSelectDay_1->setHidden(true);
        ui->lblAt_1->setHidden(true);
        ui->cmbMonthDay_1->setHidden(true);
        ui->timeEdit_1->setHidden(true);
        break;
    case 1:
        ui->lblEvery_1->setHidden(false);
        ui->lblDay_1->setHidden(true);
        ui->spinMinute_1->setHidden(false);
        ui->lblMinute_1->setHidden(false);
        ui->cmbSelectDay_1->setHidden(true);
        ui->lblAt_1->setHidden(false);
        ui->cmbMonthDay_1->setHidden(true);
        ui->timeEdit_1->setHidden(true);
        break;
     case 2:
        ui->lblEvery_1->setHidden(false);
        ui->lblDay_1->setHidden(false);
        ui->spinMinute_1->setHidden(true);
        ui->lblMinute_1->setHidden(true);
        ui->cmbSelectDay_1->setHidden(true);
        ui->lblAt_1->setHidden(false);
        ui->cmbMonthDay_1->setHidden(true);
        ui->timeEdit_1->setHidden(false);
        break;
     case 3:
        ui->lblEvery_1->setHidden(false);
        ui->lblDay_1->setHidden(true);
        ui->spinMinute_1->setHidden(true);
        ui->lblMinute_1->setHidden(true);
        ui->cmbSelectDay_1->setHidden(false);
        ui->lblAt_1->setHidden(false);
        ui->cmbMonthDay_1->setHidden(true);
        ui->timeEdit_1->setHidden(false);
        break;
     case 4:
        ui->lblEvery_1->setHidden(false);
        ui->lblDay_1->setHidden(true);
        ui->spinMinute_1->setHidden(true);
        ui->lblMinute_1->setHidden(true);
        ui->cmbSelectDay_1->setHidden(true);
        ui->lblAt_1->setHidden(false);
        ui->cmbMonthDay_1->setHidden(false);
        ui->timeEdit_1->setHidden(false);
        break;
     case 5:
        ui->lblEvery_1->setHidden(false);
        ui->lblDay_1->setHidden(true);
        ui->spinMinute_1->setHidden(true);
        ui->lblMinute_1->setHidden(true);
        ui->cmbSelectDay_1->setHidden(true);
        ui->lblAt_1->setHidden(false);
        ui->cmbMonthDay_1->setHidden(false);
        ui->timeEdit_1->setHidden(false);
        break;
    }


     int CurrentSelect_2 = ui->cmbScheduleSelect_2->currentIndex();
     switch (CurrentSelect_2) {
     case 0:
        ui->lblEvery_2->setHidden(true);
        ui->lblDay_2->setHidden(true);
        ui->spinMinute_2->setHidden(true);
        ui->lblMinute_2->setHidden(true);
        ui->cmbSelectDay_2->setHidden(true);
        ui->lblAt_2->setHidden(true);
        ui->cmbMonthDay_2->setHidden(true);
        ui->timeEdit_2->setHidden(true);
        break;
     case 1:
        ui->lblEvery_2->setHidden(false);
        ui->lblDay_2->setHidden(true);
        ui->spinMinute_2->setHidden(false);
        ui->lblMinute_2->setHidden(false);
        ui->cmbSelectDay_2->setHidden(true);
        ui->lblAt_2->setHidden(false);
        ui->cmbMonthDay_2->setHidden(true);
        ui->timeEdit_2->setHidden(true);
        break;
      case 2:
        ui->lblEvery_2->setHidden(false);
        ui->lblDay_2->setHidden(false);
        ui->spinMinute_2->setHidden(true);
        ui->lblMinute_2->setHidden(true);
        ui->cmbSelectDay_2->setHidden(true);
        ui->lblAt_2->setHidden(false);
        ui->cmbMonthDay_2->setHidden(true);
        ui->timeEdit_2->setHidden(false);
        break;
      case 3:
        ui->lblEvery_2->setHidden(false);
        ui->lblDay_2->setHidden(true);
        ui->spinMinute_2->setHidden(true);
        ui->lblMinute_2->setHidden(true);
        ui->cmbSelectDay_2->setHidden(false);
        ui->lblAt_2->setHidden(false);
        ui->cmbMonthDay_2->setHidden(true);
        ui->timeEdit_2->setHidden(false);
        break;
      case 4:
        ui->lblEvery_2->setHidden(false);
        ui->lblDay_2->setHidden(true);
        ui->spinMinute_2->setHidden(true);
        ui->lblMinute_2->setHidden(true);
        ui->cmbSelectDay_2->setHidden(true);
        ui->lblAt_2->setHidden(false);
        ui->cmbMonthDay_2->setHidden(false);
        ui->timeEdit_2->setHidden(false);
        break;
      case 5:
        ui->lblEvery_2->setHidden(false);
        ui->lblDay_2->setHidden(true);
        ui->spinMinute_2->setHidden(true);
        ui->lblMinute_2->setHidden(true);
        ui->cmbSelectDay_2->setHidden(true);
        ui->lblAt_2->setHidden(false);
        ui->cmbMonthDay_2->setHidden(false);
        ui->timeEdit_2->setHidden(false);
        break;
     }

     int CurrentSelect_3 = ui->cmbScheduleSelect_3->currentIndex();
     switch (CurrentSelect_3) {
     case 0:
        ui->lblEvery_3->setHidden(true);
        ui->lblDay_3->setHidden(true);
        ui->spinMinute_3->setHidden(true);
        ui->lblMinute_3->setHidden(true);
        ui->cmbSelectDay_3->setHidden(true);
        ui->lblAt_3->setHidden(true);
        ui->cmbMonthDay_3->setHidden(true);
        ui->timeEdit_3->setHidden(true);
        break;
     case 1:
        ui->lblEvery_3->setHidden(false);
        ui->lblDay_3->setHidden(true);
        ui->spinMinute_3->setHidden(false);
        ui->lblMinute_3->setHidden(false);
        ui->cmbSelectDay_3->setHidden(true);
        ui->lblAt_3->setHidden(false);
        ui->cmbMonthDay_3->setHidden(true);
        ui->timeEdit_3->setHidden(true);
        break;
      case 2:
        ui->lblEvery_3->setHidden(false);
        ui->lblDay_3->setHidden(false);
        ui->spinMinute_3->setHidden(true);
        ui->lblMinute_3->setHidden(true);
        ui->cmbSelectDay_3->setHidden(true);
        ui->lblAt_3->setHidden(false);
        ui->cmbMonthDay_3->setHidden(true);
        ui->timeEdit_3->setHidden(false);
        break;
      case 3:
        ui->lblEvery_3->setHidden(false);
        ui->lblDay_3->setHidden(true);
        ui->spinMinute_3->setHidden(true);
        ui->lblMinute_3->setHidden(true);
        ui->cmbSelectDay_3->setHidden(false);
        ui->lblAt_3->setHidden(false);
        ui->cmbMonthDay_3->setHidden(true);
        ui->timeEdit_3->setHidden(false);
        break;
      case 4:
        ui->lblEvery_3->setHidden(false);
        ui->lblDay_3->setHidden(true);
        ui->spinMinute_3->setHidden(true);
        ui->lblMinute_3->setHidden(true);
        ui->cmbSelectDay_3->setHidden(true);
        ui->lblAt_3->setHidden(false);
        ui->cmbMonthDay_3->setHidden(false);
        ui->timeEdit_3->setHidden(false);
        break;
      case 5:
        ui->lblEvery_3->setHidden(false);
        ui->lblDay_3->setHidden(true);
        ui->spinMinute_3->setHidden(true);
        ui->lblMinute_3->setHidden(true);
        ui->cmbSelectDay_3->setHidden(true);
        ui->lblAt_3->setHidden(false);
        ui->cmbMonthDay_3->setHidden(false);
        ui->timeEdit_3->setHidden(false);
        break;
     }

     int CurrentSelect_4 = ui->cmbScheduleSelect_4->currentIndex();
     switch (CurrentSelect_4) {
     case 0:
        ui->lblEvery_4->setHidden(true);
        ui->lblDay_4->setHidden(true);
        ui->spinMinute_4->setHidden(true);
        ui->lblMinute_4->setHidden(true);
        ui->cmbSelectDay_4->setHidden(true);
        ui->lblAt_4->setHidden(true);
        ui->cmbMonthDay_4->setHidden(true);
        ui->timeEdit_4->setHidden(true);
        break;
     case 1:
        ui->lblEvery_4->setHidden(false);
        ui->lblDay_4->setHidden(true);
        ui->spinMinute_4->setHidden(false);
        ui->lblMinute_4->setHidden(false);
        ui->cmbSelectDay_4->setHidden(true);
        ui->lblAt_4->setHidden(false);
        ui->cmbMonthDay_4->setHidden(true);
        ui->timeEdit_4->setHidden(true);
        break;
      case 2:
        ui->lblEvery_4->setHidden(false);
        ui->lblDay_4->setHidden(false);
        ui->spinMinute_4->setHidden(true);
        ui->lblMinute_4->setHidden(true);
        ui->cmbSelectDay_4->setHidden(true);
        ui->lblAt_4->setHidden(false);
        ui->cmbMonthDay_4->setHidden(true);
        ui->timeEdit_4->setHidden(false);
        break;
      case 3:
        ui->lblEvery_4->setHidden(false);
        ui->lblDay_4->setHidden(true);
        ui->spinMinute_4->setHidden(true);
        ui->lblMinute_4->setHidden(true);
        ui->cmbSelectDay_4->setHidden(false);
        ui->lblAt_4->setHidden(false);
        ui->cmbMonthDay_4->setHidden(true);
        ui->timeEdit_4->setHidden(false);
        break;
      case 4:
        ui->lblEvery_4->setHidden(false);
        ui->lblDay_4->setHidden(true);
        ui->spinMinute_4->setHidden(true);
        ui->lblMinute_4->setHidden(true);
        ui->cmbSelectDay_4->setHidden(true);
        ui->lblAt_4->setHidden(false);
        ui->cmbMonthDay_4->setHidden(false);
        ui->timeEdit_4->setHidden(false);
        break;
      case 5:
        ui->lblEvery_4->setHidden(false);
        ui->lblDay_4->setHidden(true);
        ui->spinMinute_4->setHidden(true);
        ui->lblMinute_4->setHidden(true);
        ui->cmbSelectDay_4->setHidden(true);
        ui->lblAt_4->setHidden(false);
        ui->cmbMonthDay_4->setHidden(false);
        ui->timeEdit_4->setHidden(false);
        break;
     }

     int CurrentSelect_5 = ui->cmbScheduleSelect_5->currentIndex();
     switch (CurrentSelect_5) {
     case 0:
        ui->lblEvery_5->setHidden(true);
        ui->lblDay_5->setHidden(true);
        ui->spinMinute_5->setHidden(true);
        ui->lblMinute_5->setHidden(true);
        ui->cmbSelectDay_5->setHidden(true);
        ui->lblAt_5->setHidden(true);
        ui->cmbMonthDay_5->setHidden(true);
        ui->timeEdit_5->setHidden(true);
        break;
     case 1:
        ui->lblEvery_5->setHidden(false);
        ui->lblDay_5->setHidden(true);
        ui->spinMinute_5->setHidden(false);
        ui->lblMinute_5->setHidden(false);
        ui->cmbSelectDay_5->setHidden(true);
        ui->lblAt_5->setHidden(false);
        ui->cmbMonthDay_5->setHidden(true);
        ui->timeEdit_5->setHidden(true);
        break;
      case 2:
        ui->lblEvery_5->setHidden(false);
        ui->lblDay_5->setHidden(false);
        ui->spinMinute_5->setHidden(true);
        ui->lblMinute_5->setHidden(true);
        ui->cmbSelectDay_5->setHidden(true);
        ui->lblAt_5->setHidden(false);
        ui->cmbMonthDay_5->setHidden(true);
        ui->timeEdit_5->setHidden(false);
        break;
      case 3:
        ui->lblEvery_5->setHidden(false);
        ui->lblDay_5->setHidden(true);
        ui->spinMinute_5->setHidden(true);
        ui->lblMinute_5->setHidden(true);
        ui->cmbSelectDay_5->setHidden(false);
        ui->lblAt_5->setHidden(false);
        ui->cmbMonthDay_5->setHidden(true);
        ui->timeEdit_5->setHidden(false);
        break;
      case 4:
        ui->lblEvery_5->setHidden(false);
        ui->lblDay_5->setHidden(true);
        ui->spinMinute_5->setHidden(true);
        ui->lblMinute_5->setHidden(true);
        ui->cmbSelectDay_5->setHidden(true);
        ui->lblAt_5->setHidden(false);
        ui->cmbMonthDay_5->setHidden(false);
        ui->timeEdit_5->setHidden(false);
        break;
      case 5:
        ui->lblEvery_5->setHidden(false);
        ui->lblDay_5->setHidden(true);
        ui->spinMinute_5->setHidden(true);
        ui->lblMinute_5->setHidden(true);
        ui->cmbSelectDay_5->setHidden(true);
        ui->lblAt_5->setHidden(false);
        ui->cmbMonthDay_5->setHidden(false);
        ui->timeEdit_5->setHidden(false);
        break;
     }
}

/******************************************************************/

} // namespace SDPO

