TEMPLATE = app
TARGET = palmyrafm

CONFIG += qt warn_on release

HEADERS = palmyrafm.h \
      dirview.h
SOURCES = main.cpp \
      palmyrafm.cpp \
      dirview.cpp

QT += core gui
QT += widgets
greaterThan(QT_MAJOR_VERSION, X): QT += widgets
