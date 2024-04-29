CDPVERSION = 4.12
TYPE = library
PROJECTNAME = xwiimotelib

DEPS += \

INCLUDEPATH = xwiimote

HEADERS += \
    xwiimoteIO.h \
    xwiimotelib.h \
    xwiimotelibBuilder.h \
    xwiimote/lib/xwiimote.h

SOURCES += \
    xwiimotelibBuilder.cpp \
    xwiimoteIO.cpp

linux {
SOURCES += \
    xwiimote/lib/core.c \
    xwiimote/lib/monitor.c
}
!linux {
message("xwiimotelib: Note that this library is only functional on Linux targets.")
}

linux {
    DEFINES = XWII__EXPORT=
    LIBS += -ludev
}

DISTFILES += $$files(*.xml, true) \
    Templates/Models/xwiimotelib.xwiimoteIO.xml

load(cdp)
