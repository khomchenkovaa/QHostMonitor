#include "qSpecialsPropertiesWidget.h"
#include "ui_qSpecialsPropertiesWidget.h"
#include "tFolder.h"

namespace SDPO {

/******************************************************************/

SpecialsPropertiesWidget::SpecialsPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpecialsPropertiesWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

SpecialsPropertiesWidget::~SpecialsPropertiesWidget()
{
    delete ui;
}

/******************************************************************/

void SpecialsPropertiesWidget::init(TNode *node)
{
    if (!node) {
        reset();
        return;
    }
    if (node->getType() != TNode::FOLDER) {
        reset();
        return;
    }
    TFolder *folder = qobject_cast<TFolder*>(node);
    ui->chkTestStatuses->setChecked(folder->isTestStatusesNotAffectTrayIconColor());
    ui->chkTestExecution->setChecked(folder->isNonSimultaneouslyTestExecution());
}

/******************************************************************/

void SpecialsPropertiesWidget::save(TNode *node)
{
    if (!node) {
        return;
    }
    if (node->getType() != TNode::FOLDER) {
        return;
    }
    TFolder *folder = qobject_cast<TFolder*>(node);
    folder->setTestStatusesNotAffectTrayIconColor(ui->chkTestStatuses->isChecked());
    folder->setNonSimultaneouslyTestExecution(ui->chkTestExecution->isChecked());
}

/******************************************************************/

void SpecialsPropertiesWidget::reset()
{
    ui->chkTestStatuses->setChecked(false);
    ui->chkTestExecution->setChecked(false);
}

/******************************************************************/

} // namespace SDPO
