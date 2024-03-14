#pragma once

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>


class SerialPortManager : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortManager();
    ~SerialPortManager();

    QSerialPort *serialPortInit(QString portName,
                        qint32 baud = QSerialPort::Baud9600,
                        QSerialPort::DataBits bits = QSerialPort::Data8,
                        QSerialPort::StopBits sbits = QSerialPort::OneStop,
                        QSerialPort::Parity parity = QSerialPort::NoParity,
                        QSerialPort::FlowControl flow = QSerialPort::NoFlowControl);
    QList<QSerialPort*> getSerialPorts() const;

private:
    QList<QSerialPort*> serialPorts;
    QList<QString> portsToInit;

signals:
    void newPortReceived(QSerialPort *portPtr);

public slots:
    void portsInterrogate();
};
