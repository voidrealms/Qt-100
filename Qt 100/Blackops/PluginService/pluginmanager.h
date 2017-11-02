/*
* PluginManager
* Manages plugins and notifies all connected objects using Qt signals and slots
*
* Bryan Cairns - 2011
* All rights reserved.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include "plugininterface.h"
#include "pluginitem.h"

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = 0);
    
private:
    /*!
    * The path to the plugins
    */
    QDir path;

    /*!
    * A QMap<QString,PluginInterface*> of all loaded plugins
    */
    QMap<QString,PluginItem*> PluginList; /**< A List of all plugins loaded */

public slots:
    /*!
    * Gets a plugin interface fromt he loaded plugins
    * @param Name the name of the plugin
    */
    PluginItem* GetPlugin(QString Name);

    /*!
    * Lists all the plugins and their status
    */
    QStringList List();

    /*!
    * Install a plugin
    * @param Filename the filename of the plugin
    */
    QString Install(QString Filename);

    /*!
    * Uninstall a plugin
    * @param Name the name of the plugin
    */
    QString Uninstall(QString Name);

    /*!
    * Start a plugin
    * @param Name the name of the plugin
    */
    QString Start(QString Name);

    /*!
    * Stop the plugin
    * @param Name the name of the plugin
    */
    QString Stop(QString Name);

    /*!
    * List of the available commands a plugin supports
    * @param Name the name of the plugin
    */
    QStringList Commands(QString Name);

    /*!
    * Execute a plugin command
    * @param Name the name of the plugin
    * @param command the command to execute
    * @param args a QStringList of arguments for the command
    */
    QString Exec(QString Name, QString command, QStringList args);

    /*!
    * Load a plugin into memory
    */
    QString Load(QString Name);

    /*!
    * Unload a plugin from memory
    * @param Name the name of the plugin
    */
    QString Unload(QString Name);

    /*!
    * Start all plugins
    */
    QString StartAll();

    /*!
    * Stop all plugins
    */
    QString StopAll();

    /*!
    * Load all plugins into memory
    */
    QString LoadAll();

    /*!
    * Unload all plugins from memory
    */
    QString UnloadAll();
};

#endif // PLUGINMANAGER_H
