TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    repo.cpp \
    ctrl.cpp \
    painting.cpp \
    ui.cpp \
    undooperation.cpp

HEADERS += \
    repo.h \
    ctrl.h \
    painting.h \
    ui.h \
    undooperation.h
