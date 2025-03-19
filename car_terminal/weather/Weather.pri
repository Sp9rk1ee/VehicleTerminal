QT       += network
SOURCES += \
    ./weather/weather.cpp \
    ./weather/wforecast.cpp

HEADERS += \
    ./weather/weather.h \
    ./weather/wforecast.h

FORMS += \
     $$PWD/weather.ui

RESOURCES += \
    $$PWD/weather.qrc
