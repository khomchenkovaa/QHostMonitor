#include "qSchedulerOptionsWidget.h"
#include "ui_qSchedulerOptionsWidget.h"
#include "qActionProfiles.h"
#include "global/ioActionProfileLoader.h"
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

void SchedulerOptionsWidget::init()
{
    reset_AlertProfiles();

    QVariant value = Settings::get(Settings::Scheduler, Settings::Mode1, QVariant(0));
        ui->cmbScheduleSelect_1->setCurrentIndex(value.toInt());
        on_SchedulerSelect();
        connect(ui->cmbScheduleSelect_1, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));

    value = Settings::get(Settings::Scheduler, Settings::Time1, QVariant());
        ui->timeEdit_1->setTime(value.toTime());

    value = Settings::get(Settings::Scheduler, Settings::Interval1, QVariant(60));
        ui->spinMinute_1->setValue(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day1, QVariant(1));
        ui->cmbSelectDay_1->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day1, QVariant(1));
        ui->cmbMonthDay_1->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::SchedAlerts1, QVariant());
        ui->cmbAlertSelect_1->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Mode2, QVariant(0));
        ui->cmbScheduleSelect_2->setCurrentIndex(value.toInt());
        on_SchedulerSelect();
        connect(ui->cmbScheduleSelect_2, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));

    value = Settings::get(Settings::Scheduler, Settings::Time2, QVariant());
        ui->timeEdit_2->setTime(value.toTime());

    value = Settings::get(Settings::Scheduler, Settings::Interval2, QVariant(60));
        ui->spinMinute_2->setValue(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day2, QVariant(2));
        ui->cmbSelectDay_2->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day2, QVariant(2));
        ui->cmbMonthDay_2->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::SchedAlerts3, QVariant());
        ui->cmbAlertSelect_2->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Mode3, QVariant(0));
        ui->cmbScheduleSelect_3->setCurrentIndex(value.toInt());
        on_SchedulerSelect();
        connect(ui->cmbScheduleSelect_3, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));

    value = Settings::get(Settings::Scheduler, Settings::Time3, QVariant());
        ui->timeEdit_3->setTime(value.toTime());

    value = Settings::get(Settings::Scheduler, Settings::Interval3, QVariant(60));
        ui->spinMinute_3->setValue(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day3, QVariant(3));
        ui->cmbSelectDay_3->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day3, QVariant(3));
        ui->cmbMonthDay_3->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::SchedAlerts3, QVariant());
        ui->cmbAlertSelect_3->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Mode4, QVariant(0));
        ui->cmbScheduleSelect_4->setCurrentIndex(value.toInt());
        on_SchedulerSelect();
        connect(ui->cmbScheduleSelect_4, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));

    value = Settings::get(Settings::Scheduler, Settings::Time4, QVariant());
        ui->timeEdit_4->setTime(value.toTime());

    value = Settings::get(Settings::Scheduler, Settings::Interval4, QVariant(60));
        ui->spinMinute_4->setValue(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day4, QVariant(4));
        ui->cmbSelectDay_4->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day4, QVariant(4));
        ui->cmbMonthDay_4->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::SchedAlerts4, QVariant());
        ui->cmbAlertSelect_4->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Mode5, QVariant(0));
        ui->cmbScheduleSelect_5->setCurrentIndex(value.toInt());
        on_SchedulerSelect();
        connect(ui->cmbScheduleSelect_5, SIGNAL(currentIndexChanged(int)),this, SLOT(on_SchedulerSelect()));

    value = Settings::get(Settings::Scheduler, Settings::Time5, QVariant());
        ui->timeEdit_5->setTime(value.toTime());

    value = Settings::get(Settings::Scheduler, Settings::Interval5, QVariant(60));
        ui->spinMinute_5->setValue(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day5, QVariant(5));
        ui->cmbSelectDay_5->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::Day5, QVariant(5));
        ui->cmbMonthDay_5->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Scheduler, Settings::SchedAlerts5, QVariant());
        ui->cmbAlertSelect_5->setCurrentIndex(value.toInt());

}

/******************************************************************/

void SchedulerOptionsWidget::prepareToSave()
{
      Settings::set(Settings::Scheduler, Settings::Mode1) = QVariant(ui->cmbScheduleSelect_1->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Time1) = QVariant(ui->timeEdit_1->text());
      Settings::set(Settings::Scheduler, Settings::Interval1) = QVariant(ui->spinMinute_1->value());
      Settings::set(Settings::Scheduler, Settings::Day1) = QVariant(ui->cmbSelectDay_1->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Day1) = QVariant(ui->cmbMonthDay_1->currentIndex());
      Settings::set(Settings::Scheduler, Settings::SchedAlerts1) = QVariant(ui->cmbAlertSelect_1->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Mode2) = QVariant(ui->cmbScheduleSelect_2->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Time2) = QVariant(ui->timeEdit_2->text());
      Settings::set(Settings::Scheduler, Settings::Interval2) = QVariant(ui->spinMinute_2->value());
      Settings::set(Settings::Scheduler, Settings::Day2) = QVariant(ui->cmbSelectDay_2->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Day2) = QVariant(ui->cmbMonthDay_2->currentIndex());
      Settings::set(Settings::Scheduler, Settings::SchedAlerts2) = QVariant(ui->cmbAlertSelect_2->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Mode3) = QVariant(ui->cmbScheduleSelect_3->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Time3) = QVariant(ui->timeEdit_3->text());
      Settings::set(Settings::Scheduler, Settings::Interval3) = QVariant(ui->spinMinute_3->value());
      Settings::set(Settings::Scheduler, Settings::Day3) = QVariant(ui->cmbSelectDay_3->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Day3) = QVariant(ui->cmbMonthDay_3->currentIndex());
      Settings::set(Settings::Scheduler, Settings::SchedAlerts3) = QVariant(ui->cmbAlertSelect_3->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Mode4) = QVariant(ui->cmbScheduleSelect_4->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Time4) = QVariant(ui->timeEdit_4->text());
      Settings::set(Settings::Scheduler, Settings::Interval4) = QVariant(ui->spinMinute_4->value());
      Settings::set(Settings::Scheduler, Settings::Day4) = QVariant(ui->cmbSelectDay_4->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Day4) = QVariant(ui->cmbMonthDay_4->currentIndex());
      Settings::set(Settings::Scheduler, Settings::SchedAlerts4) = QVariant(ui->cmbAlertSelect_4->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Mode5) = QVariant(ui->cmbScheduleSelect_5->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Time5) = QVariant(ui->timeEdit_5->text());
      Settings::set(Settings::Scheduler, Settings::Interval5) = QVariant(ui->spinMinute_5->value());
      Settings::set(Settings::Scheduler, Settings::Day5) = QVariant(ui->cmbSelectDay_5->currentIndex());
      Settings::set(Settings::Scheduler, Settings::Day5) = QVariant(ui->cmbMonthDay_5->currentIndex());
      Settings::set(Settings::Scheduler, Settings::SchedAlerts5) = QVariant(ui->cmbAlertSelect_5->currentIndex());
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

