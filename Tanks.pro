QT       += core gui widgets

TARGET = Tanks
TEMPLATE = app

CONFIG   += c++11 warn_on

LIBS += -lassimp

SOURCES += main.cpp\
        mainwindow.cpp \
    view/openglwidget.cpp \
    controller/game.cpp \
    view/model3d.cpp \
    utils/openglhelpers.cpp

HEADERS  += mainwindow.hpp \
    view/openglwidget.hpp \
    controller/game.hpp \
    view/model3d.hpp \
    utils/openglhelpers.hpp

FORMS    += mainwindow.ui

DISTFILES += \
    Tanks.astylerc \
    view/base.vert \
    view/base.frag
