#include "qPreferencesWidget.h"
#include "ui_qPreferencesWidget.h"

using namespace SDPO;

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
    ui->cmbPrefWindowsFont->setCurrentFont (s->value(SKEY_PREF_FontName, SVAL_PREF_FontName).toString());
    ui->spinPrefWindowsFontSize->setValue  (s->value(SKEY_PREF_FontSize, SVAL_PREF_FontSize).toInt());
    ui->cmbPrefTerminalFont->setCurrentFont(s->value(SKEY_PREF_TelnetFontName, SVAL_PREF_TelnetFontName).toString());
    ui->spinPrefTerminalFontSize->setValue (s->value(SKEY_PREF_TelnetFontSize, SVAL_PREF_TelnetFontSize).toInt());

    // Autosave options
    ui->chkPrefAutoSaveOptions->setChecked     (s->value(SKEY_PREF_AutoSave, SVAL_PREF_AutoSave).toInt());
    ui->cmbPrefAutoSaveOptions->setCurrentIndex(s->value(SKEY_PREF_AutoSaveMode, SVAL_PREF_AutoSaveMode).toInt());
    ui->chkPrefRecent->setChecked              (s->value(SKEY_PREF_KeptAddresses, SVAL_PREF_KeptAddresses).toInt());
    ui->spinPrefRecent->setValue               (s->value(SKEY_PREF_DeepAddresses, SVAL_PREF_DeepAddresses).toInt());

    // Icon
    ui->chkPrefMinToTray->setChecked    (s->value(SKEY_PREF_MinToTray, SVAL_PREF_MinToTray).toInt());
    ui->chkPrefAnimateIcon->setChecked  (s->value(SKEY_PREF_AnimateIcon, SVAL_PREF_AnimateIcon).toInt());
    ui->chkPrefChangeIconDie->setChecked(s->value(SKEY_PREF_ChangeIcon, SVAL_PREF_ChangeIcon).toInt());
    ui->chkPrefAlwaysTop->setChecked    (s->value(SKEY_PREF_StayFormTop, SVAL_PREF_StayFormTop).toInt());

    // Save options
    ui->chkPrefStoreStatHML->setChecked         (s->value(SKEY_MISC_StoreStatistics, SVAL_MISC_StoreStatistics).toInt());
    ui->chkPrefStoreRecurencesHML->setChecked   (s->value(SKEY_MISC_StoreIterations, SVAL_MISC_StoreIterations).toInt());
    ui->chkPrefRememberCurrentFolder->setChecked(s->value(SKEY_INTERFACE_SaveCurrFolder, SVAL_INTERFACE_SaveCurrFolder).toInt());
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
