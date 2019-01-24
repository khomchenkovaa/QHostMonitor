#ifndef QSPECIALSPROPERTIESWIDGET_H
#define QSPECIALSPROPERTIESWIDGET_H

#include <QWidget>

namespace Ui {
class SpecialsPropertiesWidget;
}

namespace SDPO {

class TNode;

class SpecialsPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpecialsPropertiesWidget(QWidget *parent = 0);
    ~SpecialsPropertiesWidget();

    void init(TNode *node = 0);
    void save(TNode *node);
    void reset();

private:
    Ui::SpecialsPropertiesWidget *ui;
};

} // namespace SDPO

#endif // QSPECIALSPROPERTIESWIDGET_H
