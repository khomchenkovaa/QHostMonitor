#ifndef DEPENDENCIESEDITWIDGET_H
#define DEPENDENCIESEDITWIDGET_H

#include <QWidget>

namespace Ui {
class DependenciesEditWidget;
}

namespace SDPO {

class TTest;

class DependenciesEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DependenciesEditWidget(QWidget *parent = nullptr);
    ~DependenciesEditWidget();

    void reset();
    void init(TTest *item = nullptr);
    void save(TTest *item);
    int doHide(bool hide);

signals:
    void hideMe(bool hide);

private:
    void setupUI();

private:
    Ui::DependenciesEditWidget *ui;
};

} // namespace SDPO

#endif // DEPENDENCIESEDITWIDGET_H
