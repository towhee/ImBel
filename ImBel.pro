#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T04:40:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImBel
TEMPLATE = app


FORMS       = mainwindow.ui

HEADERS     = mainwindow.h \
              ui_mainwindow.h \
              dataitem.h \
              datamodel.h \
              delegate.h \
    propertyeditor.h

RESOURCES   = imbel.qrc

SOURCES     = mainwindow.cpp \
              dataitem.cpp \
              datamodel.cpp \
              main.cpp \
              delegate.cpp \
    propertyeditor.cpp

OTHER_FILES += \
    ToDo.txt \
    Notes.txt
