#include "mastereditwidget.h"
#include "ui_mastereditwidget.h"

using namespace SDPO;

/******************************************************************/

MasterEditWidget::MasterEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MasterEditWidget)
{
    ui->setupUi(this);
    setupUI();
}

/******************************************************************/

MasterEditWidget::~MasterEditWidget()
{
    delete ui;
}

/******************************************************************/

void MasterEditWidget::reset(TNode *root)
{
    ui->cmbDependencyMode->setCurrentIndex(0);
    MasterTestsEditWidget *masterTests = qobject_cast<MasterTestsEditWidget*>(ui->wMasterTests);
    if (masterTests) {
        masterTests->reset(root);
    }
    ExpressionTestsEditWidget *expressionTests = qobject_cast<ExpressionTestsEditWidget*>(ui->wExpressionTests);
    if (expressionTests) {
        expressionTests->reset();
    }
    ui->chkSynchronizeCounters->setChecked(true);
    ui->chkSynchronizeStatusAlerts->setChecked(false);
}

/******************************************************************/

void MasterEditWidget::init(TTest *item)
{
    ui->cmbDependencyMode->setCurrentIndex(item->getDependencyMode());
    ui->wMasterTests->init(item);
    ui->wExpressionTests->init(item);
    ui->chkSynchronizeCounters->setChecked(item->isSynchronizeCounters());
    ui->chkSynchronizeStatusAlerts->setChecked(item->isSynchronizeStatusAlerts());

}

/******************************************************************/

void MasterEditWidget::save(TTest *item)
{
    item->setDependencyMode(ui->cmbDependencyMode->currentIndex());
    ui->wMasterTests->save(item);
    ui->wExpressionTests->save(item);
    item->setSynchronizeCounters(ui->chkSynchronizeCounters->isChecked());
    item->setSynchronizeStatusAlerts(ui->chkSynchronizeStatusAlerts->isChecked());
}

/******************************************************************/

int MasterEditWidget::doHide(bool hide)
{
    int result = 0;
    ui->btnDependenciesHideLeft->setChecked(hide);
    if (ui->frmMasterTests->isHidden() != hide) {
        if (hide) {
            result = ui->frmMasterTests->height();
        }
        ui->frmMasterTests->setHidden(hide);
    }
    return result;
}

/******************************************************************/

void MasterEditWidget::setupUI()
{
    connect(ui->btnDependenciesHideLeft, &QPushButton::toggled,
            this, &MasterEditWidget::hideMe);
    connect(ui->cmbDependencyMode, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->stwMasterTest, &QStackedWidget::setCurrentIndex);
    connect(ui->chkSynchronizeCounters, &QCheckBox::toggled,
            ui->chkSynchronizeStatusAlerts, &QCheckBox::setEnabled);

}

/******************************************************************/
