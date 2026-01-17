QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = ProgettoGestione
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Dipendente.cpp \
    Junior.cpp \
    Senior.cpp \
    Progetto.cpp \
    Gestore.cpp

HEADERS += \
    mainwindow.h \
    Dipendente.h \
    Junior.h \
    Senior.h \
    Progetto.h \
    Gestore.h
