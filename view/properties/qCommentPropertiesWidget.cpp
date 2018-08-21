#include "qCommentPropertiesWidget.h"
#include "ui_qCommentPropertiesWidget.h"
#include "tNode.h"

namespace SDPO {

/******************************************************************/

CommentPropertiesWidget::CommentPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentPropertiesWidget)
{
    ui->setupUi(this);
}

/******************************************************************/

CommentPropertiesWidget::~CommentPropertiesWidget()
{
    delete ui;
}

/******************************************************************/

void CommentPropertiesWidget::init(TNode *node)
{
    if (!node) {
        reset();
        return;
    }
    ui->textComment->setPlainText(node->getComment());
}

/******************************************************************/

void CommentPropertiesWidget::save(TNode *node)
{
    if (!node) {
        return;
    }
    node->setComment(ui->textComment->toPlainText());
}

/******************************************************************/

void CommentPropertiesWidget::reset()
{
    ui->textComment->clear();
}

/******************************************************************/

} // namespace SDPO
