#include "qPalettesWin.h"
#include "ui_qPalettesWin.h"
#include "QtWidgets"

namespace SDPO {

/******************************************************************/

PalettesWin::PalettesWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PalettesWin)
{
    ui->setupUi(this);
    m_model = new PalettesTreeModel(this);
    ui->trvReport->setModel(m_model);
}

/******************************************************************/

PalettesWin::~PalettesWin()
{
    delete ui;
    delete m_model;
}

/******************************************************************/

void PalettesWin::currentChanged()
{
    int idx = ui->listProfiles->currentRow();
    if (idx >= GData::colorProfiles.count()) {
        idx = GData::colorProfiles.count()-1;
    }
    GColorProfile profile = GData::colorProfiles.at(idx);
    m_model->setProfile(profile);
    QString style = QString("color: %1; background-color: %2; font: 8pt \"DejaVu Sans\";").arg(profile.htmlText.at(0).name(),profile.htmlText.at(1).name());
    ui->trvReport->setStyleSheet(style);
    ui->lblHtmlText->setStyleSheet(style);
    ui->lblHMReports->setStyleSheet(style);
    ui->lblLinks->setStyleSheet(QString("color: %1; background-color: %2").arg(profile.links.at(0).name(),profile.links.at(1).name()));
    ui->lblLinksVisited->setStyleSheet(QString("color: %1; background-color: %2").arg(profile.linkVisited.at(0).name(),profile.linkVisited.at(1).name()));
    ui->lblLinksActive->setStyleSheet(QString("color: %1; background-color: %2").arg(profile.linkActive.at(0).name(),profile.linkActive.at(1).name()));
    // ui->trvReport->repaint();
}

/******************************************************************/

void PalettesWin::on_btnNew_clicked()
{
    bool ok;
    QString newName = QInputDialog::getText(this, tr("New palette"),tr("Palette name"), QLineEdit::Normal, QString(), &ok);
    if (!ok) {
        return;
    }
    foreach (const GColorProfile &profile, GData::colorProfiles) {
        if(profile.name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Color profiles"),
                             QString("Palette '%1' already exists").arg(newName));
        return;
    }
    GColorProfile newProfile;
    newProfile.name = newName;
    newProfile.htmlText << QColor("#000000") << QColor("#ffffff");
    newProfile.header << QColor("#ffffff") << QColor("#0000ff");
    newProfile.folder << QColor("#000000") << QColor("#00ff00");
    newProfile.testNotTested << QColor("#000000") << QColor("#ffffff");
    newProfile.testOk << QColor("#000000") << QColor("#ffffff");
    newProfile.testNormal << QColor("#ffffff") << QColor("#000000");
    newProfile.testWarning << QColor("#ffffff") << QColor("#000000");
    newProfile.testBad << QColor("#ffffff") << QColor("#ff0000");
    newProfile.testAcknowledged << QColor("#ffffff") << QColor("#9b0000");
    newProfile.testUnknown << QColor("#ff8040") << QColor("#ffffff");
    newProfile.message << QColor("#000000") << QColor("#ffffff");
    newProfile.testChecking << QColor("#000000") << QColor("#ffffff");
    newProfile.testDisabled << QColor("#000000") << QColor("#c0c0c0");
    newProfile.testWaitForMaster << QColor("#800040") << QColor("#e4ffff");
    newProfile.testOutOfSchedule << QColor("#800040") << QColor("#e4ffff");
    newProfile.links << QColor("#0000ff") << QColor("#ffffff");
    newProfile.linkVisited << QColor("#0000ff") << QColor("#ffffff");
    newProfile.linkActive << QColor("#0000ff") << QColor("#ffffff");
    GData::colorProfiles.append(newProfile);
    ui->listProfiles->addItem(newName);
    ui->listProfiles->setCurrentRow(GData::colorProfiles.count()-1);
}

/******************************************************************/

void PalettesWin::on_btnCopy_clicked()
{
    int idx = ui->listProfiles->currentRow();
    GColorProfile profile = GData::colorProfiles.at(idx);
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Copy palette"),
                                            tr("New palette's name"),
                                            QLineEdit::Normal,
                                            QString("Copy of %1").arg(profile.name), &ok);
    if (!ok) {
        return;
    }
    foreach (const GColorProfile &tmp, GData::colorProfiles) {
        if(tmp.name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Color profiles"),
                             QString("Palette '%1' already exists").arg(newName));
        return;
    }
    GColorProfile newProfile;
    newProfile.name = newName;
    newProfile.htmlText = profile.htmlText;
    newProfile.header = profile.header;
    newProfile.folder = profile.folder;
    newProfile.testNotTested  = profile.testNotTested;
    newProfile.testOk = profile.testOk;
    newProfile.testNormal = profile.testNormal;
    newProfile.testWarning = profile.testWarning;
    newProfile.testBad = profile.testBad;
    newProfile.testAcknowledged = profile.testAcknowledged;
    newProfile.testUnknown  = profile.testUnknown;
    newProfile.message  = profile.message;
    newProfile.testChecking  = profile.testChecking;
    newProfile.testDisabled  = profile.testDisabled;
    newProfile.testWaitForMaster  = profile.testWaitForMaster;
    newProfile.testOutOfSchedule  = profile.testOutOfSchedule;
    newProfile.links  = profile.links;
    newProfile.linkVisited  = profile.linkVisited;
    newProfile.linkActive  = profile.linkActive;
    GData::colorProfiles.append(newProfile);
    ui->listProfiles->addItem(newName);
    ui->listProfiles->setCurrentRow(GData::colorProfiles.count()-1);
}

/******************************************************************/

void PalettesWin::on_btnRename_clicked()
{
    int idx = ui->listProfiles->currentRow();
    GColorProfile profile = GData::colorProfiles.at(idx);
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Rename palette"),
                                            tr("Rename to"),
                                            QLineEdit::Normal,
                                            profile.name, &ok);
    if (!ok) {
        return;
    }
    for (int i=0; i < GData::colorProfiles.count(); i++) {
        if (i == idx) {
            continue;
        }
        if(GData::colorProfiles.at(i).name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Rename palette"),
                             QString("Palette '%1' already exists").arg(newName));
        return;
    }
    GColorProfile newProfile;
    newProfile.name = newName;
    newProfile.htmlText = profile.htmlText;
    newProfile.header = profile.header;
    newProfile.folder = profile.folder;
    newProfile.testNotTested  = profile.testNotTested;
    newProfile.testOk = profile.testOk;
    newProfile.testNormal = profile.testNormal;
    newProfile.testWarning = profile.testWarning;
    newProfile.testBad = profile.testBad;
    newProfile.testAcknowledged = profile.testAcknowledged;
    newProfile.testUnknown  = profile.testUnknown;
    newProfile.message  = profile.message;
    newProfile.testChecking  = profile.testChecking;
    newProfile.testDisabled  = profile.testDisabled;
    newProfile.testWaitForMaster  = profile.testWaitForMaster;
    newProfile.testOutOfSchedule  = profile.testOutOfSchedule;
    newProfile.links  = profile.links;
    newProfile.linkVisited  = profile.linkVisited;
    newProfile.linkActive  = profile.linkActive;
    GData::colorProfiles.replace(idx,newProfile);
    ui->listProfiles->currentItem()->setText(newName);
    ui->listProfiles->setCurrentRow(idx);
}

/******************************************************************/

void PalettesWin::on_btnDelete_clicked()
{
    int idx = ui->listProfiles->currentRow();
    GColorProfile profile = GData::colorProfiles.at(idx);
    if (idx == 0) { // default
        QMessageBox::warning(this, tr("Color profiles"),
                             QString("You cannot delete '%1' color scheme").arg(profile.name));
        return;
    }
    int ret = QMessageBox::question(this,tr("Confirm"),
                  QString("Are you sure you want to delete palette '%1'?").arg(profile.name),
                  QMessageBox::Yes | QMessageBox::No,
                  QMessageBox::Yes);
    if (ret == QMessageBox::No) {
        return;
    }
    GData::colorProfiles.removeAt(idx);
    QListWidgetItem *item = ui->listProfiles->takeItem(idx);
    delete item;
    if (idx >= GData::colorProfiles.count()) {
        idx = GData::colorProfiles.count() - 1;
    }
    ui->listProfiles->setCurrentRow(idx);
}

/******************************************************************/

void PalettesWin::on_trvReport_clicked(const QModelIndex &index)
{
    changeColor(index.row(), 0);
}

/******************************************************************/

void PalettesWin::on_trvReport_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->trvReport->indexAt(pos);
    changeColor(index.row(), 1);
}

/******************************************************************/

void PalettesWin::init(const QString name)
{
    int idx = 0;
    ui->listProfiles->clear();
    for (int i=0; i< GData::colorProfiles.count(); i++) {
        ui->listProfiles->addItem(GData::colorProfiles.at(i).name);
        if (name == GData::colorProfiles.at(i).name) {
            idx = i;
        }
    }
    connect(ui->listProfiles,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(currentChanged()));
    ui->listProfiles->setCurrentRow(idx);
    ui->lblHMReports->installEventFilter(this);
    ui->lblHtmlText->installEventFilter(this);
    ui->lblLinks->installEventFilter(this);
    ui->lblLinksVisited->installEventFilter(this);
    ui->lblLinksActive->installEventFilter(this);
}

/******************************************************************/

QString PalettesWin::getSelected() const
{
    int idx = ui->listProfiles->currentRow();
    return GData::colorProfiles.at(idx).name;
}

/******************************************************************/

void PalettesWin::changeColor(const int row, const int backgroundIdx)
{
    int idx = ui->listProfiles->currentRow();
    if (idx >= GData::colorProfiles.count()) {
        return;
    }
    QColor initial = m_model->getColor(row, backgroundIdx);
    QColor color = 	QColorDialog::getColor(initial, this, tr("Color"));
    if (!color.isValid()) {
        return;
    }
    GColorProfile profile = m_model->setColor(row, backgroundIdx, color);
    GData::colorProfiles.replace(idx,profile);
}

/******************************************************************/

bool PalettesWin::mouseEvent(const int row, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
         QMouseEvent* e = dynamic_cast<QMouseEvent*>(event);
         if (e->button() == Qt::LeftButton) {
             changeColor(row, 0);
             currentChanged();
             return true;
         } else if (e->button() == Qt::RightButton) {
             changeColor(row, 1);
             currentChanged();
             return true;
         }
    }
    return false;
}

/******************************************************************/

bool PalettesWin::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->lblHMReports || watched == ui->lblHtmlText) {
        return mouseEvent(14, event);
    } else if (watched == ui->lblLinks) {
        return mouseEvent(15, event);
    } else if (watched == ui->lblLinksVisited) {
        return mouseEvent(16, event);
    } else if (watched == ui->lblLinksActive) {
        return mouseEvent(17, event);
    }
    return QDialog::eventFilter(watched, event);
}

/******************************************************************/
// PalettesTreeModel class


} // namespace SDPO {

