QT += core
DEFINES += BUILD_QXT_CORE

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/qxtabstractconnectionmanager.h \
    $$PWD/qxtabstractfileloggerengine.h \
    $$PWD/qxtabstractiologgerengine.h \
    $$PWD/qxtabstractsignalserializer.h \
    $$PWD/qxtalgorithms.h \
    $$PWD/qxtbasicfileloggerengine.h \
    $$PWD/qxtbasicstdloggerengine.h \
    $$PWD/qxtboundcfunction.h \
    $$PWD/qxtboundfunction.h \
    $$PWD/qxtboundfunctionbase.h \
    $$PWD/qxtcommandoptions.h \
    $$PWD/qxtcore.h \
    $$PWD/qxtcsvmodel.h \
    $$PWD/qxtcurrency.h \
    $$PWD/qxtdaemon.h \
    $$PWD/qxtdatastreamsignalserializer.h \
    $$PWD/qxtdeplex.h \
    $$PWD/qxtdeplex_p.h \
    $$PWD/qxterror.h \
    $$PWD/qxtfifo.h \
    $$PWD/qxtglobal.h \
    $$PWD/qxthmac.h \
    $$PWD/qxtjob.h \
    $$PWD/qxtjob_p.h \
    $$PWD/qxtjson.h \
    $$PWD/qxtlinesocket.h \
    $$PWD/qxtlinesocket_p.h \
    $$PWD/qxtlinkedtree.h \
    $$PWD/qxtlocale.h \
    $$PWD/qxtlocale_data_p.h \
    $$PWD/qxtlogger.h \
    $$PWD/qxtlogger_p.h \
    $$PWD/qxtloggerengine.h \
    $$PWD/qxtlogstream.h \
    $$PWD/qxtlogstream_p.h \
    $$PWD/qxtmetaobject.h \
    $$PWD/qxtmetatype.h \
    $$PWD/qxtmodelserializer.h \
    $$PWD/qxtmultisignalwaiter.h \
    $$PWD/qxtnamespace.h \
    $$PWD/qxtnull.h \
    $$PWD/qxtnullable.h \
    $$PWD/qxtpairlist.h \
    $$PWD/qxtpimpl.h \
    $$PWD/qxtpipe.h \
    $$PWD/qxtpipe_p.h \
    $$PWD/qxtpointerlist.h \
    $$PWD/qxtrpcservice.h \
    $$PWD/qxtrpcservice_p.h \
    $$PWD/qxtsharedprivate.h \
    $$PWD/qxtsignalgroup.h \
    $$PWD/qxtsignalwaiter.h \
    $$PWD/qxtslotjob.h \
    $$PWD/qxtslotjob_p.h \
    $$PWD/qxtslotmapper.h \
    $$PWD/qxtstdio.h \
    $$PWD/qxtstdio_p.h \
    $$PWD/qxtstdstreambufdevice.h \
    $$PWD/qxttemporarydir.h \
    $$PWD/qxttemporarydir_p.h \
    $$PWD/qxttimer.h \
    $$PWD/qxttypelist.h \
    $$PWD/qxtxmlfileloggerengine.h

SOURCES += \
    $$PWD/qxtabstractconnectionmanager.cpp \
    $$PWD/qxtabstractfileloggerengine.cpp \
    $$PWD/qxtabstractiologgerengine.cpp \
    $$PWD/qxtbasicfileloggerengine.cpp \
    $$PWD/qxtbasicstdloggerengine.cpp \
    $$PWD/qxtcommandoptions.cpp \
    $$PWD/qxtcsvmodel.cpp \
    $$PWD/qxtcurrency.cpp \
    $$PWD/qxtdaemon.cpp \
    $$PWD/qxtdatastreamsignalserializer.cpp \
    $$PWD/qxtdeplex.cpp \
    $$PWD/qxterror.cpp \
    $$PWD/qxtfifo.cpp \
    $$PWD/qxtglobal.cpp \
    $$PWD/qxthmac.cpp \
    $$PWD/qxtjob.cpp \
    $$PWD/qxtjson.cpp \
    $$PWD/qxtlinesocket.cpp \
    $$PWD/qxtlinkedtree.cpp \
    $$PWD/qxtlocale.cpp \
    $$PWD/qxtlogger.cpp \
    $$PWD/qxtloggerengine.cpp \
    $$PWD/qxtlogstream.cpp \
    $$PWD/qxtmetaobject.cpp \
    $$PWD/qxtmodelserializer.cpp \
    $$PWD/qxtmultisignalwaiter.cpp \
    $$PWD/qxtnull.cpp \
    $$PWD/qxtpipe.cpp \
    $$PWD/qxtpointerlist.cpp \
    $$PWD/qxtrpcservice.cpp \
    $$PWD/qxtsignalgroup.cpp \
    $$PWD/qxtsignalwaiter.cpp \
    $$PWD/qxtslotjob.cpp \
    $$PWD/qxtslotmapper.cpp \
    $$PWD/qxtstdio.cpp \
    $$PWD/qxtstdstreambufdevice.cpp \
    $$PWD/qxttemporarydir.cpp \
    $$PWD/qxttimer.cpp \
    $$PWD/qxtxmlfileloggerengine.cpp

!symbian {
    # QxtSerialDevice and QxtFileLock
    # are disabled for Symbian pending implementation

    HEADERS  += \
       $$PWD/qxtfilelock.h \
       $$PWD/qxtfilelock_p.h

    SOURCES  += $$PWD/qxtfilelock.cpp

    unix {
        HEADERS  += $$PWD/unix/qxtserialdevice.h
        HEADERS  += $$PWD/unix/qxtserialdevice_p.h
        SOURCES  += $$PWD/unix/qxtfilelock_unix.cpp
        SOURCES  += $$PWD/unix/qxtserialdevice.cpp
        SOURCES  += $$PWD/unix/qxtserialdevice_unix.cpp
        SOURCES  += $$PWD/unix/qxttemporarydir_unix.cpp
    }
    
    win32 {
        SOURCES  += $$PWD/win/qxtfilelock_win.cpp
        SOURCES  += $$PWD/win/qxttemporarydir_win.cpp
    }
}


