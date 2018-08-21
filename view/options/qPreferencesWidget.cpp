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

void PreferencesWidget::init()
{

    QVariant value = Settings::get(Settings::Environ, Settings::FontName, QVariant("DejaVu Sans"));
        ui->cmbPrefWindowsFont->setCurrentFont(value.toString());

    value = Settings::get(Settings::Environ, Settings::FontSize, QVariant(8));
        ui->spinPrefWindowsFontSize->setValue(value.toInt());

    value = Settings::get(Settings::Environ, Settings::TelnetFontName, QVariant("Carlito"));
        ui->cmbPrefTerminalFont->setCurrentFont(value.toString());

    value = Settings::get(Settings::Environ, Settings::TelnetFontSize, QVariant(12));
        ui->spinPrefTerminalFontSize->setValue(value.toInt());

    value = Settings::get(Settings::Environ, Settings::AutoSave, QVariant(1));
        if (value.toInt() == 0) {
            ui->chkPrefAutoSaveOptions->setChecked(false);
              }
        else  {
            ui->chkPrefAutoSaveOptions->setChecked(true);
              }

    value = Settings::get(Settings::Environ, Settings::MinToTray, QVariant(1));
        if (value.toInt() == 0) {
            ui->chkPrefMinToTray->setChecked(false);
              }
        else  {
            ui->chkPrefMinToTray->setChecked(true);
              }

    value = Settings::get(Settings::Environ, Settings::StayFormTop, QVariant(0));
        if (value.toInt() == 0) {
            ui->chkPrefAlwaysTop->setChecked(false);
              }
        else  {
            ui->chkPrefAlwaysTop->setChecked(true);
              }

    value = Settings::get(Settings::Environ, Settings::KeptAddresses, QVariant(1));
        if (value.toInt() == 0) {
           ui->chkPrefRecent->setChecked(false);
              }
        else  {
           ui->chkPrefRecent->setChecked(true);
               }

    value = Settings::get(Settings::Environ, Settings::DeepAddresses, QVariant(5));
        ui->spinPrefRecent->setValue(value.toInt());

    value = Settings::get(Settings::Environ, Settings::AnimateIcon, QVariant(1));
        if (value.toInt() == 0) {
           ui->chkPrefAnimateIcon->setChecked(false);
              }
        else  {
           ui->chkPrefAnimateIcon->setChecked(true);
              }

    value = Settings::get(Settings::Environ, Settings::ChangeIcon, QVariant(1));
        if (value.toInt() == 0) {
           ui->chkPrefChangeIconDie->setChecked(false);
              }
        else  {
           ui->chkPrefChangeIconDie->setChecked(true);
              }

    value = Settings::get(Settings::Environ, Settings::AutoSaveMode, QVariant(1));
        ui->cmbPrefAutoSaveOptions->setCurrentIndex(value.toInt());

    value = Settings::get(Settings::Misc, Settings::StoreStatistics, QVariant(1));
        if (value.toInt() == 0) {
           ui->chkPrefStoreStatHML->setChecked(false);
              }
        else  {
           ui->chkPrefStoreStatHML->setChecked(true);
              }

    value = Settings::get(Settings::Misc, Settings::StoreIterations, QVariant(1));
        if (value.toInt() == 0) {
           ui->chkPrefStoreRecurencesHML->setChecked(false);
              }
        else  {
           ui->chkPrefStoreRecurencesHML->setChecked(true);
              }

    value = Settings::get(Settings::Interface, Settings::SaveCurrFolder, QVariant(1));
        if (value.toInt() == 0) {
           ui->chkPrefRememberCurrentFolder->setChecked(false);
              }
        else  {
           ui->chkPrefRememberCurrentFolder->setChecked(true);
              }
}

/******************************************************************/

void PreferencesWidget::prepareToSave()
{ Settings::set(Settings::Environ, Settings::FontName) = QVariant(ui->cmbPrefWindowsFont->currentFont());
    Settings::set(Settings::Environ, Settings::FontSize) = QVariant(ui->spinPrefWindowsFontSize->value());
    Settings::set(Settings::Environ, Settings::TelnetFontName) = QVariant(ui->cmbPrefTerminalFont->currentFont());
    Settings::set(Settings::Environ, Settings::TelnetFontSize) = QVariant(ui->spinPrefTerminalFontSize->value());
    Settings::set(Settings::Environ, Settings::AutoSave) = QVariant(ui->chkPrefAutoSaveOptions->isChecked()?1:0);
    Settings::set(Settings::Environ, Settings::MinToTray) = QVariant(ui->chkPrefMinToTray->isChecked()?1:0);
    Settings::set(Settings::Environ, Settings::StayFormTop) = QVariant(ui->chkPrefAlwaysTop->isChecked()?1:0);
    Settings::set(Settings::Environ, Settings::KeptAddresses) = QVariant(ui->chkPrefRecent->isChecked()?1:0);
    Settings::set(Settings::Environ, Settings::DeepAddresses) = QVariant(ui->spinPrefRecent->value());
    Settings::set(Settings::Environ, Settings::AnimateIcon) = QVariant(ui->chkPrefAnimateIcon->isChecked()?1:0);
    Settings::set(Settings::Environ, Settings::ChangeIcon) = QVariant(ui->chkPrefChangeIconDie->isChecked()?1:0);
    Settings::set(Settings::Environ, Settings::AutoSaveMode) = QVariant(ui->cmbPrefAutoSaveOptions->currentIndex());
    Settings::set(Settings::Misc, Settings::StoreStatistics) = QVariant(ui->chkPrefStoreStatHML->isChecked()?1:0);
    Settings::set(Settings::Misc, Settings::StoreIterations) = QVariant(ui->chkPrefStoreRecurencesHML->isChecked()?1:0);
    Settings::set(Settings::Interface, Settings::SaveCurrFolder) = QVariant(ui->chkPrefRememberCurrentFolder->isChecked()?1:0);



}

/******************************************************************/

} // namespace SDPO
