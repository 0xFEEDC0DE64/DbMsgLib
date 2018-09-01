#include <QCoreApplication>
#include <QDebug>

#include "mymessage.h"

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    MyMessage message("Daniel", QDate(1996, 11, 12), QDateTime::currentDateTime(), 21, 80);
    message.debug();

    qDebug() << "changing name...";

    message.setName("Peter");
    message.debug();

    qDebug() << "clearing touched...";

    message.setTouched(false);
    message.debug();

    return app.exec();
}
