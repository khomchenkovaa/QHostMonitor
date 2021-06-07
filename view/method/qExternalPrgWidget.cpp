#include "qExternalPrgWidget.h"
#include "ui_qExternalPrgWidget.h"
#include "method/tExternalPrg.h"
#include <QFileDialog>

namespace SDPO {

/******************************************************************/

ExternalPrgWidget::ExternalPrgWidget(QWidget *parent) :
    TestWidget(parent),
    ui(new Ui::ExternalPrgWidget)
{
    ui->setupUi(this);
    ui->cmbWinMode->setDisabled(true);
    connect(ui->editExternalPrg, SIGNAL(textEdited(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

ExternalPrgWidget::~ExternalPrgWidget()
{
    delete ui;
}

/******************************************************************/

void ExternalPrgWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Externalprg) ) {
        reset();
        return;
    }
    TExternalPrg *t = qobject_cast<TExternalPrg*>(item);
    ui->editExternalPrg->setText(t->getExternalPrg());
    ui->cmbAlertCondition->setCurrentIndex(t->getAlertMode());
    ui->spinAlertValue->setValue(t->getExitCode());
    ui->cmbWinMode->setCurrentIndex(t->getWinMode());
    ui->chkKillApp->setChecked(t->isKillPrg());
    ui->spinWaitTimeout->setValue(t->getKillTimeout());
}

/******************************************************************/

TestMethod *ExternalPrgWidget::save(TestMethod *item)
{
    TExternalPrg *t;
    if (item && (item->getTMethodID() == TMethodID::Externalprg)) {
        t = qobject_cast<TExternalPrg*>(item);
    } else {
        t = new TExternalPrg();
    }
    t->setExternalPrg(ui->editExternalPrg->text());
    t->setAlertMode(ui->cmbAlertCondition->currentIndex());
    t->setExitCode(ui->spinAlertValue->value());
    t->setWinMode(ui->cmbWinMode->currentIndex());
    t->setKillPrg(ui->chkKillApp->isChecked());
    t->setKillTimeout(ui->spinWaitTimeout->value());
    return t;
}

/******************************************************************/

void ExternalPrgWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::Externalprg);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->editExternalPrg->clear();
    ui->cmbAlertCondition->setCurrentIndex(3);
    ui->spinAlertValue->setValue(0);
    ui->cmbWinMode->setCurrentIndex(0);
    ui->chkKillApp->setChecked(false);
    ui->spinWaitTimeout->setValue(60);
}

/******************************************************************/

QStringList ExternalPrgWidget::validate()
{
    QStringList errors;
    if (ui->editExternalPrg->text().trimmed().isEmpty()) {
        errors.append(tr("Please provide command line to execute"));
    }
    return errors;
}

/******************************************************************/

QString ExternalPrgWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Externalprg);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::Externalprg);
    case Macro::Path : return ui->editExternalPrg->text();
    case Macro::Object : return ui->editExternalPrg->text().mid(ui->editExternalPrg->text().lastIndexOf("/"));
    default: return QString();
    }

}

/******************************************************************/

 void ExternalPrgWidget::on_btnExternalPrg_clicked()
{
    QString defFileName = ui->editExternalPrg->text().trimmed();
    if (defFileName.isEmpty()) defFileName = "/usr/lib64/nagios/plugins";
    QString fileName = QFileDialog::getOpenFileName(this,tr("External application"),defFileName);
    if (!fileName.isEmpty()) {
        ui->editExternalPrg->setText(fileName);
    }
}

/******************************************************************/

} // namespace SDPO
