#ifndef QREGIONALPROPERTIESWIDGET_H
#define QREGIONALPROPERTIESWIDGET_H

#include <QWidget>

namespace Ui {
class RegionalPropertiesWidget;
}

namespace SDPO {

class TNode;

class RegionalPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegionalPropertiesWidget(QWidget *parent = 0);
    ~RegionalPropertiesWidget();

    void init(TNode *node = 0);
    void save(TNode *node);
    void reset();

private slots:
    void on_rbUseOwnRegionalSettings_toggled(bool checked);

private:
    Ui::RegionalPropertiesWidget *ui;
};

} // namespace SDPO

#endif // QREGIONALPROPERTIESWIDGET_H
