#include <QCoreApplication>
#include <QDebug>

#include "mymessage.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    MyMessage message("Daniel", QDate(1996, 11, 12), QDateTime::currentDateTime(), 21, 80);

    QVariantMap map;
    message.copyTo(map);
    qDebug() << "full" << map;

    message.setName("Peter");

    map.clear();
    message.copyTo(map);
    qDebug() << "full" << map;

    map.clear();
    message.copyTouchedTo(map);
    qDebug() << "delta:" << map;

    qDebug() << "clearing touched...";

    message.setTouched(false);

    map.clear();
    message.copyTouchedTo(map);
    qDebug() << "delta:" << map;

    return app.exec();
}
