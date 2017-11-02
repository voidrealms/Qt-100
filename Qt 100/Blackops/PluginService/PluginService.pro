#-------------------------------------------------
#
# Project created by QtCreator 2011-12-22T13:08:24
#
#-------------------------------------------------

QT       += core
QT       += network
QT       += xml
QT       -= gui

TARGET = PluginService
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    pluginmanager.cpp \
    commandmanager.cpp \
    tcpserver.cpp \
    tcpclient.cpp \
    commandrequest.cpp \
    commandresponse.cpp \
    tester.cpp \
    pluginitem.cpp

HEADERS += \
    pluginmanager.h \
    commandmanager.h \
    tcpserver.h \
    tcpclient.h \
    plugininterface.h \
    commandrequest.h \
    commandresponse.h \
    tester.h \
    pluginitem.h
