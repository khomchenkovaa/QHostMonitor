#include "mTestListModel.h"
#include "utils.h"
#include "tTest.h"
#include "tLink.h"
#include "tTestInfo.h"
#include "global/tMethod.h"
#include "gData.h"

namespace SDPO {

/******************************************************************/

TestListModel::TestListModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_recursive = true;
    m_current = 0;
    setProfile();
}

/******************************************************************/

TestListModel::~TestListModel()
{
    m_list.clear();
    Utils::DestructorMsg(this);
}

/******************************************************************/

int TestListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.count();
}

/******************************************************************/

int TestListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columns.size();
}

/******************************************************************/

QModelIndex TestListModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

/******************************************************************/

QVariant TestListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.column() >= m_columns.size() || index.column() < 0)
        return QVariant();

    if (index.row() >= m_list.size() || index.row() < 0)
        return QVariant();

    TNode *item = m_list.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return getColumn(item, index.column());
    case Qt::DecorationRole:
        if (index.column() == 0) {
            return getIcon(item);
        } else {
            return QVariant();
        }
    case Qt::BackgroundRole:
        return getBgColor(item);
    case Qt::TextColorRole:
        return getColor(item);
    default:
        return QVariant();
    }
}

/******************************************************************/

Qt::ItemFlags TestListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled;
}

/******************************************************************/

TNode *TestListModel::itemFromIndex(const QModelIndex &index)
{
    if (!index.isValid())
        return 0;

    return m_list.at(index.row());
}

/******************************************************************/

void TestListModel::setRecursive(const bool value)
{
    if (m_recursive != value) {
        m_recursive = value;
        resetModel();
    }
}

/******************************************************************/

void TestListModel::setCurrent(TNode *value)
{
    if (m_current != value) {
        m_current = value;
        resetModel();
    }
}

/******************************************************************/

void TestListModel::updateTest(TNode *test)
{
    int idx = m_list.indexOf(test);
    if (idx != -1) {
        emit dataChanged(index(idx,0), index(idx,m_columns.size()-1)) ;
    }
}

/******************************************************************/

void TestListModel::setProfile()
{
    m_columns.clear();
    m_colorProfile = GData::colorProfiles.at(1);
    QColumnList columns;
    QString colorScheme;
    if (m_current) {
        columns = m_current->getColumns();
        colorScheme = m_current->getColorScheme();
    } else {
        foreach (const GUserProfile &profile, GData::userProfiles) {
            if (profile.id == GData::currentUser ) {
                columns.append(profile.columns);
                colorScheme = profile.colorScheme;
                break;
            }
        }
    }
    foreach (const TLColumn &column, columns) {
        if (column.checked) {
            m_columns.append(column);
        }
    }
    foreach(const GColorProfile &clrProfile, GData::colorProfiles) {
        if (colorScheme == clrProfile.name) {
            m_colorProfile = clrProfile;
            break;
        }
    }
}

/******************************************************************/

void TestListModel::resetModel()
{
    beginResetModel();
    m_list.clear();
    if (m_current) {
        m_list.append(m_current);
        updateList(m_current);
    }
    setProfile();
    endResetModel();
}

/******************************************************************/

void TestListModel::updateList(TNode *item)
{
    m_list.append(item->tests());
    if (!m_recursive) {
        return;
    }
    foreach(TNode *node, item->folders()) {
        if (node->hasTests()) {
            m_list.append(node);
            updateList(node);
        }
    }
}

/******************************************************************/

QVariant TestListModel::headerData(int section, Qt::Orientation orientation, int role) const
{   
    if (section >= m_columns.size() || section < 0)
        return QVariant();

    if (orientation == Qt::Vertical)
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return m_columns.at(section).title;
    case Qt::BackgroundRole:
        return QVariant(m_colorProfile.header.at(1));
    case Qt::TextColorRole:
        return QVariant(m_colorProfile.header.at(0));
    }

    return QVariant();
}

/******************************************************************/

QVariant TestListModel::getIcon( TNode *item) const
{
    TTest* test;
    bool isTest = true;
    // folder has no statuses
    switch(item->getType()) {
    case TNode::FOLDER:
    case TNode::VIEW:
        return QIcon(":/img/folder.png");
    case TNode::LINK: {
        TLink* link = qobject_cast<TLink*>(item);
        test = link->getTest();
        isTest = false;
        } break;
    case TNode::TEST:
        test = qobject_cast<TTest*>(item);
        break;
    default:
        return QVariant();
    }

    // icon by status
    switch(test->statusID()) {
    case TestStatus::NotTested:
        return QIcon(isTest?":/img/status/tstNotTested.png":":/img/status/lnkNotTested.png");
    case TestStatus::HostAlive:
        return QIcon(isTest?":/img/status/tstHostAlive.png":":/img/status/lnkHostAlive.png");
    case TestStatus::NoAnswer:
        return QIcon(isTest?":/img/status/tstNoAnswer.png":":/img/status/lnkNoAnswer.png");
    case TestStatus::Unknown:
        return QIcon(isTest?":/img/status/tstUnknown.png":":/img/status/lnkUnknown.png");
    case TestStatus::UnknownHost:
        return QIcon(isTest?":/img/status/tstUnknownHost.png":":/img/status/lnkUnknownHost.png");
    case TestStatus::Checking:
        return QIcon(isTest?":/img/status/tstChecking.png":":/img/status/lnkChecking.png");
    case TestStatus::Resolving:
        return QIcon(isTest?":/img/status/tstResolving.png":":/img/status/lnkResolving.png");
    case TestStatus::Ok:
        return QIcon(isTest?":/img/status/tstOk.png":":/img/status/lnkOk.png");
    case TestStatus::Bad:
        return QIcon(isTest?":/img/status/tstBad.png":":/img/status/lnkBad.png");
    case TestStatus::Disabled:
        return QIcon(isTest?":/img/status/tstDisabled.png":":/img/status/lnkDisabled.png");
    case TestStatus::BadContents:
        return QIcon(isTest?":/img/status/tstBadContents.png":":/img/status/lnkBadContents.png");
    case TestStatus::WaitForMaster:
        return QIcon(isTest?":/img/status/tstWaitForMaster.png":":/img/status/lnkWaitForMaster.png");
    case TestStatus::OutOfSchedule:
        return QIcon(isTest?":/img/status/tstOutOfSchedule.png":":/img/status/lnkOutOfSchedule.png");
    case TestStatus::Paused:
        return QIcon(isTest?":/img/status/tstPaused.png":":/img/status/lnkPaused.png");
    case TestStatus::Warning:
        return QIcon(isTest?":/img/status/tstWarning.png":":/img/status/lnkWarning.png");
    case TestStatus::Normal:
        return QIcon(isTest?":/img/status/tstNormal.png":":/img/status/lnkNormal.png");
    }
    return QVariant();
}

/******************************************************************/

QVariant TestListModel::getColor(TNode *item) const
{
    TTest* test;
    // folder has no statuses
    switch(item->getType()) {
    case TNode::FOLDER:
    case TNode::VIEW:
        return QVariant(m_colorProfile.folder.at(0));
    case TNode::LINK: {
        TLink* link = qobject_cast<TLink*>(item);
        test = link->getTest();
        } break;
    case TNode::TEST:
        test = qobject_cast<TTest*>(item);
        break;
    default:
        return QVariant();
    }
    return QVariant(m_colorProfile.colorByStatus(test->statusID()));
}

/******************************************************************/

QVariant TestListModel::getBgColor(TNode *item) const
{
    TTest* test;
    // folder has no statuses
    switch(item->getType()) {
    case TNode::FOLDER:
    case TNode::VIEW:
        return QVariant(m_colorProfile.folder.at(1));
    case TNode::LINK: {
        TLink* link = qobject_cast<TLink*>(item);
        test = link->getTest();
        } break;
    case TNode::TEST:
        test = qobject_cast<TTest*>(item);
        break;
    default:
        return QVariant();
    }
    return QVariant(m_colorProfile.bgColorByStatus(test->statusID()));
}

/******************************************************************/

QVariant TestListModel::getColumn(TNode *item, int column) const
{
    QString macroVar = m_columns.at(column).macro;
    QString propName = macroVar.mid(1, macroVar.length()-2);
    return item->property(propName);
}

/******************************************************************/

void TestListModel::addTest(TNode *item)
{
    bool inList = false;
    TNode *node = item;
    while(node->parentNode()) {
        node = node->parentNode();
        if (m_list.contains(node)) {
            inList = true;
            break;
        }
    }

    if (inList) {
        resetModel();
    }
}

/******************************************************************/

void TestListModel::removeTest(TNode *item)
{
    int idx = m_list.indexOf(item);
    if (idx == -1) {
        return;
    }
    beginRemoveRows(QModelIndex(), idx, idx);
    m_list.removeAt(idx);
    endRemoveRows();

    TNode *folder = item->parentNode();
    if ( folder != m_current && !folder->hasTests() ) {
        removeTest(folder);
    }
}

/******************************************************************/

} // namespace SDPO


