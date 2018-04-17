#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T09:50:21
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBMS_Mittelstufenprojekt_V02
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
    datenverwaltung.cpp \
    parser.cpp \
    parsercsv.cpp \
    exportdialog.cpp \
    parserxml.cpp \
    newtabledialog.cpp

HEADERS += \
        mainwindow.h \
    datenverwaltung.h \
    parser.h \
    parsercsv.h \
    exportdialog.h \
    parserxml.h \
    newtabledialog.h

FORMS += \
        mainwindow.ui \
    mainwindow.ui \
    exportdialog.ui \
    newtabledialog.ui
