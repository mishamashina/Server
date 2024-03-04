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
    //QTcpSocket *socket_test;
    void SendToClient(QString str);

private:
    QVector <QTcpSocket*> Sockets;
    QByteArray Data;
    quint16 nextBlockSize;
    int i = 0;
    //void SendToClient(QString str);
    //void CheckConnection();

public slots:
    void incomingConnection(qintptr socketDescriptor);
    //void slotReadyRead();
    void slotbytesWritten(qint64 bytes);
    void slotConnected();

signals:
    void signalConnected();

};

#endif // SERVER_H
