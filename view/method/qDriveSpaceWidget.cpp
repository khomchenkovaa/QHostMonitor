#include "qDriveSpaceWidget.h"
#include "ui_qDriveSpaceWidget.h"
#include <QStorageInfo>
#include "method/tDriveSpace.h"

namespace SDPO {

/******************************************************************/

DriveSpaceWidget::DriveSpaceWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::DriveSpaceWidget)
{
    ui->setupUi(this);
    connect(ui->cmbDrive, SIGNAL(currentIndexChanged(int)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

DriveSpaceWidget::~DriveSpaceWidget()
{
    delete ui;
}

/******************************************************************/

void DriveSpaceWidget::init(TTestMethod *item)
{
    reset();
    TDriveSpace* driveSpace = qobject_cast<TDriveSpace*>(item);
    ui->cmbDrive->setCurrentText(driveSpace->getDrive());
    ui->spinMinFreeSpace->setValue(driveSpace->getMinFreeSpace());
    ui->cmbDimension->setCurrentText(driveSpace->getDimension());
}

/******************************************************************/

TTestMethod *DriveSpaceWidget::save(TTestMethod *item)
{
    TDriveSpace* driveSpace;
    if (item && (item->getTMethodID() == TMethodID::DriveSpace)) {
        driveSpace = qobject_cast<TDriveSpace*>(item);
    } else {
        driveSpace = new TDriveSpace();
    }
    driveSpace->setDrive(ui->cmbDrive->currentText().trimmed());
    driveSpace->setMinFreeSpace(ui->spinMinFreeSpace->value());
    driveSpace->setDimension(ui->cmbDimension->currentText());
    return driveSpace;
}

/******************************************************************/

void DriveSpaceWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::DriveSpace);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->cmbDrive->clear();
    QList<QStorageInfo> drives = QStorageInfo::mountedVolumes();
    foreach(QStorageInfo storage, drives) {
        ui->cmbDrive->addItem(QString(storage.device()));
    }
    ui->spinMinFreeSpace->setValue(ui->spinMinFreeSpace->minimum());
    ui->cmbDimension->setCurrentText("MB");
}

/******************************************************************/

QStringList DriveSpaceWidget::validate()
{
    QStringList errors;
    if(ui->cmbDrive->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a drive"));
    }
    return errors;
}

/******************************************************************/

QString DriveSpaceWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::DriveSpace);
    case Macro::TestMethod : return TMethod::toName(TMethodID::DriveSpace);
    case Macro::Host :
    case Macro::HostAddr : return "localhost";
    case Macro::Path : return ui->cmbDrive->currentText();
    case Macro::Object : {
        QFileInfo fInfo(ui->cmbDrive->currentText());
        return fInfo.baseName();
    }

    default: return QString();
    }

}

/******************************************************************/

} // namespace SDPO
