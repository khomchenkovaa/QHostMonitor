#ifndef QCOMMENTPROPERTIESWIDGET_H
#define QCOMMENTPROPERTIESWIDGET_H

#include <QWidget>

namespace Ui {
class CommentPropertiesWidget;
}

namespace SDPO {

class TNode;

class CommentPropertiesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentPropertiesWidget(QWidget *parent = 0);
    ~CommentPropertiesWidget();

    void init(TNode *node = 0);
    void save(TNode *node);
    void reset();

private:
    Ui::CommentPropertiesWidget *ui;
};

} // namespace SDPO

#endif // QCOMMENTPROPERTIESWIDGET_H
