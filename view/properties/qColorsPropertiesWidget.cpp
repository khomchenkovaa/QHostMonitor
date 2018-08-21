#include "qColorsPropertiesWidget.h"
#include "ui_qColorsPropertiesWidget.h"
#include "qPalettesWin.h"
#include "tFolder.h"
#include "tView.h"
#include "tRoot.h"

namespace SDPO {

/******************************************************************/

ColorsPropertiesWidget::ColorsPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorsPropertiesWidget)
{
    ui->setupUi(this);
    m_model = new PalettesTreeModel(this);
    ui->trvColors->setModel(m_model);
}

/******************************************************************/

ColorsPropertiesWidget::~ColorsPropertiesWidget()
{
    delete ui;
    delete m_model;
}

/******************************************************************/

void ColorsPropertiesWidget::init(TNode *node)
{
    if (!node) {
        reset();
        return;
    }
    if (node->getType() != TNode::FOLDER && node->getType() != TNode::VIEW) {
        reset();
        return;
    }
    if (node->getType() == TNode::FOLDER) {
        ui->rbUseOwnColorScheme->setText(tr("Use folder's own color settings"));
    } else if (node->getType() == TNode::VIEW){
        ui->rbUseOwnColorScheme->setText(tr("Use views's own color settings"));
    }
    if (node->isUseOwnColorSettings()) {
        ui->rbUseOwnColorScheme->setChecked(true);
    } else {
        ui->rbUseInheritableColor->setChecked(true);
    }
    if (node->isRootFolder()) {
        if (node->getName() == ROOT_VIEW_NAME) {
            ui->rbUseInheritableColor->setText(tr("Use common settings (Options dialog)"));
        } else {
            ui->rbUseInheritableColor->setText(tr("Apply user specific settings"));
        }
    } else {
        ui->rbUseInheritableColor->setText(tr("Use inheritable settings from parent"));
    }
    ui->editColorScheme->setText(node->getColorScheme());
    ui->chkCheckingColorStatus->setChecked(node->isCheckingColorStatus());
}

/******************************************************************/

void ColorsPropertiesWidget::save(TNode *node)
{
    if (!node) {
        return;
    }
    node->setUseOwnColorSettings(ui->rbUseOwnColorScheme->isChecked());
    node->setColorScheme(ui->editColorScheme->text());
    node->setCheckingColorStatus(ui->chkCheckingColorStatus->isChecked());
}

/******************************************************************/

void ColorsPropertiesWidget::reset()
{
    ui->rbUseOwnColorScheme->setChecked(false);
}

/******************************************************************/

void ColorsPropertiesWidget::on_btnSelectColorScheme_clicked()
{
    PalettesWin dlg;
    dlg.init(ui->editColorScheme->text());
    if (dlg.exec() == QDialog::Accepted) {
        ui->editColorScheme->setText(dlg.getSelected());
    }
}

/******************************************************************/

void ColorsPropertiesWidget::on_editColorScheme_textChanged(const QString &colorScheme)
{
    if (colorScheme.isEmpty()) return;
    GColorProfile profile = GData::getColorProfile(colorScheme);
    m_model->setProfile(profile);
    QString style = QString("color: %1; background-color: %2; font: 8pt \"DejaVu Sans\";").arg(profile.htmlText.at(0).name(),profile.htmlText.at(1).name());
    ui->trvColors->setStyleSheet(style);
}

/******************************************************************/

void ColorsPropertiesWidget::on_rbUseOwnColorScheme_toggled(bool checked)
{
    ui->editColorScheme->setEnabled(checked);
    ui->btnSelectColorScheme->setEnabled(checked);
    ui->trvColors->setEnabled(checked);
    ui->chkCheckingColorStatus->setEnabled(checked);
}

/******************************************************************/

} // namespace SDPO



