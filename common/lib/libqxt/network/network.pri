QT += network
DEFINES += BUILD_QXT_NETWORK

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += $$PWD/qxtjsonrpccall.h
HEADERS += $$PWD/qxtjsonrpcclient.h
HEADERS += $$PWD/qxtnetwork.h
HEADERS += $$PWD/qxtmail_p.h
HEADERS += $$PWD/qxtsmtp.h
HEADERS += $$PWD/qxtsmtp_p.h
HEADERS += $$PWD/qxtmailattachment.h
HEADERS += $$PWD/qxtmailmessage.h
HEADERS += $$PWD/qxtrpcpeer.h
HEADERS += $$PWD/qxttcpconnectionmanager.h
HEADERS += $$PWD/qxttcpconnectionmanager_p.h
HEADERS += $$PWD/qxtxmlrpccall.h
HEADERS += $$PWD/qxtxmlrpcclient.h
HEADERS += $$PWD/qxtxmlrpc_p.h
HEADERS += $$PWD/qxtpop3.h
HEADERS += $$PWD/qxtpop3_p.h
HEADERS += $$PWD/qxtpop3reply.h
HEADERS += $$PWD/qxtpop3reply_p.h
HEADERS += $$PWD/qxtpop3statreply.h
HEADERS += $$PWD/qxtpop3listreply.h
HEADERS += $$PWD/qxtpop3retrreply.h
HEADERS += $$PWD/qxtsslserver.h
HEADERS += $$PWD/qxtsslconnectionmanager.h

SOURCES += $$PWD/qxtjsonrpccall.cpp
SOURCES += $$PWD/qxtjsonrpcclient.cpp
SOURCES += $$PWD/qxtmailattachment.cpp
SOURCES += $$PWD/qxtmailmessage.cpp
SOURCES += $$PWD/qxtrpcpeer.cpp
SOURCES += $$PWD/qxtsmtp.cpp
SOURCES += $$PWD/qxttcpconnectionmanager.cpp
SOURCES += $$PWD/qxtxmlrpccall.cpp
SOURCES += $$PWD/qxtxmlrpcclient.cpp
SOURCES += $$PWD/qxtxmlrpc_p.cpp
SOURCES += $$PWD/qxtpop3.cpp
SOURCES += $$PWD/qxtpop3reply.cpp
SOURCES += $$PWD/qxtsslserver.cpp
SOURCES += $$PWD/qxtsslconnectionmanager.cpp

contains(DEFINES,HAVE_OPENSSL){
 HEADERS += $$PWD/qxtsshchannel.h
 HEADERS += $$PWD/qxtsshchannel_p.h
 HEADERS += $$PWD/qxtsshclient.h
 HEADERS += $$PWD/qxtsshclient_p.h
 HEADERS += $$PWD/qxtsshprocess.h
 HEADERS += $$PWD/qxtsshtcpsocket.h

 SOURCES += $$PWD/qxtsshchannel.cpp
 SOURCES += $$PWD/qxtsshclient.cpp
 SOURCES += $$PWD/qxtsshprocess.cpp
 SOURCES += $$PWD/qxtsshtcpsocket.cpp
}

