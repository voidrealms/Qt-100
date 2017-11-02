TEMPLATE = lib
TARGET = MyPlugin
CONFIG += plugin release
VERSION = 1.0.0

INSTALLS += target

HEADERS += \
    PluginInterface.h \
    myplugin.h

SOURCES += \
    myplugin.cpp



