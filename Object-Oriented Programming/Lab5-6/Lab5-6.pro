TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    controller.cpp \
    dynamicarray.cpp \
    repository.cpp \
    tutorial.cpp \
    ui.cpp \
    src/controller.cpp \
    src/dynamicarray.cpp \
    src/repository.cpp \
    src/tutorial.cpp \
    src/ui.cpp \
    main.cpp \
    tests.cpp \
    tutorialvalidator.cpp

HEADERS += \
    controller.h \
    dynamicarray.h \
    repository.h \
    tutorial.h \
    ui.h \
    include/controller.h \
    include/dynamicarray.h \
    include/repository.h \
    include/tutorial.h \
    include/ui.h \
    tutorialvalidator.h
