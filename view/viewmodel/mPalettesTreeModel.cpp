#include "mPalettesTreeModel.h"

namespace SDPO {

/******************************************************************/

PalettesTreeModel::PalettesTreeModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    fillData();
}

/******************************************************************/

int PalettesTreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 14;
}

/******************************************************************/

int PalettesTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

/******************************************************************/

QVariant PalettesTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_data.size() || index.row() < 0)
        return QVariant();

    if (index.column() >= 4 || index.column() < 0)
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return m_data.at(index.row()).at(index.column());
    case Qt::BackgroundRole:
        return QVariant(getColor(index.row(),1));
    case Qt::TextColorRole:
        return QVariant(getColor(index.row(),0));
    case Qt::ToolTipRole:
        return m_hint.at(index.row());
    default:
        return QVariant();
    }
}

/******************************************************************/

QVariant PalettesTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    return QVariant();
}

/******************************************************************/

Qt::ItemFlags PalettesTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEnabled;
}

/******************************************************************/

void PalettesTreeModel::setProfile(const GColorProfile profile)
{
    m_profile = profile;
}

/******************************************************************/

void PalettesTreeModel::fillData()
{
    m_hint << "Report table header" << "Folder"
           << "Item not tested yet" << "Records with good status"
           << "User defined 'normal' status" << "User defined 'warning' status"
           << "Records with bad status" << "Acknowledged bad/unknown records"
           << "Program cannot retrieve information from this host" << "System messages"
           << "Test in progress" << "Disabled items"
           << "Item awaiting master test result" << "Out of schedule";
    QStringList header;
    header << "Host" << "Status" << "Reply" << "Comment";
    QStringList folder;
    folder << "/USA Branch/" << QString() << QString() << QString();
    QStringList notTested;
    notTested << "www.sniip.ru" << "Not tested" << "198 ms" << "test by TCP connect on port";
    QStringList ok;
    ok << "www.yahoo.com" << "Ok" << "213 ms" << "test by URL request";
    QStringList normal;
    normal << "Backup SQL C:/" << "Normal" << "25GB" << "Drive Free Space";
    QStringList warning;
    warning << "Backup SQL" << "Warning" << "80 %" << "CPU Usage";
    QStringList noAnswer;
    noAnswer << "205.43.122.1" << "No answer" << QString() << "NGTH ftp server";
    QStringList acknowleged;
    acknowleged << "205.43.122.1" << "Acknowleged" << QString() << "NGTH ftp server";
    QStringList unknown;
    unknown << "CPU usage" << "Unknown" << QString() << "Web";
    QStringList stop;
    stop << "System message" << "Stop" << QString() << QString();
    QStringList checking;
    checking << "www.mstb.com" << "Checking..." << QString() << "Web";
    QStringList disabled;
    disabled << "Interbase" << "Disabled" << QString() << QString();
    QStringList waitForMaster;
    waitForMaster << "www.mstb.com" << "Wait for master" << QString() << "Web";
    QStringList outOfSchedule;
    outOfSchedule << "www.mstb.com" << "Out of schedule" << QString() << "Web";
    m_data << header << folder << notTested << ok
           << normal << warning << noAnswer << acknowleged
           << unknown << stop << checking << disabled
           << waitForMaster << outOfSchedule;
}

/******************************************************************/

QColor PalettesTreeModel::getColor(const int row, const int idx) const
{
    switch(row) {
    case 0: return m_profile.header.at(idx);
    case 1: return m_profile.folder.at(idx);
    case 2: return m_profile.testNotTested.at(idx);
    case 3: return m_profile.testOk.at(idx);
    case 4: return m_profile.testNormal.at(idx);
    case 5: return m_profile.testWarning.at(idx);
    case 6: return m_profile.testBad.at(idx);
    case 7: return m_profile.testAcknowledged.at(idx);
    case 8: return m_profile.testUnknown.at(idx);
    case 9: return m_profile.message.at(idx);
    case 10: return m_profile.testChecking.at(idx);
    case 11: return m_profile.testDisabled.at(idx);
    case 12: return m_profile.testWaitForMaster.at(idx);
    case 13: return m_profile.testOutOfSchedule.at(idx);
    case 14: return m_profile.htmlText.at(idx);
    case 15: return m_profile.links.at(idx);
    case 16: return m_profile.linkVisited.at(idx);
    case 17: return m_profile.linkActive.at(idx);
    default: return m_profile.htmlText.at(idx);
    }
}

/******************************************************************/

GColorProfile PalettesTreeModel::setColor(const int row, const int idx, const QColor color)
{
    QList<QColor> value;
    if (idx) {
        value << getColor(row, 0) << color;
    } else {
        value << color << getColor(row, 1);
    }
    switch (row) {
    case 0: m_profile.header = value; break;
    case 1: m_profile.folder = value; break;
    case 2: m_profile.testNotTested = value; break;
    case 3: m_profile.testOk = value; break;
    case 4: m_profile.testNormal = value; break;
    case 5: m_profile.testWarning = value; break;
    case 6: m_profile.testBad = value; break;
    case 7: m_profile.testAcknowledged = value; break;
    case 8: m_profile.testUnknown = value; break;
    case 9: m_profile.message = value; break;
    case 10: m_profile.testChecking = value; break;
    case 11: m_profile.testDisabled = value; break;
    case 12: m_profile.testWaitForMaster = value; break;
    case 13: m_profile.testOutOfSchedule = value; break;
    case 14: m_profile.htmlText = value; break;
    case 15: m_profile.links = value; break;
    case 16: m_profile.linkVisited = value; break;
    case 17: m_profile.linkActive = value; break;
    default: m_profile.htmlText = value; break;
    }
    if (row <= 13) {
        emit dataChanged(index(row,0),index(row,3));
    }
    return m_profile;
}

/******************************************************************/

} // namespace SDPO
