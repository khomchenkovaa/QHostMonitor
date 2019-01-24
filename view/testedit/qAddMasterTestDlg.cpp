#include "qAddMasterTestDlg.h"
#include "ui_qAddMasterTestDlg.h"
#include "viewmodel/mTestsTreeModel.h"
#include "tLink.h"

namespace SDPO {

/******************************************************************/

AddMasterTestDlg::AddMasterTestDlg(TNode *root, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMasterTestDlg)
{
    ui->setupUi(this);
    ui->trvTests->setModel(new TestsTreeModel(root, this));
    connect(ui->trvTests->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onNodeSelected(QModelIndex,QModelIndex)));
}

/******************************************************************/

AddMasterTestDlg::~AddMasterTestDlg()
{
    delete ui;
}

/******************************************************************/

QPair<TTest *, int> AddMasterTestDlg::getResult() const
{
    TTest *test = 0;
    QModelIndex index = ui->trvTests->currentIndex();
    if (index.isValid()) {
        TNode *item = static_cast<TNode*>(index.internalPointer());
        if (item->getType() == TNode::TEST) {
            test = qobject_cast<TTest*>(item);
        } else if (item->getType() == TNode::LINK) {
            TLink *link = qobject_cast<TLink*>(item);
            test = link->getTest();
        }
    }
    QPair<TTest *, int> result;
    result.first = test;
    result.second = ui->cmbCondition->currentIndex();
    return result;
}

/******************************************************************/

void AddMasterTestDlg::onNodeSelected(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    if (!current.isValid()) {
        return;
    }
    TNode *item = static_cast<TNode*>(current.internalPointer());
    TTest *test = 0;
    QString testSelected = "<not selected>";
    if (item->getType() == TNode::TEST) {
        test = qobject_cast<TTest*>(item);
    } else if (item->getType() == TNode::LINK) {
        TLink *link = qobject_cast<TLink*>(item);
        test = link->getTest();
    }
    if (test) {
        testSelected = QString("%1 (method: %2)").arg(test->getName()).arg(test->property("TestedObjectInfo").toString());
    }
    ui->lblSelectedTest->setText(testSelected);
}

/******************************************************************/

} // namespace SDPO
