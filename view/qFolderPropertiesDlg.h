#ifndef QFOLDERPROPERTIESDLG_H
#define QFOLDERPROPERTIESDLG_H

#include <QDialog>
#include "tFolder.h"

namespace Ui {
class FolderPropertiesDlg;
}

namespace SDPO {

class HMListService;

class FolderPropertiesDlg : public QDialog
{
    Q_OBJECT

    Ui::FolderPropertiesDlg *ui;
    TFolder *m_folder;
    HMListService *m_HML;

public:
    explicit FolderPropertiesDlg(TFolder *folder, HMListService *hml, QWidget *parent = 0);
    ~FolderPropertiesDlg();

private slots:
    void save();

private:
    void init();
};

} // namespace SDPO

#endif // QFOLDERPROPERTIESDLG_H
