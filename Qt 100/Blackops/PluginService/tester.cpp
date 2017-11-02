#include "tester.h"


Tester::Tester(QObject *parent) :
    QObject(parent)
{
    try
    {

        Plugins = new PluginManager(this);
        qDebug() << Plugins->LoadAll();
        qDebug() << Plugins->StartAll();

        //qDebug() << Plugins->Install("L:/Bryan/SourceCode/PluginService/PluginService-build-desktop-4_6_4_Release/Plugins/tmp/TestPlugin1.dll");
        //qDebug() << Plugins->Uninstall("TestPlugin1.dll");


//        QStringList list = Plugins->List();
//        foreach(QString item, list)
//        {
//            qDebug() << item;
//        }


        Manager = new CommandManager(this);
        Manager->SetPluginManager(Plugins);

        connect(Manager,SIGNAL(ResponseReady(CommandResponse&)), this, SLOT(ResponseReady(CommandResponse&)));

    }
    catch(QString err)
    {
        qDebug() << "Error: " << err;
    }
    catch(...)
    {
        qDebug() << "UNKNOWN ERROR";
    }
}

void Tester::TestRequest()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Do Something</command><arguments><arg>This is argument 1</arg><arg>This is argument 2</arg><arg>This is argument 3</arg></arguments></commandpacket>";
    request.FromXML(xml);

}

void Tester::TestResponse()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>help</command><arguments><arg>This is argument 1</arg><arg>This is argument 2</arg><arg>This is argument 3</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestLoad()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Load</command><arguments><arg>TestPlugin1.dll</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);

}

void Tester::TestList()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>List</command><arguments></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestInstall()
{
     CommandRequest request;
     QString xml = "<commandpacket><from>Bryan</from><command>Install</command><arguments><arg>L:/Bryan/SourceCode/PluginService/PluginService-build-desktop-4_6_4_Release/Plugins/tmp/TestPlugin1.dll</arg></arguments></commandpacket>";
     request.FromXML(xml);

     Manager->ParseRequest(request);
}

void Tester::TestUninstall()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Uninstall</command><arguments><arg>TestPlugin1.dll</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestStart()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Start</command><arguments><arg>TestPlugin1.dll</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestStop()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Stop</command><arguments><arg>TestPlugin1.dll</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::testCommands()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Commands</command><arguments><arg>TestPlugin1.dll</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestExec1()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Exec</command><arguments><arg>TestPlugin1.dll</arg><arg>Command1</arg><arg>arqument 1</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestExec2()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Exec</command><arguments><arg>TestPlugin1.dll</arg><arg>Command2</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestUnload()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>Unload</command><arguments><arg>TestPlugin1.dll</arg></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestStartAll()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>STARTALL</command><arguments></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestStopAll()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>STOPALL</command><arguments></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestLoadAll()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>LOADALL</command><arguments></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::TestUnloadAll()
{
    CommandRequest request;
    QString xml = "<commandpacket><from>Bryan</from><command>UNLOADALL</command><arguments></arguments></commandpacket>";
    request.FromXML(xml);

    Manager->ParseRequest(request);
}

void Tester::ResponseReady(CommandResponse &Reponse)
{
    qDebug() << "Response from Manager:";
    qDebug() << Reponse.ToXML();
}

