#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QObject>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *tcpSocket;
private:
    QVector <QTcpSocket*> tcpSockets;
    QByteArray Data;
    void SendToClient(QString str);
public slots:
    void incomingConnection(qintptr socketDescription);
    void slotReadyRead();
};

#endif // SERVER_H
