QT += network script multimedia sql

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/monitoringTask.h \
    $$PWD/actionTask.h \
    $$PWD/manageableService.h \
    $$PWD/monitoringService.h \
    $$PWD/actionService.h \
    $$PWD/hmListService.h \
    $$PWD/hmScriptRunner.h \
    $$PWD/logService.h \
    $$PWD/logger/textLogger.h \
    $$PWD/logger/htmlLogger.h \
    $$PWD/logger/dbfLogger.h \
    $$PWD/logger/odbcLogger.h \
    $$PWD/io/ioDataLoader.h \
    $$PWD/io/ioTestMethodLoader.h \
    $$PWD/io/ioUserVarsLoader.h \
    $$PWD/io/ioMailProfileLoader.h \
    $$PWD/io/ioColorProfileLoader.h \
    $$PWD/io/ioActionProfileLoader.h \
    $$PWD/io/ioUserProfileLoader.h \
    $$PWD/io/ioHelper.h \
    $$PWD/io/ioTextFile.h \
    $$PWD/io/ioHMList.h \
    $$PWD/io/method/sdpoTestMethodConverters.h \
    $$PWD/io/method/ioTestMethodConverter.h \
    $$PWD/io/method/ioDriveSpaceConverter.h \
    $$PWD/io/method/ioFileExistsConverter.h \
    $$PWD/io/method/ioPingConverter.h \
    $$PWD/io/method/ioFolderSizeConverter.h \
    $$PWD/io/method/ioShellScriptConverter.h \
    $$PWD/io/method/ioSnmpGetConverter.h \
    $$PWD/io/method/ioOracleConverter.h \
    $$PWD/io/method/ioMySqlConverter.h \
    $$PWD/io/method/ioPostgreSqlConverter.h \
    $$PWD/io/method/ioInterbaseConverter.h \
    $$PWD/io/method/ioODBCConverter.h \
    $$PWD/io/method/ioExternalPrgConverter.h \
    $$PWD/io/method/ioDICOMConverter.h \
    $$PWD/io/method/ioDHCPConverter.h \
    $$PWD/io/method/ioCPUUsageConverter.h \
    $$PWD/io/method/ioCountFilesConverter.h \
    $$PWD/io/method/ioCompareFilesConverter.h

SOURCES += \
    $$PWD/monitoringTask.cpp \
    $$PWD/actionTask.cpp \
    $$PWD/manageableService.cpp \
    $$PWD/monitoringService.cpp \
    $$PWD/actionService.cpp \
    $$PWD/hmListService.cpp \
    $$PWD/hmScriptRunner.cpp \
    $$PWD/logService.cpp \
    $$PWD/logger/textLogger.cpp \
    $$PWD/logger/htmlLogger.cpp \
    $$PWD/logger/dbfLogger.cpp \
    $$PWD/logger/odbcLogger.cpp \
    $$PWD/io/ioDataLoader.cpp \
    $$PWD/io/ioTestMethodLoader.cpp \
    $$PWD/io/ioUserVarsLoader.cpp \
    $$PWD/io/ioMailProfileLoader.cpp \
    $$PWD/io/ioColorProfileLoader.cpp \
    $$PWD/io/ioActionProfileLoader.cpp \
    $$PWD/io/ioUserProfileLoader.cpp \
    $$PWD/io/ioHelper.cpp \
    $$PWD/io/ioTextFile.cpp \
    $$PWD/io/ioHMList.cpp \
    $$PWD/io/method/ioTestMethodConverter.cpp \
    $$PWD/io/method/ioDriveSpaceConverter.cpp \
    $$PWD/io/method/ioFileExistsConverter.cpp \
    $$PWD/io/method/ioPingConverter.cpp \
    $$PWD/io/method/ioFolderSizeConverter.cpp \
    $$PWD/io/method/ioShellScriptConverter.cpp \
    $$PWD/io/method/ioSnmpGetConverter.cpp \
    $$PWD/io/method/ioOracleConverter.cpp \
    $$PWD/io/method/ioMySqlConverter.cpp \
    $$PWD/io/method/ioPostgreSqlConverter.cpp \
    $$PWD/io/method/ioInterbaseConverter.cpp \
    $$PWD/io/method/ioODBCConverter.cpp \
    $$PWD/io/method/ioExternalPrgConverter.cpp \
    $$PWD/io/method/ioDICOMConverter.cpp \
    $$PWD/io/method/ioDHCPConverter.cpp \
    $$PWD/io/method/ioCPUUsageConverter.cpp \
    $$PWD/io/method/ioCountFilesConverter.cpp \
    $$PWD/io/method/ioCompareFilesConverter.cpp
