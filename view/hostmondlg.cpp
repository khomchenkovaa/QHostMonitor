#include "hostmondlg.h"

#include "testeditwidget.h"
#include "testschedulewidget.h"
#include "qAlertsEditWidget.h"
#include "qLogReportsEditWidget.h"
#include "mastereditwidget.h"
#include "dependencieseditwidget.h"
#include "optionalprocessingwidget.h"
#include "qLinksList.h"
#include "settings.h"
#include "tTest.h"
#include "tRoot.h"
#include "hmListService.h"

#include <QtWidgets>
#include <QDebug>

namespace SDPO {

/******************************************************************/

HostMonDlg::HostMonDlg(HMListService *hml, QWidget *parent)
    : QDialog(parent)
    , m_HML(hml)
    , m_Item(nullptr)
    , changed(false)
    , uiTestEdit(new TestEditWidget(this))
    , uiSchedule(new TestScheduleWidget(this))
    , uiAlerts(new AlertsEditWidget(this))
    , uiLogsReports(new LogReportsEditWidget(this))
    , uiMaster(new MasterEditWidget(this))
    , uiDependencies(new DependenciesEditWidget(this))
    , uiOptional(new OptionalProcessingWidget(this))
    , cmbEnabled(new QComboBox(this))
    , textWarnMemo(new QPlainTextEdit(this))
    , btnLinks(new QPushButton(this))
{
    setupUI();
}

/******************************************************************/

HostMonDlg::~HostMonDlg()
{
}

/******************************************************************/

void HostMonDlg::reset()
{
    uiTestEdit->reset();
    uiSchedule->reset();
    uiAlerts->reset();
    uiLogsReports->reset();
    uiMaster->reset(m_HML->rootFolder());
    uiDependencies->reset();
    uiOptional->reset();

    cmbEnabled->setCurrentIndex(0);
    textWarnMemo->clear();
    btnLinks->setVisible(false);
}

/******************************************************************/

void HostMonDlg::hideDependencies(bool hide)
{
    int hRight = uiDependencies->doHide(hide);
    int hLeft = uiMaster->doHide(hide);

    int delta = qMax(hRight, hLeft);
    if (delta) {
        QSize newSize = size();
        int h = newSize.height();
        newSize.setHeight(h - delta);
        resize(newSize);
    }
}

/******************************************************************/

void HostMonDlg::onPrevClicked()
{
    qDebug() << "TODO: Hostmondlg -> onPrevClicked";
}

/******************************************************************/

void HostMonDlg::onNextClicked()
{
    qDebug() << "TODO: Hostmondlg -> onNextClicked";
}

/******************************************************************/

bool HostMonDlg::saveTest()
{
    bool isNew = (m_Item == nullptr);
    TTest *test = uiTestEdit->save(m_HML, m_Item);
    if (test == nullptr) return false;
    m_Item = test;

    uiSchedule->save(m_Item);
    uiAlerts->save(m_Item);
    uiLogsReports->save(m_Item);
    uiMaster->save(m_Item);
    uiDependencies->save(m_Item);
    uiOptional->save(m_Item);

    m_Item->setEnabled(cmbEnabled->currentIndex() == 0);

    if (isNew) {
        m_HML->addNode(m_HML->currentFolder(),m_Item);
        // emit testAdded(m_Item);
    } else {
        emit testChanged(m_Item);
    }
    return true;
}

/******************************************************************/

void HostMonDlg::init(TTest *item)
{
    m_Item = item;
    if(!m_Item) {
        init(TMethodID::Ping);
        return;
    }

    uiTestEdit->init(item);
    uiAlerts->init(m_Item);
    uiLogsReports->init(m_Item);
    uiMaster->init(m_Item);
    uiDependencies->init(m_Item);
    uiOptional->init(m_Item);

    cmbEnabled->setCurrentIndex(m_Item->isEnabled()?0:1);
    btnLinks->setVisible(m_Item->linkCount());
}

/******************************************************************/

void HostMonDlg::init(TMethodID method, QVariant data)
{
    m_Item = nullptr;
    uiTestEdit->setData(data);
    reset();
    uiTestEdit->setMethodID(method);
}

/******************************************************************/

void HostMonDlg::onLinksClicked()
{
    if (!m_Item) return;
    if (m_Item->linkCount() == 0) return;

    LinksList linksDlg(m_Item);
    linksDlg.setReadOnly();
    linksDlg.exec();
}

/******************************************************************/

void HostMonDlg::onOkClicked()
{
    if (saveTest()) {
        close();
    }
}

/******************************************************************/

void HostMonDlg::onAddClicked()
{
    qDebug() << "TODO: Hostmondlg -> onAddClicked";
}

/******************************************************************/

void HostMonDlg::onHelpClicked()
{
    qDebug() << "TODO: Hostmondlg -> onHelpClicked";
}

/******************************************************************/

void HostMonDlg::setupUI()
{
    if (objectName().isEmpty()) {
        setObjectName(QStringLiteral("HostMonDlg"));
    }
    resize(921, 693);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy);

    setFont(QFont("DejaVu Sans", 8));

    setWindowIcon(QIcon(":/img/hostMonitor.png"));
    setWindowTitle(tr("Test properties"));
    setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

    cmbEnabled->insertItems(0, QStringList() << tr("Enabled") << tr("Disabled"));
    cmbEnabled->setWhatsThis(tr("This option enables or disables test execution."));

    textWarnMemo->setMaximumSize(QSize(16777215, 32));
    QPalette palette;
    QBrush brush(QColor(255, 255, 225, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
    QBrush brush1(QColor(239, 235, 231, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
    textWarnMemo->setPalette(palette);
    textWarnMemo->setFrameShape(QFrame::NoFrame);

    btnLinks->setMaximumSize(QSize(27, 27));
    btnLinks->setIcon(QIcon(":/img/test/links.bmp"));

    QPushButton *btnPrev = new QPushButton(this);
    btnPrev->setIcon(QIcon(":/img/test/previous.png"));

    QPushButton *btnNext = new QPushButton(this);
    btnNext->setIcon(QIcon(":/img/test/next.png"));

    QPushButton *btnOk = new QPushButton(tr("Ok"), this);
    QPushButton *btnAdd = new QPushButton(tr("&New test"), this);
    QPushButton *btnCancel = new QPushButton(tr("Cancel"), this);
    QPushButton *btnHelp = new QPushButton(tr("&Help"), this);

    QFrame *leftFrame = new QFrame(this);
    leftFrame->setFrameShape(QFrame::Panel);
    leftFrame->setFrameShadow(QFrame::Sunken);
    QHBoxLayout *leftLayout = new QHBoxLayout(leftFrame);
    leftLayout->setSpacing(6);
    leftLayout->addWidget(new QLabel(tr("Test is"), this));
    leftLayout->addWidget(cmbEnabled);
    leftLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    leftLayout->addWidget(textWarnMemo);
    leftLayout->addWidget(btnLinks);
    leftLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    leftLayout->addWidget(btnPrev);
    leftLayout->addWidget(btnNext);

    QFrame *rightFrame = new QFrame(this);
    rightFrame->setFrameShape(QFrame::Panel);
    rightFrame->setFrameShadow(QFrame::Sunken);
    QHBoxLayout *rightLayout = new QHBoxLayout(rightFrame);
    rightLayout->setSpacing(6);
    rightLayout->addWidget(btnOk);
    rightLayout->addWidget(btnAdd);
    rightLayout->addWidget(btnCancel);
    rightLayout->addWidget(btnHelp);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(uiTestEdit, 0, 0, 3, 1);
    mainLayout->addWidget(uiSchedule, 0, 1);
    mainLayout->addWidget(uiAlerts, 1, 1);
    mainLayout->addWidget(uiLogsReports, 2, 1);
    mainLayout->addWidget(uiMaster, 3, 0);
    mainLayout->addWidget(uiDependencies, 3, 1);
    mainLayout->addWidget(uiOptional, 4, 0, 1, 2);
    mainLayout->addWidget(leftFrame, 5, 0);
    mainLayout->addWidget(rightFrame, 5, 1);

    connect(uiMaster, &MasterEditWidget::hideMe,
            this, &HostMonDlg::hideDependencies);
    connect(uiDependencies, &DependenciesEditWidget::hideMe,
            this, &HostMonDlg::hideDependencies);
    connect(btnLinks, &QPushButton::clicked,
            this, &HostMonDlg::onLinksClicked);
    connect(btnOk, &QPushButton::clicked,
            this, &HostMonDlg::onOkClicked);
    connect(btnAdd, &QPushButton::clicked,
            this, &HostMonDlg::onAddClicked);
    connect(btnCancel, &QPushButton::clicked,
            this, &HostMonDlg::close);
    connect(btnHelp, &QPushButton::clicked,
            this, &HostMonDlg::onHelpClicked);

}


/******************************************************************/

} // namespace SDPO
