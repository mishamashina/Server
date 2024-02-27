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
}

void Server::incomingConnection(qintptr socketDescriptor) //This virtual function is called by QTcpServer when a new connection is available
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor); //  The socketDescriptor argument is the native socket descriptor for the accepted connection
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::bytesWritten, this, &Server::slotbytesWritten);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

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

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender(); //Returns a pointer to the object that sent the signal; signal - readyRead; object - server socket

    QDataStream in(socket); // Working with data in server socket - port 2323
    in.setVersion(QDataStream::Qt_5_15);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "read...";
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    qDebug() << "Data < 2, break";
                    break;
                }
                in >> nextBlockSize;
                qDebug() << "nextBlockSize" << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                qDebug() << "Data not full, break";
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            qDebug() << "Receiver Data" << str;
            SendToClient(str);
            break;
        }
    }
    else
    {
        qDebug() << "DataStrem error";
    }
}

void Server::SendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    //socket->write(Data);
    for(int i = 0; i < Sockets.size(); i++)
    {
        Sockets[i]->write(Data);
    }
}