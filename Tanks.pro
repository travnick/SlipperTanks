QT       += core gui widgets

TARGET = Tanks
TEMPLATE = app

CONFIG   += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    view/openglwidget.cpp \
    controller/game.cpp

HEADERS  += mainwindow.hpp \
    view/openglwidget.hpp \
    controller/game.hpp

FORMS    += mainwindow.ui

DISTFILES += \
    Tanks.astylerc
