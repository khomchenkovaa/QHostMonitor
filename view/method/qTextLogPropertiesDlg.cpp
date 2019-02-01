#include "qTextLogPropertiesDlg.h"
#include "ui_qTextLogPropertiesDlg.h"

namespace SDPO {

TextLogPropertiesDlg::TextLogPropertiesDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextLogPropertiesDlg)
{
    ui->setupUi(this);
}

TextLogPropertiesDlg::~TextLogPropertiesDlg()
{
    delete ui;
}

} // namespace SDPO
