#include "qFileContentsWidget.h"
#include "ui_qFileContentsWidget.h"
#include "method/tFileContents.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

FileContentsWidget::FileContentsWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::FileContentsWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

FileContentsWidget::~FileContentsWidget()
{
    delete ui;
}

/******************************************************************/

void FileContentsWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::FileCRC) ) {
        reset();
        return;
    }
    TFileContents* test = qobject_cast<TFileContents*>(item);
    ui->lineEditFile->setText(test->getFile());
    ui->lineCrcEdit->setText(test->getCrc());
    ui->chkRecalculateCrc->setChecked(test->isRecalculateCrc());
}

/*****************************************************************/

TestMethod *FileContentsWidget::save(TestMethod *item)
{
    TFileContents* test;
    if (item && (item->getTMethodID() == TMethodID::FileCRC)) {
        test = qobject_cast<TFileContents*>(item);
    } else {
        test = new TFileContents();
    }
    test->setFile(ui->lineEditFile->text());
    test->setCrc(ui->lineCrcEdit->text());
    test->setRecalculateCrc(ui->chkRecalculateCrc->isChecked());
    return test;
}

/******************************************************************/

void FileContentsWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::FileCRC);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->lineEditFile->clear();
    ui->lineCrcEdit->clear();
    ui->chkRecalculateCrc->setChecked(false);
}

/******************************************************************/

QStringList FileContentsWidget::validate()
{
    QStringList errors;
    if(ui->lineEditFile->text().trimmed().isEmpty()) {
        errors.append(tr("Please, specify a file name"));
    }
    if(ui->lineCrcEdit->text().trimmed().isEmpty()) {
        errors.append(tr("File CRC not specified \n To retrive CRC value click the \"Calculate CRC\" button"));
    }
    return errors;
}

/******************************************************************/

QString FileContentsWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::FileCRC);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::FileCRC);
    case Macro::Host : return "localhost";
    case Macro::Path : return ui->lineEditFile->text();
    case Macro::Object : {
        QFileInfo fInfo(ui->lineEditFile->text());
        return fInfo.baseName();
    }

    default: return QString();
    }
}

/******************************************************************/

void FileContentsWidget::on_btnEditFile_clicked()
{
   QString dirName = QFileDialog::getOpenFileName(this,tr("Select Directory"),ui->lineEditFile->text());
   if (!dirName.isEmpty()) {
       ui->lineEditFile->setText(dirName);
   }
}

/******************************************************************/

} // namespace SDPO

