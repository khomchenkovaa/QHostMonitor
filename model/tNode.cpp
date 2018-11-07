#include "tNode.h"
#include "tTest.h"
#include "tLink.h"
#include "utils.h"
#include <QDebug>
#include "gData.h"
#include "gSettings.h"

namespace SDPO {

/*************************************************/

TNode::TNode(const int id, const QString &name, const NodeType type, QObject *parent) :
    QObject(parent),
    m_ID(id),
    m_Name(name),
    m_Type(type),
    m_parentNode(0)
{
    m_Path = QString();
    m_CreatedAt =  QDateTime::currentDateTime();
    m_ModifiedAt = QDateTime::currentDateTime();

    b_UseOwnColumnSettings = false;
    b_UseOwnColorSettings = false;
    b_UseOwnReportSettings = false;
    b_CheckingColorStatus = false;
}

/*************************************************/

TNode::~TNode()
{
    clearAll();
}

/*************************************************/

QString TNode::getCommentLine(int line) const
{
    QStringList commentLines = m_Comment.split(QRegExp("[\r\n]"));
    return (line < commentLines.size()) ? commentLines.at(line) : QString();
}

/*************************************************/

void TNode::appendChild(TNode *child)
{
    child->m_parentNode = this;
    switch(child->m_Type) {
        case ROOT:
            break;
        case FOLDER:
        case VIEW:
            m_childNodes.append(child);
            child->m_Path = this->m_Path + QString(PATH_DELIMITER) + child->m_Name;
            break;
        default: // TEST, LINK
            m_childTests.append(child);
            child->m_Path = this->m_Path;
            break;
    }
}

/*************************************************/

void TNode::removeChild(TNode *child)
{
    switch(child->m_Type) {
    case ROOT: break;
    case FOLDER: m_childNodes.removeOne(child); break;
    case VIEW: m_childNodes.removeOne(child); break;
    default: m_childTests.removeOne(child); break;
    }
    delete child;
}

/*************************************************/

void TNode::clearTests()
{
    qDeleteAll(m_childTests);
    m_childTests.clear();
}

/*************************************************/

void TNode::clearAll()
{
    clearTests();
    qDeleteAll(m_childNodes);
    m_childNodes.clear();
}

/*************************************************/

TNode *TNode::child(int idx, bool withTests)
{
    if (idx < 0) {
        return 0;
    }
    if (idx < m_childNodes.count()) {
        return m_childNodes.value(idx);
    }
    if (withTests && idx < (m_childTests.count() + m_childNodes.count())) {
        return m_childTests.value(idx - m_childNodes.count());
    }
    return 0;
}

/*************************************************/

TNode *TNode::test(int idx)
{
    if (idx < 0) {
        return 0;
    }
    if (idx < m_childTests.count()) {
        return m_childTests.value(idx);
    }
    return 0;
}

/*************************************************/

TNode *TNode::lastChild()
{
    if (m_childNodes.count()) {
        return m_childNodes.value(m_childNodes.count()-1);
    }
    return 0;
}

/*************************************************/

TNode *TNode::findChild(QString nm)
{
    foreach(TNode *node , m_childNodes) {
        if (node->getName() == nm) return node;
    }
    return 0;
}

/*************************************************/

TNode *TNode::findChildRecursive(QString nm)
{
    if (m_Name == nm) return this;
    foreach(TNode *node , m_childNodes) {
        TNode *found = node->findChildRecursive(nm);
        if (found) return found;
    }
    return 0;
}

/*************************************************/

TNode *TNode::findByID(int id)
{
    if(m_ID == id) return this;
    foreach(TNode *node , m_childNodes) {
        TNode *found = node->findByID(id);
        if (found) return found;
    }
    return 0;
}

/*************************************************/

TNode *TNode::findTest(QString nm)
{
    foreach(TNode *node , m_childTests) {
        if (node->getType() == TNode::TEST && node->getName() == nm) {
            return node;
        }
    }
    foreach(TNode *node , m_childNodes) {
        TNode *test = node->findTest(nm);
        if (test) return test;
    }
    return 0;

}

/*************************************************/

int TNode::childCount(bool withTests) const
{
    if (withTests) {
        return m_childNodes.count() + m_childTests.count();
    }
    return m_childNodes.count();
}

/*************************************************/

int TNode::foldersTotal() const
{
    int total = 0;
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            total += (node->foldersTotal() + 1);
        }
    }
    return total;
}

/*************************************************/

int TNode::viewsTotal() const
{
    int total = 0;
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            total += node->viewsTotal();
        }
        if (node->getType() == TNode::VIEW) {
            total++;
        }
    }
    return total;
}

/*************************************************/

int TNode::testsCount() const
{
    return m_childTests.count();
}

/*************************************************/

bool TNode::hasTests() const
{
    if (m_childTests.count()) {
        return true;
    }
    foreach(TNode *node , m_childNodes) {
        if (node->hasTests()) {
            return true;
        }
    }
    return false;
}

/*************************************************/

bool TNode::isChildOf(TNode *node)
{
    bool result = false;
    TNode *item = this;
    while(item->parentNode()) {
        item = item->parentNode();
        if (item == node) {
            result = true;
            break;
        }
    }
    return result;
}

/*************************************************/

TLink *TNode::findLinkByTest(TTest *test)
{
    for (int i=0; i<m_childTests.count(); ++i) {
        if ( m_childTests.at(i)->getType() != TNode::LINK ) continue;
        TLink *link = qobject_cast<TLink *>(m_childTests.at(i));
        if (link->getTest()->getID() == test->getID()) {
            return link;
        }
    }
    return 0;
}

/*************************************************/

int TNode::row(bool withTests) const
{
    if (m_parentNode) {
        int idx = m_parentNode->m_childNodes.indexOf(const_cast<TNode*>(this));
        if (withTests && idx==-1) {
            idx = m_parentNode->m_childTests.indexOf(const_cast<TNode*>(this));
        }
        if (idx == -1) {
            idx = 0;
        }
        return idx;
    }
    return 0;
}

/*************************************************/

TNode *TNode::parentNode()
{
    return m_parentNode;
}

/*************************************************/

TNode *TNode::getRoot()
{
    if (getType() == ROOT) {
        return this;
    } else {
        return m_parentNode->getRoot();
    }
}

/*************************************************/

QVariant TNode::property(QString name) const
{
    return QObject::property(name.toLatin1());
}

/*************************************************/

QVariant TNode::getGlobal(Macro::Variable globalVar) const
{
    if (globalVar == Macro::TestName) {
        return m_Path;
    }
    return QVariant();
}

/*************************************************/

QColumnList TNode::getColumns()
{
    QColumnList result;
    if (b_UseOwnColumnSettings) {
        result = m_columns;
    } else {
        if (m_parentNode->getType() == TNode::FOLDER) {
            result = m_parentNode->getColumns();
        } else { // Root
            foreach (const GUserProfile &profile, GData::userProfiles) {
                if (profile.id == GData::currentUser ) {
                    result.append(profile.columns);
                }
            }
        }
    }
    return result;
}

/*************************************************/

void TNode::setColumns(QColumnList columns)
{
    m_columns.clear();
    if (!b_UseOwnColumnSettings) {
        return;
    }
    m_columns.append(columns);
}

/*************************************************/

QSortPairList TNode::getSort()
{
    QSortPairList result;
    if (b_UseOwnColumnSettings) {
        result = m_sort;
    } else {
        if (m_parentNode->getType() == TNode::FOLDER) {
            result = m_parentNode->getSort();
        } else { // Root
            foreach (const GUserProfile &profile, GData::userProfiles) {
                if (profile.id == GData::currentUser ) {
                    result.append(profile.sort);
                }
            }
        }
    }
    return result;
}

/*************************************************/

void TNode::setSort(QSortPairList sort)
{
    m_sort.clear();
    if (!b_UseOwnColumnSettings) {
        return;
    }
    m_sort.append(sort);
}

/*************************************************/

bool TNode::isRootFolder()
{
    return (m_parentNode->getType() == TNode::ROOT);
}

/*************************************************/

QString TNode::getColorScheme() const
{
    QString result;
    if (b_UseOwnColorSettings) {
        result = m_ColorScheme;
    } else {
        if (m_parentNode->getType() == TNode::FOLDER) {
            result = m_parentNode->getColorScheme();
        } else { // Root
            if (m_Name == ROOT_VIEW_NAME) { // Root View inherits from options
                QSettings s;
                result = s.value(SKEY_INTERFACE_DefaultLogPaletteID, "<Default>").toString();
            } else { // Root Folder inherits from profile
                foreach (const GUserProfile &profile, GData::userProfiles) {
                    if (profile.id == GData::currentUser ) {
                        result = profile.colorScheme;
                        break;
                    }
                }
            }
        }
    }
    return result;
}

/*************************************************/

void TNode::setColorScheme(const QString &value)
{
    if (b_UseOwnColorSettings) {
        m_ColorScheme = value;
    } else {
        m_ColorScheme.clear();
    }
}

/*************************************************/

} // namespace SDPO
