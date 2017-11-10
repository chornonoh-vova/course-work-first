TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    main_funcs.cpp \
    file_funcs.cpp \
    special_funcs.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    main_types.h \
    file_funcs.h \
    main_funcs.h \
    special_funcs.h

