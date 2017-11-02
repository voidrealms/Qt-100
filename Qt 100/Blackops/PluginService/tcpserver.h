/*
* TCPServer
* Listens for incomming TCP connections
*
* This class uses the following
* TCPClient
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


#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "tcpclient.h"
#include "pluginmanager.h"
#include "commandmanager.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:

    /*!
    * Constructor
    * @param parent The parent object
    */
    explicit TCPServer(QObject *parent = 0);
    
    /*!
    * Starts the TCP Server
    * @param port The port to start the server on
    */
    void StartServer(qint16 port);

    /*!
    * Stops the TCP Server
    */
    void StopServer();

signals:
    /*!
    * Signal indicates the TCP Server has stopped
    */
    void OnStarted();

    /*!
    * Signal indicates the TCP Server has stopped
    */
    void OnStopped();

public slots:


protected:

    /**
    * Processes incomming TCP connections
    * @param socketDescriptor The descriptor of the conection
    */
    void incomingConnection(int socketDescriptor);

private:
    PluginManager *cPluginManager;
    CommandManager *cCommandManager;
    
};

#endif // TCPSERVER_H
