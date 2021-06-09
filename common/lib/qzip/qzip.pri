isEmpty(__QZIP_PRI__) {
    __QZIP_PRI__ = yup

    INCLUDEPATH += $$PWD
    DEPENDPATH += $$PWD

    HEADERS += \
        $$PWD/qzipreader_p.h \
        $$PWD/qzipwriter_p.h

# source is commented because it has compiled in Qt lib
#    SOURCES += \
#        $$PWD/qzip.cpp

}