#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTimer>
#include <QTime>
#include <QThread>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
    void CheckConnection();
    void SendToClient(QString str);

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    quint16 nextBlockSize;
    int i = 0;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotbytesWritten(qint64 bytes);
    void slotNewConnection();
    void slotDisconnected();
};

#endif // SERVER_H
