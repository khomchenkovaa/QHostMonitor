#include "qFolderPropertiesStatisticWidget.h"
#include "ui_qFolderPropertiesStatisticWidget.h"

namespace SDPO {

FolderPropertiesStatisticWidget::FolderPropertiesStatisticWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FolderPropertiesStatisticWidget)
{
    ui->setupUi(this);
}

FolderPropertiesStatisticWidget::~FolderPropertiesStatisticWidget()
{
    delete ui;
}

} // namespace SDPO
