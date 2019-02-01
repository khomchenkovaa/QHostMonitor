#include "qLinksList.h"
#include "ui_qLinksList.h"
#include "tTest.h"
#include <QtWidgets>

namespace SDPO {

/******************************************************************/

LinksList::LinksList(TTest *test, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinksList),
    m_test(test),
    m_result(Result::DoNothing)
{
    ui->setupUi(this);
    ui->editTestName->setText(m_test->testName());
    ui->editTestMethod->setText(m_test->testMethod());
    ui->editParentFolder->setText(m_test->getPath());
    if (m_test->linkCount() > 0) {
        ui->groupBox->setTitle(tr("There is %1 link(s) to the test, located in the following folder(s)").arg(m_test->linkCount()));
        QList<TNode*> links = m_test->links();
        for (int i=0; i<links.count(); ++i) {
            QListWidgetItem *item = new QListWidgetItem(links.at(i)->getPath());
            item->setCheckState(Qt::Unchecked);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            ui->listLinks->addItem(item);
        }
    } else {
        ui->groupBox->setTitle(tr("There is no links to the test"));
    }
}

/******************************************************************/

LinksList::~LinksList()
{
    delete ui;
}

/******************************************************************/

QStringList LinksList::getChecked() const
{
    QStringList result;
    for(int i=0; i<ui->listLinks->count(); ++i) {
        if (ui->listLinks->item(i)->checkState() == Qt::Checked) {
            result.append(ui->listLinks->item(i)->text());
        }
    }
    return result;
}

/******************************************************************/

LinksList::Result LinksList::getResult() const
{
    return m_result;
}

/******************************************************************/

void LinksList::setReadOnly()
{
    ui->btnRemoveLinks->setVisible(false);
    ui->btnRemoveTest->setVisible(false);
}

/******************************************************************/

void LinksList::on_btnRemoveLinks_clicked()
{
    bool itemChecked = false;
    for(int i=0; i<ui->listLinks->count(); ++i) {
        if (ui->listLinks->item(i)->checkState() == Qt::Checked) {
            itemChecked = true;
            break;
        }
    }
    if (!itemChecked) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("No links are selected"),
                             QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    m_result = Result::RemoveLinks;
    this->accept();
}

/******************************************************************/

void LinksList::on_btnRemoveTest_clicked()
{
    int ret = QMessageBox::question(this,tr("Confirm"),
                                    tr("Remove %1 link(s) and the test?").arg(m_test->linkCount()),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::Yes);
    if (ret == QMessageBox::Yes) {
        m_result = Result::RemoveTest;
        this->accept();
    }
}

/******************************************************************/

} // namespace SDPO

