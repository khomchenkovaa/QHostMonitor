isEmpty(__QCRON_PRI__) {
    __QCRON_PRI__ = yup
    INCLUDEPATH += $$PWD
    DEPENDPATH += $$PWD

    HEADERS += \
        $$PWD/holiday.hpp \
        $$PWD/qcron.hpp \
        $$PWD/qcronfield.hpp \
        $$PWD/qcronnode.hpp

    SOURCES += \
        $$PWD/holiday.cpp \
        $$PWD/qcron.cpp \
        $$PWD/qcronfield.cpp \
        $$PWD/qcronnode.cpp
}
