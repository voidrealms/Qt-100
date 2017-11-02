#include "commandmanager.h"

CommandManager::CommandManager(QObject *parent) :
    QObject(parent)
{
}

void CommandManager::SetPluginManager(PluginManager *ObjectManager)
{
    Plugins = ObjectManager;
}

void CommandManager::ParseRequest(CommandRequest &Request)
{

    CommandResponse Response;

    Response.FromRequest(Request);

    QMetaObject metaObject = this->staticMetaObject;
    QMetaEnum metaEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Commands"));

    Response.SetResponseData("No data");

    //Idenitfy and handle the command
    switch(metaEnum.keysToValue(Response.Command().toUpper().toAscii()))
    {
    case HELP: // Lists all available commands
        DoHelp(&Response, &Request);
        break;

    case QUIT: // Closes the session
        DoQuit(&Response, &Request);
        break;

    case LIST: // Lists all plugins and the status of each one
        DoList(&Response, &Request);
        break;

    case INSTALL: // Installs a plugin
        DoInstall(&Response, &Request);
        break;

    case UNINSTALL: // Uninstalls a plugin
        DoUninstall(&Response, &Request);
        break;

    case START:  // Starts a plugin
        DoStart(&Response, &Request);
        break;

    case STOP: // Stops a plugin
        DoStop(&Response, &Request);
        break;

    case COMMANDS: // Lists the commands available from the plugin
        DoCommands(&Response, &Request);
        break;

    case EXEC: // Executes a command from a plugin
        DoExec(&Response, &Request);
        break;

    case LOAD: // Loads a plugin into memory
        DoLoad(&Response, &Request);
        break;

    case UNLOAD: // Unloads a plugin from memory
        DoUnload(&Response, &Request);
        break;

    case STARTALL: // Starts all plugins
        DoStartAll(&Response, &Request);
        break;

    case STOPALL: // Stops all plugin
        DoStopAll(&Response, &Request);
        break;

    case LOADALL: // Loads all plugins into memory
        DoLoadAll(&Response, &Request);
        break;

    case UNLOADALL: // Unloads all plugins from memory
        DoUnloadAll(&Response, &Request);
        break;

    default:
        DoDefault(&Response, &Request);
        break;
    }

    //return Response;
    emit ResponseReady(Response);

}

void CommandManager::SetResponse(Responses ResponseType, QString ResponseData,CommandResponse *Response)
{   

    QMetaObject metaObject = this->staticMetaObject;
    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator("Responses"));
    QString StatusText;

    if(ResponseData.toUpper().startsWith("ERROR"))
    {
        //Set the status to error if there was a plugin level error
        StatusText = metaEnum.valueToKey(ERROR);
    }
    else
    {
        //Find the enum item and convert it to text
        StatusText = metaEnum.valueToKey(ResponseType);
    }

    Response->SetStatus(StatusText);
    Response->SetResponseData(ResponseData);
}

void CommandManager::DoDefault(CommandResponse *Response,CommandRequest *Request)
{
    try
    {
        SetResponse(SUCCESS,"Command not handled, please use HELP to see a list of commands.",Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoQuit()",Response);
    }
}

void CommandManager::DoHelp(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData = "Core System Help:\r\n";
        ResponseData.append("HELP - Lists all available commands\r\n");
        ResponseData.append("QUIT - Closes the session\r\n");
        ResponseData.append("LIST - Lists all plugins and the status of each one\r\n");
        ResponseData.append("INSTALL (filename) - Instals a plugin\r\n");
        ResponseData.append("UNINSTALL (name) - Uninstalls a plugin\r\n");
        ResponseData.append("START (name) - Starts a plugin\r\n");
        ResponseData.append("STOP (name) - Stops a plugin\r\n");
        ResponseData.append("COMMANDS (name) - Lists the commands available from the plugin\r\n");
        ResponseData.append("EXEC (name) (command) (arg 1) (arg 2) - Executes a command from a plugin\r\n");
        ResponseData.append("LOAD (name) - Loads a plugin into memory\r\n");
        ResponseData.append("UNLOAD (name) - Unloads a plugin from memory\r\n");
        ResponseData.append("STARTALL- Starts all plugins\r\n");
        ResponseData.append("STOPALL - Stops all plugin\r\n");
        ResponseData.append("LOADALL - Loads all plugins into memory\r\n");
        ResponseData.append("UNLOADALL - Unloads all plugins from memory\r\n");

        SetResponse(SUCCESS,ResponseData,Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoHelp()",Response);
    }
}

void CommandManager::DoQuit(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        SetResponse(SUCCESS,"Goodbye",Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoQuit()",Response);
    }
}

void CommandManager::DoList(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QStringList List = Plugins->List();
        QString ResponseData = "Loaded Plugins:\r\n";

        foreach(QString item, List)
        {
            ResponseData.append(item + "\r\n");
        }

        SetResponse(SUCCESS,ResponseData,Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoList()",Response);
    }
}

void CommandManager::DoInstall(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 0)
        {
            QString Name = Request->Args().at(0).trimmed();
            ResponseData.append(Plugins->Install(Name));
            QFileInfo info(Name);
            Response->SetSource(info.fileName());
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin to install!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoInstall()",Response);
    }
}

void CommandManager::DoUninstall(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 0)
        {
            QString Name = Request->Args().at(0).trimmed();
            ResponseData.append(Plugins->Uninstall(Name));
            Response->SetSource(Name);
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin to uninstall!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoUninstall()",Response);
    }
}

void CommandManager::DoStart(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 0)
        {
            QString Name = Request->Args().at(0).trimmed();
            ResponseData.append(Plugins->Start(Name));
            Response->SetSource(Name);
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin to start!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoStart()",Response);
    }
}

void CommandManager::DoStop(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 0)
        {
            QString Name = Request->Args().at(0).trimmed();
            ResponseData.append(Plugins->Stop(Name));
            Response->SetSource(Name);
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin to stop!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoStop()",Response);
    }
}

void CommandManager::DoCommands(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 0)
        {
            QString Name = Request->Args().at(0).trimmed();

            QStringList List = Plugins->Commands(Name);
            foreach(QString item, List)
            {
                ResponseData.append(item + "\r\n");
            }

            Response->SetSource(Name);
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin to get commands from!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoCommands()",Response);
    }
}

void CommandManager::DoExec(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 1)
        {
            QString Name = Request->Args().at(0).trimmed();
            QString Command = Request->Args().at(1).trimmed();
            QStringList Args = Request->Args();

            Args.removeAt(0); //Remove the plugin name
            Args.removeAt(0); //Remove the Command

            ResponseData.append(Plugins->Exec(Name,Command,Args));

            Response->SetSource(Name);
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin, the command, and any arguments!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoExec()",Response);
    }
}

void CommandManager::DoLoad(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 0)
        {
            QString Name = Request->Args().at(0).trimmed();
            ResponseData.append(Plugins->Load(Name));
            Response->SetSource(Name);
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin to load!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoLoad()",Response);
    }
}

void CommandManager::DoUnload(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;

        if(Request->Args().count() > 0)
        {
            QString Name = Request->Args().at(0).trimmed();
            ResponseData.append(Plugins->Unload(Name));
            Response->SetSource(Name);
            SetResponse(SUCCESS,ResponseData,Response);
        }
        else
        {
            ResponseData = "Please include the filename of the plugin to unload!";
            SetResponse(ERROR,ResponseData,Response);
        }
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoUnload()",Response);
    }
}

void CommandManager::DoStartAll(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;
        ResponseData.append(Plugins->StartAll());
        SetResponse(SUCCESS,ResponseData,Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoStartAll()",Response);
    }
}

void CommandManager::DoStopAll(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;
        ResponseData.append(Plugins->StopAll());
        SetResponse(SUCCESS,ResponseData,Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoStopAll()",Response);
    }
}

void CommandManager::DoLoadAll(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;
        ResponseData.append(Plugins->LoadAll());
        SetResponse(SUCCESS,ResponseData,Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoLoadAll()",Response);
    }
}

void CommandManager::DoUnloadAll(CommandResponse *Response, CommandRequest *Request)
{
    try
    {
        QString ResponseData;
        ResponseData.append(Plugins->UnloadAll());
        SetResponse(SUCCESS,ResponseData,Response);
    }
    catch(...)
    {
        SetResponse(ERROR,"An error occured in DoUnloadAll()",Response);
    }
}



