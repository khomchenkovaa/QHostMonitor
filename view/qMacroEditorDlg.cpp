#include "qMacroEditorDlg.h"
#include "ui_qMacroEditorDlg.h"
#include "global/gUserVars.h"
#include "xMacroVar.h"
#include "tEnums.h"
#include <QtWidgets>
#include "qMacroEditorScriptRunnerDlg.h"

using namespace SDPO;

/******************************************************************/

MacroEditorDlg::MacroEditorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MacroEditorDlg)
{
    ui->setupUi(this);
    init();
}

/******************************************************************/

MacroEditorDlg::~MacroEditorDlg()
{
    delete ui;
}

/******************************************************************/

QString MacroEditorDlg::getScript() const
{
    return ui->editScript->toPlainText();
}

/******************************************************************/

void MacroEditorDlg::setScript(const QString script)
{
    ui->editScript->setPlainText(script);
}

/******************************************************************/

void MacroEditorDlg::currentUserMacroChanged(const int row)
{
    if (row < GUserVars::variables.size()) {
        QString key = GUserVars::variables.keys().at(row);
        ui->lineUserDefinedMacroVariables->setText(GUserVars::variables.value(key));
    }
}

/******************************************************************/

void MacroEditorDlg::initMacroVars()
{
    ui->listStandartMacroVariables->clear();
    for(unsigned i=0;i<TMacro::varList.size();++i) {
        bool added = false;
        MVariablesStruct var = TMacro::varList.at(i);
        switch(var.group) {
        case Macro::TP:
            if (ui->btnTP->isChecked()) {
                added = true;
            }
            break;
        case Macro::TS:
            if (ui->btnTS->isChecked()) {
                added = true;
            }
            break;
        case Macro::SS:
            if (ui->btnSS->isChecked()) {
                added = true;
            }
            break;
        case Macro::AI:
            if (ui->btnAI->isChecked()) {
                added = true;
            }
            break;
        case Macro::LS:
            if (ui->btnLS->isChecked()) {
                added = true;
            }
            break;
        case Macro::ST:
            if (ui->btnST->isChecked()) {
                added = true;
            }
            break;
        case Macro::SP:
            if (ui->btnSP->isChecked()) {
                added = true;
            }
            break;
        }
        if (added) {
            ui->listStandartMacroVariables->addItem(QString("%%1%").arg(var.name));
        }
    }
}

/******************************************************************/

void MacroEditorDlg::on_listStandartMacroVariables_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction actInsert("Insert into expression", this);
    connect(&actInsert, SIGNAL(triggered()), this, SLOT(appentStandartMacroVariable()));
    contextMenu.addAction(&actInsert);

    contextMenu.addSeparator();

    QAction actFavorite("Add variable to favorites", this);
    connect(&actFavorite, SIGNAL(triggered()), this, SLOT(addFavoriteStandartMacroVariable()));
    contextMenu.addAction(&actFavorite);

    contextMenu.setStyleSheet("font: 8pt \"DejaVu Sans\";");
    contextMenu.exec(ui->listStandartMacroVariables->mapToGlobal(pos));
}

/******************************************************************/

void MacroEditorDlg::on_listUserDefinedMacroVariables_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction actInsert("Insert into expression", this);
    connect(&actInsert, SIGNAL(triggered()), this, SLOT(appendUserDefinedVariable()));
    contextMenu.addAction(&actInsert);

    contextMenu.addSeparator();

    QAction actFavorite("Add variable to favorites", this);
    connect(&actFavorite, SIGNAL(triggered()), this, SLOT(addFavoriteUserDefinedVariable()));
    contextMenu.addAction(&actFavorite);

    contextMenu.setStyleSheet("font: 8pt \"DejaVu Sans\";");
    contextMenu.exec(ui->listUserDefinedMacroVariables->mapToGlobal(pos));
}

/******************************************************************/

void MacroEditorDlg::on_listFavoriteMacroVariables_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction actInsert("Insert into expression", this);
    connect(&actInsert, SIGNAL(triggered()), this, SLOT(appendFavoriteVariable()));
    contextMenu.addAction(&actInsert);

    contextMenu.addSeparator();

    QAction actMoveUp("Move up", this);
    connect(&actMoveUp, SIGNAL(triggered()), this, SLOT(moveFavoriteUp()));
    contextMenu.addAction(&actMoveUp);

    QAction actMoveDown("Move down", this);
    connect(&actMoveDown, SIGNAL(triggered()), this, SLOT(moveFavoriteDown()));
    contextMenu.addAction(&actMoveDown);

    QAction actSort("Sort alphabetically", this);
    connect(&actSort, SIGNAL(triggered()), this, SLOT(sortFavorite()));
    contextMenu.addAction(&actSort);

    contextMenu.addSeparator();

    QAction actRemove("Remove item", this);
    connect(&actRemove, SIGNAL(triggered()), this, SLOT(removeFromFavorite()));
    contextMenu.addAction(&actRemove);

    contextMenu.setStyleSheet("font: 8pt \"DejaVu Sans\";");
    contextMenu.exec(ui->listFavoriteMacroVariables->mapToGlobal(pos));
}

/******************************************************************/

void MacroEditorDlg::appentStandartMacroVariable()
{
    QString text = ui->listStandartMacroVariables->currentItem()->text();
    ui->editScript->insertPlainText(text);
}

/******************************************************************/

void MacroEditorDlg::addFavoriteStandartMacroVariable()
{
    QString text = ui->listStandartMacroVariables->currentItem()->text();
    if (!GUserVars::favorite.contains(text)) {
        GUserVars::favorite.append(text);
        ui->listFavoriteMacroVariables->addItem(text);
    }
}

/******************************************************************/

void MacroEditorDlg::appendUserDefinedVariable()
{
    QString text = ui->listUserDefinedMacroVariables->currentItem()->text();
    ui->editScript->insertPlainText(text);

}

/******************************************************************/

void MacroEditorDlg::addFavoriteUserDefinedVariable()
{
    QString text = ui->listUserDefinedMacroVariables->currentItem()->text();
    if (!GUserVars::favorite.contains(text)) {
        GUserVars::favorite.append(text);
        ui->listFavoriteMacroVariables->addItem(text);
    }
}

/******************************************************************/

void MacroEditorDlg::appendFavoriteVariable()
{
    QString text = ui->listFavoriteMacroVariables->currentItem()->text();
    ui->editScript->insertPlainText(text);
}

/******************************************************************/

void MacroEditorDlg::moveFavoriteUp()
{
    int idx = ui->listFavoriteMacroVariables->currentRow();
    if (idx > 0 && idx < GUserVars::favorite.count()) {
        GUserVars::favorite.swap(idx-1, idx);
        initFavorites();
    }
}

/******************************************************************/

void MacroEditorDlg::moveFavoriteDown()
{
    int idx = ui->listFavoriteMacroVariables->currentRow();
    if (idx >= 0 && idx < GUserVars::favorite.count()-1) {
        GUserVars::favorite.swap(idx, idx+1);
        initFavorites();
    }
}

/******************************************************************/

void MacroEditorDlg::sortFavorite()
{
    GUserVars::favorite.sort();
    initFavorites();
}

/******************************************************************/

void MacroEditorDlg::removeFromFavorite()
{
    int idx = ui->listFavoriteMacroVariables->currentRow();
    if (idx >= 0 && idx < GUserVars::favorite.count()) {
        GUserVars::favorite.removeAt(idx);
        initFavorites();
    }
}

/******************************************************************/

void SDPO::MacroEditorDlg::on_btnRun_clicked()
{
    MacroEditorScriptRunnerDlg dlg;
    dlg.setScript(ui->editScript->toPlainText());
    dlg.exec();
}

/******************************************************************/

void MacroEditorDlg::init()
{
    // user defined
    ui->listUserDefinedMacroVariables->clear();
    foreach(const QString &key, GUserVars::variables.keys()) {
        ui->listUserDefinedMacroVariables->addItem(QString("%%1%").arg(key));
    }
    connect(ui->listUserDefinedMacroVariables, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(appendUserDefinedVariable()));
    connect(ui->listUserDefinedMacroVariables, SIGNAL(currentRowChanged(int)), this, SLOT(currentUserMacroChanged(int)));

    // global macro
    ui->btnTS->setChecked(true);
    ui->btnSS->setChecked(true);
    ui->btnLS->setChecked(true);
    initMacroVars();
    connect(ui->btnTP, SIGNAL(clicked()), this, SLOT(initMacroVars()));
    connect(ui->btnTS, SIGNAL(clicked()), this, SLOT(initMacroVars()));
    connect(ui->btnSS, SIGNAL(clicked()), this, SLOT(initMacroVars()));
    connect(ui->btnAI, SIGNAL(clicked()), this, SLOT(initMacroVars()));
    connect(ui->btnLS, SIGNAL(clicked()), this, SLOT(initMacroVars()));
    connect(ui->btnST, SIGNAL(clicked()), this, SLOT(initMacroVars()));
    connect(ui->btnSP, SIGNAL(clicked()), this, SLOT(initMacroVars()));
    connect(ui->listStandartMacroVariables, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(appentStandartMacroVariable()));

    // favorites
    initFavorites();
    connect(ui->listFavoriteMacroVariables, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(appendFavoriteVariable()));

}

/******************************************************************/

void MacroEditorDlg::initFavorites()
{
    ui->listFavoriteMacroVariables->clear();
    foreach(const QString &key, GUserVars::favorite) {
        ui->listFavoriteMacroVariables->addItem(key);
    }
}

/******************************************************************/
