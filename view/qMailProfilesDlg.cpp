#include "qMailProfilesDlg.h"
#include "ui_qMailProfilesDlg.h"
#include "gData.h"
#include <QtWidgets>

namespace SDPO {

/*****************************************************************/

MailProfilesDlg::MailProfilesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MailProfilesDlg)
{
    ui->setupUi(this);
}

/*****************************************************************/

MailProfilesDlg::~MailProfilesDlg()
{
    delete ui;
}

/*****************************************************************/

void MailProfilesDlg::currentChanged(int idx)
{
    if (idx < 0) {
        idx = 0;
    }
    if (idx >= GData::mailProfiles.count()) {
        idx = GData::mailProfiles.count()-1;
    }
    GMailProfile profile = GData::mailProfiles.at(idx);
    ui->cmbEmailBody->setCurrentText(profile.type);
    ui->cmbCharset->setCurrentText(profile.charset);
    ui->emailEdit->clear();
    foreach(const QString &line, profile.body) {
        ui->emailEdit->append(line);
    }
}

/*****************************************************************/

void MailProfilesDlg::on_btnNew_clicked()
{
    bool ok;
    QString newName = QInputDialog::getText(this, tr("New mail template"),tr("Template name"), QLineEdit::Normal, QString(), &ok);
    if (!ok) {
        return;
    }
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        if(profile.name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Mail profiles"),
                             QString("Mail template '%1' already exists").arg(newName));
        return;
    }
    GMailProfile newProfile;
    newProfile.name = newName;
    newProfile.type = "Text";
    newProfile.charset = QString();
    newProfile.body = QStringList();
    GData::mailProfiles.append(newProfile);
    ui->listProfiles->addItem(newName);
    ui->listProfiles->setCurrentRow(GData::mailProfiles.count()-1);
}

/*****************************************************************/

void MailProfilesDlg::on_btnCopy_clicked()
{
    int idx = ui->listProfiles->currentRow();
    GMailProfile profile = GData::mailProfiles.at(idx);
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Copy mail template"),
                                            tr("New template's name"),
                                            QLineEdit::Normal,
                                            QString("Copy of %1").arg(profile.name), &ok);
    if (!ok) {
        return;
    }
    foreach (const GMailProfile &tmp, GData::mailProfiles) {
        if(tmp.name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Mail profiles"),
                             QString("Mail template '%1' already exists").arg(newName));
        return;
    }
    GMailProfile newProfile;
    newProfile.name = newName;
    newProfile.type = profile.type;
    newProfile.charset = profile.charset;
    newProfile.body = profile.body;
    GData::mailProfiles.append(newProfile);
    ui->listProfiles->addItem(newName);
    ui->listProfiles->setCurrentRow(GData::mailProfiles.count()-1);
}

/*****************************************************************/

void MailProfilesDlg::on_btnRename_clicked()
{
    int idx = ui->listProfiles->currentRow();
    GMailProfile profile = GData::mailProfiles.at(idx);
    bool ok;
    QString newName = QInputDialog::getText(this, tr("Rename mail template"),
                                            tr("Rename to"),
                                            QLineEdit::Normal,
                                            profile.name, &ok);
    if (!ok) {
        return; // Cancel pressed
    }
    for (int i=0; i < GData::mailProfiles.count(); i++) {
        if (i == idx) {
            continue;
        }
        if(GData::mailProfiles.at(i).name == newName) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        QMessageBox::warning(this, tr("Mail profiles"),
                             QString("Mail template '%1' already exists").arg(newName));
        return;
    }
    GMailProfile newProfile;
    newProfile.name = newName;
    newProfile.type = profile.type;
    newProfile.charset = profile.charset;
    newProfile.body = profile.body;
    GData::mailProfiles.replace(idx,newProfile);
    ui->listProfiles->currentItem()->setText(newName);
    ui->listProfiles->setCurrentRow(idx);
}

/*****************************************************************/

void MailProfilesDlg::on_btnDelete_clicked()
{
    int idx = ui->listProfiles->currentRow();
    GData::mailProfiles.removeAt(idx);
    QListWidgetItem *item = ui->listProfiles->takeItem(idx);
    delete item;
    if (idx >= GData::mailProfiles.count()) {
        idx = GData::mailProfiles.count() - 1;
    }
    ui->listProfiles->setCurrentRow(idx);
}

/*****************************************************************/

void MailProfilesDlg::on_cmbEmailBody_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    int idx = ui->listProfiles->currentRow();
    GMailProfile profile = GData::mailProfiles.at(idx);
    GMailProfile newProfile;
    newProfile.name = profile.name;
    newProfile.type = ui->cmbEmailBody->currentText();
    newProfile.charset = profile.charset;
    newProfile.body = profile.body;
    GData::mailProfiles.replace(idx,newProfile);
}

/*****************************************************************/

void MailProfilesDlg::on_cmbCharset_currentTextChanged(const QString &charset)
{
    int idx = ui->listProfiles->currentRow();
    if (idx<0) idx=0;
    GMailProfile profile = GData::mailProfiles.at(idx);
    GMailProfile newProfile;
    newProfile.name = profile.name;
    newProfile.type = profile.type;
    newProfile.charset = charset;
    newProfile.body = profile.body;
    GData::mailProfiles.replace(idx,newProfile);
}

/*****************************************************************/

void MailProfilesDlg::on_emailEdit_textChanged()
{
    int idx = ui->listProfiles->currentRow();
    if (idx<0) idx=0;
    GMailProfile profile = GData::mailProfiles.at(idx);
    GMailProfile newProfile;
    newProfile.name = profile.name;
    newProfile.type = profile.type;
    newProfile.charset = profile.charset;
    newProfile.body = ui->emailEdit->toPlainText().split("\n");
    GData::mailProfiles.replace(idx,newProfile);
}

/*****************************************************************/

void MailProfilesDlg::init(int row)
{
    ui->listProfiles->clear();
    foreach (const GMailProfile &profile, GData::mailProfiles) {
        ui->listProfiles->addItem(profile.name);
    }
    connect(ui->listProfiles,SIGNAL(currentRowChanged(int)),this,SLOT(currentChanged(int)));
    ui->listProfiles->setCurrentRow(row);
}

/*****************************************************************/

int MailProfilesDlg::getSelected() const
{
    return ui->listProfiles->currentRow();
}

/*****************************************************************/

} // namespace SDPO





