QT += core
QT += network
QT -= gui

CONFIG += c++11

CONFIG += debug_and_release
CONFIG += build_all

TARGET = BMS-server-status
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    memoryhandler.cpp \
    bmsrequestcontroller.cpp \
    pilotstatuscontroller.cpp \
    pilotlistcontroller.cpp

HEADERS += \
    memoryhandler.h \
    bmsrequestcontroller.h \
    pilotstatuscontroller.h \
    FlightData.h \
    pilotlistcontroller.h

EXTRAS += doc
include(3rd/QtWebApp/httpserver/httpserver.pri)
