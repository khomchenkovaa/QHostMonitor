isEmpty(__LIBQXT_PRI__) {
    __LIBQXT_PRI__ = yup
    QT += core sql network

    include(core/core.pri)
    include(network/network.pri)
    include(sql/sql.pri)
    include(web/web.pri)

    contains(DEFINES,HAVE_OPENSSL){
     include(../libssh2/libssh2.pri)
    }

    contains(DEFINES,HAVE_XRANDR){
        !win32:LIBS += -lXrandr
    }
}
