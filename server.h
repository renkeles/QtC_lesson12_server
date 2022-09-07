#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QObject>
#include <QTime>
#include <QString>
#include <QTextStream>
#include <QUdpSocket>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(int, QString);
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;
private:
    QVector <QTcpSocket*> tcpSockets;
    QByteArray Data;
    void SendToClient(QString str);
    quint16 nextBlockSize;
    QString protocol;
    void initServer();

public slots:
    void incomingConnection(qintptr socketDescription);
    void slotReadyRead();
};

#endif // SERVER_H
