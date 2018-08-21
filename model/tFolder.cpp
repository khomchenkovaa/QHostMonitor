#include "tFolder.h"
#include "tTest.h"
#include "gData.h"

namespace SDPO {

/*************************************************/

TFolder::TFolder(const QString &name, QObject *parent) :
    TNode(name, TNode::FOLDER, parent)
{
    b_UseOwnRegionalSettings = false;
    b_ApplyRemoteTimeToGui = false;
    b_ApplyRemoteTimeToSchedules = false;
}

/*************************************************/

int TFolder::testsTotal() const
{
    int total = 0;
    foreach(TNode *node , m_childTests) { // without links
        if (node->getType() == TNode::TEST) {
            total++;
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsGood() const
{
    int total = 0;
    foreach(TNode *node , m_childTests) { // without links
        if (node->getType() == TNode::TEST) {
            TTest *test = qobject_cast<TTest*>(node);
            if (test->simpleStatusID() == SimpleStatusID::UP) {
                total++;
            }
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsBad() const
{
    int total = 0;
    foreach(TNode *node , m_childTests) { // without links
        if (node->getType() == TNode::TEST) {
            TTest *test = qobject_cast<TTest*>(node);
            if (test->simpleStatusID() == SimpleStatusID::DOWN) {
                total++;
            }
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsUnknown() const
{
    int total = 0;
    foreach(TNode *node , m_childTests) { // without links
        if (node->getType() == TNode::TEST) {
            TTest *test = qobject_cast<TTest*>(node);
            if (test->simpleStatusID() == SimpleStatusID::UNKNOWN) {
                total++;
            }
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsWarning() const
{
    int total = 0;
    foreach(TNode *node , m_childTests) { // without links
        if (node->getType() == TNode::TEST) {
            TTest *test = qobject_cast<TTest*>(node);
            if (test->simpleStatusID() == SimpleStatusID::WARNING) {
                total++;
            }
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsBadAcknowleged() const
{
    return 0; //! TODO
}

/*************************************************/

int TFolder::testsUnknownAcknowkeged() const
{
    return 0; //! TODO
}

/*************************************************/

int TFolder::testsWarningAcknowkeged() const
{
    return 0; //! TODO
}

/*************************************************/

int TFolder::testsTotalRecursive() const
{
    int total = testsTotal();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsTotalRecursive();
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsGoodRecursive() const
{
    int total = testsGood();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsGoodRecursive();
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsBadRecursive() const
{
    int total = testsBad();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsBadRecursive();
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsUnknownRecursive() const
{
    int total = testsUnknown();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsUnknownRecursive();
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsWarningRecursive() const
{
    int total = testsWarning();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsWarningRecursive();
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsBadAcknowlegedRecursive() const
{
    int total = testsBadAcknowleged();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsBadAcknowlegedRecursive();
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsUnknownAcknowkegedRecursive() const
{
    int total = testsUnknownAcknowkeged();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsUnknownAcknowkegedRecursive();
        }
    }
    return total;
}

/*************************************************/

int TFolder::testsWarningAcknowkegedRecursive() const
{
    int total = testsWarningAcknowkeged();
    foreach(TNode *node , m_childNodes) {
        if (node->getType() == TNode::FOLDER) {
            TFolder *folder = qobject_cast<TFolder*>(node);
            total += folder->testsWarningAcknowkegedRecursive();
        }
    }
    return total;
}

/*************************************************/

QVariant TFolder::property(QString name) const
{
    if (name.startsWith("FCommentLine")) {
        int idx = name.mid(12).toInt();
        return getCommentLine(idx);
    } else if (name == "TestName") {
        return getPath();
    }
    return QObject::property(name.toLatin1());
}

/*************************************************/

bool TFolder::isApplyRemoteTimeToGui() const
{
    if (!b_UseOwnRegionalSettings && (m_parentNode->getType() == TNode::FOLDER)) {
        TFolder *parent = qobject_cast<TFolder*>(m_parentNode);
        return parent->isApplyRemoteTimeToGui();
    }
    return b_ApplyRemoteTimeToGui;
}

/*************************************************/

void TFolder::setApplyRemoteTimeToGui(const bool value)
{
    if (!b_UseOwnRegionalSettings && (m_parentNode->getType() == TNode::FOLDER)) {
        b_ApplyRemoteTimeToGui = false;
    } else {
        b_ApplyRemoteTimeToGui = value;
    }
}

/*************************************************/

bool TFolder::isApplyRemoteTimeToSchedules() const
{
    if (!b_UseOwnRegionalSettings && (m_parentNode->getType() == TNode::FOLDER)) {
        TFolder *parent = qobject_cast<TFolder*>(m_parentNode);
        return parent->isApplyRemoteTimeToSchedules();
    }
    return b_ApplyRemoteTimeToSchedules;
}

/*************************************************/

void TFolder::setApplyRemoteTimeToSchedules(const bool value)
{
    if (!b_UseOwnRegionalSettings && (m_parentNode->getType() == TNode::FOLDER)) {
        b_ApplyRemoteTimeToSchedules = false;
    } else {
        b_ApplyRemoteTimeToSchedules = value;
    }
}

/*************************************************/

QString TFolder::getTimeZoneIanaId() const
{
    if (!b_UseOwnRegionalSettings && (m_parentNode->getType() == TNode::FOLDER)) {
        TFolder *parent = qobject_cast<TFolder*>(m_parentNode);
        return parent->getTimeZoneIanaId();
    }
    return m_TimeZoneIanaId;
}

/*************************************************/

void TFolder::setTimeZoneIanaId(const QString &value)
{
    if (!b_UseOwnRegionalSettings && (m_parentNode->getType() == TNode::FOLDER)) {
        m_TimeZoneIanaId.clear();
    } else {
        m_TimeZoneIanaId = value;
    }
}

/*************************************************/

} // namespace SDPO
