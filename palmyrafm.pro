QT += core widgets gui concurrent

TARGET = palmyrafm
TEMPLATE = app

CONFIG += c++17

HEADERS = palmyrafm.h

SOURCES = main.cpp \
          palmyrafm.cpp \
          dirview.cpp
