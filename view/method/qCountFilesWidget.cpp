#include "qCountFilesWidget.h"
#include "ui_qCountFilesWidget.h"
#include "method/tCountFiles.h"
#include <QFileDialog>

namespace SDPO {

/*****************************************************************/

CountFilesWidget::CountFilesWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::CountFilesWidget)
{
    ui->setupUi(this);
    connect(ui->lnEditFolder, SIGNAL(textChanged(QString)), this, SIGNAL(propertiesChanged()));
    connect(ui->cmbFileName, SIGNAL(currentTextChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/*****************************************************************/

CountFilesWidget::~CountFilesWidget()
{
    delete ui;
}

/*****************************************************************/

void CountFilesWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::CountFiles) ) {
        reset();
        return;
    }
    TCountFiles* test = qobject_cast<TCountFiles*>(item);
    ui->lnEditFolder->setText(test->getFolder());
    ui->chkTranslateMacros->setChecked(test->isTranslateMacros());
    ui->cmbFileName->setCurrentText(test->getFileNameMask());
    ui->chkSubFolders->setChecked(test->isIncludeSybFolder());
    ui->cmbCount->setCurrentIndex(test->getCondition());
    ui->spinCount->setValue(test->getCountValue());
    ui->spinAlertSize->setValue(test->getAlertWhen());
}

/*****************************************************************/

TestMethod *CountFilesWidget::save(TestMethod *item)
{
    TCountFiles* test;
    if (item && (item->getTMethodID() == TMethodID::CountFiles)) {
        test = qobject_cast<TCountFiles*>(item);
    } else {
        test = new TCountFiles();
    }
    test->setFolder(ui->lnEditFolder->text());
    test->setTranslateMacros(ui->chkTranslateMacros->isChecked());
    test->setFileNameMask(ui->cmbFileName->currentText());
    test->setIncludeSybFolder(ui->chkSubFolders->isChecked());
    test->setCondition((TCountFiles::CountCondition)ui->cmbCount->currentIndex());
    test->setCountValue(ui->spinCount->value());
    test->setAlertWhen(ui->spinAlertSize->value());
    return test;
}

/******************************************************************/

void CountFilesWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::CountFiles);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->lnEditFolder->clear();
    ui->chkTranslateMacros->setChecked(false);
    ui->cmbFileName->clear();
    ui->chkSubFolders->setChecked(false);
    ui->cmbCount->setCurrentIndex(0);
    on_CountSelect();
    connect(ui->cmbCount, SIGNAL(currentIndexChanged(int)),this, SLOT(on_CountSelect()));

    ui->spinCount->setValue(60);
    ui->spinAlertSize->setValue(100);

}

/******************************************************************/

QStringList CountFilesWidget::validate()
{
    QStringList errors;
    if(ui->lnEditFolder->text().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a folder name"));
    }
    if(ui->cmbFileName->currentText().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a file name mask"));
    }
    return errors;
}

/******************************************************************/

QString CountFilesWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::CountFiles);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::CountFiles);
    case Macro::Object : return ui->lnEditFolder->text();
    case Macro::Path : return ui->cmbFileName->currentText();
    default: return QString();
    }
}

/*****************************************************************/

void CountFilesWidget::on_CountSelect()
{
    TCountFiles::CountCondition condition = (TCountFiles::CountCondition)ui->cmbCount->currentIndex();
    switch (condition) {
    case TCountFiles::AllFiles :
    case TCountFiles::SubfolderOnly :
        ui->spinCount->setHidden(true);
        ui->lblBytesMin->setHidden(true);
        break;
    case TCountFiles::OlderThan :
    case TCountFiles::NewerThan :
        ui->spinCount->setHidden(false);
        ui->lblBytesMin->setHidden(false);
        ui->lblBytesMin->setText(QString("min"));
        break;
    case TCountFiles::BiggerThan :
    case TCountFiles::SmallerThan :
        ui->spinCount->setHidden(false);
        ui->lblBytesMin->setHidden(false);
        ui->lblBytesMin->setText(QString("bytes"));
        break;
    }
}

/******************************************************************/

void CountFilesWidget::on_btnEditFolder_clicked()
{
    QString fileName = QFileDialog::getExistingDirectory(this,tr("Folder"),ui->lnEditFolder->text());
    if (!fileName.isEmpty()) {
        ui->lnEditFolder->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO

