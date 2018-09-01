#include <QCoreApplication>
#include <QDebug>

#include "messages/mymessage.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    MyMessage message("Daniel", QDate(1996, 11, 12), QDateTime::currentDateTime(), 21, 80);

    QVariantMap map;
    message.copyTo(map);
    qDebug() << "full" << map;



    qDebug() << "changing name...";

    message.setName("Peter");

    map.clear();
    message.copyTo(map);
    qDebug() << "full" << map;

    map.clear();
    message.copyTouchedTo(map);
    qDebug() << "delta:" << map;



    qDebug() << "clearing name...";

    message.nameField().clear();

    map.clear();
    message.copyTo(map);
    qDebug() << "full" << map;

    map.clear();
    message.copyTouchedTo(map);
    qDebug() << "delta:" << map;

    return app.exec();
}
