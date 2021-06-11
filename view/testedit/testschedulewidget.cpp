#include "testschedulewidget.h"
#include "ui_testschedulewidget.h"

#include "tTest.h"

#include <QDebug>

using namespace SDPO;

/******************************************************************/

TestScheduleWidget::TestScheduleWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TestScheduleWidget)
{
    ui->setupUi(this);
    setupUI();
}

/******************************************************************/

TestScheduleWidget::~TestScheduleWidget()
{
    delete ui;
}

/******************************************************************/

void TestScheduleWidget::reset()
{
    ui->btnScheduleRegular->setChecked(true);
    ui->btnScheduleIrregular->setChecked(false);
    ui->btnScheduleByExpression->setChecked(false);
    ui->stwSchedule->setCurrentIndex(1);
    ui->cmbSchedIrregularMode->setCurrentIndex(0);
    ui->cmbSchedDayOfMonth->setHidden(true);
    ui->cmbSchedDayOfWeek->setHidden(true);
    ui->sbScheduleHours->setValue(0);
    ui->sbScheduleMin->setValue(10);
    ui->sbScheduleSec->setValue(0);
}

/******************************************************************/

void TestScheduleWidget::init(TTest *item)
{
    int hours = item->interval()/(60*60); // hours
    int min = (item->interval() - hours*60*60) / 60; // minutes
    int sec = (item->interval() - hours*60*60 - min*60); // sec
    switch( item->schedule()->getMode() ) {
    case TSchedule::Regular : // Regular
        onBtnRegular();
        ui->sbScheduleHours->setValue(hours);
        ui->sbScheduleMin->setValue(min);
        ui->sbScheduleSec->setValue(sec);
        ui->cmbSchedule->setCurrentText(item->schedule()->getScheduleName());
        break;
    case TSchedule::OncePerDay : // Irregular - OneTestPerDay
        onBtnIrregular();
        ui->cmbSchedIrregularMode->setCurrentIndex(0);
        onCmbIrregularModeChanged(0);
        ui->timeSchedIrregular->setTime(item->schedule()->getScheduleTime());
        break;
    case TSchedule::OncePerWeek : // Irregular - OneTestPerWeek
        onBtnIrregular();
        ui->cmbSchedIrregularMode->setCurrentIndex(1);
        onCmbIrregularModeChanged(1);
        ui->cmbSchedDayOfWeek->setCurrentIndex(item->schedule()->getScheduleDay());
        ui->timeSchedIrregular->setTime(item->schedule()->getScheduleTime());
        break;
    case TSchedule::OncePerMonth : // Irregular - OneTestPerMonth
        onBtnIrregular();
        ui->cmbSchedIrregularMode->setCurrentIndex(2);
        onCmbIrregularModeChanged(2);
        ui->cmbSchedDayOfMonth->setCurrentIndex(item->schedule()->getScheduleDay());
        ui->timeSchedIrregular->setTime(item->schedule()->getScheduleTime());
        break;
    case TSchedule::ByExpression : // By Expression
        onBtnByExpression();
        ui->cmbScheduleExpr1->setCurrentText(item->schedule()->getScheduleExpr1());
        ui->cmbScheduleExpr2->setCurrentText(item->schedule()->getScheduleExpr2());
        break;
    }
}

/******************************************************************/

void TestScheduleWidget::save(TTest *item)
{
    if (ui->btnScheduleRegular->isChecked()) {
        item->setRegularSchedule((ui->sbScheduleHours->value() * 60 +
                                    ui->sbScheduleMin->value()) * 60 +
                                       ui->sbScheduleSec->value(),
                                   ui->cmbSchedule->currentText());
    } else if (ui->btnScheduleIrregular->isChecked()) {
        switch (ui->cmbSchedIrregularMode->currentIndex()) {
        case 0: // once per day
            item->setOncePerDaySchedule(ui->timeSchedIrregular->time());
            break;
        case 1: // once per week
            item->setOncePerWeekSchedule(ui->cmbSchedDayOfWeek->currentIndex(), ui->timeSchedIrregular->time());
            break;
        case 2: // once per month
            item->setOncePerMonthSchedule(ui->cmbSchedDayOfMonth->currentIndex(), ui->timeSchedIrregular->time());
            break;
        }
    } else if (ui->btnScheduleByExpression->isChecked()) {
        item->setByExpressionSchedule(
            ui->cmbScheduleExpr1->currentText(),
            ui->cmbScheduleExpr2->currentText());
    }
}

/******************************************************************/

void TestScheduleWidget::onBtnSchedulesDlg()
{
    qDebug() << "TODO: HostMonDlg -> OpenSchedilesDlg";
}

/******************************************************************/

void TestScheduleWidget::onBtnRegular()
{
    ui->btnScheduleRegular->setChecked(true);
    ui->btnScheduleIrregular->setChecked(false);
    ui->btnScheduleByExpression->setChecked(false);
    ui->stwSchedule->setCurrentIndex(1);
}

/******************************************************************/

void TestScheduleWidget::onBtnIrregular()
{
    ui->btnScheduleRegular->setChecked(false);
    ui->btnScheduleIrregular->setChecked(true);
    ui->btnScheduleByExpression->setChecked(false);
    ui->stwSchedule->setCurrentIndex(2);
}

/******************************************************************/

void TestScheduleWidget::onBtnByExpression()
{
    ui->btnScheduleRegular->setChecked(false);
    ui->btnScheduleIrregular->setChecked(false);
    ui->btnScheduleByExpression->setChecked(true);
    ui->stwSchedule->setCurrentIndex(0);
}

/******************************************************************/

void TestScheduleWidget::onCmbIrregularModeChanged(int index)
{
    switch(index) {
    case 0: // once a day
        ui->cmbSchedDayOfMonth->setHidden(true);
        ui->cmbSchedDayOfWeek->setHidden(true);
        break;
    case 1: // once a week
        ui->cmbSchedDayOfMonth->setHidden(true);
        ui->cmbSchedDayOfWeek->setHidden(false);
        break;
    case 2: // once a month
        ui->cmbSchedDayOfMonth->setHidden(false);
        ui->cmbSchedDayOfWeek->setHidden(true);
        break;
    }
}

/******************************************************************/

void TestScheduleWidget::setupUI()
{
    connect(ui->btnSchedulesDlg, &QPushButton::clicked,
            this, &TestScheduleWidget::onBtnSchedulesDlg);
    connect(ui->btnScheduleRegular, &QPushButton::clicked,
            this, &TestScheduleWidget::onBtnRegular);
    connect(ui->btnScheduleIrregular, &QPushButton::clicked,
            this, &TestScheduleWidget::onBtnIrregular);
    connect(ui->btnScheduleByExpression, &QPushButton::clicked,
            this, &TestScheduleWidget::onBtnByExpression);
    connect(ui->cmbSchedIrregularMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TestScheduleWidget::onCmbIrregularModeChanged);
}

/******************************************************************/
