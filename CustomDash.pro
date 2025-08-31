#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomDash
TEMPLATE = app

QMAKE_CXXFLAGS += /utf-8

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        customdash.cpp \
        main.cpp \
        widgetselectionwindow.cpp \
        canvasscene.cpp \
        customwidget.cpp \
        idgenerator.cpp \
        datarefreshthread.cpp

HEADERS += \
        customdash.h \
        widgetselectionwindow.h \
        canvasscene.h \
        customwidget.h \
        idgenerator.h \
        datarefreshthread.h \
        widgetinterface.h

FORMS += \
        customdash.ui \
        widgetselectionwindow.ui

