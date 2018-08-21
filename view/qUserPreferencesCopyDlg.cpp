#include "qUserPreferencesCopyDlg.h"
#include "ui_qUserPreferencesCopyDlg.h"

namespace SDPO {

/******************************************************************/

UserPreferencesCopyDlg::UserPreferencesCopyDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPreferencesCopyDlg)
{
    ui->setupUi(this);
}

/******************************************************************/

UserPreferencesCopyDlg::~UserPreferencesCopyDlg()
{
    delete ui;
}

/******************************************************************/

void UserPreferencesCopyDlg::setItems(QStringList profiles, int hiddenIdx)
{
    for(int i=0; i < profiles.count(); i++) {
        QListWidgetItem *item = new QListWidgetItem(profiles.at(i));
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        if (i == hiddenIdx) {
            item->setHidden(true);
        }
        ui->listWidget->addItem(item);
    }
}

/******************************************************************/

QList<int> UserPreferencesCopyDlg::getSelectedIds()
{
    QList<int> result;
    for (int i=0; i<ui->listWidget->count(); i++) {
        if (ui->listWidget->item(i)->checkState() == Qt::Checked) {
            result.append(i);
        }
    }
    return result;
}

/******************************************************************/

} // namespace SDPO
