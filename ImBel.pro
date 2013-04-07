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
              treeitem.h \
              treemodel.h

RESOURCES   = imbel.qrc

SOURCES     = mainwindow.cpp \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp

OTHER_FILES += \
    ToDo.txt
