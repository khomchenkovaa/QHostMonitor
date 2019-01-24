#ifndef QDYNAMICVIEWPROPERTIESDLG_H
#define QDYNAMICVIEWPROPERTIESDLG_H

#include <QDialog>
#include "tView.h"

namespace Ui {
class DynamicViewPropertiesDlg;
}

namespace SDPO {

class HMListService;

class DynamicViewPropertiesDlg : public QDialog
{
    Q_OBJECT

    Ui::DynamicViewPropertiesDlg *ui;
    TView *m_view;
    HMListService *m_HML;
    TFolder *m_SourceFolder;

public:
    explicit DynamicViewPropertiesDlg(TView *view, HMListService *hml, QWidget *parent = 0);
    ~DynamicViewPropertiesDlg();

private slots:
    void on_btnSelectSubfolders_clicked();
    void save();

private:
    void init();
};

} // namespace SDPO

#endif // QDYNAMICVIEWPROPERTIESDLG_H
