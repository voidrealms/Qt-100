#include "testplugin.h"

Q_EXPORT_PLUGIN2( TestPlugin, TestPlugin )

TestPlugin::TestPlugin()
{
}

QString TestPlugin::Name() const
{
    return "Test Plugin 1.0";
}

QString TestPlugin::Description() const
{
    return "Description here";
}

QString TestPlugin::Status() const
{
    return "Status here";
}

QString TestPlugin::Install() const
{
    return "Install code here";
}

QString TestPlugin::Uninstall() const
{
    return "Uninstall code here";
}

QString TestPlugin::Start() const
{
    return "Start code here";
}

QString TestPlugin::Stop() const
{
    return "Stop code here";
}

QStringList TestPlugin::Commands() const
{
    QStringList List;
    List << "Command1" << "Command2";
    return List;
}

QString TestPlugin::Exec(QString command, QStringList args) const
{

    QString arg = QString::number(args.count());
    QString ret;

    if(command.toUpper() == "COMMAND1")
    {
        ret = "Execute: " + command + " with " + arg + " args\r\n";
        ret.append("You entered Command1, yay!\r\n");
    }

    if(command.toUpper() == "COMMAND2")
    {
        ret = "Error: " + command + " with " + arg + " args\r\n";
        ret.append("You entered Command2, how sad!\r\n");
    }

    return ret;
}
