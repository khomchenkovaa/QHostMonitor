#include "qFileContentsWidget.h"
#include "ui_qFileContentsWidget.h"
#include "method/tFileContents.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

FileContentsWidget::FileContentsWidget(QWidget *parent) :
    TestWidget(parent),
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

void FileContentsWidget::init(TTestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::FileContents) ) {
        reset();
        return;
    }
    TFileContents* test = qobject_cast<TFileContents*>(item);
    ui->lineEditFile->setText(test->getFile());
    ui->lineCrcEdit->setText(test->getCrc());
    ui->chkRecalculateCrc->setChecked(test->isRecalculateCrc());
}

/*****************************************************************/

TTestMethod *FileContentsWidget::save(TTestMethod *item)
{
    TFileContents* test;
    if (item && (item->getTMethodID() == TMethodID::FileContents)) {
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
    TMethod method = TMethod::tMethodList.at((int)TMethodID::FileContents);
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
    return errors;
}

/******************************************************************/

QString FileContentsWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TEnums::mvFromString(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::FileContents);
    case Macro::MethodName :
    case Macro::TestMethod : return TMethod::toName(TMethodID::FileContents);
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

