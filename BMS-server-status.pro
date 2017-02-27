QT += core
QT += network
QT -= gui

CONFIG += c++11

CONFIG += debug_and_release

TARGET = BMS-server-status
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    memoryhandler.cpp \
    bmsrequestcontroller.cpp \
    playerlistcontroller.cpp \
    pilotstatuscontroller.cpp

HEADERS += \
    memoryhandler.h \
    bmsrequestcontroller.h \
    playerlistcontroller.h \
    pilotstatuscontroller.h \
    FlightData.h

EXTRAS += doc
include(3rd/QtWebApp/httpserver/httpserver.pri)
