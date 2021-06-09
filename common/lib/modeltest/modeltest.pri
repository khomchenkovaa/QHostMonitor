isEmpty(__MODELTEST_PRI__) {
    __MODELTEST_PRI__ = yup

    INCLUDEPATH += $$PWD
    DEPENDPATH += $$PWD

    HEADERS += $$PWD/modeltest.h
    SOURCES += $$PWD/modeltest.cpp
}
