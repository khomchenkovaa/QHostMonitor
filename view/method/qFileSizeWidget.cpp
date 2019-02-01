#include "qFileSizeWidget.h"
#include "ui_qFileSizeWidget.h"
#include "method/tFolderSize.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

FileSizeWidget::FileSizeWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::FileSizeWidget)
{
    ui->setupUi(this);
    connect(ui->editFolder, SIGNAL(textEdited(QString)),SIGNAL(propertiesChanged()));
}

/******************************************************************/

FileSizeWidget::~FileSizeWidget()
{
    delete ui;
}

/******************************************************************/

void FileSizeWidget::init(TTestMethod *item)
{
    TFolderSize *folderSize = qobject_cast<TFolderSize*>(item);
    ui->editFolder->setText(folderSize->getPath());
    ui->chkSubFolders->setChecked(folderSize->isIncludeSubfolders());
    ui->chkUseMacros->setChecked(folderSize->isTranslateMacros());
    ui->spinMaxSize->setValue(folderSize->getMaxSize());
    ui->cmbSizeUnits->setCurrentText(folderSize->getDimension());
}

/******************************************************************/

TTestMethod *FileSizeWidget::save(TTestMethod *item)
{
    TFolderSize* folderSize;
    if (item && (item->getTMethodID() == TMethodID::FileSize)) {
        folderSize = qobject_cast<TFolderSize*>(item);
    } else {
        folderSize = new TFolderSize();
    }
    folderSize->setPath(ui->editFolder->text());
    folderSize->setIncludeSubfolders(ui->chkSubFolders->isChecked());
    folderSize->setTranslateMacros(ui->chkUseMacros->isChecked());
    folderSize->setMaxSize(ui->spinMaxSize->value());
    folderSize->setDimension(ui->cmbSizeUnits->currentText());
    return folderSize;
}

/******************************************************************/

void FileSizeWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::FileSize);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->editFolder->clear();
    ui->chkSubFolders->setChecked(false);
    ui->chkUseMacros->setChecked(false);
    ui->spinMaxSize->setValue(64);
    ui->cmbSizeUnits->setCurrentText("KB");
}

/******************************************************************/

QStringList FileSizeWidget::validate()
{
    QStringList errors;
    if(ui->editFolder->text().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a folder (file) name"));
    }
    return errors;
}

/******************************************************************/

QString FileSizeWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::FileSize);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::FileSize);
    case Macro::Host :
    case Macro::HostAddr : return "localhost";
    case Macro::Path : return ui->editFolder->text();
    case Macro::Object : {
        QFileInfo fInfo(ui->editFolder->text());
        return fInfo.baseName();
    }

    default: return QString();
    }

}

/******************************************************************/

void FileSizeWidget::on_btnFolder_clicked()
{
    QString dirName = QFileDialog::getOpenFileName(this,tr("Select Directory"),ui->editFolder->text());
    if (!dirName.isEmpty()) {
        ui->editFolder->setText(dirName);
    }
}

/******************************************************************/

} // namespace SDPO

