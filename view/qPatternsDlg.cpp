#include "qPatternsDlg.h"
#include "ui_qPatternsDlg.h"

namespace SDPO {

/*****************************************************************/

PatternsDlg::PatternsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatternsDlg)
{
    ui->setupUi(this);
    ui->tablePatterns->setModel(new PatternsTableModel(this));
    ui->tablePatterns->resizeColumnsToContents();
}

/*****************************************************************/

PatternsDlg::~PatternsDlg()
{
    delete ui;
}

/*****************************************************************/

PatternsTableModel::PatternsTableModel(QWidget *parent) :
    QAbstractTableModel(parent)
{
    m_header << "Active" << "Testname template" << "Comment template";
}

/*****************************************************************/

int PatternsTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return TestMethod::metaInfo.count();
}

/*****************************************************************/

int PatternsTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

/*****************************************************************/

QVariant PatternsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= TestMethod::metaInfo.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        TestMethodMetaInfo method = TestMethod::metaInfo.at(index.row());
        switch(index.column()) {
        case 0: return method.active ? "yes" : "no";
        case 1: return method.namePattern;
        case 2: return method.commentPattern;
        }
    }
    return QVariant();
}

/*****************************************************************/

bool PatternsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        TestMethodMetaInfo method = TestMethod::metaInfo.at(index.row());
        switch (index.column()) {
        case 0: method.active = (value.toString() == "yes"); break;
        case 1: method.namePattern = value.toString(); break;
        case 2: method.commentPattern = value.toString(); break;
        }
        TestMethod::metaInfo.replace(index.row(), method);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

/*****************************************************************/

QVariant PatternsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            return m_header.at(section);
        } else {
            TestMethodMetaInfo method = TestMethod::metaInfo.at(section);
            return method.title;
        }
    }
    return QVariant();
}

/*****************************************************************/

Qt::ItemFlags PatternsTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

/*****************************************************************/

} // namespace SDPO
