#ifndef QFOLDERPROPERTIESSTATISTICWIDGET_H
#define QFOLDERPROPERTIESSTATISTICWIDGET_H

#include <QWidget>

namespace Ui {
class FolderPropertiesStatisticWidget;
}

namespace SDPO {

class FolderPropertiesStatisticWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FolderPropertiesStatisticWidget(QWidget *parent = 0);
    ~FolderPropertiesStatisticWidget();

private:
    Ui::FolderPropertiesStatisticWidget *ui;
};

} // namespace SDPO

#endif // QFOLDERPROPERTIESSTATISTICWIDGET_H
