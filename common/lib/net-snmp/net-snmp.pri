isEmpty(__NET_SNMP_PRI__) {
    __NET_SNMP_PRI__ = yup

    INCLUDEPATH += $$PWD
    DEPENDPATH += $$PWD

    HEADERS += \
        $$PWD/mibnode.h \
        $$PWD/miboid.h \
        $$PWD/mibtreemodel.h \
        $$PWD/netsnmpsession.h \
        $$PWD/oidstring.h \
        $$PWD/snmp.h \
        $$PWD/snmppdu.h \
        $$PWD/snmpprofile.h \
        $$PWD/snmptablemodel.h \
        $$PWD/snmpvar.h

    SOURCES += \
        $$PWD/mibnode.cpp \
        $$PWD/miboid.cpp \
        $$PWD/mibtreemodel.cpp \
        $$PWD/netsnmpsession.cpp \
        $$PWD/oidstring.cpp \
        $$PWD/snmp.cpp \
        $$PWD/snmpprofile.cpp \
        $$PWD/snmptablemodel.cpp \
        $$PWD/snmpvar.cpp

    LIBS += -lnetsnmp
}
