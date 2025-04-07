#include <QCoreApplication>
#include <QNetworkInterface>
#include <QSqlDatabase>
//#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QNetworkInterface networkInterface;
    QSqlDatabase sqlDatabase;
//    std::cout<< "Hello, Graphic world!"<< std::endl;
    return a.exec();
}
