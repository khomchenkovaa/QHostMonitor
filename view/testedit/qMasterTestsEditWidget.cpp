#include "qMasterTestsEditWidget.h"
#include "ui_qMasterTestsEditWidget.h"
#include "qAddMasterTestDlg.h"

namespace SDPO {

/******************************************************************/

MasterTestsEditWidget::MasterTestsEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MasterTestsEditWidget)
{
    ui->setupUi(this);
    m_conditions << "'Alive'" << "'Alive' or 'Unknown'" << "'Dead'" << "'Dead' or 'Unknown'";
    connect(ui->treeMasterTests->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this, SLOT(currentChanged(QModelIndex,QModelIndex)));
}

/******************************************************************/

MasterTestsEditWidget::~MasterTestsEditWidget()
{
    delete ui;
}

/******************************************************************/

void MasterTestsEditWidget::init(TTest *item)
{
    m_masterTests.clear();
    m_masterTests.append(item->getMasterTests());
    updateMasterTests();
    ui->btnMasterTestUp->setEnabled(false);
    ui->btnMasterTestDown->setEnabled(false);
    ui->btnMasterTestDelete->setEnabled(false);
}

/******************************************************************/

void MasterTestsEditWidget::save(TTest *item)
{
    item->setMasterTests(m_masterTests);
}

/******************************************************************/

void MasterTestsEditWidget::reset(TNode *root)
{
    m_root = root;
    ui->treeMasterTests->clear();
    ui->btnMasterTestUp->setEnabled(false);
    ui->btnMasterTestDown->setEnabled(false);
    ui->btnMasterTestDelete->setEnabled(false);
}

/******************************************************************/

void MasterTestsEditWidget::on_btnMasterTestUp_clicked()
{
    QModelIndex idx = ui->treeMasterTests->currentIndex();
    int row = idx.isValid() ? idx.row() : 0;
    if (row > 0 && row < m_masterTests.size()) {
        m_masterTests.swap(row, row-1);
        updateMasterTests();
        ui->treeMasterTests->setCurrentIndex(ui->treeMasterTests->indexAbove(idx));
    }
}

/******************************************************************/

void MasterTestsEditWidget::on_btnMasterTestDown_clicked()
{
    QModelIndex idx = ui->treeMasterTests->currentIndex();
    int row = idx.isValid() ? idx.row()+1 : 0;
    if (row > 0 && row < m_masterTests.size()) {
        m_masterTests.swap(row, row-1);
        updateMasterTests();
        ui->treeMasterTests->setCurrentIndex(ui->treeMasterTests->indexBelow(idx));
    }
}

/******************************************************************/

void MasterTestsEditWidget::on_btnMasterTestAdd_clicked()
{
    AddMasterTestDlg dlg(m_root, this);
    if (dlg.exec() == QDialog::Accepted) {
        TTestPair master = dlg.getResult();
        if (master.first) {
            m_masterTests.append(master);
            updateMasterTests();
        }
    }
}

/******************************************************************/

void MasterTestsEditWidget::on_btnMasterTestDelete_clicked()
{
    QModelIndex idx = ui->treeMasterTests->currentIndex();
    if (idx.isValid()) {
        int row = idx.row();
        m_masterTests.removeAt(row);
        updateMasterTests();
        if (row > 0) {
            ui->treeMasterTests->setCurrentIndex(ui->treeMasterTests->indexAbove(idx));
        } else if (!m_masterTests.isEmpty()) {
            ui->treeMasterTests->setCurrentIndex(idx);
        }
    }
}

/******************************************************************/

void MasterTestsEditWidget::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    if (!current.isValid()) {
        ui->btnMasterTestDelete->setEnabled(false);
        return;
    }
    int row = current.row();
    ui->btnMasterTestUp->setEnabled( row > 0 );
    ui->btnMasterTestDown->setEnabled( row+1 < m_masterTests.count());
    ui->btnMasterTestDelete->setEnabled(true);
}

/******************************************************************/

void MasterTestsEditWidget::updateMasterTests()
{
    ui->treeMasterTests->clear();
    QList<QTreeWidgetItem *> items;
    foreach(const TTestPair &test, m_masterTests) {
        QStringList names;
        names << test.first->getName() << m_conditions.at(test.second);
        items.append(new QTreeWidgetItem(names));
    }
    ui->treeMasterTests->insertTopLevelItems(0,items);

}

/******************************************************************/

} // namespace SDPO

