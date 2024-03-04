#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server s;
    // while (i < 100)
    // {
    //     qDebug() << "Вошло";
    //     s.SendToClient(QString::number(i));
    //     i ++;
    //     //qDebug() << "Вошло";
    // }
    return a.exec();
}
