
TEMPLATE = lib
TARGET = CLIPlugin
CONFIG += plugin release
VERSION = 1.0.0

HEADERS += \
    PluginInterface.h \
    cliplugin.h

SOURCES += \
    cliplugin.cpp

INSTALLS += target
