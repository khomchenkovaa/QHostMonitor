#ifndef QCOMPAREFILESWIDGET_H
#define QCOMPAREFILESWIDGET_H

#include "testmethodwidget.h"

#include <QTextCodec>

namespace Ui {
class CompareFilesWidget;
}

namespace SDPO {

class CompareFilesWidget : public TestMethodWidget
{
    Q_OBJECT

    Ui::CompareFilesWidget *ui;
public:
    explicit CompareFilesWidget(QWidget *parent = 0);
    ~CompareFilesWidget();

    virtual void init(TestMethod *item = 0) Q_DECL_OVERRIDE;
    virtual TestMethod* save(TestMethod *item) Q_DECL_OVERRIDE;
    virtual void reset(QVariant data = QVariant()) Q_DECL_OVERRIDE;
    virtual QStringList validate() Q_DECL_OVERRIDE;
    virtual QString getTemplateValue(const QString var) const Q_DECL_OVERRIDE;

private slots:
    void on_selectAlert();
    void on_btnFirstFile_clicked();
    void on_btnSecondFile_clicked();

private:
    QList<QTextCodec *> findCodecs();
};

} // namespace SDPO

#endif // QCOMPAREFILESWIDGET_H
