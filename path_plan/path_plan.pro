TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tinystr.cpp \
    tinyxml.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp

win32 {
QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
}

HEADERS += \
    tinystr.h \
    tinyxml.h
