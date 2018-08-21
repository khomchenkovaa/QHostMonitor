QT += network script multimedia sql

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/monitoringTask.h \
    $$PWD/monitoringService.h \
    $$PWD/actionTask.h \
    $$PWD/io/ioTextFile.h \
    ../service/actionService.h \
    ../service/logService.h \
    ../service/logger/textLogger.h \
    ../service/logger/htmlLogger.h \
    ../service/logger/dbfLogger.h \
    ../service/logger/odbcLogger.h \
    ../service/hmListService.h \
    ../service/hmScriptRunner.h \
    ../service/io/method/ioTestMethodConverter.h \
    ../service/io/method/ioDriveSpaceConverter.h \
    ../service/io/method/ioFileExistsConverter.h \
    ../service/io/method/ioPingConverter.h \
    ../service/io/method/ioFolderSizeConverter.h \
    ../service/io/method/ioShellScriptConverter.h \
    ../service/io/method/ioSnmpGetConverter.h \
    ../service/io/method/sdpoTestMethodConverters.h \
    ../service/io/method/ioOracleConverter.h \
    ../service/io/method/ioMySqlConverter.h \
    ../service/io/method/ioPostgreSqlConverter.h \
    ../service/io/method/ioInterbaseConverter.h \
    ../service/io/method/ioODBCConverter.h \
    ../service/io/method/ioExternalPrgConverter.h \
    ../service/io/method/ioDICOMConverter.h \
    ../service/io/method/ioDHCPConverter.h \
    ../service/io/method/ioCPUUsageConverter.h \
    ../service/io/method/ioCountFilesConverter.h \
    ../service/io/method/ioCompareFilesConverter.h

SOURCES += \
    $$PWD/monitoringTask.cpp \
    $$PWD/monitoringService.cpp \
    $$PWD/actionTask.cpp \
    $$PWD/io/ioTextFile.cpp \
    ../service/actionService.cpp \
    ../service/logService.cpp \
    ../service/logger/textLogger.cpp \
    ../service/logger/htmlLogger.cpp \
    ../service/logger/dbfLogger.cpp \
    ../service/logger/odbcLogger.cpp \
    ../service/hmListService.cpp \
    ../service/hmScriptRunner.cpp \
    ../service/io/method/ioTestMethodConverter.cpp \
    ../service/io/method/ioDriveSpaceConverter.cpp \
    ../service/io/method/ioFileExistsConverter.cpp \
    ../service/io/method/ioPingConverter.cpp \
    ../service/io/method/ioFolderSizeConverter.cpp \
    ../service/io/method/ioShellScriptConverter.cpp \
    ../service/io/method/ioSnmpGetConverter.cpp \
    ../service/io/method/ioOracleConverter.cpp \
    ../service/io/method/ioMySqlConverter.cpp \
    ../service/io/method/ioPostgreSqlConverter.cpp \
    ../service/io/method/ioInterbaseConverter.cpp \
    ../service/io/method/ioODBCConverter.cpp \
    ../service/io/method/ioExternalPrgConverter.cpp \
    ../service/io/method/ioDICOMConverter.cpp \
    ../service/io/method/ioDHCPConverter.cpp \
    ../service/io/method/ioCPUUsageConverter.cpp \
    ../service/io/method/ioCountFilesConverter.cpp \
    ../service/io/method/ioCompareFilesConverter.cpp
