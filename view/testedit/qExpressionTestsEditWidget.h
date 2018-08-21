#ifndef QEXPRESSIONTESTSEDITWIDGET_H
#define QEXPRESSIONTESTSEDITWIDGET_H

#include <QWidget>

namespace Ui {
class ExpressionTestsEditWidget;
}

namespace SDPO {

class TTest;

class ExpressionTestsEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExpressionTestsEditWidget(QWidget *parent = 0);
    ~ExpressionTestsEditWidget();

    void init(TTest *item = 0);
    void save(TTest *item);
    void reset();

private slots:
    void on_btnCondition_clicked();

private:
    Ui::ExpressionTestsEditWidget *ui;
};

} // namespace SDPO

#endif // QEXPRESSIONTESTSEDITWIDGET_H
