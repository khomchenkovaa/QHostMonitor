#ifndef QEXTERNALPRGWIDGET_H
#define QEXTERNALPRGWIDGET_H

#include "qTestWidget.h"

namespace Ui {
class ExternalPrgWidget;
}

namespace SDPO {

class ExternalPrgWidget : public TestWidget
{
    Q_OBJECT
public:
    explicit ExternalPrgWidget(QWidget *parent = 0);
    ~ExternalPrgWidget();

    virtual void init(TTestMethod *item = 0);
    virtual TTestMethod* save(TTestMethod *item);
    virtual void reset(QVariant data=QVariant());
    virtual QStringList validate();
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

signals:

private slots:
    void on_btnExternalPrg_clicked();

private:
    Ui::ExternalPrgWidget *ui;

};

} // namespace SDPO

#endif // QEXTERNALPRGWIDGET_H
