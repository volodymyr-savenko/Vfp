#-------------------------------------------------
#
# Project created by QtCreator 2017-06-05T23:46:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vfp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS = -std=c++11

SOURCES += main.cpp\
        View/mainview.cpp \
    View/setuptab.cpp \
    Model/settings.cpp \
    startup.cpp \
    utils.cpp \
    Model/provider.cpp \
    Model/instsocket.cpp \
    Model/instrument.cpp \
    ViewMgr/setupviewmanager.cpp \
    View/controltab.cpp \
    ViewMgr/controltabviewmanager.cpp

HEADERS  += View/mainview.h \
    View/setuptab.h \
    startup.h \
    utils.h \
    Model/provider.h \
    Model/settings.h \
    Model/instsocket.h \
    Model/instrument.h \
    ViewMgr/setupviewmanager.h \
    View/controltab.h \
    ViewMgr/controltabviewmanager.h

FORMS    += View/mainview.ui \
    View/setuptab.ui \
    View/controltab.ui

RESOURCES += \
    vfpresources.qrc
