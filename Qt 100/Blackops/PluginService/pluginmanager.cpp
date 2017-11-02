#include "pluginmanager.h"

PluginManager::PluginManager(QObject *parent) :
    QObject(parent)
{
    //Find the plugin path
    path = QDir(path.currentPath());

    //Change to the plugin path
    if(!path.cd("Plugins")) qDebug() << "Could not find plugin directory";

    qDebug() << "CURRENTPATH = " << path.absolutePath();
}

PluginItem* PluginManager::GetPlugin(QString Name)
{
    PluginItem *plugin = NULL;

    foreach(QString item, PluginList.keys())
    {
        if(item == Name)
        {
            plugin = PluginList.value(item);
            return plugin;
        }
    }

    return plugin;
}

QStringList PluginManager::List()
{
    QStringList List;

    foreach(QString name, PluginList.keys())
    {
        PluginItem *item = PluginList.value(name);
        List.append(name + " - " + item->Plugin()->Name() + " - " +  item->Plugin()->Description());
    }

    return List;
}

QString PluginManager::Install(QString Filename)
{

    try
    {
        //copy the file to the plugin directory
        QFileInfo Info(Filename);
        QFile file(Filename);

        QString NewFile = path.absolutePath() + "/" + Info.fileName();
        QFileInfo NewInfo(NewFile);


        if(!Info.exists()) throw QString("File not found!");
        if(NewInfo.exists()) throw QString("File already exists");


        if(file.copy(NewFile))
        {
            //Load the plugin
            Load(Info.fileName());

            //get the plugin from the list and call the install routine
            PluginItem *item = GetPlugin(Info.fileName());
            if(item != NULL)
            {
                item->Plugin()->Install();
            }
        }
        else
        {
            throw file.errorString();
        }

        return "Installed: " + Filename;

    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Install()";
    }
}

QString PluginManager::Uninstall(QString Name)
{
    try
    {
        //Remove the file from memory
        Unload(Name);

        //remove the file
        QFile file(path.absolutePath() + "/" + Name);

        if(file.exists())
        {
            if(!file.remove())
            {
                throw file.errorString();
            }
        }

        return "Uninstalled: " + Name;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Uninstall()";
    }
}

QString PluginManager::Start(QString Name)
{
    try
    {
        QString ret;
        PluginItem *item = GetPlugin(Name);
        if(item != NULL)
        {
            ret = item->Plugin()->Start();
        }
        else
        {
            throw QString("Plugin not found!");
        }

        return ret;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Start()";
    }
}

QString PluginManager::Stop(QString Name)
{
    try
    {
        QString ret;
        PluginItem *item = GetPlugin(Name);
        if(item != NULL)
        {
            ret = item->Plugin()->Stop();
        }
        else
        {
            throw QString("Plugin not found!");
        }

        return ret;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Stop()";
    }
}

QStringList PluginManager::Commands(QString Name)
{
    QStringList List;

    PluginItem *item = GetPlugin(Name);
    if(item != NULL)
    {
       List = item->Plugin()->Commands();
    }
    else
    {
        throw QString("Plugin not found!");
    }

    return List;
}

QString PluginManager::Exec(QString Name, QString command, QStringList args)
{
    try
    {
        QString ret;
        PluginItem *item = GetPlugin(Name);
        if(item != NULL)
        {
           ret = item->Plugin()->Exec(command,args);
        }
        else
        {
            throw QString("Plugin not found!");
        }

        return ret;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Exec()";
    }
}

QString PluginManager::Load(QString Name)
{
    try
    {
        if(PluginList.contains(Name)) throw Name + " already loaded!";

        QString ret;
        QString filename = path.absolutePath() + "/" + Name;
        QPluginLoader *loader = new QPluginLoader(filename,this);
        QObject *possiblePlugin = loader->instance();

        if(possiblePlugin)
        {

            PluginInterface *plugin = qobject_cast<PluginInterface*>( possiblePlugin );
            if( plugin )
            {
                //Create the plugin
                PluginItem *item = new PluginItem(this,loader,plugin);

                //Add the plugin to the list of loaded plugins
                PluginList.insert(Name, item);

                ret = "Loaded: " + Name;
            }
            qDebug() << "Loaded: " << ret;
            return ret;
        }
        else
        {
            throw QString(loader->errorString());
            loader->deleteLater();
        }
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Load()";
    }
}

QString PluginManager::Unload(QString Name)
{

    try
    {
        PluginItem *item = GetPlugin(Name);
        if(item != NULL)
        {
            item->Plugin()->Uninstall();
            item->PluginLoader()->unload();

            //remove it from the list of loaded plugins
            PluginList.remove(Name);
            delete item;
            item = NULL;
        }
        else
        {
            throw QString("Plugin not found!");
        }

        return "Unloaded: " + Name;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Unload()";
    }
}

QString PluginManager::StartAll()
{
    try
    {
        QString ret = "Starting all plugins\r\n";
        foreach( QString filename, path.entryList(QDir::Files))
        {
            ret.append(filename + " = " + Start(filename)  + "\r\n");
        }
        ret.append("Done starting all plugins\r\n");
        return ret;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Unload()";
    }
}

QString PluginManager::StopAll()
{
    try
    {
        QString ret = "Stopping all plugins\r\n";
        foreach( QString filename, path.entryList(QDir::Files))
        {
            ret.append(filename + " = " + Stop(filename) + "\r\n");
        }
        ret.append("Done stopping all plugins\r\n");
        return ret;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Unload()";
    }
}

QString PluginManager::LoadAll()
{
    try
    {
        QString ret = "Loading all plugins\r\n";
        foreach( QString filename, path.entryList(QDir::Files))
        {
            ret.append(Load(filename) + "\r\n");
        }
        ret.append("Done loading all plugins\r\n");
        return ret;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Unload()";
    }
}

QString PluginManager::UnloadAll()
{
    try
    {
        QString ret = "Unloading all plugins\r\n";
        foreach( QString filename, path.entryList(QDir::Files))
        {
            ret.append(Unload(filename) + "\r\n");
        }
        ret.append("Done unloading all plugins\r\n");
        return ret;
    }
    catch(QString err)
    {
        return "ERROR: " + err;
    }
    catch(...)
    {
        return "ERROR: Unknown Error in Unload()";
    }
}

