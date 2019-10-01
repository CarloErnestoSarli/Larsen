#-------------------------------------------------
#
# Project created by QtCreator 2019-03-26T13:58:02
#
#-------------------------------------------------

QT       += core gui opengl


INCLUDEPATH += /home/carlo/Development/PhD/C++/Larsen/Libs/GLM



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Larsen
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    colourmapdialog.cpp \
    connector.cpp \
        main.cpp \
        mainwindow.cpp \
    datahandler.cpp \
    canvas.cpp \
    samplerwindow.cpp \
    transform3D.cpp \
    camera3D.cpp \
    quad.cpp \
    triangle.cpp \
    colourmap.cpp \
    userinput.cpp \
    geometryprocessor.cpp

HEADERS += \
    colourmapdialog.h \
    connector.h \
        mainwindow.h \
    datahandler.h \
    constants.h \
    canvas.h \
    samplerwindow.h \
    vertex.h \
    transform3D.h \
    camera3D.h \
    quad.h \
    triangle.h \
    colourmap.h \
    userinput.h \
    geometryprocessor.h

FORMS += \
        colourmapdialog.ui \
        mainwindow.ui \
        samplerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc


DISTFILES +=
