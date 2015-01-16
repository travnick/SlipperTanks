QT       += core gui widgets

TARGET = Tanks
TEMPLATE = app

CONFIG   += c++11

#general compiler flags
QMAKE_CXXFLAGS += \
    -pipe \
    -fvisibility=hidden \
    -fpic \

#code protection flags
QMAKE_CXXFLAGS += \
    -fstack-protector-strong \

#warnings as errors
QMAKE_CXXFLAGS += \
    -Werror \

#error checking flags
QMAKE_CXXFLAGS += \
    -Wall \
    -Wdouble-promotion \
    -Wextra \
    -Wfloat-equal \
    -Wformat=2 \
    -Winvalid-pch \
    -Wlogical-op \
    -Wnonnull \
    -Wopenmp-simd \
    -Wpointer-arith \
    -Wredundant-decls \
    -Wshadow \
    -Wsign-promo \
    -Wstrict-null-sentinel \
    -Wstrict-overflow=5 \
    -Wuninitialized \
    -Wvector-operation-performance \

#OOP warning flags
QMAKE_CXXFLAGS += \
    -Wctor-dtor-privacy \
    -Woverloaded-virtual \
    -Wnon-virtual-dtor \
    -Wold-style-cast \

QMAKE_CXXFLAGS_DEBUG += \
    -g3 \
    -ftrapv \

QMAKE_CXXFLAGS_RELEASE += \
    -O3

LIBS += -lassimp

SOURCES += main.cpp\
    mainwindow.cpp \
    controller/game.cpp \
    model/model3d.cpp \
    model/camera.cpp \
    model/scene.cpp \
    utils/openglhelpers.cpp \
    view/openglwidget.cpp \


HEADERS  += mainwindow.hpp \
    controller/game.hpp \
    model/model3d.hpp \
    model/camera.hpp \
    model/scene.hpp \
    utils/openglhelpers.hpp \
    view/openglwidget.hpp \
    utils/commondefines.hpp \
    model/mesh.hpp \
    model/vertexbufferitem.hpp


FORMS    += mainwindow.ui

DISTFILES += \
    Tanks.astylerc \
    view/base.vert \
    view/base.frag
