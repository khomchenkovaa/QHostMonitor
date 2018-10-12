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
    QVariant val;
    val = s->value(SKEY_PREF_FontName, "DejaVu Sans");
    ui->cmbPrefWindowsFont->setCurrentFont(val.toString());

    val = s->value(SKEY_PREF_FontSize, 8);
    ui->spinPrefWindowsFontSize->setValue(val.toInt());

    val = s->value(SKEY_PREF_TelnetFontName, "Carlito");
    ui->cmbPrefTerminalFont->setCurrentFont(val.toString());

    val = s->value(SKEY_PREF_TelnetFontSize, 12);
    ui->spinPrefTerminalFontSize->setValue(val.toInt());

    val = s->value(SKEY_PREF_AutoSave, 1);
    ui->chkPrefAutoSaveOptions->setChecked(val.toInt() == 1);

    val = s->value(SKEY_PREF_MinToTray, 1);
    ui->chkPrefMinToTray->setChecked(val.toInt() == 1);

    val = s->value(SKEY_PREF_StayFormTop, 0);
    ui->chkPrefAlwaysTop->setChecked(val.toInt() == 1);

    val = s->value(SKEY_PREF_KeptAddresses, 1);
    ui->chkPrefRecent->setChecked(val.toInt() == 1);

    val = s->value(SKEY_PREF_DeepAddresses, 5);
    ui->spinPrefRecent->setValue(val.toInt());

    val = s->value(SKEY_PREF_AnimateIcon, 1);
    ui->chkPrefAnimateIcon->setChecked(val.toInt() == 1);

    val = s->value(SKEY_PREF_ChangeIcon, 1);
    ui->chkPrefChangeIconDie->setChecked(val.toInt() == 1);

    val = s->value(SKEY_PREF_AutoSaveMode, 5);
    ui->cmbPrefAutoSaveOptions->setCurrentIndex(val.toInt());

    val = s->value(SKEY_MISC_StoreStatistics, 1);
    ui->chkPrefStoreStatHML->setChecked(val.toInt() == 1);

    val = s->value(SKEY_MISC_StoreIterations, 1);
    ui->chkPrefStoreRecurencesHML->setChecked(val.toInt() == 1);

    val = s->value(SKEY_INTERFACE_SaveCurrFolder, 1);
    ui->chkPrefRememberCurrentFolder->setChecked(val.toInt() == 1);
}

/******************************************************************/

void PreferencesWidget::prepareToSave(QSettings *s)
{
    s->setValue(SKEY_PREF_FontName, ui->cmbPrefWindowsFont->currentFont());
    s->setValue(SKEY_PREF_FontSize, ui->spinPrefWindowsFontSize->value());
    s->setValue(SKEY_PREF_TelnetFontName, ui->cmbPrefTerminalFont->currentFont());
    s->setValue(SKEY_PREF_TelnetFontSize, ui->spinPrefTerminalFontSize->value());
    s->setValue(SKEY_PREF_AutoSave, ui->chkPrefAutoSaveOptions->isChecked()?1:0);
    s->setValue(SKEY_PREF_MinToTray, ui->chkPrefMinToTray->isChecked()?1:0);
    s->setValue(SKEY_PREF_StayFormTop, ui->chkPrefAlwaysTop->isChecked()?1:0);
    s->setValue(SKEY_PREF_KeptAddresses, ui->chkPrefRecent->isChecked()?1:0);
    s->setValue(SKEY_PREF_DeepAddresses, ui->spinPrefRecent->value());
    s->setValue(SKEY_PREF_AnimateIcon, ui->chkPrefAnimateIcon->isChecked()?1:0);
    s->setValue(SKEY_PREF_ChangeIcon, ui->chkPrefChangeIconDie->isChecked()?1:0);
    s->setValue(SKEY_PREF_AutoSaveMode, ui->cmbPrefAutoSaveOptions->currentIndex());
    s->setValue(SKEY_MISC_StoreStatistics, ui->chkPrefStoreStatHML->isChecked()?1:0);
    s->setValue(SKEY_MISC_StoreIterations, ui->chkPrefStoreRecurencesHML->isChecked()?1:0);
    s->setValue(SKEY_INTERFACE_SaveCurrFolder, ui->chkPrefRememberCurrentFolder->isChecked()?1:0);
}

/******************************************************************/

} // namespace SDPO
