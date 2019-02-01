#ifndef QURLTESTPROPERTIESDLG_H
#define QURLTESTPROPERTIESDLG_H

#include <QDialog>

namespace Ui {
class UrlTestPropertiesDlg;
}

namespace SDPO {

class UrlTestPropertiesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit UrlTestPropertiesDlg(QWidget *parent = 0);
    ~UrlTestPropertiesDlg();

private:
    Ui::UrlTestPropertiesDlg *ui;
};

} // namespace SDPO

#endif // QURLTESTPROPERTIESDLG_H
