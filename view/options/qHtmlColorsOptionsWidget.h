#ifndef QHTMLCOLORSOPTIONSWIDGET_H
#define QHTMLCOLORSOPTIONSWIDGET_H

#include "qOptionsWidget.h"
#include "viewmodel/mPalettesTreeModel.h"

namespace Ui {
class HtmlColorsOptionsWidget;
}

namespace SDPO {

class HtmlColorsOptionsWidget : public OptionsWidget
{
    Q_OBJECT

    Ui::HtmlColorsOptionsWidget *ui;
    PalettesTreeModel *m_model;
public:
    explicit HtmlColorsOptionsWidget(QWidget *parent = 0);
    ~HtmlColorsOptionsWidget();

    virtual void init() Q_DECL_OVERRIDE;
    virtual void prepareToSave() Q_DECL_OVERRIDE;

private slots:
    void on_btnColorScheme_clicked();
    void on_editColorScheme_textChanged(const QString &colorScheme);

};

} // namespace SDPO

#endif // QHTMLCOLORSOPTIONSWIDGET_H
