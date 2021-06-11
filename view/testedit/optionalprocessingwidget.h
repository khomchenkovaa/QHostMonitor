#ifndef OPTIONALPROCESSINGWIDGET_H
#define OPTIONALPROCESSINGWIDGET_H

#include <QWidget>

namespace Ui {
class OptionalProcessingWidget;
}

namespace SDPO {

class TTest;

class OptionalProcessingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionalProcessingWidget(QWidget *parent = nullptr);
    ~OptionalProcessingWidget();

    void reset();
    void init(TTest *item);
    void save(TTest *item);

private slots:
    void hideOptional(bool hide);
    void onBtnWarningCondition();
    void onBtnNormalCondition();
    void onBtnTuneUpReply();

private:
    void setupUI();

private:
    Ui::OptionalProcessingWidget *ui;
};

} // namespace SDPO

#endif // OPTIONALPROCESSINGWIDGET_H
