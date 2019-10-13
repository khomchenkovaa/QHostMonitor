QT += sql
DEFINES += BUILD_QXT_SQL

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS  += $$PWD/qxtsql.h
HEADERS  += $$PWD/qxtsqlpackage.h
HEADERS  += $$PWD/qxtsqlpackagemodel.h
HEADERS  += $$PWD/qxtsqlthreadmanager.h

SOURCES  += $$PWD/qxtsqlpackage.cpp
SOURCES  += $$PWD/qxtsqlpackagemodel.cpp
SOURCES  += $$PWD/qxtsqlthreadmanager.cpp
