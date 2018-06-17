#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T11:02:01
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += xml
CONFIG += openssl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testowo
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

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    listpackage.cpp \
    pocztapolska.cpp \
    inpostzdarzenie.cpp \
    inpost.cpp \
    infopackageinpost.cpp \
    inpoststatusy.cpp \
    inpoststatus.cpp

HEADERS += \
        mainwindow.h \
    listpackage.h \
    pocztapolska.h \
    inpostzdarzenie.h \
    inpost.h \
    infopackageinpost.h \
    inpoststatusy.h \
    inpoststatus.h

FORMS += \
        mainwindow.ui \
    listpackage.ui \
    infopackageinpost.ui
