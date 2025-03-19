QT       += network multimedia multimediawidgets
SOURCES += \
    ./voice/asr.cpp \
    ./voice/audiorecorder.cpp \
    ./voice/voice.cpp

HEADERS += \
    ./voice/asr.h \
    ./voice/audiorecorder.h \
    ./voice/voice.h

RESOURCES += \
    $$PWD/switch.qrc

FORMS += \
     $$PWD/voice.ui
