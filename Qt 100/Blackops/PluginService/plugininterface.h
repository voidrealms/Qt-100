/*
* PluginInterface
* All plugins must use this interface
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
*
* Plugins that can run as a long as the Service runs
* or they can simply return results from executed commands
*/


#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>
#include <QStringList>

class PluginInterface
{

public:
    /*!
    * Returns the name of the plugin
    */
    virtual QString Name() const = 0;

    /*!
    * Returns the description of the plugin
    */
    virtual QString Description() const = 0;

    /*!
    * Returns the status of the plugin
    */
    virtual QString Status() const = 0;

    /*!
    * Tells the plugin that it is being installed
    * The plugin should perform any installtion code
    */
    virtual QString Install() const = 0;

    /*!
    * Tells the plugin that it is being uninstalled
    * The plugin should perform any uninstalltion code
    */
    virtual QString Uninstall() const = 0;

    /*!
    * Called when the plugin is started
    */
    virtual QString Start() const = 0;

    /*!
    * Called when the plugin is stopped
    */
    virtual QString Stop() const = 0;

    /*!
    * Returns a QStringList of available commands
    */
    virtual QStringList Commands() const = 0;

    /*!
    * Askes the plugin to execute a command and returns the results
    * @param command The command to execute
    * @param args A list of arguments for the command
    */
    virtual QString Exec(QString command, QStringList args) const = 0;
};

Q_DECLARE_INTERFACE( PluginInterface, "com.voidrealms.PlugService.PluginInterface/0.1" )


#endif // PLUGININTERFACE_H
