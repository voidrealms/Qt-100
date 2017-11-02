TEMPLATE = lib
TARGET = TestPlugin
CONFIG += plugin release
VERSION = 1.0.0

HEADERS += testplugin.h \
    PluginInterface.h
SOURCES += testplugin.cpp

INSTALLS += target
