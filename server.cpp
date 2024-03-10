#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 2323)) //Tells the server to listen for incoming connections
    {
        qDebug() << "Start";
    }
    else
    {
        qDebug() << "Error";
    }
    nextBlockSize = 0;

    connect(this, &QTcpServer::newConnection, this, &Server::slotNewConnection);
}

void Server::incomingConnection(qintptr socketDescriptor) //This virtual function is called by QTcpServer when a new connection is available
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor); //  The socketDescriptor argument is the native socket descriptor for the accepted connection
    connect(socket, &QTcpSocket::bytesWritten, this, &Server::slotbytesWritten);
    connect(socket, &QTcpSocket::disconnected, this, &Server::slotDisconnected);

    Sockets.push_back(socket);

    qDebug() << "Client connected";
    qDebug() << "INFORMATION ABOUT SERVER SOCKET";
    qDebug() << "socketDescriptor()" << socket->socketDescriptor();
    qDebug() << "isValid()" << socket->isValid();
    qDebug() << "PeerPort()" << socket->peerPort() << "PeerAddress()" << socket->peerAddress() << "PeerName()" << socket->peerName();
    qDebug() << "localPort()" << socket->localPort() << "localAddress()" << socket->localAddress();
}

void Server::slotbytesWritten(qint64 bytes)
{
    qDebug() << "bytes" << bytes;
}

void Server::slotNewConnection()
{
    int i = 0;
    for (;;)
    {
        this->waitForNewConnection(100);
        SendToClient(QString::number(i) + " " + QString::number(i+1) + " " + QString::number(i+2) + " " + QString::number(i+3));
        i ++;
    }
}

void Server::slotDisconnected()
{
    qDebug() << "slotDisconnected Server";
    socket = (QTcpSocket*)sender();
    qDebug() << "Все сокеты" << Sockets;
    Sockets.remove(Sockets.indexOf(socket));
    socket->deleteLater();
    qDebug() << "Сокет" << socket << "удален и убран из списка. Оставшиеся сокеты" << Sockets;
}

void Server::SendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    for(int i = 0; i < Sockets.size(); i++)
    {
        if (Sockets[i]->state() == QAbstractSocket::ConnectedState)
        {
            Sockets[i]->write(Data);
            Sockets[i]->waitForReadyRead(700);
        }
    }
}
