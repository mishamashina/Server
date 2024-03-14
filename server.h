#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QTime>
#include <QTimer>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    quint16 nextBlockSize;
    int i = 0;

public slots:
    void SendToClient(QString str);
    void incomingConnection(qintptr socketDescriptor);
    void slotbytesWritten(qint64 bytes);
    void dataReceiver();
    void slotDisconnected();

signals:
    void dataSend();
};

#endif // SERVER_H
