#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTime>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
    //QTcpSocket *socket_test;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    quint16 nextBlockSize;
    void SendToClient(QString str);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void slotbytesWritten(qint64 bytes);
};

#endif // SERVER_H
