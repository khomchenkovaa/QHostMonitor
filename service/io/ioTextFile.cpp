#include "ioTextFile.h"

#include "utils.h"
#include "hmListService.h"
#include "gData.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

namespace SDPO {

/******************************************************************/

IOTextFile::IOTextFile(HMListService *hml, QString fileName, QObject *parent) :
    QObject(parent),
    m_HML(hml),
    m_fileName(fileName)
{
    // defaults
    m_defaultSchedule = QString();
    m_defaultAlertProfile = QString();
    m_defaultInterval = 300;
    m_defaultComment = QString();
    m_defaultFolder = ROOT_FOLDER_NAME;
    m_ImportMode = IM_ADD;
    // helpers
    m_curTest = 0;
    m_curMethodConverter = 0;
    m_Breakers << DEFAULT_SCHEDULE << DEFAULT_ALERT_PROFILE << DEFAULT_INTERVAL
               << DEFAULT_COMMENT << DEFAULT_FOLDER << CMD_IMPORT_MODE
               << CMD_CREATE_FOLDER << PRM_METHOD;
    m_ScheduleMode << "Regular" << "OneTestPerDay" << "OneTestPerWeek"
                   << "OneTestPerMonth" << "ByExpression";
}

/******************************************************************/

IOTextFile::~IOTextFile()
{
    Utils::DestructorMsg(this);
    if (m_curMethodConverter) {
        delete m_curMethodConverter;
        m_curMethodConverter = 0;
    }
}

/******************************************************************/

bool IOTextFile::validateImportTextFile(QString &errorMsg, int &foldersCnt, int &testsCnt)
{
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            errorMsg = "Can not open file for Read";
            return false;
    }

    QTextStream in(&file);
    QString line = ""; // not null

    while (!line.isNull()) {
        line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        if (line[0] == ';') continue;
        QStringList record = line.split("=");
        QString key = record.at(0).trimmed();
        if (key == DEFAULT_FOLDER) {
            foldersCnt++;
        } else if (key == PRM_METHOD) {
            testsCnt++;
        }
    }
    file.close();
    return true;
}

/******************************************************************/

void IOTextFile::importTextFile()
{
    m_lineCnt = 0;
    m_foldersCnt = 0;
    m_testsAdded = 0;
    m_testsChanged = 0;
    m_errorsCnt = 0;
    m_warningsCnt = 0;
    m_testProps.clear();
    m_linkedTo.clear();
    emit importMessage(tr("Opening input file \"%1\" ..").arg(m_fileName));
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit importMessageAppend(tr("Fail"));
        emit importMessage(tr("Error opening file \"%1\" ..").arg(m_fileName));
        ++m_errorsCnt;
        emit importDone(m_foldersCnt,m_testsAdded,m_testsChanged,m_errorsCnt,m_warningsCnt);
        return;
    }
    emit importMessageAppend(tr("Ok"));
    emit importMessage(tr("Reading"));

    QTextStream in(&file);
    QString line = ""; // not null
    while (!line.isNull()) {
        ++m_lineCnt;
        line = in.readLine().trimmed();
        // find valid command
        if (line.isEmpty()) continue;
        if (line[0] == ';') continue; // comments
        if (!line.contains("=")) {
            emit importMessage(tr("[Error] Line %1: Wrong format... Should be 'KEY = VALUE'").arg(m_lineCnt));
            ++m_errorsCnt;
            continue;
        }
        IOTextFileCmd cmd(m_lineCnt,line);
        // add previous test
        if (m_Breakers.contains(cmd.key, Qt::CaseInsensitive)) {
            if(m_testProps.keys().contains(PRM_METHOD)) {
                addTest();
            }
            m_testProps.clear();
            m_linkedTo.clear();
        }
        // set test's properties
        if (cmd.key == DEFAULT_SCHEDULE) {
            m_defaultSchedule = cmd.value;
        } else if (cmd.key == DEFAULT_ALERT_PROFILE) {
            m_defaultAlertProfile = cmd.value;
        } else if (cmd.key == DEFAULT_INTERVAL) {
            m_defaultInterval = cmd.value.toInt();
        } else if (cmd.key == DEFAULT_COMMENT) {
            m_defaultComment = cmd.value.replace("^M","\n");
        } else if (cmd.key == DEFAULT_FOLDER) {
            m_defaultFolder = cmd.value.replace("\\","/");
            ++m_foldersCnt;
        } else if (cmd.key == CMD_IMPORT_MODE) {
            if (!cmd.value.compare("Add",Qt::CaseInsensitive)) {
                m_ImportMode = IM_ADD;
            } else if (!cmd.value.compare("Modify",Qt::CaseInsensitive)) {
                m_ImportMode = IM_MODIFY;
            } else if (!cmd.value.compare("Replace",Qt::CaseInsensitive)) {
                m_ImportMode = IM_REPLACE;
            }
        } else if (cmd.key == CMD_CREATE_FOLDER) {
            QString path = cmd.value.replace("\\","/");
            m_HML->cmdCreateFolder(path);
        } else if (cmd.key == PRM_LINKED_TO) {
            m_linkedTo.append(cmd.value.replace("\\","/"));
        } else {
            // all other are test's properties
            m_testProps[cmd.key] = cmd;
        }
    }
    // add final test if properties exists
    if (m_testProps.keys().contains(PRM_METHOD)) {
        addTest();
    }
    emit importDone(m_foldersCnt,m_testsAdded,m_testsChanged,m_errorsCnt,m_warningsCnt);
    file.close();
}

/******************************************************************/

bool IOTextFile::exportTextFile(bool incFolder, bool incLinks, int expType)
{
    Q_UNUSED(incFolder)
    Q_UNUSED(incLinks)
    Q_UNUSED(expType)
    QFile file(m_fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

    QTextStream out(&file);
    out << ";-----------------------------------------------------------------------------" << endl;
    out << ";- HostMonitor`s export/import file" << endl;
    out << ";- Generated by SDPO at " << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss") << endl;
    out << ";- Source file: C:\\Program Files (x86)\\HostMonitor8\\Examples\\example1.hml" << endl;
    out << ";- Generation mode: All_Tests" << endl;
    out << ";-----------------------------------------------------------------------------" << endl;
    out << endl << endl;
    writeFolder(out, m_HML->rootFolder());
    file.flush();
    file.close();

    return true;
}

/******************************************************************/

void IOTextFile::writeFolder(QTextStream &out, TNode *parent) {
    m_defaultFolder = parent->getPath();
    QString folder = m_defaultFolder.replace("/","\\");
    folder = folder.mid(1);
    out << ";-----------------------------------------------------------------------------" << endl;
    out << "; Folder: " << folder << endl;
    out << ";-----------------------------------------------------------------------------" << endl;
    out << ";You may comment the following line to import tests into current folder" << endl;
    out << CMD_CREATE_FOLDER << QString(" = ") << folder << endl;
    out << DEFAULT_FOLDER << QString(" = ") << folder << endl;
    out << endl << endl;

    for (int i=0; i<parent->tests().count();++i) {
        TTest *test = qobject_cast<TTest*>(parent->tests().at(i));
        if (test) { // skip links
            writeTest(out, test);
        }
    }

    for (int i=0; i<parent->folders().count();++i) {
        TNode* node = parent->folders().at(i);
        writeFolder(out, node);
    }
}

/******************************************************************/

void IOTextFile::writeTest(QTextStream &out, TTest *test)
{
    QStringList logMode;
    logMode << "Default" << "brief" << "full" << "reply";
    out << "; ------- Test #" <<  test->getID() << "-------" << endl;
    out << endl << endl;
    out << PRM_METHOD         << " = " << TMethod::toName(test->methodId()) << endl;
    out << ";--- Common properties ---" << endl;
    out << ";" << PRM_DEST_FOLDER << " = " << test->getPath().replace("/","\\").mid(1) << endl;
    foreach (TNode *node, test->links()) {
        out << PRM_LINKED_TO  << " = " << node->getPath().replace("/","\\").mid(1) << endl;
    }
    out << PRM_TITLE          << " = " << test->getName()                          << endl;
    out << PRM_COMMENT        << " = " << test->getComment().replace("\n","^M")    << endl;
    out << PRM_RELATED_URL    << " = " << test->getRelatedURL()                    << endl;
    out << PRM_NAME_PATTERN   << " = " << test->method()->getNamePattern()           << endl;
    out << PRM_CMNT_PATTERN   << " = " << test->method()->getCommentPattern()        << endl;
    out << PRM_SCHEDULE_MODE  << " = " << m_ScheduleMode.at(test->scheduleMode())   << endl;
    out << PRM_SCHEDULE       << " = " << test->scheduleName()                     << endl;
    out << PRM_INTERVAL       << " = " << test->interval()                         << endl;
    out << PRM_ALERTS         << " = " << endl; //!TODO
    out << PRM_REVERSE_ALERT  << " = " << (test->isReverseAlert()?"Yes":"No")      << endl;
    out << PRM_UNKNOWN_IS_BAD << " = " << (test->isUnknownIsBad()?"Yes":"No")      << endl;
    out << PRM_WARNING_IS_BAD << " = " << (test->isWarningIsBad()?"Yes":"No")      << endl;
    out << PRM_USE_COMMON_LOG << " = " << (test->isUseCommonLog()?"Yes":"No")      << endl;
    out << PRM_PRIV_LOG_MODE  << " = " << logMode.at(test->getPrivateLogMode())    << endl;
    out << PRM_COM_LOG_MODE   << " = " << logMode.at(test->getCommonLogMode())     << endl;
    out << ";--- Test specific properties ---" << endl;
    if (getConverter(test->methodId())) {
        m_curMethodConverter->setTestMethod(test->method());
        m_curMethodConverter->exportTo(out);
    }
    out << endl << endl;
}

/******************************************************************/

void IOTextFile::addTest() {
    m_curTest = 0;
    // check required parameters
    IOTextFileCmd cmd = m_testProps.take(PRM_METHOD);
    TMethodID methodId = TMethod::fromString(cmd.value);
    TTestMethod *testMethod = getConverter(methodId) ? m_curMethodConverter->getTestMethod() : 0;
    if (!testMethod) {
        emit importMessage(tr("[Error] Line %1: Unknown test method at '%2'... Ignored").arg(cmd.line).arg(cmd.command));
        ++m_errorsCnt;
        return;
    }
    if(!m_testProps.uniqueKeys().contains(PRM_TITLE)) {
        emit importMessage(tr("[Error] Line %1: No title specified for test method at '%2'... Ignored").arg(cmd.line).arg(cmd.command));
        ++m_errorsCnt;
        return;
    }
    // set defaults
    if(!m_testProps.uniqueKeys().contains(PRM_SCHEDULE)) {
        IOTextFileCmd cmdSchedule(PRM_SCHEDULE, m_defaultSchedule);
        m_testProps[PRM_SCHEDULE] = cmdSchedule;
    }
    if(!m_testProps.uniqueKeys().contains(PRM_ALERTS)) {
        IOTextFileCmd cmdAlerts(PRM_ALERTS, m_defaultAlertProfile);
        m_testProps[PRM_ALERTS] = cmdAlerts;
    }
    if(!m_testProps.uniqueKeys().contains(PRM_INTERVAL)) {
        IOTextFileCmd cmdInterval(PRM_INTERVAL, QString::number(m_defaultInterval));
        m_testProps[PRM_INTERVAL] = cmdInterval;
    }
    if(!m_testProps.uniqueKeys().contains(PRM_COMMENT)) {
        IOTextFileCmd cmdComment(PRM_COMMENT, m_defaultComment);
        m_testProps[PRM_COMMENT] = cmdComment;
    }
    if(!m_testProps.uniqueKeys().contains(PRM_DEST_FOLDER)) {
        IOTextFileCmd cmdFolder(PRM_DEST_FOLDER, m_defaultFolder);
        m_testProps[PRM_DEST_FOLDER] = cmdFolder;
    }
    // find or create test
    cmd = m_testProps.take(PRM_TITLE);
    m_curTest = new TTest(m_HML->nextID(),cmd.value);
    m_curTest->setTest(testMethod);
    cmd = m_testProps.take(PRM_DEST_FOLDER);
    TNode *node = m_HML->cmdCreateFolder(cmd.value);
    m_HML->addNode(node,m_curTest);
    ++m_testsAdded;
    setTestProperties();
}

/******************************************************************/

void IOTextFile::setTestProperties()
{
    IOTextFileCmd cmd;
    // main
    if (m_testProps.keys().contains(PRM_RM_AGENT)) {
        cmd = m_testProps.take(PRM_RM_AGENT);
        qDebug() << "TODO: Text Import. Key = " << PRM_RM_AGENT;
    }
    if (m_testProps.keys().contains(PRM_NAME_PATTERN)) {
        cmd = m_testProps.take(PRM_NAME_PATTERN);
        m_curTest->method()->setNamePattern(cmd.value);
    }
    if (m_testProps.keys().contains(PRM_CMNT_PATTERN)) {
        cmd = m_testProps.take(PRM_CMNT_PATTERN);
        m_curTest->method()->setCommentPattern(cmd.value.replace("^M","\n"));
    }
    if (m_testProps.keys().contains(PRM_COMMENT)) {
        cmd = m_testProps.take(PRM_COMMENT);
        if (!cmd.value.isEmpty()) {
            m_curTest->setComment(cmd.value.replace("^M","\n"));
        }
    }
    if (m_testProps.keys().contains(PRM_RELATED_URL)) {
        cmd = m_testProps.take(PRM_RELATED_URL);
        m_curTest->setRelatedURL(cmd.value);
    }
    // schedule
    TSchedule::ScheduleMode schMode = TSchedule::Regular;
    if (m_testProps.keys().contains(PRM_SCHEDULE_MODE)) {
        cmd = m_testProps.take(PRM_SCHEDULE_MODE);
        int idx = m_ScheduleMode.indexOf(cmd.value);
        if (idx == -1) {
            emit importMessage(tr("[Error] Line %1: Unknown ScheduleMod at '%2'... set to Regular").arg(cmd.line).arg(cmd.command));
            ++m_errorsCnt;
        } else {
            schMode = (TSchedule::ScheduleMode)idx;
        }
    }
    switch(schMode) {
    case TSchedule::Regular: {
        QString scheduleName = m_testProps.take(PRM_SCHEDULE).value;
        int interval = m_testProps.take(PRM_INTERVAL).value.toInt();
        m_curTest->setRegularSchedule(interval, scheduleName);
    } break;
    case TSchedule::OncePerDay:
    case TSchedule::OncePerWeek:
    case TSchedule::OncePerMonth:{
        int idx = ((int)schMode) - 1;
        int scheduleDay = 2;
        if (m_testProps.keys().contains(PRM_SCHEDULE_DAY)) {
            scheduleDay = m_testProps.take(PRM_SCHEDULE_DAY).value.toInt();
        }
        QTime scheduleTime(9,0,0);
        if (m_testProps.keys().contains(PRM_SCHEDULE_TIME)) {
            scheduleTime = QTime::fromString(m_testProps.take(PRM_SCHEDULE_TIME).value,"hh:mm:ss");
        }
        m_curTest->setIrregularSchedule(idx,scheduleDay,scheduleTime);
    } break;
    case TSchedule::ByExpression: {
        QString scheduleExpr;
        if (m_testProps.keys().contains(PRM_SCHEDULE_EXPR)) {
            scheduleExpr = m_testProps.take(PRM_SCHEDULE_EXPR).value;
        }
        m_curTest->setByExpressionSchedule(scheduleExpr,QString());
    } break;
    }
    // alerts
    if (m_testProps.keys().contains(PRM_ALERTS)) {
        cmd = m_testProps.take(PRM_ALERTS);
        int idx = GData::getActionProfileIdx(cmd.value);
        if (idx != -1) {
            m_curTest->setAlertProfileID(idx);
        }
    }
    // Log & Reports
    if (m_testProps.keys().contains(PRM_USE_COMMON_LOG)) {
        cmd = m_testProps.take(PRM_USE_COMMON_LOG);
        m_curTest->setUseCommonLog(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_USE_COMMON_LOG)) {
        cmd = m_testProps.take(PRM_USE_COMMON_LOG);
        m_curTest->setUseCommonLog(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_COM_LOG_MODE)) {
        cmd = m_testProps.take(PRM_COM_LOG_MODE);
        if (cmd.value == "brief") m_curTest->setPrivateLogMode(1);
        else if (cmd.value == "full") m_curTest->setPrivateLogMode(2);
        else if (cmd.value == "reply") m_curTest->setPrivateLogMode(3);
        else m_curTest->setPrivateLogMode(0);
    }
    if (m_testProps.keys().contains(PRM_PRIV_LOG)) {
        cmd = m_testProps.take(PRM_PRIV_LOG);
        m_curTest->setUsePrivateLog(true);
        m_curTest->setPrivateLog(cmd.value);
    } else {
        m_curTest->setUsePrivateLog(false);
    }
    if (m_testProps.keys().contains(PRM_PRIV_LOG_MODE)) {
        cmd = m_testProps.take(PRM_PRIV_LOG_MODE);
        if (cmd.value == "brief") m_curTest->setPrivateLogMode(1);
        else if (cmd.value == "full") m_curTest->setPrivateLogMode(2);
        else if (cmd.value == "reply") m_curTest->setPrivateLogMode(3);
        else m_curTest->setPrivateLogMode(0);
    }
    //? ExcludeFromHtmlReport
    //? ExcludeFromWmlReport
    //? ExcludeFromDbfReport
    // Master tests
    if (m_testProps.keys().contains(PRM_DEPENDS_ON)) {
        cmd = m_testProps.take(PRM_DEPENDS_ON);
        m_curTest->setDependencyMode(cmd.value=="list"?0:1);
    }
    if (m_curTest->getDependencyMode()) { // Expression
        if (m_testProps.keys().contains(PRM_DEPEND_EXPR)) {
            cmd = m_testProps.take(PRM_DEPEND_EXPR);
            qDebug() << "TODO: Text Import. Key = " << PRM_DEPEND_EXPR;
        }
        if (m_testProps.keys().contains(PRM_DEPEND_EXPR_ID)) {
            cmd = m_testProps.take(PRM_DEPEND_EXPR_ID);
            qDebug() << "TODO: Text Import. Key = " << PRM_DEPEND_EXPR_ID;
        }
        if (m_testProps.keys().contains(PRM_DEPEND_STATUS)) {
            cmd = m_testProps.take(PRM_DEPEND_STATUS);
            qDebug() << "TODO: Text Import. Key = " << PRM_DEPEND_STATUS;
        }
        if (m_testProps.keys().contains(PRM_DEPEND_STAT_ID)) {
            cmd = m_testProps.take(PRM_DEPEND_STAT_ID);
            qDebug() << "TODO: Text Import. Key = " << PRM_DEPEND_STAT_ID;
        }
    } else { // anothe test(s)
        if (m_testProps.keys().contains(PRM_MASTER_TEST_ALIVE)) {
            cmd = m_testProps.take(PRM_MASTER_TEST_ALIVE);
            qDebug() << "TODO: Text Import. Key = " << PRM_MASTER_TEST_ALIVE;
        }
        if (m_testProps.keys().contains(PRM_MASTER_TEST_ALIVE_OR_UNKNOWN)) {
            cmd = m_testProps.take(PRM_MASTER_TEST_ALIVE_OR_UNKNOWN);
            qDebug() << "TODO: Text Import. Key = " << PRM_MASTER_TEST_ALIVE_OR_UNKNOWN;
        }
        if (m_testProps.keys().contains(PRM_MASTER_TEST_DEAD_OR_UNKNOWN)) {
            cmd = m_testProps.take(PRM_MASTER_TEST_DEAD_OR_UNKNOWN);
            qDebug() << "TODO: Text Import. Key = " << PRM_MASTER_TEST_DEAD_OR_UNKNOWN;
        }
        if (m_testProps.keys().contains(PRM_MASTER_TEST_DEAD)) {
            cmd = m_testProps.take(PRM_MASTER_TEST_DEAD);
            qDebug() << "TODO: Text Import. Key = " << PRM_MASTER_TEST_DEAD;
        }
    }
    if (m_testProps.keys().contains(PRM_SYNC_COUNTERS)) {
        cmd = m_testProps.take(PRM_SYNC_COUNTERS);
        m_curTest->setSynchronizeCounters(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_SYNC_ALERTS)) {
        cmd = m_testProps.take(PRM_SYNC_ALERTS);
        m_curTest->setSynchronizeStatusAlerts(cmd.value == "Yes");
    }
    // optional
    if (m_testProps.keys().contains(PRM_REVERSE_ALERT)) {
        cmd = m_testProps.take(PRM_REVERSE_ALERT);
        m_curTest->setReverseAlert(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_UNKNOWN_IS_BAD)) {
        cmd = m_testProps.take(PRM_UNKNOWN_IS_BAD);
        m_curTest->setUnknownIsBad(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_WARNING_IS_BAD)) {
        cmd = m_testProps.take(PRM_WARNING_IS_BAD);
        m_curTest->setWarningIsBad(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_USE_WARNING)) {
        cmd = m_testProps.take(PRM_USE_WARNING);
        m_curTest->setUseWarningScript(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_USE_NORMAL)) {
        cmd = m_testProps.take(PRM_USE_NORMAL);
        m_curTest->setUseNormalScript(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_TUNEUP_REPLY)) {
        cmd = m_testProps.take(PRM_TUNEUP_REPLY);
        m_curTest->setTuneUpReply(cmd.value == "Yes");
    }
    if (m_testProps.keys().contains(PRM_WARNING_EXPR)) {
        cmd = m_testProps.take(PRM_WARNING_EXPR);
        m_curTest->setWarningScript(cmd.value);
    }
    if (m_testProps.keys().contains(PRM_NORMAL_EXPR)) {
        cmd = m_testProps.take(PRM_NORMAL_EXPR);
        m_curTest->setNormalScript(cmd.value);
    }
    if (m_testProps.keys().contains(PRM_TUNE_REPLY_EXP)) {
        cmd = m_testProps.take(PRM_TUNE_REPLY_EXP);
        m_curTest->setTuneUpScript(cmd.value);
    }
    // test method properties
    foreach(const QString &key, m_testProps.uniqueKeys()) {
        cmd = m_testProps.take(key);
        if (cmd.line == -1) continue; // unused defaults
        if (!m_curMethodConverter->setValue(key, cmd.value)) {
            emit importMessage(tr("[Warning]! Line %1: Unknown key at '%2'... Ignored").arg(cmd.line).arg(cmd.command));
            ++m_warningsCnt;
        }
    }
    m_curTest->updateSpecificProperties();
}

/******************************************************************/

void IOTextFile::createLinks()
{
    foreach(QString link, m_linkedTo) {
        TNode *linkNode = m_HML->cmdCreateFolder(link.replace("\\","/"));
        m_curTest->addLink(linkNode);
        m_HML->addNode(linkNode, new TLink(m_HML->nextID(), m_curTest));
    }
}

/******************************************************************/

IOTestMethodConverter *IOTextFile::getConverter(TMethodID methodId)
{
    if (m_curMethodConverter) {
        delete m_curMethodConverter;
        m_curMethodConverter = 0;
    }
    switch (methodId) {
    case TMethodID::Ping :
        m_curMethodConverter = new IOPingConverter();
        break;
    case TMethodID::DriveSpace :
        m_curMethodConverter = new IODriveSpaceConverter();
        break;
    case TMethodID::FileSize :
        m_curMethodConverter = new IOFolderSizeConverter();
        break;
    case TMethodID::FileExists :
        m_curMethodConverter = new IOFileExistsConverter();
        break;
    case TMethodID::SNMP :
        m_curMethodConverter = new IOSnmpGetConverter();
        break;
    case TMethodID::ShellScript :
        m_curMethodConverter = new IOShellScriptConverter();
        break;
    case TMethodID::Oracle :
        m_curMethodConverter = new IOOracleConverter();
        break;
    case TMethodID::MySQL :
        m_curMethodConverter = new IOMySqlConverter();
        break;
    case TMethodID::Postgre :
        m_curMethodConverter = new IOPostgreSqlConverter();
        break;
    case TMethodID::Interbase :
        m_curMethodConverter = new IOInterbaseConverter();
        break;
    case TMethodID::ODBC :
        m_curMethodConverter = new IOODBCConverter();
        break;
    case TMethodID::Externalprg :
        m_curMethodConverter = new IOExternalPrgConverter();
        break;
    case TMethodID::DICOM :
        m_curMethodConverter = new IODICOMConverter();
        break;
    case TMethodID::DHCP :
        m_curMethodConverter = new IODHCPConverter();
        break;
    case TMethodID::CPU :
        m_curMethodConverter = new IOCPUUsageConverter();
        break;
    case TMethodID::CountFiles :
        m_curMethodConverter = new IOCountFilesConverter();
        break;
    case TMethodID::FileCompare :
        m_curMethodConverter = new IOCompareFilesConverter();
        break;
    default:
        m_curMethodConverter = new IOTestMethodConverter();
        break;
    }
    return m_curMethodConverter;
}

/******************************************************************/

} // namespace SDPO
