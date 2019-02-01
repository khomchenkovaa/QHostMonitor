#include "qTestListProperties.h"
#include "ui_qTestListProperties.h"
#include <QUuid>

namespace SDPO {

/******************************************************************/

TestListProperties::TestListProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestListProperties)
{
    ui->setupUi(this);
}

/******************************************************************/

TestListProperties::~TestListProperties()
{
    delete ui;
}

/******************************************************************/

void TestListProperties::setFileName(const QString fileName)
{
    if (fileName.isEmpty()) {
        ui->lblFileNameValue->setText(tr("not specified yet"));
    } else {
        ui->lblFileNameValue->setText(fileName);
    }
}

/******************************************************************/

void TestListProperties::setGuid(const QUuid guid)
{
    ui->lblGUIDValue->setText(guid.toString());
}

/******************************************************************/

void TestListProperties::setFileSize(const int bytes)
{
    ui->lblFileSizeValue->setText(QString::number(bytes));
}

/******************************************************************/

void TestListProperties::setFoldersCnt(const int foldersCnt)
{
    ui->lblFoldersValue->setText(QString::number(foldersCnt));
}

/******************************************************************/

void TestListProperties::setViewsCnt(const int viewsCnt)
{
    ui->lblViewsValue->setText(QString::number(viewsCnt));
}

/******************************************************************/

void TestListProperties::setTestsCnt(const int testsCnt)
{
    ui->lblTestItemsValue->setText(QString::number(testsCnt));
}

/******************************************************************/

void TestListProperties::setTotalRecords(const int totalCnt)
{
    ui->lblTotalRecordsValue->setText(QString::number(totalCnt));
}

/******************************************************************/

bool TestListProperties::storeHistory() const
{
    return ui->chbxStoreHistory->isChecked();
}

/******************************************************************/

void TestListProperties::setStoreHistory(const bool value)
{
    ui->chbxStoreHistory->setChecked(value);
}

/******************************************************************/

} // namespace SDPO
