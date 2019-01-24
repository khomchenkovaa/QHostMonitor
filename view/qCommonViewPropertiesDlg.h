#ifndef QCOMMONVIEWPROPERTIESDLG_H
#define QCOMMONVIEWPROPERTIESDLG_H

#include <QDialog>
#include "tFolder.h"

namespace Ui {
class CommonViewPropertiesDlg;
}

namespace SDPO {

class HMListService;

class CommonViewPropertiesDlg : public QDialog
{
    Q_OBJECT

    Ui::CommonViewPropertiesDlg *ui;
    TFolder *m_folder;
    HMListService *m_HML;

public:
    explicit CommonViewPropertiesDlg(TFolder *folder, HMListService *hml, QWidget *parent = 0);
    ~CommonViewPropertiesDlg();

private slots:
    void save();

private:
    void init();

};

} // namespace SDPO

#endif // QCOMMONVIEWPROPERTIESDLG_H
