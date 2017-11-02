/*
* CommandManager
* Parses incomming commands and returns a response to the caller
*
* This class uses the following
* PluginManager
* TCPServer
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

#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QMetaEnum>
#include "commandrequest.h"
#include "commandresponse.h"
#include "pluginmanager.h"

class CommandManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(Commands)
    Q_ENUMS(Responses)


public:
    explicit CommandManager(QObject *parent = 0);
    
    /*!
    * Commands enumeration
    */
    enum Commands
    {
        HELP,               /**< Lists all available commands */
        QUIT,               /**< Closes the session */
        LIST,               /**< Lists all plugins and the status of each one */
        INSTALL,            /**< Installs a plugin */
        UNINSTALL,          /**< Uninstalls a plugin */
        START,              /**< Starts a plugin */
        STOP,               /**< Stops a plugin */
        COMMANDS,           /**< Lists the commands available from the plugin */
        EXEC,               /**< Executes a command from a plugin */
        LOAD,               /**< Loads a plugin into memory */
        UNLOAD,             /**< Unloads a plugin from memory */
        STARTALL,           /**< Starts all plugins */
        STOPALL,            /**< Stops all plugin */
        LOADALL,            /**< Loads all plugins into memory */
        UNLOADALL           /**< Unloads all plugins from memory */
    };

    /*!
    * Response enumeration
    */
    enum Responses
    {
        INFO,               /**< Information Response */
        SYSTEM,             /**< Shell Response */
        PLUGIN,             /**< Plugin Response */
        SUCCESS,            /**< Success Response */
        ERROR               /**< Error Response */
    };


signals:

    /*!
    * Signal is emitted when the response has been parsed and is ready to be sent back
    * @param Reponse The response data
    */
    void ResponseReady(CommandResponse &Reponse);


public slots:
    /*!
    * Sets the plugin manager object
    * @param ObjectManager The plugin manager object
    */
    void SetPluginManager(PluginManager *ObjectManager);

    /*!
    * Slot is called when a request is made
    * @param Request The request data
    */
    void ParseRequest(CommandRequest &Request);
\
private:
    /*!
    * A pointer to the plugin object
    */
    PluginManager *Plugins;

    /*!
    * Slot is called when a request is made
    * @param ResponseType The type of response
    * @param ResponseData The response data
    * @param Response The response object
    */
    void SetResponse(Responses ResponseType, QString ResponseData, CommandResponse *Response);

    /*!
    * Returns the default message
    * @param Response The response object
    * @param Request The request object
    */
    void DoDefault(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Returns the help information
    * @param Response The response object
    * @param Request The request object
    */
    void DoHelp(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Asks the application to close
    * @param Response The response object
    * @param Request The request object
    */
    void DoQuit(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Returns a list of all loaded plugins
    * @param Response The response object
    * @param Request The request object
    */
    void DoList(CommandResponse *Response, CommandRequest *Request);
    
    /*!
    * Installs a plugin
    * @param Response The response object
    * @param Request The request object
    */
    void DoInstall(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Uninstalls a plugin
    * @param Response The response object
    * @param Request The request object
    */
    void DoUninstall(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Starts a plugin
    * @param Response The response object
    * @param Request The request object
    */
    void DoStart(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Stops a plugin
    * @param Response The response object
    * @param Request The request object
    */
    void DoStop(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Gets a list of commands from a plugin
    * @param Response The response object
    * @param Request The request object
    */
    void DoCommands(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Executes a command in a plugin
    * @param Response The response object
    * @param Request The request object
    */
    void DoExec(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Loads a plugin into memory
    * @param Response The response object
    * @param Request The request object
    */
    void DoLoad(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Unloads a plugin from memory
    * @param Response The response object
    * @param Request The request object
    */
    void DoUnload(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Starts all plugins
    * @param Response The response object
    */
    void DoStartAll(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Stops all plugins
    * @param Response The response object
    * @param Request The request object
    */
    void DoStopAll(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Loads all plugins into memory
    * @param Response The response object
    * @param Request The request object
    */
    void DoLoadAll(CommandResponse *Response, CommandRequest *Request);

    /*!
    * Unloads all plugins into memory
    * @param Response The response object
    * @param Request The request object
    */
    void DoUnloadAll(CommandResponse *Response, CommandRequest *Request);
};

#endif // COMMANDMANAGER_H
