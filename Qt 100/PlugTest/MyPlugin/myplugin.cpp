#include "myplugin.h"

MyPlugin::MyPlugin()
{
}

Q_EXPORT_PLUGIN2( MyPlugin, MyPlugin )

QString MyPlugin::Name() const
{
    return "My Plugin Version 1";
}

void MyPlugin::DoSomething() const
{
    qDebug() << "Doing something really cool here";
}
