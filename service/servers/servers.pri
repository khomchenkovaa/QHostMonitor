INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/rci/rciServer.h \
    $$PWD/rci/rciConnection.h \
    $$PWD/tcp/tcpconnection.h \
    $$PWD/tcp/tcprunnable.h \
    $$PWD/tcp/tcpserver.h \
    $$PWD/qtelnet/telnetLogic.h \
    $$PWD/qtelnet/telnetTcpClient.h \
    $$PWD/qtelnet/telnetTcpServer.h \
    $$PWD/qtelnet/qTelnetServer.h \
    $$PWD/telnet/telnetConnection.h \
    $$PWD/telnet/telnetServer.h \
    $$PWD/telnet/telnetWorker.h

SOURCES += \
    $$PWD/rci/rciServer.cpp \
    $$PWD/rci/rciConnection.cpp \
    $$PWD/tcp/tcpconnection.cpp \
    $$PWD/tcp/tcprunnable.cpp \
    $$PWD/tcp/tcpserver.cpp \
    $$PWD/qtelnet/telnetLogic.cpp \
    $$PWD/qtelnet/telnetTcpClient.cpp \
    $$PWD/qtelnet/telnetTcpServer.cpp \
    $$PWD/qtelnet/qTelnetServer.cpp \
    $$PWD/telnet/telnetConnection.cpp \
    $$PWD/telnet/telnetServer.cpp \
    $$PWD/telnet/telnetWorker.cpp
