#ifndef QEXTERNALPRGWIDGET_H
#define QEXTERNALPRGWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class ExternalPrgWidget;
}

namespace SDPO {

class ExternalPrgWidget : public TestMethodWidget
{
    Q_OBJECT
public:
    explicit ExternalPrgWidget(QWidget *parent = 0);
    ~ExternalPrgWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data=QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnExternalPrg_clicked();

private:
    Ui::ExternalPrgWidget *ui;

};

} // namespace SDPO

#endif // QEXTERNALPRGWIDGET_H
