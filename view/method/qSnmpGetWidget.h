#ifndef QSNMPGETWIDGET_H
#define QSNMPGETWIDGET_H

#include "qTestWidget.h"

QT_BEGIN_NAMESPACE
class QProcess;
QT_END_NAMESPACE

namespace Ui {
class SnmpGetWidget;
}

namespace SDPO {

class SnmpGetWidget : public TestWidget
{
    Q_OBJECT

public:
    explicit SnmpGetWidget(QWidget *parent = 0);
    ~SnmpGetWidget();
    virtual void init(TTestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TTestMethod* save(TTestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_btnSnmpCredentials_clicked();
    void on_btnMibBrowser_clicked();
    void on_btnGetValue_clicked();
    void onReadyRead();
    void onRunFinished(int exitCode);

private:
    Ui::SnmpGetWidget *ui;
    QProcess *m_process;
};

} // namespace SDPO

#endif // QSNMPGETWIDGET_H
