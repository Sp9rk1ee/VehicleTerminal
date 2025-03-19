QT       += network
SOURCES += \
    ./myMap/mymap.cpp \
    ./myMap/longitudelatitude.cpp \
    ./myMap/map.cpp

HEADERS += \
    ./myMap/mymap.h \
    ./myMap/longitudelatitude.h \
    ./myMap/map.h

FORMS += \
     $$PWD/mymap.ui

RESOURCES += \
    $$PWD/myMap.qrc
