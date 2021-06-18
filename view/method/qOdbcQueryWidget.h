#ifndef QODBCQUERYWIDGET_H
#define QODBCQUERYWIDGET_H

#include "testmethodwidget.h"

namespace Ui {
class OdbcQueryWidget;
}

namespace SDPO {

class OdbcQueryWidget : public TestMethodWidget
{
    Q_OBJECT

    bool m_TestAlert;
    int m_AlertRow;
    int m_AlertCol;
    int m_CriteriaMode;
    QString m_CriteriaValue;
    QString m_UnavailableStatus;

public:
    explicit OdbcQueryWidget(QWidget *parent = 0);
    ~OdbcQueryWidget();
    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnEdit_clicked();

private:
    Ui::OdbcQueryWidget *ui;
};

} // namespace SDPO

#endif // QODBCQUERYWIDGET_H
