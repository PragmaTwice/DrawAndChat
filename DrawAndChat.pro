QT += quick quickcontrols2 websockets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/main.cpp \
    src/draw/drawboard.cpp \
    src/draw/drawshape.cpp \
    src/draw/penshape.cpp \
    src/draw/linesshape.cpp \
    src/draw/textshape.cpp \
    src/network/drawandchatclient.cpp \
    src/network/networkinfo.cpp \
    src/draw/drawinfo.cpp

RESOURCES += \
    ui.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/src

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/draw/drawboard.h \
    src/draw/drawshape.h \
    src/draw/penshape.h \
    src/draw/linesshape.h \
    src/draw/textshape.h \
    src/network/drawandchatclient.h \
    src/network/networkinfo.h \
    src/draw/drawinfo.h

STATECHARTS +=
