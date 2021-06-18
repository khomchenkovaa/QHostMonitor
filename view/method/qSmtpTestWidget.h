#ifndef QSMTPTESTWIDGET_H
#define QSMTPTESTWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class SmtpTestWidget;
}

namespace SDPO {

class SmtpTestWidget : public TestMethodWidget
{
    Q_OBJECT

public:
    explicit SmtpTestWidget(QWidget *parent = 0);
    ~SmtpTestWidget();

private:
    Ui::SmtpTestWidget *ui;
};

} // namespace SDPO

#endif // QSMTPTESTWIDGET_H
