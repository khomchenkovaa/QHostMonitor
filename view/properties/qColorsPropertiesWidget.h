#ifndef QCOLORSPROPERTIESWIDGET_H
#define QCOLORSPROPERTIESWIDGET_H

#include <QWidget>
#include "viewmodel/mPalettesTreeModel.h"

namespace Ui {
class ColorsPropertiesWidget;
}

namespace SDPO {

class TNode;

class ColorsPropertiesWidget : public QWidget
{
    Q_OBJECT

    Ui::ColorsPropertiesWidget *ui;
    PalettesTreeModel *m_model;

public:
    explicit ColorsPropertiesWidget(QWidget *parent = 0);
    ~ColorsPropertiesWidget();

    void init(TNode *node = 0);
    void save(TNode *node);
    void reset();

private slots:
    void on_btnSelectColorScheme_clicked();
    void on_editColorScheme_textChanged(const QString &colorScheme);

    void on_rbUseOwnColorScheme_toggled(bool checked);
};

} // namespace SDPO

#endif // QCOLORSPROPERTIESWIDGET_H
