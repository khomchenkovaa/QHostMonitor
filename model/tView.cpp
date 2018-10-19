#include "tView.h"
#include "tRoot.h"
#include "global/gMacroTranslator.h"

#include <QScriptEngine>
#include <QDebug>

namespace SDPO {

/***********************************************/

TView::TView(const QString &name, TFolder *folder, QObject *parent) :
    TNode(name, TNode::VIEW, parent),
    m_folder(folder)
{
    b_Recursive = true;
    setupCriteriaDefaults();
    updateList();
    setupListeners();
}

/***********************************************/

TView::~TView()
{
    m_childTests.clear();
}

/***********************************************/

void TView::setupCriteriaDefaults()
{
    b_SelectByStatus = false;
    b_SelectByTestMethod = false;
    b_SelectByStats = false;
    b_SelectByTestName = false;
    b_SelectByComment = false;
    b_SelectByTarget = false;
    b_SelectByAgent = false;
    b_SelectUsingExpression = false;
    a_StatsCriteria = VC_AliveRatio;
    a_AliveRatioValue = 0.0;
    a_DeadRatioValue = 0.0;
    a_UnknownRatioValue = 0.0;
    a_ReplyGTValue = 0.0;
    a_ReplyLTValue = 0.0;
    b_DurationGreater = true;
    a_DurationValue = 1;
}

/***********************************************/

void TView::setupListeners()
{
    if (!m_folder) return;
    TRoot *root = qobject_cast<TRoot*>(m_folder->getRoot());
    connect(root, SIGNAL(pasteTest(TNode*)),   this, SLOT(updateByCriteria(TNode*)));
    connect(root, SIGNAL(delTest(TNode*)),     this, SLOT(updateByCriteria(TNode*)));
    connect(root, SIGNAL(cutTest(TNode*)),     this, SLOT(updateByCriteria(TNode*)));
    connect(root, SIGNAL(testUpdated(TNode*)), this, SLOT(updateByCriteria(TNode*)));
}

/***********************************************/

bool TView::checkStatusCriteria(TTest *test)
{
    foreach(VStatus check, m_StatusCriteria) {
        switch(check) {
        case VS_Good:
            if (test->simpleStatusID() == SimpleStatusID::UP) return true;
            break;
        case VS_BadNew:
            if (test->simpleStatusID() == SimpleStatusID::DOWN && !(test->isAcknowledged())) return true;
            break;
        case VS_BadAcknowleged:
            if (test->simpleStatusID() == SimpleStatusID::DOWN && test->isAcknowledged()) return true;
            break;
        case VS_UnknownNew:
            if (test->simpleStatusID() == SimpleStatusID::UNKNOWN && !(test->isAcknowledged())) return true;
            break;
        case VS_UnknownAcknowleged:
            if (test->simpleStatusID() == SimpleStatusID::UNKNOWN && test->isAcknowledged()) return true;
            break;
        case VS_WaitForMaster:
            if (test->getStatusID() == TestStatus::WaitForMaster) return true;
            break;
        case VS_OutOfSchedule:
            if (test->getStatusID() == TestStatus::OutOfSchedule) return true;
            break;
        case VS_NotTestedYet:
            if (test->getStatusID() == TestStatus::NotTested) return true;
            break;
        case VS_Disabled:
            if (test->getStatusID() == TestStatus::Disabled) return true;
            break;
        case VS_WarningNew:
            if (test->simpleStatusID() == SimpleStatusID::WARNING && !(test->isAcknowledged())) return true;
            break;
        case VS_WarningAcknowleged:
            if (test->simpleStatusID() == SimpleStatusID::WARNING && test->isAcknowledged()) return true;
            break;
        }
    }
    return false;
}

/***********************************************/

bool TView::checkTestMethodCriteria(TTest *test)
{
    foreach(TMethodID methodID, m_MethodCriteria) {
        if (methodID == test->methodId()) {
            return true;
        }
    }
    return false;
}

/***********************************************/

bool TView::checkStatsCritetia(TTest *test)
{
    switch(a_StatsCriteria) {
    case VC_AliveRatio:
        if (test->getAliveRatio() > a_AliveRatioValue) return true;
        break;
    case VC_DeadRatio:
        if (test->getDeadRatio() > a_DeadRatioValue) return true;
        break;
    case VC_UnknownRatio:
        if (test->getUnknownRatio() > a_UnknownRatioValue) return true;
        break;
    case VC_ReplyGT:
        if (test->getReplyNumber() > a_ReplyGTValue) return true;
        break;
    case VC_ReplyLT:
        if (test->getReplyNumber() < a_ReplyLTValue) return true;
        break;
    case VC_Duration:
        if (b_DurationGreater) {
            if(test->getCurrentStatusDurationSec() > (a_DurationValue * 60)) return true;
        } else {
            if(test->getCurrentStatusDurationSec() < (a_DurationValue * 60)) return true;
        }
        break;
    }
    return false;
}

/***********************************************/

bool TView::checkExpression(TTest *test)
{
    GMacroTranslator translator(a_ExpressionValue, test);
    QString script = translator.translate();
    QScriptEngine scriptEngine;
    QScriptValue value = scriptEngine.evaluate(script);
    if (value.isBool() && value.toBool()) {
        return true;
    }
    return false;
}

/***********************************************/

void TView::updateByCriteria(TNode *item)
{
    if (item->getType() != TNode::TEST) {
        return;
    }
    TTest *test = qobject_cast<TTest*>(item);
    bool inList = test->isChildOf(m_folder);
    if (b_SelectByStatus) {
        inList &= checkStatusCriteria(test);
    }
    if (b_SelectByTestMethod) {
        inList &= checkTestMethodCriteria(test);
    }
    if (b_SelectByStats) {
        inList &= checkStatsCritetia(test);
    }
    if (b_SelectByTestName) {
        inList &= test->testName().contains(a_TestNameValue, Qt::CaseInsensitive);
    }
    if (b_SelectByComment) {
        inList &= test->getComment().contains(a_TestNameValue, Qt::CaseInsensitive);
    }
    if (b_SelectByTarget) {
        qDebug() << "TODO(tView) : checkByTarget - Not implemented";
    }
    if (b_SelectByAgent) {
        qDebug() << "TODO(tView) : checkByAgent - Not implemented";
    }
    if (b_SelectUsingExpression) {
        inList &= checkExpression(test);
    }

    if (inList) {
        if (!m_childTests.contains(item)) {
            m_childTests.append(item);
        }
    } else {
        if (m_childTests.contains(item)) {
            m_childTests.removeOne(item);
        }
    }
}

/***********************************************/

void TView::updateList()
{
    m_childTests.clear();
    if (!m_folder) return;
    foreach(TNode *item, m_folder->testList()) {
        if (item->getType() != TNode::TEST) continue;
        updateByCriteria(item);
    }
}

/***********************************************/

QVariant TView::property(QString name) const
{
    if (name == "TestName") {
        return getPath();
    }
    return QObject::property(name.toLatin1());
}

/***********************************************/

} // namespace SDPO
