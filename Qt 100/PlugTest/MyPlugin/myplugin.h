#ifndef MYPLUGIN_H
#define MYPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QDebug>
#include "PluginInterface.h"

class MyPlugin : public QObject, PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

public:
    MyPlugin();

    /**
    * Returns the name of the plugin
    */
    QString Name() const;

    /**
    * Does something cool
    */
    void DoSomething() const;

signals:

public slots:

};

#endif // MYPLUGIN_H
