#ifndef QHTTPPROXIESLISTDLG_H
#define QHTTPPROXIESLISTDLG_H

#include <QDialog>

namespace Ui {
class HttpProxiesListDlg;
}

namespace SDPO {

class HttpProxiesListDlg : public QDialog
{
    Q_OBJECT

public:
    explicit HttpProxiesListDlg(QWidget *parent = 0);
    ~HttpProxiesListDlg();

private:
    Ui::HttpProxiesListDlg *ui;
};

} // namespace SDPO
#endif // QHTTPPROXIESLISTDLG_H
