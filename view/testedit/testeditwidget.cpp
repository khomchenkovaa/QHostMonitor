#include "testeditwidget.h"
#include "ui_testeditwidget.h"

#include "sdpoTestMethodWidgets.h"
#include "testmethodselectdlg.h"
#include "gMacroTranslator.h"
#include "tTest.h"
#include "hmListService.h"

#include <QMessageBox>

using namespace SDPO;

/******************************************************************/

TestEditWidget::TestEditWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TestEditWidget)
{
    ui->setupUi(this);
    setupUI();
}

/******************************************************************/

TestEditWidget::~TestEditWidget()
{
    delete ui;
}

/******************************************************************/

void TestEditWidget::reset()
{
    ui->cmbAgent->setCurrentIndex(0);
    ui->cmbTestName->clearEditText();
    ui->ledTestComment->clear();
    ui->cmbTestRelatedURL->clearEditText();

    for (int i=0; i<ui->stwTestMethod->count(); ++i) {
        TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->widget(i));
        if (widget) {
            widget->reset(m_Data);
        }
    }
}

/******************************************************************/

void TestEditWidget::setMethodID(const TMethodID methodID)
{
    ui->cmbTestMethod->setCurrentIndex(static_cast<int>(methodID));
    emit ui->cmbTestMethod->currentIndexChanged(ui->cmbTestMethod->currentIndex());
}

/******************************************************************/

void TestEditWidget::init(TTest *item)
{
    if (item == nullptr) return;

    ui->cmbTestMethod->setCurrentIndex(item->testMethodId());
    ui->cmbTestName->setCurrentText(item->testName());
    ui->ledTestComment->setText(item->getComment());
    ui->cmbTestRelatedURL->setCurrentText(item->getRelatedURL());

    emit ui->cmbTestMethod->currentIndexChanged(ui->cmbTestMethod->currentIndex());

    TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
    if (widget) {
        widget->init(item->method());
        widget->setNamePattern(item->method()->getNamePattern());
        widget->setCommentPattern(item->method()->getCommentPattern());
        refreshNameAndComment();
    }
}

/******************************************************************/

TTest *TestEditWidget::save(HMListService  *hmlService, TTest *item)
{
    TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
    if (!widget) {
        QMessageBox::information(nullptr,"Info", tr("Oops! Not implemented yet"));
        return nullptr;
    }
    QStringList errors = widget->validate();
    if (!errors.isEmpty()) {
        QMessageBox::warning(nullptr,"Warning", errors.at(0));
        return nullptr;
    }

    TestMethod* testMethod = nullptr;
    if (item) {
        testMethod = item->method();
    }
    testMethod = widget->save(testMethod);
    testMethod->setNamePattern(widget->getNamePattern());
    testMethod->setCommentPattern(widget->getCommentPattern());

    QString testName = getTestName().trimmed();
    if (item == nullptr) {
        item = new TTest(hmlService->nextID(), testName);
    }
    item->setMethod(testMethod);
    item->updateSpecificProperties();

    if (!testName.isEmpty())  {
        item->setName(testName);
        ui->cmbTestName->addItem(testName);
    }
    QString taskComment = getTestComment().trimmed();
    if (!taskComment.isEmpty()) item->setComment(taskComment);
    QString relatedUrl = ui->cmbTestRelatedURL->currentText().trimmed();
    if (!relatedUrl.isEmpty()) {
        item->setRelatedURL(relatedUrl);
        ui->cmbTestRelatedURL->addItem(relatedUrl);
    }
    return item;
}

/******************************************************************/

void TestEditWidget::openMethodSelectDialog()
{
    TestMethodSelectDlg dlg;
    dlg.setCurrent(ui->cmbTestMethod->currentIndex());
    if (dlg.exec() == QDialog::Accepted) {
        int idx = dlg.getCurrent();
        ui->cmbTestMethod->setCurrentIndex(idx);
    }
}

/******************************************************************/

void TestEditWidget::refreshNameAndComment()
{
    ui->cmbTestName->setCurrentText(getTestName());
    ui->ledTestComment->setText(getTestComment());
}

/******************************************************************/

void TestEditWidget::setupUI()
{
    if (objectName().isEmpty()) {
        setObjectName(QStringLiteral("TestEditWidget"));
    }
    setFont(QFont("DejaVu Sans", 8));

    setupTestMethodCombo();
    setupTestMethodWidgets();

    // connections
    connect(ui->btnTestMethod, &QToolButton::clicked,
            this, &TestEditWidget::openMethodSelectDialog);
    connect(ui->btnTestMethodLabel, &QPushButton::clicked,
            this, &TestEditWidget::openMethodSelectDialog);
    connect(ui->stwTestMethod, &QStackedWidget::currentChanged,
            this, &TestEditWidget::refreshNameAndComment);
    connect(ui->stwTestMethod, &QStackedWidget::currentChanged,
            ui->cmbTestMethod, &QComboBox::setCurrentIndex);
    connect(ui->cmbTestMethod, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            ui->stwTestMethod, &QStackedWidget::setCurrentIndex);

    ui->cmbTestName->installEventFilter(this);
    ui->ledTestComment->installEventFilter(this);

    for (int i = 0; i < ui->stwTestMethod->count(); ++i) {
        TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->widget(i));
        if (widget) {
            connect(widget, &TestMethodWidget::propertiesChanged,
                    this, &TestEditWidget::refreshNameAndComment);
        }
    }

}

/******************************************************************/

void TestEditWidget::setupTestMethodCombo()
{
    QComboBox *box = ui->cmbTestMethod;
    foreach(const TestMethodMetaInfo &meta, TestMethod::metaInfo) {
        if (meta.id == TMethodID::Unknown) continue;
        box->addItem(QIcon(meta.icon), meta.text, static_cast<int>(meta.id));
    }
    box->setCurrentIndex(0);
}

/******************************************************************/

void TestEditWidget::setupTestMethodWidgets()
{
    QStackedWidget *box = ui->stwTestMethod;
    box->addWidget(new PingWidget);
    box->addWidget(new TcpWidget);
    box->addWidget(new UrlWidget);
    box->addWidget(new DriveSpaceWidget);
    box->addWidget(new FileSizeWidget);
    box->addWidget(new FileExistsWidget);
    box->addWidget(new ExternalPrgWidget);
    box->addWidget(new SshWidget);
    box->addWidget(new FileContentsWidget);
    box->addWidget(new OracleWidget);
    box->addWidget(new UncWidget);
    box->addWidget(new InterbaseWidget);
    box->addWidget(new MsSqlWidget);
    box->addWidget(new MySqlWidget);
    box->addWidget(new PostgreSqlWidget);
    box->addWidget(new SybaseWidget);
    box->addWidget(new ProcessWidget);
    box->addWidget(new ServiceWidget);
    box->addWidget(new SnmpGetWidget);
    box->addWidget(new NtEventLogWidget);
    box->addWidget(new CpuUsageWidget);
    box->addWidget(new CompareFilesWidget);
    box->addWidget(new OdbcQueryWidget);
    box->addWidget(new SmtpTestWidget);
    box->addWidget(new Pop3TestWidget);
    box->addWidget(new ImapTestWidget);
    box->addWidget(new DnsTestWidget);
    box->addWidget(new LdapTestWidget);
    box->addWidget(new TraceTestWidget);
    box->addWidget(new CountFilesWidget);
    box->addWidget(new RasTestWidget);
    box->addWidget(new PerformanceCounterWidget);
    box->addWidget(new ActiveScriptWidget);
    box->addWidget(new UdpTestWidget);
    box->addWidget(new NtpTestWidget);
    box->addWidget(new RadiusWidget);
    box->addWidget(new HttpWidget);
    box->addWidget(new TextLogWidget);
    box->addWidget(new ShellScriptWidget);
    box->addWidget(new TemperatureMonitorWidget);
    box->addWidget(new TrafficMonitorWidget);
    box->addWidget(new SnmpTrapWidget);
    box->addWidget(new WmiWidget);
    box->addWidget(new MailRelayWidget);
    box->addWidget(new DicomWidget);
    box->addWidget(new DominantProcessWidget);
    box->addWidget(new DhcpWidget);
    box->addWidget(new SdpoMonitorWidget);
    box->addWidget(new NagiosPluginWidget);
    box->setCurrentIndex(0);
}

/******************************************************************/

QString TestEditWidget::getTestName() const
{
    TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
    QString nameSource = widget->getNamePattern();
    GMacroTranslator translator(nameSource);
    QStringList nameParams = translator.parse();
    if (nameParams.count()) {
        QVariantMap nameValues = widget->setTemplateVars(nameParams);
        translator.setValues(nameValues);
        return translator.build();
    }
    return nameSource;
}

/******************************************************************/

QString TestEditWidget::getTestComment() const
{
    TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
    QString commentSource = widget->getCommentPattern();
    GMacroTranslator translator(commentSource);
    QStringList commentParams = translator.parse();
    if (commentParams.count()) {
        QVariantMap commentValues = widget->setTemplateVars(commentParams);
        translator.setValues(commentValues);
        return translator.build();
    }
    return commentSource;
}

/******************************************************************/

bool TestEditWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        if (watched == ui->cmbTestName) {
            TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
            QString nameSource = widget->getNamePattern();
            ui->cmbTestName->setCurrentText(nameSource);
            GMacroTranslator translator(nameSource);
            QStringList nameParams = translator.parse();
            if (nameParams.count()) {
                QPalette palette = ui->cmbTestName->palette();
                palette.setColor(QPalette::Base,Qt::yellow);
                ui->cmbTestName->setPalette(palette);
            }
        } else if (watched == ui->ledTestComment) {
            TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
            QString commentSource = widget->getCommentPattern();
            ui->ledTestComment->setText(commentSource);
            GMacroTranslator translator(commentSource);
            QStringList commentParams = translator.parse();
            if (commentParams.count()) {
                QPalette palette = ui->ledTestComment->palette();
                palette.setColor(QPalette::Base,Qt::yellow);
                ui->ledTestComment->setPalette(palette);
            }
        }
    }
    if (event->type() == QEvent::FocusOut) {
        if (watched == ui->cmbTestName) {
            TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
            widget->setNamePattern(ui->cmbTestName->currentText());
            refreshNameAndComment();
            QPalette palette = ui->cmbTestName->palette();
            palette.setColor(QPalette::Base,Qt::white);
            ui->cmbTestName->setPalette(palette);
        } else if (watched == ui->ledTestComment) {
            TestMethodWidget* widget = qobject_cast<TestMethodWidget*>(ui->stwTestMethod->currentWidget());
            widget->setCommentPattern(ui->ledTestComment->text());
            refreshNameAndComment();
            QPalette palette = ui->ledTestComment->palette();
            palette.setColor(QPalette::Base,Qt::white);
            ui->ledTestComment->setPalette(palette);
        }
    }
    return QFrame::eventFilter(watched,event);
}

/******************************************************************/
