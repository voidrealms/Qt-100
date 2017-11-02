/*
* TCPClient
* Represents a connected TCPClient
*
*
* This class uses the following
* CommandManager
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


#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include "pluginmanager.h"
#include "commandmanager.h"
#include "commandrequest.h"
#include "commandresponse.h"

class TCPClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPClient(int SocketDescriptor,QObject *parent = 0);
    
signals:
    /*!
    * Signal to the Command Manager that a rquest is ready
    * @param Request The request data
    */
    void RequestReady(CommandRequest &Request);

public slots:
    /*!
    * Gets the request from the client
    */
    void SocketReadyRead();

    /*!
    * Slot for the TCP socket disconnected() signal
    */
    void SocketDisconnected();

    /*!
    * Sends the response to the client socket
    * @param data The QByteArray to send
    */
    void SendResponse(QByteArray data);

    /*!
    * Called when the CommandManager has data to process
    * @param data The QByteArray to send
    */
    void ResponseReady(CommandResponse &Reponse);

private:
    int SessionID;
    QTcpSocket *Socket;
    QString CommandBuffer;

};

#endif // TCPCLIENT_H
