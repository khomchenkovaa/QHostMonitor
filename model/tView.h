#ifndef TVIEW_H
#define TVIEW_H

#include "tFolder.h"
#include "tTest.h"
#include "global/tMethod.h"

namespace SDPO {

class TView : public TNode
{
    Q_OBJECT

    TFolder *m_folder;

    BOOL_PROPERTY(Recursive)

    BOOL_PROPERTY(SelectByStatus)
    BOOL_PROPERTY(SelectByTestMethod)
    BOOL_PROPERTY(SelectByStats)
    BOOL_PROPERTY(SelectByTestName)
    BOOL_PROPERTY(SelectByComment)
    BOOL_PROPERTY(SelectByTarget)
    BOOL_PROPERTY(SelectByAgent)
    BOOL_PROPERTY(SelectUsingExpression)

public:
    enum VStatus { VS_Good, VS_BadNew, VS_BadAcknowleged, VS_UnknownNew, VS_UnknownAcknowleged, VS_WaitForMaster,
                   VS_OutOfSchedule, VS_NotTestedYet, VS_Disabled, VS_WarningNew, VS_WarningAcknowleged };
    Q_ENUM(VStatus)

    enum VCriteria { VC_AliveRatio, VC_DeadRatio, VC_UnknownRatio, VC_ReplyGT, VC_ReplyLT, VC_Duration };
    Q_ENUM(VCriteria)

    explicit TView(const QString &name, TFolder* folder, QObject *parent = 0);
    ~TView();

private: // properties
    QList<VStatus> m_StatusCriteria;
    QList<TMethodID> m_MethodCriteria;
    AUTO_PROPERTY(VCriteria, StatsCriteria)
    AUTO_PROPERTY(double, AliveRatioValue)
    AUTO_PROPERTY(double, DeadRatioValue)
    AUTO_PROPERTY(double, UnknownRatioValue)
    AUTO_PROPERTY(double, ReplyGTValue)
    AUTO_PROPERTY(double, ReplyLTValue)
    BOOL_PROPERTY(DurationGreater)
    AUTO_PROPERTY(int, DurationValue)
    AUTO_PROPERTY(QString, TestNameValue)
    AUTO_PROPERTY(QString, CommentValue)
    AUTO_PROPERTY(QString, TargetValue)
    AUTO_PROPERTY(QString, AgentValue)
    AUTO_PROPERTY(QString, ExpressionValue)

public: // properties
    QList<VStatus> getStatusCriteria() { return m_StatusCriteria; }
    void clearStatusCriteria() { m_StatusCriteria.clear(); }
    void addStatusCriteria(VStatus value) { m_StatusCriteria.append(value); }
    QList<TMethodID> getMethodCriteria() { return m_MethodCriteria; }
    void clearMethodCriteria() { m_MethodCriteria.clear(); }
    void addMethodCriteria(TMethodID value) { m_MethodCriteria.append(value); }

private:
    void setupCriteriaDefaults();
    void setupListeners();
    bool checkStatusCriteria(TTest *test);
    bool checkTestMethodCriteria(TTest *test);
    bool checkStatsCritetia(TTest *test);
    bool checkExpression(TTest *test);

public slots:
    void updateByCriteria(TNode* item);
    void updateList();

public: // methods
    TFolder* getSourceFolder() { return m_folder; }
    void setSourceFolder(TFolder *folder) { m_folder = folder; }

    QVariant property(QString name) const Q_DECL_OVERRIDE;

};

} // namespace SDPO

#endif // TVIEW_H
