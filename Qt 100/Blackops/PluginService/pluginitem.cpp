#include "pluginitem.h"

PluginItem::PluginItem(QObject *parent,QPluginLoader* LoaderObj, PluginInterface* PluginObj) :
    QObject(parent)
{
    Loader = LoaderObj;
    Interface = PluginObj;
}

QPluginLoader *PluginItem::PluginLoader()
{
    return Loader;
}

PluginInterface *PluginItem::Plugin()
{
    return Interface;
}
