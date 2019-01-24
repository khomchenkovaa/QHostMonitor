#ifndef QVIEWCRITERIAPROPERTIESWIDGET_H
#define QVIEWCRITERIAPROPERTIESWIDGET_H

#include <QWidget>

namespace Ui {
class ViewCriteriaPropertiesWidget;
}

namespace SDPO {

class TNode;

class ViewCriteriaPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewCriteriaPropertiesWidget(QWidget *parent = 0);
    ~ViewCriteriaPropertiesWidget();

    void init(TNode *node = 0);
    void save(TNode *node);
    void reset();

private slots:
    void on_btnSelectExpression_clicked();
    void on_rbStatusDuration_toggled(bool checked);

private:
    Ui::ViewCriteriaPropertiesWidget *ui;
};

} // namespace SDPO

#endif // QVIEWCRITERIAPROPERTIESWIDGET_H
