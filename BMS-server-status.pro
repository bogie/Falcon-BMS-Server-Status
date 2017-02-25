QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = BMS-server-status
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    memoryhandler.cpp \
    bmsrequestcontroller.cpp \
    playerlistcontroller.cpp

HEADERS += \
    memoryhandler.h \
    bmsrequestcontroller.h \
    playerlistcontroller.h

include(3rd/QtWebApp/httpserver/httpserver.pri)
