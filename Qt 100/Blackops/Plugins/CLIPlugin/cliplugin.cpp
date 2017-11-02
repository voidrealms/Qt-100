#include "cliplugin.h"

Q_EXPORT_PLUGIN2( CLIPLugin, CLIPLugin )

CLIPLugin::CLIPLugin()
{
}

QString CLIPLugin::Name() const
{
    return "Command Line Interface Plugin 1.0";
}

QString CLIPLugin::Description() const
{
    return "Description here";
}

QString CLIPLugin::Status() const
{
    return "Status here";
}

QString CLIPLugin::Install() const
{
    return "Install code here";
}

QString CLIPLugin::Uninstall() const
{
    return "Uninstall code here";
}

QString CLIPLugin::Start() const
{
    return "Start code here";
}

QString CLIPLugin::Stop() const
{
    return "Stop code here";
}

QStringList CLIPLugin::Commands() const
{
    QStringList List;
    List << "Command1" << "Command2";
    return List;
}

QString CLIPLugin::Exec(QString command, QStringList args) const
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
