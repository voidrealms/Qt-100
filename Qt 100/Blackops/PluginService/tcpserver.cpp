#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent) :
    QTcpServer(parent)
{
    //Make a new plugin manager to controll the plugins
    cPluginManager  = new PluginManager(this);
    cCommandManager = new CommandManager(this);
    cCommandManager->SetPluginManager(cPluginManager);

    //Load all available plugins
    cPluginManager->LoadAll();

    //Start all available plugins
    cPluginManager->StartAll();
}

void TCPServer::StartServer(qint16 port)
{

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening...";

        //notify connected objects
        emit OnStarted();
    }
}


void TCPServer::StopServer()
{
    this->close();
     qDebug() << "Server stopped";

     // TO DO - kill all active sessions

     //notify connected objects
     emit OnStopped();
}

void TCPServer::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting..." << socketDescriptor;

    //Accept the incomming client
    TCPClient *cClient = new TCPClient(socketDescriptor,this);

    //connect the client signals and slots
    connect(cCommandManager,SIGNAL(ResponseReady(CommandResponse&)),cClient,SLOT(ResponseReady(CommandResponse&)));
    connect(cClient,SIGNAL(RequestReady(CommandRequest&)), cCommandManager,SLOT(ParseRequest(CommandRequest&)));
}

