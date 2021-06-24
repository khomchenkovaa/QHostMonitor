#include "nagiospluginwidget.h"
#include "ui_nagiospluginwidget.h"

#include "tnagiosplugin.h"
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QProcess>

class QMessageBoxResize: public QMessageBox
  {
  public:
    QMessageBoxResize() {
      setMouseTracking(true);
      setSizeGripEnabled(true);
    }
  private:
    virtual bool event(QEvent *e) {
      bool res = QMessageBox::event(e);
      switch (e->type()) {
      case QEvent::MouseMove:
      case QEvent::MouseButtonPress:
        setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        if (QWidget *textEdit = findChild<QTextEdit *>()) {
          textEdit->setMaximumHeight(QWIDGETSIZE_MAX);
        }
      default: break;
      }
      return res;
    }
  };

using namespace SDPO;

/******************************************************************/

NagiosPluginWidget::NagiosPluginWidget(QWidget *parent) :
    TestMethodWidget(parent),
    ui(new Ui::NagiosPluginWidget)
{
    ui->setupUi(this);
    connect(ui->editNagiosPlugin, SIGNAL(textChanged(QString)), this, SIGNAL(propertiesChanged()));
}

/******************************************************************/

NagiosPluginWidget::~NagiosPluginWidget()
{
    delete ui;
}

/******************************************************************/

void NagiosPluginWidget::init(TestMethod *item)
{
    if (!item || (item->getTMethodID() != TMethodID::Nagios) ) {
        reset();
        return;
    }
    TNagiosPlugin *t = qobject_cast<TNagiosPlugin*>(item);
    ui->editNagiosPlugin->setText(t->getNagiosPlugin());
    ui->editArguments->setText(t->getArguments());
    ui->chkKillApp->setChecked(t->isKillPrg());
    ui->spinWaitTimeout->setValue(t->getKillTimeout());
}

/******************************************************************/

TestMethod *NagiosPluginWidget::save(TestMethod *item)
{
    TNagiosPlugin *t;
    if (item && (item->getTMethodID() == TMethodID::Nagios)) {
        t = qobject_cast<TNagiosPlugin*>(item);
    } else {
        t = new TNagiosPlugin();
    }
    t->setNagiosPlugin(ui->editNagiosPlugin->text());
    t->setArguments(ui->editArguments->text());
    t->setKillPrg(ui->chkKillApp->isChecked());
    t->setKillTimeout(ui->spinWaitTimeout->value());
    return t;
}

/******************************************************************/

void NagiosPluginWidget::reset(QVariant data)
{
    Q_UNUSED(data)
    TestMethodMetaInfo method = TestMethod::metaInfoItem(TMethodID::Nagios);
    setNamePattern(method.namePattern);
    setCommentPattern(method.commentPattern);
    ui->editNagiosPlugin->clear();
    ui->editArguments->clear();
    ui->chkKillApp->setChecked(false);
    ui->spinWaitTimeout->setValue(60);
}

/******************************************************************/

QStringList NagiosPluginWidget::validate()
{
    QStringList errors;
    if (ui->editNagiosPlugin->text().trimmed().isEmpty()) {
        errors.append(tr("Please provide command line to execute"));
    }
    return errors;
}

/******************************************************************/

QString NagiosPluginWidget::getTemplateValue(const QString var) const
{
    Macro::Variable globalVar = TMacro::var(var);
    switch (globalVar) {
    case Macro::MethodID : return QString::number((int)TMethodID::Nagios);
    case Macro::MethodName :
    case Macro::TestMethod : return TestMethod::metaName(TMethodID::Nagios);
    case Macro::Path : return ui->editNagiosPlugin->text();
    case Macro::Object : return ui->editNagiosPlugin->text().mid(ui->editNagiosPlugin->text().lastIndexOf("/"));
    default: return QString();
    }
}

/******************************************************************/

void NagiosPluginWidget::on_btnSelect_clicked()
{
    QString defFileName = ui->editNagiosPlugin->text().trimmed();
    if (defFileName.isEmpty()) defFileName = "/usr/lib/nagios/plugins";
    QString fileName = QFileDialog::getOpenFileName(this,tr("Nagios plugin"),defFileName);
    if (!fileName.isEmpty()) {
        ui->editNagiosPlugin->setText(fileName);
    }
}

/******************************************************************/

void NagiosPluginWidget::on_btnHelp_clicked()
{
    // TODO run nagios plugin with --help argument and display it
    QString command = ui->editNagiosPlugin->text().trimmed();
    if (command.isEmpty()) {
        QMessageBox::warning(this, "Nagios plugin",
                             "Please select a Nagios plugin");
        ui->editNagiosPlugin->setFocus();
        return;
    }
    command.append(" --help");
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start(command);
    if (!process.waitForStarted()) {
        process.close();
        QMessageBox::warning(this, "Nagios plugin",
                             "Cannot start the Nagios plugin");
        ui->editNagiosPlugin->setFocus();
        return;
    }
    if(!process.waitForFinished()) {
        process.close();
        QMessageBox::warning(this, "Nagios plugin",
                             "The Nagios plugin is not finished yet");
        ui->editNagiosPlugin->setFocus();
        return;
    }
    QString output = process.readAll();
    process.close();
//    QInputDialog::getMultiLineText(this, "Nagios plugin", command, output);
//    QMessageBox::about(this, "Nagios plugin", output);
    QMessageBoxResize mbox;
    mbox.setIcon(QMessageBox::Icon::Information);
    mbox.setWindowTitle("Nagios plugin");
    mbox.setText(command);
    mbox.setDetailedText(output);
    mbox.exec();
}

/******************************************************************/
