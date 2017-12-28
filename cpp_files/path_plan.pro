TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tinystr.cpp \
    tinyxml.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp \
    astar.cpp \
    config.cpp \
    dijkstra.cpp \
    environmentoptions.cpp \
    isearch.cpp \
    jp_search.cpp \
    main.cpp \
    map.cpp \
    mission.cpp \
    theta.cpp \
    tinystr.cpp \
    tinyxml.cpp \
    tinyxml2.cpp \
    tinyxmlerror.cpp \
    tinyxmlparser.cpp \
    xmllogger.cpp

win32 {
QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
}

HEADERS += \
    tinystr.h \
    tinyxml.h \
    astar.h \
    config.h \
    dijkstra.h \
    environmentoptions.h \
    gl_const.h \
    ilogger.h \
    isearch.h \
    jp_search.h \
    map.h \
    mission.h \
    node.h \
    searchresult.h \
    theta.h \
    tinystr.h \
    tinyxml.h \
    tinyxml2.h \
    xmllogger.h

SUBDIRS += \
    path_plan.pro

DISTFILES += \
    ASearch.pro.user \
    path_plan.pro.user \
    CMakeLists.txt
