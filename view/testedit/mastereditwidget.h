#ifndef MASTEREDITWIDGET_H
#define MASTEREDITWIDGET_H

#include <QWidget>

namespace Ui {
class MasterEditWidget;
}

namespace SDPO {

class TNode;
class TTest;

class MasterEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MasterEditWidget(QWidget *parent = nullptr);
    ~MasterEditWidget();

    void reset(TNode *root);
    void init(TTest *item = nullptr);
    void save(TTest *item);
    int doHide(bool hide);

signals:
    void hideMe(bool hide);

private:
    void setupUI();

private:
    Ui::MasterEditWidget *ui;
};

} // namespace SDPO

#endif // MASTEREDITWIDGET_H
