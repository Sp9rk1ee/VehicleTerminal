QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ap3216c.cpp \
    icm20608.cpp \
    jiemian.cpp \
    main.cpp \
    led.cpp \
    key.cpp

HEADERS += \
    ap3216c.h \
    icm20608.h \
    jiemian.h \
    led.h \
    key.h

FORMS += \
    jiemian.ui \
    icm20608.ui \
    key.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
