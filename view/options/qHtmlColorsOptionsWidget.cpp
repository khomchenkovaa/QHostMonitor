#include "qHtmlColorsOptionsWidget.h"
#include "ui_qHtmlColorsOptionsWidget.h"
#include "qPalettesWin.h"

namespace SDPO {

/******************************************************************/

HtmlColorsOptionsWidget::HtmlColorsOptionsWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::HtmlColorsOptionsWidget)
{
    ui->setupUi(this);
    m_model = new PalettesTreeModel(this);
    ui->trvColors->setModel(m_model);
}

/******************************************************************/

HtmlColorsOptionsWidget::~HtmlColorsOptionsWidget()
{
    delete ui;
    delete m_model;
}

/******************************************************************/

void HtmlColorsOptionsWidget::init(QSettings *s)
{
     ui->editColorScheme->setText(s->value(SKEY_INTERFACE_DefaultLogPaletteID, "Grey").toString());
}

/******************************************************************/

void HtmlColorsOptionsWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_INTERFACE_DefaultLogPaletteID, ui->editColorScheme->text());
}

/******************************************************************/

void HtmlColorsOptionsWidget::on_btnColorScheme_clicked()
{
    PalettesWin dlg;
    dlg.init(ui->editColorScheme->text());
    if (dlg.exec() == QDialog::Accepted) {
        ui->editColorScheme->setText(dlg.getSelected());
    }
}

/******************************************************************/

void HtmlColorsOptionsWidget::on_editColorScheme_textChanged(const QString &colorScheme)
{
    if (colorScheme.isEmpty()) return;
    GColorProfile profile = GData::getColorProfile(colorScheme);
    m_model->setProfile(profile);
    QString style = QString("color: %1; background-color: %2; font: 8pt \"DejaVu Sans\";").arg(profile.htmlText.at(0).name(),profile.htmlText.at(1).name());
    ui->lblTitle->setStyleSheet(style);
    ui->trvColors->setStyleSheet(style);
}

/******************************************************************/

} // namespace SDPO


