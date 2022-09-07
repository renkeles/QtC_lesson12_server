#include <QCoreApplication>
#include "server.h"

int PORT = 3333;
QString PROTOCOL = "TCP"; //TCP or UDP

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server(PORT, PROTOCOL);

    return a.exec();
}
