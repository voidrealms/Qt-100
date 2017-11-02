#include "tcpclient.h"

TCPClient::TCPClient(int SocketDescriptor,QObject *parent) :
    QObject(parent)
{
    SessionID = SocketDescriptor;

    Socket = new QTcpSocket(this);
    if(!Socket->setSocketDescriptor(SessionID))
    {
        qDebug() << SessionID << " Error binding socket";
        return;
    }

    //connect the signals
    connect(Socket,SIGNAL(readyRead()),this,SLOT(SocketReadyRead()),Qt::DirectConnection);
    connect(Socket,SIGNAL(disconnected()),this,SLOT(SocketDisconnected()),Qt::DirectConnection);

    qDebug() << SessionID << " session Connected";
}

void TCPClient::SocketReadyRead()
{

    //Keep adding to the command buffer
    QByteArray Data = Socket->readAll();
    qDebug() << SessionID << " Data: " << Data;

    CommandBuffer.append(Data);

    //Check to see if the CommandBuffer has a command
    if(CommandBuffer.endsWith('\n'))
    {
        //Process the command
        CommandRequest Request;
        Request.FromString(CommandBuffer);
        emit RequestReady(Request);
        CommandBuffer.clear();
    }
}

void TCPClient::SocketDisconnected()
{
    qDebug() << SessionID << " session disconnected";

    //Cleanup
    Socket->deleteLater();
    this->deleteLater();
}

void TCPClient::SendResponse(QByteArray data)
{
    //Send the data to the client
    Socket->write(data);
}

void TCPClient::ResponseReady(CommandResponse &Reponse)
{
    //Send the data to the client
    Socket->write(Reponse.ToString().toAscii());
}
