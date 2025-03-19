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
    main.cpp \
    camera.cpp

HEADERS += \
    camera.h

FORMS += \
    camera.ui

win32{
    ##包含路径
    INCLUDEPATH += D:\laosirangxiazai\openCV\opencv\opencv_build\install\include
    ##包含库文件
    LIBS += D:\laosirangxiazai\openCV\opencv\opencv_build\lib\libopencv_*.dll.a
}
unix{
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
