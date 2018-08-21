#ifndef QMAININFOPANEWIDGET_H
#define QMAININFOPANEWIDGET_H

#include <QWidget>

namespace Ui {
class MainInfoPaneWidget;
}

namespace SDPO {
class TNode;
class HMListService;

class MainInfoPaneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainInfoPaneWidget(QWidget *parent = 0);
    ~MainInfoPaneWidget();

    void testInfo(const TNode *test);
    void folderInfo(HMListService *hml, const int testVisible, const int testSelected);

private:
    Ui::MainInfoPaneWidget *ui;
    void showSingleInfo(const bool isSingle);
};

} // namespace SDPO

#endif // QMAININFOPANEWIDGET_H
