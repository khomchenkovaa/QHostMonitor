#ifndef IOTEXTFILE_H
#define IOTEXTFILE_H

#include "tEnums.h"
#include "method/sdpoTestMethodConverters.h"

// Defaults (optional)
#define DEFAULT_SCHEDULE      "DefaultSchedule"
#define DEFAULT_ALERT_PROFILE "DefaultAlertProfile"
#define DEFAULT_INTERVAL      "DefaultInterval"
#define DEFAULT_COMMENT       "DefaultComment"
#define DEFAULT_FOLDER        "DefaultFolder"

// Special commands (optional)
#define CMD_IMPORT_MODE   "ImportMode"
#define CMD_CREATE_FOLDER "CreateFolder"

QT_BEGIN_NAMESPACE
class QTextStream;
QT_END_NAMESPACE

namespace SDPO {

class HMListService;
class TNode;
class TTest;

struct IOTextFileCmd {
    int line;
    QString command;
    QString key;
    QString value;

    IOTextFileCmd() {
        line = -1;
    }

    IOTextFileCmd(const QString &key, const QString &value) {
        line = -1;
        this->key = key;
        this->value = value;
        this->command = key + " = " + value;
    }

    IOTextFileCmd(int lineNum, QString &lineRecord) {
        line = lineNum;
        command = lineRecord;
        QStringList record = lineRecord.split("=");
        key = record.at(0).trimmed();
        value = record.at(1).trimmed();
    }
};

class IOTextFile : public QObject
{
    Q_OBJECT

public: // enums
    enum ImportMode { IM_ADD, IM_MODIFY, IM_REPLACE };
    Q_ENUM(ImportMode)

private:
    HMListService *m_HML;

    // defaults
    QString m_fileName;
    QString m_defaultSchedule;
    QString m_defaultAlertProfile;
    int     m_defaultInterval;
    QString m_defaultComment;
    QString m_defaultFolder;
    ImportMode m_ImportMode;

    // helpers
    TTest  *m_curTest;
    IOTestMethodConverter *m_curMethodConverter;
    QMap<QString,IOTextFileCmd> m_testProps;
    QStringList m_linkedTo;
    QStringList m_Breakers;
    QStringList m_ScheduleMode;
    int m_lineCnt;
    int m_foldersCnt;
    int m_testsAdded;
    int m_testsChanged;
    int m_errorsCnt;
    int m_warningsCnt;

    void addTest();
    void setTestProperties();
    void createLinks();
    IOTestMethodConverter *getConverter(TMethodID methodId);
    void writeFolder(QTextStream &out, TNode *parent);
    void writeTest(QTextStream &out, TTest *test);

public:    
    explicit IOTextFile(HMListService *hml, QString fileName, QObject *parent = 0);
    ~IOTextFile();

signals:
    void importMessage(QString message);
    void importMessageAppend(QString append);
    void importDone(int folders, int tests, int changed, int errors, int warnings);

public slots:
    bool validateImportTextFile(QString &errorMsg, int &foldersCnt, int &testsCnt);
    void importTextFile();
    bool exportTextFile(bool incFolder, bool incLinks, int expType);
};

} // namespace SDPO

#endif // IOTEXTFILE_H
