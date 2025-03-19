QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    life.cpp \
    main.cpp \
    tool.cpp \
    use.cpp \
    widget.cpp

HEADERS += \
    life.h \
    tool.h \
    use.h \
    widget.h

FORMS += \
    life.ui \
    tool.ui \
    use.ui \
    widget.ui

include($$PWD/slidepage/slidepage.pri)
include($$PWD/folder/folder.pri)
#include($$PWD/camera/camera.pri)
include($$PWD/musicplay/musicplay.pri)
include($$PWD/myMap/myMap.pri)
include($$PWD/photoViem/photoViem.pri)
include($$PWD/video/video.pri)
#include($$PWD/voice/voice.pri)
include($$PWD/weather/Weather.pri)
include($$PWD/wifi/wifi.pri)
include($$PWD/key/key.pri)
include($$PWD/date_biao/date_biao.pri)
include($$PWD/compass/compass.pri)
include($$PWD/set_arm/set_arm.pri)
include($$PWD/softkeyboard/softkeyboard.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    car_terminal.qrc

