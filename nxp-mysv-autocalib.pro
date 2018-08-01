#-------------------------------------------------
#
# Project created by QtCreator 2018-07-23T14:53:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nxp-mysv-autocalib
TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv glm assimp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    src_contours.cpp \
    defisheye.cpp \
    grid.cpp \
    masks.cpp \
    settings.cpp \
    src_v4l2.cpp \
    cameracalibrator.cpp \
    gpurender.cpp \
    exposure_compensator.cpp \
    Material.cpp \
    ModelLoader.cpp \
    MRT.cpp \
    VBO.cpp \
    svgpurender.cpp

HEADERS += \
        mainwindow.h \
    src_contours.hpp \
    defisheye.hpp \
    grid.hpp \
    masks.hpp \
    lines.hpp \
    settings.h \
    shaders.hpp \
    src_v4l2.hpp \
    cameracalibrator.h \
    gpurender.h \
    exposure_compensator.hpp \
    Material.hpp \
    ModelLoader.hpp \
    MRT.hpp \
    VBO.hpp \
    svgpurender.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    fshader.fsh

target.path = /home/root/nxp-mysv-autocalib
INSTALLS += target
