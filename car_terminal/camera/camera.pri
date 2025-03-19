SOURCES += \
    ./camera/camera.cpp

HEADERS += \
    ./camera/camera.h

FORMS += \
     $$PWD/camera.ui

win32{
    ##鍖呭惈璺緞
    INCLUDEPATH += D:\laosirangxiazai\openCV\opencv\opencv_build\install\include
    ##鍖呭惈搴撴枃浠?
    LIBS += D:\laosirangxiazai\openCV\opencv\opencv_build\lib\libopencv_*.dll.a
}
unix{
    contains(QT_ARCH,arm32){
        CONFIG += link_pkgconfig
        PKGCONFIG += opencv
        INCLUDEPATH +=/opt/fsl-imx-x11/4.1.15-2.1.0/sysroots/cortexa7hf-neon-poky-linux-gnueabi/usr/include
    }else{
        ##Linux鐨凮PenCV璺緞
        INCLUDEPATH +=/usr/local/include/opencv4 \
                      /usr/local/include/opencv4/opencv2
        LIBS += /usr/local/lib/libopencv_world.so
    }
}
