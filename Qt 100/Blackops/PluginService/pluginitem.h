#ifndef PLUGINITEM_H
#define PLUGINITEM_H

#include <QObject>
#include <QString>
#include <QPluginLoader>
#include "plugininterface.h"

class PluginItem : public QObject
{
    Q_OBJECT
public:
    explicit PluginItem(QObject *parent = 0,QPluginLoader* LoaderObj = 0, PluginInterface* PluginObj = 0);
    
    //! Returns a pointer to the plugin loader
    QPluginLoader* PluginLoader();

    //! Returns a pointer to the plugin interface
    PluginInterface* Plugin();

signals:
    
public slots:

private:

    //! A pointer to the plugin loader
    QPluginLoader *Loader;

    //! A pointer to the plugin interface
    PluginInterface *Interface;
    
};

#endif // PLUGINITEM_H
