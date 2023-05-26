#-------------------------------------------------
#
# Project created by QtCreator 2022-10-31T22:07:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KRoop
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
    apartment.cpp \
    database.cpp \
    db_redactor.cpp

HEADERS += \
        mainwindow.h \
    apartment.h \
    database.h \
    db_redactor.h

FORMS += \
        mainwindow.ui \
    db_redactor.ui

RESOURCES += \
    ../imgs/pic.qrc
