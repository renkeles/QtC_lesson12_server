#include "server.h"

Server::Server(int port, QString protocol)
{
/*    if(protocol == "TCP")
    {*/
        if(this->listen(QHostAddress::Any, port))
        {
            qDebug() << "Server starting on TCP protocol!";
        }else
        {
            qDebug() << "Error: Server not starting!";
        }
        nextBlockSize = 0;
/*    }else if(protocol == "UDP")
    {
        udpSocket = new QUdpSocket(this);
        if(udpSocket->bind(QHostAddress::Any, port))
        {
            connect(udpSocket, &QUdpSocket::readyRead, this, &Server::slotReadyRead);
            connect(udpSocket, &QUdpSocket::disconnected, udpSocket, &QUdpSocket::deleteLater);
            qDebug() << "Server starting on UDP protocol!";
        }

    }
*/


}

void Server::incomingConnection(qintptr socketDescription)
{
/*    if(protocol == "TCP")
    {*/
        tcpSocket = new QTcpSocket;
        tcpSocket->setSocketDescriptor(socketDescription);
        connect(tcpSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
        connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);

        tcpSockets.push_back(tcpSocket);
        qDebug() << "Client connected with id: " << socketDescription;
/*    }else if(protocol == "UDP")
    {
        qDebug() << "inC";
        //connect(udpSocket, &QUdpSocket::readyRead, this, &Server::slotReadyRead);
        //connect(udpSocket, &QUdpSocket::disconnected, udpSocket, &QUdpSocket::deleteLater);
    }
*/
}

void Server::slotReadyRead()
{
 /*   if(protocol == "TCP")
    {*/
        tcpSocket = (QTcpSocket*)sender();
        QDataStream in(tcpSocket);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        if(in.status() == QDataStream::Ok)
        {
            qDebug() << "Read...";
            /*QString str;
            in >> str;
            qDebug() << str;
            SendToClient(str);*/
            for (; ; )
            {
                if(nextBlockSize == 0)
                {
                    qDebug() << "nextBlockSize = 0";
                    if(tcpSocket->bytesAvailable() < 2)
                    {
                        qDebug() << "Data < 2, break";
                        break;
                    }
                    in >> nextBlockSize;
                    qDebug() << "nextBlockSize = " << nextBlockSize;
                }
                if(tcpSocket->bytesAvailable() < nextBlockSize)
                {
                    qDebug() << "Data not full, break";
                    break;
                }

                    QString str;
                    QTime time;
                    in >> time >> str;
                    nextBlockSize = 0;
                    qDebug() << str;
                    SendToClient(str);
                    break;
            }
        }else
        {
            qDebug() << "DateStream error.";
        }
/*    }else if(protocol == "UDP")
    {
        do
        {
            Data.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(Data.data(), Data.size());
        }while(udpSocket->hasPendingDatagrams());

        QDataStream in(&Data, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        QString str;
        in >> str;
        qDebug() << str;


    }
*/

}

void Server::SendToClient(QString str)
{
    Data.clear();
/*    if(protocol == "TCP")
    {
*/
        QDataStream out(&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        out << quint16(0) << QTime::currentTime() << str;
        out.device()->seek(0);
        out << quint16(Data.size() - sizeof(quint16));

        //tcpSocket->write(Data);
        for(int i = 0; i < tcpSockets.size(); ++i)
        {
            tcpSockets[i]->write(Data);
        }
 /*   }else if(protocol == "UDP")
    {
        Data.append("Hello");
        udpSocket->writeDatagram(Data, QHostAddress::LocalHost, 3333);
    }
*/
}
