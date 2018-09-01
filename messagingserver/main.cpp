#include <QCoreApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    qDebug() << "hello from server";

    return 0;
}
