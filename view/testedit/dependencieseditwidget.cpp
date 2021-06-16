#include "dependencieseditwidget.h"
#include "ui_dependencieseditwidget.h"

using namespace SDPO;

/******************************************************************/

DependenciesEditWidget::DependenciesEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DependenciesEditWidget)
{
    ui->setupUi(this);
    setupUI();
}

/******************************************************************/

DependenciesEditWidget::~DependenciesEditWidget()
{
    delete ui;
}

/******************************************************************/

void DependenciesEditWidget::reset()
{
    ui->treeDependentTests->clear();
}

/******************************************************************/

void DependenciesEditWidget::init(TTest *item)
{
    Q_UNUSED(item)
    ui->treeDependentTests->clear();
    //! TODO implement DependentTests init
}

/******************************************************************/

void DependenciesEditWidget::save(TTest *item)
{
    Q_UNUSED(item)
}

/******************************************************************/

int DependenciesEditWidget::doHide(bool hide)
{
    int result = 0;
    ui->btnDependenciesHideRight->setChecked(hide);
    if (ui->frmDependentTests->isHidden() != hide) {
        if (hide) {
            result = ui->frmDependentTests->height();
        }
        ui->frmDependentTests->setHidden(hide);
    }

    return result;
}

/******************************************************************/

void DependenciesEditWidget::setupUI()
{
    connect(ui->btnDependenciesHideRight, &QPushButton::toggled,
            this, &DependenciesEditWidget::hideMe);
}

/******************************************************************/
