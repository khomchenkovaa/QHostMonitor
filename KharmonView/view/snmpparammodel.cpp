#include "snmpparammodel.h"

using namespace KharmonView;

/*****************************************************************/

SnmpParamModel::SnmpParamModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_Object(Q_NULLPTR)
    , m_Idx(0)
{
    m_Header
        << "Name"
        << "Desc"
        << "Curr Value"
        << "Curr Value Desc"
        << "Type"
        << "Data Type"
        << "Units"
        << "Status"
        << "Last Change Date"
        << "Normal Value"
        << "Low Fail Limit"
        << "Low Warning Limit"
        << "High Fail Limit"
        << "high Warning Limit"
        << "Module Index";
}

/*****************************************************************/

QVariant SnmpParamModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_Header.at(section);
}

/*****************************************************************/

QModelIndex SnmpParamModel::index(int row, int column, const QModelIndex &parent) const
{
    if (m_Object == Q_NULLPTR) {
        return QModelIndex();
    }

    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (parent.isValid()) {
        return QModelIndex();
    }

    return createIndex(row, column);
}

/*****************************************************************/

QModelIndex SnmpParamModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

/*****************************************************************/

int SnmpParamModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    if (m_Object == Q_NULLPTR) {
        return 0;
    }

    int size = 0;
    foreach(const SnmpParameter &param, *(m_Object->snmpParamList())) {
        if (param.paramModuleIndex == m_Idx) size++;
    }

    return size;
}

/*****************************************************************/

int SnmpParamModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_Header.count();
}

/*****************************************************************/

QVariant SnmpParamModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (m_Object == Q_NULLPTR) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    int row = -1;
    int cnt = 0;
    for(int i=0; i < m_Object->snmpParamList()->size(); ++i) {
        SnmpParameter param = m_Object->snmpParamList()->at(i);
        if (param.paramModuleIndex == m_Idx) {
            if (cnt == index.row()) {
                row = i;
                break;
            }
            cnt++;
        }
    }

    SnmpParameter param = m_Object->snmpParamList()->at(row);

    switch (index.column()) {
    case 0: return param.paramName; break;
    case 1: return param.paramDesc; break;
    case 2: return param.paramCurrValue; break;
    case 3: return param.paramCurrValueDesc; break;
    case 4: return param.paramType; break;
    case 5: return param.paramDataType; break;
    case 6: return param.paramUnits; break;
    case 7: return param.paramStatus; break;
    case 8: return param.paramLastChangeDate; break;
    case 9: return param.paramNormalValue; break;
    case 10: return param.paramLowFailLimit; break;
    case 11: return param.paramLowWarningLimit; break;
    case 12: return param.paramHighFailLimit; break;
    case 13: return param.paramHighWarningLimit; break;
    case 14: return QString::number(param.paramModuleIndex); break;
    }

    return QVariant();
}

/*****************************************************************/

void SnmpParamModel::setObject(SnmpObject *snmpObject, int moduleIdx)
{
    beginResetModel();
    m_Object = snmpObject;
    m_Idx = moduleIdx;
    endResetModel();
}

/*****************************************************************/
