#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>

class PluginInterface
{
public:
    /**
    * Returns the name of the plugin
    */
    virtual QString Name() const = 0;

    /**
    * Does something cool
    */
    virtual void DoSomething() const = 0;

};

Q_DECLARE_INTERFACE( PluginInterface, "com.voidrealms.PluginApp.PluginInterface/0.1" )


#endif // PLUGININTERFACE_H
