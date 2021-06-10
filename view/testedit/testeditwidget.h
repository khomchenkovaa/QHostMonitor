#ifndef TESTEDITWIDGET_H
#define TESTEDITWIDGET_H

#include "testmethod.h"

#include <QFrame>
#include <QVariant>

namespace Ui {
class TestEditWidget;
}

namespace SDPO {

class TTest;
class HMListService;

class TestEditWidget : public QFrame
{
    Q_OBJECT

    Ui::TestEditWidget *ui;
    QVariant        m_Data;

public:
    explicit TestEditWidget(QWidget *parent = nullptr);
    ~TestEditWidget();

    void reset();
    void setData(const QVariant &data) {
        m_Data = data;
    }
    void setMethodID(const TMethodID methodID);
    void init(TTest *item = nullptr);
    TTest *save(HMListService  *hmlService, TTest *item);

private slots:
    void openMethodSelectDialog();
    void refreshNameAndComment();


private:
    void setupUI();
    void setupTestMethodCombo();
    void setupTestMethodWidgets();
    QString getTestName() const;
    QString getTestComment() const;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

} // namespace SDPO

#endif // TESTEDITWIDGET_H
