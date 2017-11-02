#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "PluginInterface.h"

class TestPlugin : public QObject, PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
public:

    explicit TestPlugin();

    /**
    * Returns the name of the plugin
    */
    QString Name() const;

    /**
    * Returns the description of the plugin
    */
    QString Description() const;

    /**
    * Returns the status of the plugin
    */
    QString Status() const;

    /**
    * Tells the plugin that it is being installed
    * The plugin should perform any installtion code
    */
    QString Install() const;

    /**
    * Tells the plugin that it is being uninstalled
    * The plugin should perform any uninstalltion code
    */
    QString Uninstall() const;

    /**
    * Called when the plugin is started
    */
    QString Start() const;

    /**
    * Called when the plugin is stopped
    */
    QString Stop() const;

    /**
    * Returns a QStringList of available commands
    */
    QStringList Commands() const;

    /**
    * Askes the plugin to execute a command and returns the results
    * @param command The command to execute
    * @param args A list of arguments for the command
    */
    QString Exec(QString command, QStringList args) const;

};

#endif // TESTPLUGIN_H
