#include "appclass.h"

AppClass::AppClass(QObject *parent) :
    QObject(parent)
{
}

void AppClass::LoadAllPlugins()
{
    QDir path(QDir::currentPath() + "/plugins");

    //Display the current path and switch to the plugin directory
    qDebug() << "current path is: " << path.currentPath();

    //try to load the plugins
    foreach( QString filename, path.entryList(QDir::Files))
    {
        LoadPlugin(path.absolutePath() + "/" +  filename);
    }

}

void AppClass::LoadPlugin(QString Filename)
{

    qDebug() << "Loading: " << Filename;
    QPluginLoader loader(Filename);
    QObject *possiblePlugin = loader.instance();

    if(possiblePlugin)
    {

        PluginInterface *plugin = qobject_cast<PluginInterface*>( possiblePlugin );
        if( plugin )
        {
            qDebug() << "Loaded: " << plugin->Name();

            //Tell the plugin to do something cool
            plugin->DoSomething();
        }
    }
    else
    {
        qDebug() << "Not a plugin: " << Filename << " = " << loader.errorString();

    }
}
