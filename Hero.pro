TEMPLATE = app
QT = gui \
    core \
    network
CONFIG += qt \
    release \
    warn_on
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui \
    ui/herowin.ui \
    ui/statswin.ui \
    ui/diarywin.ui \
    ui/messager.ui \
    src/Dialog.ui
HEADERS = src/mainwindowimpl.h \
    src/hero.h \
    src/statswinimpl.h \
    src/herowinimpl.h \
    src/diarywinimpl.h \
    src/heroMessager.h \
    src/Dialog.h
SOURCES = src/mainwindowimpl.cpp \
    src/main.cpp \
    src/hero.cpp \
    src/statswinimpl.cpp \
    src/herowinimpl.cpp \
    src/diarywinimpl.cpp \
    src/heroMessager.cpp \
    src/Dialog.cpp
RESOURCES += resorce.qrc
LIBS += -L/usr/lib/qt4/plugins/designer \
    -lqprogplug
RC_FILE = main.rc
OTHER_FILES += main.rc
