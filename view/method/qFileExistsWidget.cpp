#include "qFileExistsWidget.h"
#include "ui_qFileExistsWidget.h"
#include "method/tFileExists.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

FileExistsWidget::FileExistsWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::FileExistsWidget)
{
    ui->setupUi(this);
    connect(ui->editFileName, SIGNAL(textEdited(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->rbFileDoesntExists, SIGNAL(clicked()), this, SLOT(onFileExistanceChanged()));
    connect(ui->rbFileExists, SIGNAL(clicked()), this, SLOT(onFileExistanceChanged()));
}

/******************************************************************/

FileExistsWidget::~FileExistsWidget()
{
    delete ui;
}

/******************************************************************/

void FileExistsWidget::init(TTestMethod *item)
{
    TFileExists *fileExists = qobject_cast<TFileExists*>(item);
    ui->editFileName->setText(fileExists->getFileName());
    ui->chkUseMacros->setChecked(fileExists->isTranslateMacros());
    if (fileExists->isFileExistsCriteria()) {
        ui->rbFileExists->setChecked(true);
    } else {
        ui->rbFileDoesntExists->setChecked(true);
    }
    ui->chkMaxAge->setChecked(fileExists->isFileOlderFlag());
    ui->chkMinAge->setChecked(fileExists->isFileNewerFlag());
    ui->spinMaxAge->setValue(fileExists->getFileOlderValue());
    ui->spinMinAge->setValue(fileExists->getFileNewerValue());
    onFileExistanceChanged();
    onTimeCriteriaChanged();
}

/******************************************************************/

TTestMethod *FileExistsWidget::save(TTestMethod *item)
{
    TFileExists* fileExists;
    if (item && (item->getTMethodID() == TMethodID::FileExists)) {
        fileExists = qobject_cast<TFileExists*>(item);
    } else {
        fileExists = new TFileExists();
    }
    fileExists->setFileName(ui->editFileName->text());
    fileExists->setTranslateMacros(ui->chkUseMacros->isChecked());
    fileExists->setFileExistsCriteria(ui->rbFileExists->isChecked());
    fileExists->setFileOlderFlag(ui->chkMaxAge->isChecked());
    fileExists->setFileNewerFlag(ui->chkMinAge->isChecked());
    fileExists->setFileOlderValue(ui->spinMaxAge->value());
    fileExists->setFileNewerValue(ui->spinMinAge->value());
    return fileExists;
}

/******************************************************************/

void FileExistsWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TMethod method = TMethod::tMethodList.at((int)TMethodID::FileExists);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->editFileName->clear();
    ui->chkUseMacros->setChecked(false);
    ui->rbFileExists->setChecked(true);
    ui->chkMaxAge->setChecked(false);
    ui->chkMinAge->setChecked(false);
    ui->spinMaxAge->setValue(60);
    ui->spinMinAge->setValue(60);
    onFileExistanceChanged();
    onTimeCriteriaChanged();
}

/******************************************************************/

QStringList FileExistsWidget::validate()
{
    QStringList errors;
    if(ui->editFileName->text().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a file (folder) name"));
    }
    return errors;
}

/******************************************************************/

QString FileExistsWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::FileExists);
    case Macro::TestMethod : return TMethod::toName(TMethodID::FileExists);
    case Macro::Host :
    case Macro::HostAddr : return "localhost";
    case Macro::Path : return ui->editFileName->text();
    case Macro::Object : {
        QFileInfo fInfo(ui->editFileName->text());
        return fInfo.baseName();
    }

    default: return QString();
    }

}

/******************************************************************/

void FileExistsWidget::on_btnFileName_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("File"),ui->editFileName->text());
    if (!fileName.isEmpty()) {
        ui->editFileName->setText(fileName);
    }
}

/******************************************************************/

void FileExistsWidget::onFileExistanceChanged()
{
    if (ui->rbFileExists->isChecked()) {
        ui->lblAndOr->setText("and");
    } else {
        ui->lblAndOr->setText("or");
    }
}

/******************************************************************/

void FileExistsWidget::onTimeCriteriaChanged()
{
    if (ui->chkMaxAge->isChecked() || ui->chkMinAge->isChecked()) {
        ui->lblAndOr->setEnabled(true);
        ui->lblAndOr->setFrameShadow(QFrame::Sunken);
    } else {
        ui->lblAndOr->setDisabled(true);
        ui->lblAndOr->setFrameShadow(QFrame::Raised);
    }
    if (ui->chkMaxAge->isChecked()) ui->chkMinAge->setChecked(false);
    if (ui->chkMinAge->isChecked()) ui->chkMaxAge->setChecked(false);
}

/******************************************************************/

void FileExistsWidget::on_chkMaxAge_clicked(bool checked)
{
    if (checked) {
         ui->chkMinAge->setChecked(false);
    }
    onTimeCriteriaChanged();
}

/******************************************************************/

void FileExistsWidget::on_chkMinAge_clicked(bool checked)
{
    if (checked) {
         ui->chkMaxAge->setChecked(false);
    }
    onTimeCriteriaChanged();
}

/******************************************************************/

} //namespace SDPO

