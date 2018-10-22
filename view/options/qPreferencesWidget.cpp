#include "qPreferencesWidget.h"
#include "ui_qPreferencesWidget.h"

namespace SDPO {

/******************************************************************/

PreferencesWidget::PreferencesWidget(QWidget *parent) :
    OptionsWidget(parent),
    ui(new Ui::PreferencesWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

PreferencesWidget::~PreferencesWidget()
{
    delete ui;
}

/******************************************************************/

void PreferencesWidget::init(QSettings *s)
{
    // Fonts
    ui->cmbPrefWindowsFont->setCurrentFont(s->value(SKEY_PREF_FontName, "DejaVu Sans").toString());
    ui->spinPrefWindowsFontSize->setValue(s->value(SKEY_PREF_FontSize, 8).toInt());
    ui->cmbPrefTerminalFont->setCurrentFont(s->value(SKEY_PREF_TelnetFontName, "Carlito").toString());
    ui->spinPrefTerminalFontSize->setValue(s->value(SKEY_PREF_TelnetFontSize, 12).toInt());

    // Autosave options
    ui->chkPrefAutoSaveOptions->setChecked(s->value(SKEY_PREF_AutoSave, 1).toInt());
    ui->cmbPrefAutoSaveOptions->setCurrentIndex(s->value(SKEY_PREF_AutoSaveMode, 5).toInt());
    ui->chkPrefRecent->setChecked(s->value(SKEY_PREF_KeptAddresses, 1).toInt());
    ui->spinPrefRecent->setValue(s->value(SKEY_PREF_DeepAddresses, 5).toInt());

    // Icon
    ui->chkPrefMinToTray->setChecked(s->value(SKEY_PREF_MinToTray, 1).toInt());
    ui->chkPrefAnimateIcon->setChecked(s->value(SKEY_PREF_AnimateIcon, 1).toInt());
    ui->chkPrefChangeIconDie->setChecked(s->value(SKEY_PREF_ChangeIcon, 1).toInt());
    ui->chkPrefAlwaysTop->setChecked(s->value(SKEY_PREF_StayFormTop, 0).toInt());

    // Save options
    ui->chkPrefStoreStatHML->setChecked(s->value(SKEY_MISC_StoreStatistics, 1).toInt());
    ui->chkPrefStoreRecurencesHML->setChecked(s->value(SKEY_MISC_StoreIterations, 1).toInt());
    ui->chkPrefRememberCurrentFolder->setChecked(s->value(SKEY_INTERFACE_SaveCurrFolder, 1).toInt());
}

/******************************************************************/

void PreferencesWidget::prepareToSave(QSettings *s)
{
    // Fonts
    s->setValue(SKEY_PREF_FontName, ui->cmbPrefWindowsFont->currentFont());
    s->setValue(SKEY_PREF_FontSize, ui->spinPrefWindowsFontSize->value());
    s->setValue(SKEY_PREF_TelnetFontName, ui->cmbPrefTerminalFont->currentFont());
    s->setValue(SKEY_PREF_TelnetFontSize, ui->spinPrefTerminalFontSize->value());

    // Autosave options
    s->setValue(SKEY_PREF_AutoSave, ui->chkPrefAutoSaveOptions->isChecked()?1:0);
    s->setValue(SKEY_PREF_AutoSaveMode, ui->cmbPrefAutoSaveOptions->currentIndex());
    s->setValue(SKEY_PREF_KeptAddresses, ui->chkPrefRecent->isChecked()?1:0);
    s->setValue(SKEY_PREF_DeepAddresses, ui->spinPrefRecent->value());

    // Icon
    s->setValue(SKEY_PREF_MinToTray, ui->chkPrefMinToTray->isChecked()?1:0);
    s->setValue(SKEY_PREF_AnimateIcon, ui->chkPrefAnimateIcon->isChecked()?1:0);
    s->setValue(SKEY_PREF_ChangeIcon, ui->chkPrefChangeIconDie->isChecked()?1:0);
    s->setValue(SKEY_PREF_StayFormTop, ui->chkPrefAlwaysTop->isChecked()?1:0);

    // Save options
    s->setValue(SKEY_MISC_StoreStatistics, ui->chkPrefStoreStatHML->isChecked()?1:0);
    s->setValue(SKEY_MISC_StoreIterations, ui->chkPrefStoreRecurencesHML->isChecked()?1:0);
    s->setValue(SKEY_INTERFACE_SaveCurrFolder, ui->chkPrefRememberCurrentFolder->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
