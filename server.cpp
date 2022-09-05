#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 3333))
    {
        qDebug() << "Server starting!";
    }else
    {
        qDebug() << "Error: Server not starting!";
    }
}

void Server::incomingConnection(qintptr socketDescription)
{
    tcpSocket = new QTcpSocket;
    tcpSocket->setSocketDescriptor(socketDescription);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);

    tcpSockets.push_back(tcpSocket);
    qDebug() << "Client connected with id: " << socketDescription;
}

void Server::slotReadyRead()
{
    tcpSocket = (QTcpSocket*)sender();
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "Read...";
        QString str;
        in >> str;
        qDebug() << str;
    }else
    {
        qDebug() << "DateStream error.";
    }
}

void Server::SendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << str;
    tcpSocket->write(Data);
}
