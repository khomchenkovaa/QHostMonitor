#ifndef QTEXTLOGPROPERTIESDLG_H
#define QTEXTLOGPROPERTIESDLG_H

#include <QDialog>

namespace Ui {
class TextLogPropertiesDlg;
}

namespace SDPO {

class TextLogPropertiesDlg : public QDialog
{
    Q_OBJECT

public:
    explicit TextLogPropertiesDlg(QWidget *parent = 0);
    ~TextLogPropertiesDlg();

private:
    Ui::TextLogPropertiesDlg *ui;
};

} // namespace SDPO

#endif // QTEXTLOGPROPERTIESDLG_H
